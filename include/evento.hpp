#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <string>
#include <sstream>
#include <iomanip>

// Tipos de eventos na simulação
enum TipoEvento {
    EVENTO_CHEGADA_PACOTE = 1,  // Pacote chega a um armazém
    EVENTO_TRANSPORTE = 2       // Transporte entre armazéns
};

struct Evento {
    double tempo;           // Tempo de ocorrência do evento
    TipoEvento tipo;        // Tipo do evento
    long long chave;        // Chave única para ordenação (gerada automaticamente)
    int pacoteId;          // ID do pacote (usado em eventos de chegada)
    int armazemOrigem;     // Armazém de origem
    int armazemDestino;    // Armazém de destino

    Evento() : tempo(0), tipo(EVENTO_CHEGADA_PACOTE), pacoteId(0), armazemOrigem(0), armazemDestino(0) {
        gerarChave();
    }

    Evento(double t, TipoEvento tp, int pacote, int origem, int destino) 
        : tempo(t), tipo(tp), armazemOrigem(origem), armazemDestino(destino) {
        if (tp == EVENTO_CHEGADA_PACOTE) {
            pacoteId = pacote;
        } else {
            pacoteId = 0; 
        }
        gerarChave();
    }

    void setTempo(double t) { tempo = t; gerarChave(); }
    void setTipo(TipoEvento tp) { tipo = tp; gerarChave(); }
    void setPacoteId(int id) { pacoteId = id; gerarChave(); }
    void setArmazemOrigem(int origem) { armazemOrigem = origem; gerarChave(); }
    void setArmazemDestino(int destino) { armazemDestino = destino; gerarChave(); }

    // Gera chave única baseada nos atributos do evento
    // Usada para ordenação determinística na fila de prioridade
    void gerarChave() {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(6) << (long long)(tempo);

        if (tipo == EVENTO_CHEGADA_PACOTE) {
            // Para chegadas: tempo + pacoteId + tipo
            oss << std::setfill('0') << std::setw(6) << (pacoteId % 1000000)
                << (int)tipo;
        } else if (tipo == EVENTO_TRANSPORTE) {
            // Para transportes: tempo + origem + destino + tipo
            oss << std::setfill('0') << std::setw(3) << (armazemOrigem % 1000)
                << std::setfill('0') << std::setw(3) << (armazemDestino % 1000)
                << (int)tipo;
        }

        chave = std::stoll(oss.str());
    }

    // Operadores de comparação para ordenação no heap
    bool operator<(const Evento& outro) const {
        return chave < outro.chave;
    }

    bool operator>(const Evento& outro) const {
        return chave > outro.chave;
    }

    std::string chaveFormatada() const {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(13) << chave;
        return oss.str();
    }
};

#endif

