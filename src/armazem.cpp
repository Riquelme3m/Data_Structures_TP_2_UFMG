#include"armazem.hpp"
#include<iostream>


Armazem::Armazem(int idArmazen):idArmazem(idArmazem){

}

void Armazem::adicionarSecao(int id){
    if(encontrarSecao(id)==-1){
        Secao novaSecao;
        novaSecao.idSecao=id;
        secoes.push_back(novaSecao);
    }
}
int Armazem::encontrarSecao(int id){
    for(int i=0;i<secoes.size();i++){
        if(secoes[i].idSecao == id){
            return i;
        }
    }
    return -1;
}
const Vector<Secao>& Armazem::getSecoes() const {
    return this->secoes;
}