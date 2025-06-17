#include"armazem.hpp"
#include<iostream>


Armazem::Armazem(int idArmazen):idArmazem(idArmazen){

}
Armazem::~Armazem(){
    for(int i=0;i<secoes.size();i++){
        if (secoes[i]) {
            delete secoes[i];
            secoes[i] = nullptr;
        }
    }
    secoes.clear(); // Optional: clear the vector after deleting contents
}

void Armazem::adicionarSecao(int idSecaoDestino){
    if(encontrarIndiceSecao(idSecaoDestino)==-1){ // Check if section for this destination already exists
        Secao* novaSecao = new Secao;
        novaSecao->idSecao = idSecaoDestino; // This secao is FOR packages going TO idSecaoDestino
        secoes.push_back(novaSecao);
    }
}
// Returns index or -1 if not found
int Armazem::encontrarIndiceSecao(int idSecaoDestino){
    for(int i=0;i<secoes.size();i++){
        if(secoes[i]->idSecao == idSecaoDestino){
            return i;
        }
    }
    return -1;
}

Secao* Armazem::getSecaoPorDestino(int idSecaoDestino) {
    for (int i = 0; i < secoes.size(); ++i) {
        if (secoes[i]->idSecao == idSecaoDestino) {
            return secoes[i];
        }
    }
    // This case should ideally not happen if graph and sections are set up correctly
    // Or, a section might need to be dynamically created if it doesn't exist.
    // For now, returning nullptr. Consider error handling or dynamic creation.
    // std::cerr << "Alerta: Secao para destino " << idSecaoDestino << " nao encontrada no armazem " << this->idArmazem << std::endl;
    return nullptr; 
}

const Vector<Secao*>& Armazem::getSecoes() const {
    return this->secoes;
}