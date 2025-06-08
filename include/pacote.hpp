#ifndef PACOTE_HPP
#define PACOTE_HPP

#include <string>
#include "lista_duplamente_encadeada.hpp"

enum EstadoDoPacote{
    NAO_FOI_POSTADO,
    CHEGADA_ESCALONADA_EM_UM_ARMAZEM,
    CHEGOU_MAS_NAO_FOI_ARMAZENADO,
    ARMAZENADO_EM_UM_ARMAZEM,
    ALOCADO_PARA_TRANSPORTE,
    ENTREGUE
};


class Pacote{

    private:

        static int proximo_id;

        int id;
        EstadoDoPacote estado;
        DoublyLinkedList<std::string>* rota;
        double dataHoraPostagem;
        std::string remetente;
        std::string destinatário;
        std::string tipo;
        std::string armazemOrigem;
        std::string armazemDestino;

        double tempoEsperaDeEstadia;
        double tempoArmazenado;
        double tempoEmTransito;
        double tempoUltimaMudancaDeEstado;




    public:

        Pacote(double _dataHoraPostagem,
        const std::string& remetente,
        const std::string& destinatario,
        const std::string& tipo,
        const std::string& armazemOrigem,
        const std::string& armazemDestino);

        ~Pacote();
        
        //Getters

        int getId()const;
        EstadoDoPacote getEstado()const;
        double getTempoEsperaDeEstadia();
        double getTempoArmazenado();
        double getTempoEmTransito();
        double getUltimaMudancaDeEstado();
        std::string getProximoArmazem()const;
        DoublyLinkedList<std::string>* getRotaDoPacote();

        //Setters

        void setEstado(EstadoDoPacote novoEstado,double tempoEvento);
        void setRota(DoublyLinkedList<std::string>* rotaDoPacote);



};


#endif
