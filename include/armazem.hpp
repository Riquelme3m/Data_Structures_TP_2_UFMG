#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include <string>
#include "pilha.hpp"
#include "pacote.hpp"
#include "vector.hpp"

// Seção de um armazém - representa conexão para um destino específico
// Cada seção tem uma pilha de pacotes aguardando transporte
struct Secao {
    int idSecao;           // ID do armazém de destino desta seção
    Stack<Pacote*> pilha;  // Pilha de pacotes (LIFO - último a entrar, primeiro a sair)
};  

// Armazém - contém múltiplas seções, cada uma para um destino diferente
class Armazem {
    private:
        int idArmazem;           // Identificador único do armazém
        Vector<Secao*> secoes;   // Vetor de seções (uma por destino conectado)
        
    public:
        Armazem(){}
        Armazem(int id);
        ~Armazem();
        
        // Adiciona nova seção para um destino
        void adicionarSecao(int idSecaoDestino);
        
        // Encontra índice de seção por destino
        int encontrarIndiceSecao(int idSecaoDestino);
        
        // Retorna ponteiro para seção de um destino específico
        Secao* getSecaoPorDestino(int idSecaoDestino);
        
        const Vector<Secao*>& getSecoes() const;
        int getId() const { return idArmazem; }
};

#endif