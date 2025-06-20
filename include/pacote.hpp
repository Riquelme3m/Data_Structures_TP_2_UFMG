#ifndef PACOTE_HPP
#define PACOTE_HPP

#include <string>
#include "vector.hpp"
#include "map.hpp"
#include "lista_duplamente_encadeada.hpp"

// Estados possíveis de um pacote durante a simulação
enum EstadoDoPacote{
    NAO_FOI_POSTADO,                                      // Estado inicial
    CHEGADA_ESCALONADA_A_UM_ARMAZEM,                     // Chegada agendada
    ARMAZENADO_NA_SECAO_ASSOCIADA_AO_PROXIMO_DESTINO,   // Armazenado em seção
    REMOVIDO_DA_SECAO_PARA_TRANSPORTE,                  // Removido para transporte
    ENTREGUE                                             // Estado final
};

class Pacote{

    private:

        int id;                          // Identificador único do pacote
        EstadoDoPacote estado;           // Estado atual do pacote
        DoublyLinkedList<int>* rota;     // Rota completa do pacote
        double tempoChegada;             // Tempo inicial de chegada
        int destinatario;                // Armazém de destino final
        int origem;                      // Armazém de origem
        double tempoArmazenado;          // Tempo total armazenado em seções
        double tempoEmTransito;          // Tempo total em trânsito
        double tempoUltimoEvento;        // Timestamp do último evento
        bool foiRemovidoParaRearmazenamento; // Flag para controle de rearmazenamento

        // Histórico completo de mudanças de estado
        Vector<Map<double,EstadoDoPacote>>historicoEstados;

    public:
        Node<int>* currentNode;  // Posição atual na rota (ponteiro público para facilitar acesso)
        Pacote(){}
        Pacote(double tempoChegada,int id,int origem,int destinatario);

        ~Pacote();
        
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

        void setEstado(EstadoDoPacote novoEstado,double tempoEvento);
        void setRota(DoublyLinkedList<int>* rotaDoPacote);
        void setCurrentNode();
        void avancarParaProximoArmazem();

        void setRearmazenamento(bool rearmazenar);
        bool isRearmazenamento() const;
};

#endif