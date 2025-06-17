#include "escalonador.hpp"
#include <iostream>
#include <iomanip>   // Para std::setw e std::setfill

Escalonador::Escalonador() : capacidadeTransporte(0), latenciaTransporte(0), intervaloTransporte(0), custoRemocao(0), armazens(nullptr), pacotes(nullptr), relogio(0) {}

void Escalonador::inicializar(int cap, int lat, int intervalo, int custo, Vector<Armazem*>* armazens, Vector<Pacote*>* pacotes) {
    this->capacidadeTransporte = cap;
    this->latenciaTransporte = lat;
    this->intervaloTransporte = intervalo;
    this->custoRemocao = custo;
    this->armazens = armazens;
    this->pacotes = pacotes;
    this->relogio = 0;

    // Coletar eventos iniciais de chegada de pacotes
    Vector<Evento> eventosChegada;
    for (int i = 0; i < pacotes->size(); ++i) {
        Pacote* p = (*pacotes)[i];
        Evento e(p->getTempoChegada(), EVENTO_CHEGADA_PACOTE, p->getId(), p->getOrigem(), p->getOrigem());
        eventosChegada.push_back(e);
    }
    // Ordenar por tempoChegada e, em caso de empate, por id (menor para maior)
    for (int i = 0; i < eventosChegada.size(); ++i) {
        for (int j = i + 1; j < eventosChegada.size(); ++j) {
            if ((eventosChegada[j].tempo < eventosChegada[i].tempo) ||
                (eventosChegada[j].tempo == eventosChegada[i].tempo && eventosChegada[j].pacoteId < eventosChegada[i].pacoteId)) {
                Evento tmp = eventosChegada[i];
                eventosChegada[i] = eventosChegada[j];
                eventosChegada[j] = tmp;
            }
        }
    }
    // Inserir na fila de eventos na ordem correta
    for (int i = 0; i < eventosChegada.size(); ++i) {
        insereEvento(eventosChegada[i]);
    }

    // Agendar eventos iniciais de transporte para cada ligação entre armazéns
    for (int i = 0; i < armazens->size(); ++i) {
        const Vector<Secao*>& secoes = (*armazens)[i]->getSecoes();
        for (int j = 0; j < secoes.size(); ++j) {
            int destino = secoes[j]->idSecao;
            Evento e(1, EVENTO_TRANSPORTE, 0, i, destino); // Mudança: t=1 em vez de t=0
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
                    std::cout << std::setw(7) << std::setfill('0') << (int)p->getTempoChegada()
                        << " pacote " << std::setw(3) << std::setfill('0') << p->getId()
                        << " entregue em " << std::setw(3) << std::setfill('0') << evento.armazemOrigem
                        << std::endl;
                } else {
                    int prox = p->getProximoArmazem();
                    Armazem* arm = (*armazens)[evento.armazemOrigem];
                    Secao* secao = arm->getSecaoPorDestino(prox);
                    if (secao) {
                        secao->pilha.push(p);
                        p->setEstado(ARMAZENADO_NA_SECAO_ASSOCIADA_AO_PROXIMO_DESTINO, relogio);
                        // Corrigido: contar quantas vezes o pacote foi armazenado
                        const Vector<Map<double,EstadoDoPacote>>& hist = p->getHistoricosEstados();
                        int countArmazenado = 0;
                        for (int i = 0; i < hist.size(); ++i) {
                            const Map<double,EstadoDoPacote>& m = hist[i];
                            for (int j = 0; j < m.size(); ++j) {
                                if (m[j] == ARMAZENADO_NA_SECAO_ASSOCIADA_AO_PROXIMO_DESTINO)
                                    countArmazenado++;
                            }
                        }
                        std::cout << std::setw(7) << std::setfill('0') << (int)p->getTempoChegada()
                            << " pacote " << std::setw(3) << std::setfill('0') << p->getId()
                            << (countArmazenado > 1 ? " rearmazenado em " : " armazenado em ")
                            << std::setw(3) << std::setfill('0') << evento.armazemOrigem
                            << " na secao " << std::setw(3) << std::setfill('0') << prox
                            << std::endl;
                    }
                }
            }
        } else if (evento.tipo == EVENTO_TRANSPORTE) {
            Armazem* arm = (*armazens)[evento.armazemOrigem];
            Secao* secao = arm->getSecaoPorDestino(evento.armazemDestino);

            // Remover todos os pacotes da pilha (ordem LIFO)
            Vector<Pacote*> removidos;
            while (secao && !secao->pilha.isEmpty()) {
                Pacote* p = secao->pilha.getTop();
                secao->pilha.pop();
                removidos.push_back(p);
            }

            int total = removidos.size();
            int removidosParaTransporte = (capacidadeTransporte < total) ? capacidadeTransporte : total;
            int removidosParaRearmazenar = total - removidosParaTransporte;

            Vector<double> temposRemocao;
            // CORREÇÃO: O primeiro pacote é removido em relogio + 1*custoRemocao
            for (int i = 0; i < total; ++i) {
                double tRem = relogio + (i + 1) * custoRemocao;
                temposRemocao.push_back(tRem);
            }

            // 1. Imprimir todas as remoções (no tempo correto)
            for (int i = 0; i < total; ++i) {
                Pacote* p = removidos[i];
                double tRem = temposRemocao[i];
                p->setEstado(REMOVIDO_DA_SECAO_PARA_TRANSPORTE, tRem);
                std::cout << std::setw(7) << std::setfill('0') << (int)tRem
                    << " pacote " << std::setw(3) << std::setfill('0') << p->getId()
                    << " removido de " << std::setw(3) << std::setfill('0') << evento.armazemOrigem
                    << " na secao " << std::setw(3) << std::setfill('0') << evento.armazemDestino
                    << std::endl;
            }

            // 2. Imprimir todos os "em transito" e agendar chegada (todos juntos no tempo da última remoção)
            double tempoTransito = temposRemocao.size() == 0 ? relogio : temposRemocao[temposRemocao.size() - 1];
            // Transporte: últimos removidos (do fundo)
            for (int i = total - removidosParaTransporte; i < total; ++i) {
                Pacote* p = removidos[i];
                p->avancarParaProximoArmazem();
                Evento chegada(tempoTransito + latenciaTransporte, EVENTO_CHEGADA_PACOTE, p->getId(), evento.armazemDestino, evento.armazemDestino);
                insereEvento(chegada);
            }
            // Print em transito na ordem reversa (último removido primeiro)
            for (int i = total - 1; i >= total - removidosParaTransporte; --i) {
                Pacote* p = removidos[i];
                std::cout << std::setw(7) << std::setfill('0') << (int)tempoTransito
                    << " pacote " << std::setw(3) << std::setfill('0') << p->getId()
                    << " em transito de " << std::setw(3) << std::setfill('0') << evento.armazemOrigem
                    << " para " << std::setw(3) << std::setfill('0') << evento.armazemDestino
                    << std::endl;
            }

            // 3. Rearmazenar o restante (no tempoTransito, print após trânsito)
            for (int i = 0; i < removidosParaRearmazenar; ++i) {
                Pacote* p = removidos[i];
                double tRem = tempoTransito; // Rearmazenamento ocorre no mesmo tempo do trânsito
                p->setEstado(ARMAZENADO_NA_SECAO_ASSOCIADA_AO_PROXIMO_DESTINO, tRem);
                secao->pilha.push(p);

                // Contar quantas vezes já foi armazenado
                const Vector<Map<double,EstadoDoPacote>>& hist = p->getHistoricosEstados();
                int countArmazenado = 0;
                for (int h = 0; h < hist.size(); ++h) {
                    const Map<double,EstadoDoPacote>& m = hist[h];
                    for (int j = 0; j < m.size(); ++j) {
                        if (m[j] == ARMAZENADO_NA_SECAO_ASSOCIADA_AO_PROXIMO_DESTINO)
                            countArmazenado++;
                    }
                }
                std::cout << std::setw(7) << std::setfill('0') << (int)tRem
                    << " pacote " << std::setw(3) << std::setfill('0') << p->getId()
                    << (countArmazenado > 1 ? " rearmazenado em " : " armazenado em ")
                    << std::setw(3) << std::setfill('0') << evento.armazemOrigem
                    << " na secao " << std::setw(3) << std::setfill('0') << evento.armazemDestino
                    << std::endl;
            }

            // Agendar próximo transporte: deve ser após a última remoção
            double tempoUltimaRemocao = temposRemocao.size() == 0 ? relogio : temposRemocao[temposRemocao.size() - 1];
            Evento proxTransporte(tempoUltimaRemocao + intervaloTransporte, EVENTO_TRANSPORTE, 0, evento.armazemOrigem, evento.armazemDestino);
            insereEvento(proxTransporte);
        }
    }
    finaliza();
}

void Escalonador::finaliza() {
    std::cout << "Simulação finalizada." << std::endl;
}