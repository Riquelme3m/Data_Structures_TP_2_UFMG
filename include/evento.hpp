#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <string>
#include <sstream>
#include <iomanip>

enum TipoEvento {
    EVENTO_CHEGADA_PACOTE = 1,
    EVENTO_TRANSPORTE = 2
};

struct Evento {
    double tempo;
    TipoEvento tipo;
    long long chave; 
    int pacoteId;
    int armazemOrigem;
    int armazemDestino;

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

    // Se quiser setters, sempre chame gerarChave() neles
    void setTempo(double t) { tempo = t; gerarChave(); }
    void setTipo(TipoEvento tp) { tipo = tp; gerarChave(); }
    void setPacoteId(int id) { pacoteId = id; gerarChave(); }
    void setArmazemOrigem(int origem) { armazemOrigem = origem; gerarChave(); }
    void setArmazemDestino(int destino) { armazemDestino = destino; gerarChave(); }

    void gerarChave() {
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(6) << (long long)(tempo);

        if (tipo == EVENTO_CHEGADA_PACOTE) {
            oss << std::setfill('0') << std::setw(6) << (pacoteId % 1000000)
                << (int)tipo;
        } else if (tipo == EVENTO_TRANSPORTE) {
            oss << std::setfill('0') << std::setw(3) << (armazemOrigem % 1000)
                << std::setfill('0') << std::setw(3) << (armazemDestino % 1000)
                << (int)tipo;
        }

        chave = std::stoll(oss.str());
    }

    bool operator<(const Evento& outro) const {
        return chave < outro.chave; // Para minheap: menor chave tem maior prioridade
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
