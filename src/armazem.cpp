#include"armazem.hpp"
#include<iostream>

// Construtor do armazém
Armazem::Armazem(int idArmazen):idArmazem(idArmazen){

}

// Destrutor - libera memória de todas as seções
Armazem::~Armazem(){
    for(int i=0;i<secoes.size();i++){
        if (secoes[i]) {
            delete secoes[i];
            secoes[i] = nullptr;
        }
    }
    secoes.clear();
}

// Adiciona uma nova seção para um destino específico
void Armazem::adicionarSecao(int idSecaoDestino){
    // Só adiciona se não existir uma seção para este destino
    if(encontrarIndiceSecao(idSecaoDestino)==-1){
        Secao* novaSecao = new Secao;
        novaSecao->idSecao = idSecaoDestino;
        secoes.push_back(novaSecao);
    }
}

// Encontra o índice de uma seção pelo seu destino
int Armazem::encontrarIndiceSecao(int idSecaoDestino){
    for(int i=0;i<secoes.size();i++){
        if(secoes[i]->idSecao == idSecaoDestino){
            return i;
        }
    }
    return -1; // Retorna -1 se não encontrar
}

// Retorna ponteiro para seção de um destino específico
Secao* Armazem::getSecaoPorDestino(int idSecaoDestino) {
    for (int i = 0; i < secoes.size(); ++i) {
        if (secoes[i]->idSecao == idSecaoDestino) {
            return secoes[i];
        }
    }
    return nullptr; // Retorna nullptr se não encontrar
}

const Vector<Secao*>& Armazem::getSecoes() const {
    return this->secoes;
}