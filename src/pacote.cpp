#include "pacote.hpp"
#include <iostream>





Pacote::Pacote(double tempoChegada,
        int id,
        int origem,
        int destinatario):
id(id),
estado(NAO_FOI_POSTADO),
rota(nullptr),
tempoChegada(tempoChegada),
origem(origem),
destinatario(destinatario),
tempoArmazenado(0),
tempoEmTransito(0),
tempoUltimoEvento(0),
currentNode(nullptr),
historicoEstados(){

};

Pacote::~Pacote(){
    if(rota!=nullptr){
        delete rota;
        rota=nullptr;
    }
}

int Pacote::getId()const{
    return this->id;
}

EstadoDoPacote Pacote::getEstado()const{
    return this->estado;
}

double Pacote::getTempoArmazenado()const{
    return this->tempoArmazenado;
}
double Pacote::getTempoEmTransito()const{
    return this->tempoEmTransito;
}
double Pacote::getTempoUltimoEvento()const{
    return this->tempoUltimoEvento;
}
int Pacote::getOrigem()const{
    return this->origem;
}
int Pacote::getDestinatario()const{
    return this->destinatario;
}
double Pacote::getTempoChegada() const { return tempoChegada; }

int Pacote::getProximoArmazem()const{
    if(currentNode && currentNode->next){
        return currentNode->next->data;
    }
    return -1;
}
const Vector<Map<double,EstadoDoPacote>>& Pacote::getHistoricosEstados()const{
    return this->historicoEstados;
}
DoublyLinkedList<int>* Pacote::getRotaDoPacote()const{
    return this->rota;
}

void Pacote::setEstado(EstadoDoPacote novoEstado,double tempoEvento){
    double delta = tempoEvento - tempoUltimoEvento;

    if(estado == ARMAZENADO_NA_SECAO_ASSOCIADA_AO_PROXIMO_DESTINO){
        tempoArmazenado+=delta;
    }
    if(estado == REMOVIDO_DA_SECAO_PARA_TRANSPORTE){
        tempoEmTransito+=delta;
    }

    Map<double, EstadoDoPacote> evento;
    evento.insert(tempoEvento, novoEstado);
    historicoEstados.push_back(evento);

    
    estado = novoEstado;
    tempoUltimoEvento = tempoEvento;
}
void Pacote::setRota(DoublyLinkedList<int>* rotaDoPacote){
    this->rota=rotaDoPacote;

}
void Pacote::setCurrentNode(){
    currentNode=rota->getHead();
}

void Pacote::avancarParaProximoArmazem(){
    if(currentNode && currentNode->next){
        currentNode = currentNode->next;
    }
}