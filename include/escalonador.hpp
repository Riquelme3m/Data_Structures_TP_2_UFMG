#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "evento.hpp"
#include "armazem.hpp"
#include "pacote.hpp"
#include "vector.hpp"
#include "minheap.hpp"

class Escalonador {
private:
    MinHeap<Evento> filaEventos;

    // Parâmetros globais
    int capacidadeTransporte;
    int latenciaTransporte;
    int intervaloTransporte;
    int custoRemocao;

    // Ponteiros para armazéns e pacotes
    Vector<Armazem*>* armazens;
    Vector<Pacote*>* pacotes;

    double relogio;

public:
    Escalonador();
    void inicializar(int cap, int lat, int intervalo, int custo, Vector<Armazem*>* armazens, Vector<Pacote*>* pacotes);
    void insereEvento(const Evento& evento);
    Evento retiraProximoEvento();
    bool eventosPendentes() const;
    void executarSimulacao();
    void finaliza();
};

#endif

