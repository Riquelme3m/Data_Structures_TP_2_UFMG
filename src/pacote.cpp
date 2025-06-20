#include "pacote.hpp"
#include <iostream>

// Construtor do pacote - inicializa todos os atributos
Pacote::Pacote(double tempoChegada,
        int id,
        int origem,
        int destinatario):
id(id),
estado(NAO_FOI_POSTADO), // Estado inicial do pacote
rota(nullptr), // Rota será definida posteriormente
tempoChegada(tempoChegada),
destinatario(destinatario),
origem(origem),
tempoArmazenado(0), // Tempo total armazenado
tempoEmTransito(0), // Tempo total em trânsito
tempoUltimoEvento(0), // Timestamp do último evento
foiRemovidoParaRearmazenamento(false), // Flag para rearmazenamento
historicoEstados(), // Histórico de mudanças de estado
currentNode(nullptr) // Nó atual na rota
{

};

// Destrutor - libera memória da rota se existir
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

// Retorna o próximo armazém na rota
int Pacote::getProximoArmazem()const{
    if(currentNode && currentNode->next){
        return currentNode->next->data;
    }
    return -1; // Retorna -1 se não há próximo armazém
}
const Vector<Map<double,EstadoDoPacote>>& Pacote::getHistoricosEstados()const{
    return this->historicoEstados;
}
DoublyLinkedList<int>* Pacote::getRotaDoPacote()const{
    return this->rota;
}

// Atualiza o estado do pacote e calcula tempos acumulados
void Pacote::setEstado(EstadoDoPacote novoEstado,double tempoEvento){
    double delta = tempoEvento - tempoUltimoEvento;

    // Acumula tempo armazenado quando estava na seção
    if(estado == ARMAZENADO_NA_SECAO_ASSOCIADA_AO_PROXIMO_DESTINO){
        tempoArmazenado+=delta;
    }
    // Acumula tempo em trânsito quando estava sendo transportado
    if(estado == REMOVIDO_DA_SECAO_PARA_TRANSPORTE){
        tempoEmTransito+=delta;
    }

    // Registra o evento no histórico
    Map<double, EstadoDoPacote> evento;
    evento.insert(tempoEvento, novoEstado);
    historicoEstados.push_back(evento);

    // Atualiza estado e timestamp
    estado = novoEstado;
    tempoUltimoEvento = tempoEvento;
}
void Pacote::setRota(DoublyLinkedList<int>* rotaDoPacote){
    this->rota=rotaDoPacote;

}

// Define o nó atual como o primeiro da rota
void Pacote::setCurrentNode(){
    if(rota != nullptr && rota->getHead() != nullptr){
        currentNode = rota->getHead();
    } else {
        currentNode = nullptr;
    }
}

// Avança para o próximo armazém na rota
void Pacote::avancarParaProximoArmazem(){
    if(currentNode && currentNode->next){
        currentNode = currentNode->next;
    }
}
void Pacote::setRearmazenamento(bool rearmazenar) {
    foiRemovidoParaRearmazenamento = rearmazenar;
}

bool Pacote::isRearmazenamento() const {
    return foiRemovidoParaRearmazenamento;
}