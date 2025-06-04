#ifndef PACOTE_HPP
#define PACOTE_HPP

#include <string>
#include "linked_list.hpp" 


enum class EstadoPacote {
    NAO_POSTADO,                      
    CHEGADA_ESCALONADA_ARMAZEM,       
    CHEGOU_ARMAZEM_NAO_ARMAZENADO,    
    ARMAZENADO_EM_ARMAZEM,            
    ALOCADO_PARA_TRANSPORTE,          
    ENTREGUE                          
};


class Pacote {


private:
    static int proximo_id_disponivel_; 

    int id_;//Id único para cada pacote;
    

    /*Dados coletados na entrada*/

    std::string data_hora_postagem; 
    std::string remetente;
    std::string destinatario;
    std::string tipo;
    std::string armazem_origem;
    std::string armazem_destino;
    
    /*-------------------------- */


    /*Rota do pacote*/
    //Implement doubly linked list to represent the routes

    /*-------------- */



    /*Saída para cada pacote*/
    double tempo_esperado_estadia;
    double tempo_armazenado;
    double tempo_transito;
    /*----------------------*/




    



public:


};
   

#endif // PACOTE_HPP
