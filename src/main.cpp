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
    Vector<Armazem*>armazens;
    int numeroDePacotes;
    Vector<Pacote*>pacotes;
    

    lerEntrada("entrada.txt",capacidadeTransporte,latenciaTransporte,intervaloTransporte,
    custoRemocao,numeroDeArmazens,armazens,numeroDePacotes,pacotes);


    std::cout<<"Capacidade de transporte: "<<capacidadeTransporte<<std::endl;
    std::cout<<"Latencia Transporte: "<<latenciaTransporte<<std::endl;
    std::cout<<"Intervalo Transporte: "<<intervaloTransporte<<std::endl;
    std::cout<<"Custo remocao: "<<custoRemocao<<std::endl;

    std::cout<<"Numero de armazens: "<<numeroDeArmazens<<std::endl;
    std::cout<<"Numero de pacotes: "<<numeroDePacotes<<std::endl;

    for(int i=0;i<armazens.size();i++){
        std::cout<<"Armazen: "<<i<<std::endl;
        Vector<Secao*>aux = armazens[i]->getSecoes();
        for(int j=0;j<aux.size();j++){
            std::cout<<"tem conexao com "<<aux[j]->idSecao<<std::endl;
        }
        std::cout<<"---------------------------------------"<<std::endl;
    }















    










    return 0;


}
