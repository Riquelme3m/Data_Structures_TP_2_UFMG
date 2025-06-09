#include<iostream>
#include"armazem.hpp"
#include"lista_duplamente_encadeada.hpp"
#include"map.hpp"
#include"pacote.hpp"
#include"vector.hpp"
#include "queue.hpp"
#include "lerEntrada.hpp"




int main(){

    int capacidadeTransporte;
    int latenciaTransporte;
    int intervaloTransporte;
    int custoRemocao;
    int numeroDeArmazens;
    Vector<Armazem>armazens;
    int numeroDePacotes;
    Vector<Pacote>pacotes;


    lerEntrada("entrada.txt",capacidadeTransporte,latenciaTransporte,intervaloTransporte,
    custoRemocao,numeroDeArmazens,armazens,numeroDePacotes,pacotes);

    return 0;
}
