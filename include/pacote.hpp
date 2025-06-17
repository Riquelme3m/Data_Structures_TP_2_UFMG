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
        

        Vector<Map<double,EstadoDoPacote>>historicoEstados;




    public:
        Node<int>* currentNode;
        Pacote(){}
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