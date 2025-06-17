#include"evento.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>




int main() {
    
    TipoEvento test = EVENTO_TRANSPORTE;

    Evento* x = new Evento(401,test,0,2,1);
    std::string chave = x->chaveFormatada();
    std::cout<<chave<<std::endl;


    
    delete x;
    return 0;
}
