#include "escalonador.hpp"
#include <iostream>
#include <iomanip>


Escalonador::Escalonador() : capacidadeTransporte(0), latenciaTransporte(0), intervaloTransporte(0), custoRemocao(0), armazens(nullptr), pacotes(nullptr), relogio(0) {}

// Inicializa o escalonador com parâmetros e dados
void Escalonador::inicializar(int cap, int lat, int intervalo, int custo, Vector<Armazem*>* armazens, Vector<Pacote*>* pacotes) {
    // Armazena parâmetros de configuração
    this->capacidadeTransporte = cap;
    this->latenciaTransporte = lat;
    this->intervaloTransporte = intervalo;
    this->custoRemocao = custo;
    this->armazens = armazens;
    this->pacotes = pacotes;
    this->relogio = 0;

    // Cria eventos de chegada para todos os pacotes
    Vector<Evento> eventosChegada;
    for (int i = 0; i < pacotes->size(); ++i) {
        Pacote* p = (*pacotes)[i];
        Evento e(p->getTempoChegada(), EVENTO_CHEGADA_PACOTE, p->getId(), p->getOrigem(), p->getOrigem());
        eventosChegada.push_back(e);
    }
    
    // Ordena eventos por tempo (e por ID em caso de empate)
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
    
    // Insere eventos de chegada na fila
    for (int i = 0; i < eventosChegada.size(); ++i) {
        insereEvento(eventosChegada[i]);
    }

    // Encontra o tempo do primeiro pacote para iniciar transportes
    double tempoMenorPacote = (*pacotes)[0]->getTempoChegada();
    for (int i = 1; i < pacotes->size(); ++i) {
        if ((*pacotes)[i]->getTempoChegada() < tempoMenorPacote) {
            tempoMenorPacote = (*pacotes)[i]->getTempoChegada();
        }
    }

    // Agenda primeiro evento de transporte para cada rota
    double tempoInicialTransporte = tempoMenorPacote + intervaloTransporte;
    for (int i = 0; i < armazens->size(); ++i) {
        const Vector<Secao*>& secoes = (*armazens)[i]->getSecoes();
        for (int j = 0; j < secoes.size(); ++j) {
            int destino = secoes[j]->idSecao;
            Evento e(tempoInicialTransporte, EVENTO_TRANSPORTE, 0, i, destino);
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

// Verifica se ainda há eventos pendentes ou pacotes não entregues
bool Escalonador::eventosPendentes() const {
    if (filaEventos.isEmpty()) {
        return false;
    }
    
    // Verifica se há pacotes ainda não entregues
    for (int i = 0; i < pacotes->size(); ++i) {
        if ((*pacotes)[i]->getEstado() != ENTREGUE) {
            return true;
        }
    }
    
    return false;
}

// Executa a simulação principal
void Escalonador::executarSimulacao() {
    while (eventosPendentes()) {
        Evento evento = retiraProximoEvento();
        relogio = evento.tempo;

        if (evento.tipo == EVENTO_CHEGADA_PACOTE) {
            // Encontra o pacote correspondente
            Pacote* p = nullptr;
            for (int i = 0; i < pacotes->size(); ++i) {
                if ((*pacotes)[i]->getId() == evento.pacoteId) {
                    p = (*pacotes)[i];
                    break;
                }
            }
            if (p) {
                // Verifica se chegou ao destino final
                if (evento.armazemOrigem == p->getDestinatario()) {
                    p->setEstado(ENTREGUE, relogio);
                    std::cout << std::setw(7) << std::setfill('0') << (int)relogio
                        << " pacote " << std::setw(3) << std::setfill('0') << p->getId()
                        << " entregue em " << std::setw(3) << std::setfill('0') << evento.armazemOrigem
                        << std::endl;
                } else {
                    // Armazena na seção correspondente ao próximo destino
                    int prox = p->getProximoArmazem();
                    Armazem* arm = (*armazens)[evento.armazemOrigem];
                    Secao* secao = arm->getSecaoPorDestino(prox);
                    if (secao) {
                        secao->pilha.push(p);
                        p->setEstado(ARMAZENADO_NA_SECAO_ASSOCIADA_AO_PROXIMO_DESTINO, relogio);
                        
                        std::cout << std::setw(7) << std::setfill('0') << (int)relogio
                            << " pacote " << std::setw(3) << std::setfill('0') << p->getId()
                            << " armazenado em "
                            << std::setw(3) << std::setfill('0') << evento.armazemOrigem
                            << " na secao " << std::setw(3) << std::setfill('0') << prox
                            << std::endl;
                    }
                }
            }
        } else if (evento.tipo == EVENTO_TRANSPORTE) {
            // Processa evento de transporte
            Armazem* arm = (*armazens)[evento.armazemOrigem];
            Secao* secao = arm->getSecaoPorDestino(evento.armazemDestino);

            // Remove todos os pacotes da seção
            Vector<Pacote*> removidos;
            while (secao && !secao->pilha.isEmpty()) {
                Pacote* p = secao->pilha.getTop();
                secao->pilha.pop();
                removidos.push_back(p);
            }

            int total = removidos.size();
            // Determina quantos serão transportados vs rearmazenados
            int removidosParaTransporte = (capacidadeTransporte < total) ? capacidadeTransporte : total;
            int removidosParaRearmazenar = total - removidosParaTransporte;

            // Calcula tempos de remoção (cada remoção tem um custo)
            Vector<double> temposRemocao;
            for (int i = 0; i < total; ++i) {
                double tRem = relogio + (i + 1) * custoRemocao;
                temposRemocao.push_back(tRem);
            }

            // Marca todos como removidos primeiro
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

            double tempoTransito = temposRemocao.size() == 0 ? relogio : temposRemocao[temposRemocao.size() - 1];
            
            // Agenda chegadas dos pacotes transportados
            for (int i = total - removidosParaTransporte; i < total; ++i) {
                Pacote* p = removidos[i];
                p->avancarParaProximoArmazem(); // Avança na rota
                Evento chegada(tempoTransito + latenciaTransporte, EVENTO_CHEGADA_PACOTE, p->getId(), evento.armazemDestino, evento.armazemDestino);
                insereEvento(chegada);
            }
            
            // Imprime pacotes em trânsito
            for (int i = total - 1; i >= total - removidosParaTransporte; --i) {
                Pacote* p = removidos[i];
                std::cout << std::setw(7) << std::setfill('0') << (int)tempoTransito
                    << " pacote " << std::setw(3) << std::setfill('0') << p->getId()
                    << " em transito de " << std::setw(3) << std::setfill('0') << evento.armazemOrigem
                    << " para " << std::setw(3) << std::setfill('0') << evento.armazemDestino
                    << std::endl;
            }

            // Rearmazena os pacotes que não couberam no transporte
            for (int i = removidosParaRearmazenar - 1; i >= 0; --i) {
                Pacote* p = removidos[i];
                double tRem = tempoTransito;
                p->setEstado(ARMAZENADO_NA_SECAO_ASSOCIADA_AO_PROXIMO_DESTINO, tRem);
                secao->pilha.push(p);

                std::cout << std::setw(7) << std::setfill('0') << (int)tRem
                    << " pacote " << std::setw(3) << std::setfill('0') << p->getId()
                    << " rearmazenado em "
                    << std::setw(3) << std::setfill('0') << evento.armazemOrigem
                    << " na secao " << std::setw(3) << std::setfill('0') << evento.armazemDestino
                    << std::endl;
                    this->pacotesRearmazenados++;
            }

            // Agenda próximo transporte para esta rota
            Evento proxTransporte(relogio + intervaloTransporte, EVENTO_TRANSPORTE, 0, evento.armazemOrigem, evento.armazemDestino);
            insereEvento(proxTransporte);
        }
    }
    std::cout<<"Pacotes rearmazenados numero: "<<this->pacotesRearmazenados<<std::endl;
    finaliza();
}

void Escalonador::finaliza() {
}