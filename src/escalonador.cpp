#include "escalonador.hpp"
#include <iostream>

Escalonador::Escalonador() : capacidadeTransporte(0), latenciaTransporte(0), intervaloTransporte(0), custoRemocao(0), armazens(nullptr), pacotes(nullptr), relogio(0) {}

void Escalonador::inicializar(int cap, int lat, int intervalo, int custo, Vector<Armazem*>* armazens, Vector<Pacote*>* pacotes) {
    this->capacidadeTransporte = cap;
    this->latenciaTransporte = lat;
    this->intervaloTransporte = intervalo;
    this->custoRemocao = custo;
    this->armazens = armazens;
    this->pacotes = pacotes;
    this->relogio = 0;

    // Agendar eventos iniciais de chegada de pacotes
    for (int i = 0; i < pacotes->size(); ++i) {
        Pacote* p = (*pacotes)[i];
        Evento e(p->getTempoChegada(), EVENTO_CHEGADA_PACOTE, p->getId(), p->getOrigem(), p->getOrigem());
        insereEvento(e);
    }

    // Agendar eventos iniciais de transporte para cada ligação entre armazéns
    for (int i = 0; i < armazens->size(); ++i) {
        const Vector<Secao*>& secoes = (*armazens)[i]->getSecoes();
        for (int j = 0; j < secoes.size(); ++j) {
            int destino = secoes[j]->idSecao;
            Evento e(0, EVENTO_TRANSPORTE, 0, i, destino);
            insereEvento(e);
        }
    }
}

void Escalonador::insereEvento(const Evento& evento) {
    filaEventos.insert(evento);
}

Evento Escalonador::retiraProximoEvento() {
    return filaEventos.extractMin();
}

bool Escalonador::eventosPendentes() const {
    return !filaEventos.isEmpty();
}

void Escalonador::executarSimulacao() {
    while (eventosPendentes()) {
        Evento evento = retiraProximoEvento();
        relogio = evento.tempo;

        if (evento.tipo == EVENTO_CHEGADA_PACOTE) {
            Pacote* p = nullptr;
            for (int i = 0; i < pacotes->size(); ++i) {
                if ((*pacotes)[i]->getId() == evento.pacoteId) {
                    p = (*pacotes)[i];
                    break;
                }
            }
            if (p) {
                if (evento.armazemOrigem == p->getDestinatario()) {
                    p->setEstado(ENTREGUE, relogio);
                    std::cout << evento.chaveFormatada() << " pacote " << p->getId() << " entregue em " << evento.armazemOrigem << std::endl;
                } else {
                    int prox = p->getProximoArmazem();
                    Armazem* arm = (*armazens)[evento.armazemOrigem];
                    Secao* secao = arm->getSecaoPorDestino(prox);
                    if (secao) {
                        secao->pilha.push(p);
                        p->setEstado(ARMAZENADO_NA_SECAO_ASSOCIADA_AO_PROXIMO_DESTINO, relogio);
                        std::cout << evento.chaveFormatada() << " pacote " << p->getId() << " armazenado em " << evento.armazemOrigem << " na secao " << prox << std::endl;
                    }
                }
            }
        } else if (evento.tipo == EVENTO_TRANSPORTE) {
            Armazem* arm = (*armazens)[evento.armazemOrigem];
            Secao* secao = arm->getSecaoPorDestino(evento.armazemDestino);
            int count = 0;
            Vector<Pacote*> transportados;
            while (secao && !secao->pilha.isEmpty() && count < capacidadeTransporte) {
                Pacote* p = secao->pilha.getTop();
                secao->pilha.pop();
                p->setEstado(REMOVIDO_DA_SECAO_PARA_TRANSPORTE, relogio);
                transportados.push_back(p);
                std::cout << evento.chaveFormatada() << " pacote " << p->getId() << " removido de " << evento.armazemOrigem << " na secao " << evento.armazemDestino << std::endl;
                count++;
            }
            for (int i = 0; i < transportados.size(); ++i) {
                Pacote* p = transportados[i];
                p->avancarParaProximoArmazem();
                Evento chegada(relogio + latenciaTransporte, EVENTO_CHEGADA_PACOTE, p->getId(), evento.armazemDestino, evento.armazemDestino);
                insereEvento(chegada);
                std::cout << evento.chaveFormatada() << " pacote " << p->getId() << " em transito de " << evento.armazemOrigem << " para " << evento.armazemDestino << std::endl;
            }
            Evento proxTransporte(relogio + intervaloTransporte, EVENTO_TRANSPORTE, 0, evento.armazemOrigem, evento.armazemDestino);
            insereEvento(proxTransporte);
        }
    }
    finaliza();
}

void Escalonador::finaliza() {
    std::cout << "Simulação finalizada." << std::endl;
}