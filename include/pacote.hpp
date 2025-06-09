#ifndef PACOTE_HPP
#define PACOTE_HPP

#include <string>
#include "vector.hpp"
#include "map.hpp"
#include "lista_duplamente_encadeada.hpp"

enum EstadoDoPacote{
    NAO_FOI_POSTADO,
    CHEGADA_ESCALONADA_A_UM_ARMAZEM,
    ARMAZENADO_NA_SECAO_ASSOCIADA_AO_PROXIMO_DESTINO,
    REMOVIDO_DA_SECAO_PARA_TRANSPORTE,
    ENTREGUE
};
 



class Pacote{

    private:


        int id;
        EstadoDoPacote estado;
        DoublyLinkedList<int>* rota;
        double tempoChegada;
        int destinatario;
        int origem;
        double tempoArmazenado;
        double tempoEmTransito;
        double tempoUltimoEvento;
        Node<int>* currentNode;

        Vector<Map<double,EstadoDoPacote>>historicoEstados;




    public:
        Pacote() :
            id(-1), estado(NAO_FOI_POSTADO), rota(nullptr), tempoChegada(0),
            destinatario(-1), origem(-1), tempoArmazenado(0), tempoEmTransito(0),
            tempoUltimoEvento(0), currentNode(nullptr), historicoEstados() {}
        Pacote(double tempoChegada,int id,int origem,int destinatario);

        ~Pacote();
        
        //Getters

        int getId()const;
        EstadoDoPacote getEstado()const;
        double getTempoArmazenado()const;
        double getTempoEmTransito()const;
        double getTempoUltimoEvento()const;
        double getTempoChegada() const;
        int getOrigem()const;
        int getDestinatario()const;
        int getProximoArmazem()const;
        const Vector<Map<double,EstadoDoPacote>>& getHistoricosEstados()const;
        DoublyLinkedList<int>* getRotaDoPacote()const;

        //Setters

        void setEstado(EstadoDoPacote novoEstado,double tempoEvento);
        void setRota(DoublyLinkedList<int>* rotaDoPacote);
        void setCurrentNode();
        void avancarParaProximoArmazem();



};


#endif
