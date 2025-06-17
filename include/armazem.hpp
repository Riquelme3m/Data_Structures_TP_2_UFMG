#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include <string>
#include "pilha.hpp"
#include "pacote.hpp"
#include "vector.hpp"


struct Secao {
    int idSecao;   
    Stack<Pacote*> pilha;
    
};  


class Armazem {
    private:
        int idArmazem;   
        Vector<Secao*> secoes;   
        
    public:
        Armazem(){}
        Armazem(int id);
        ~Armazem();
        void adicionarSecao(int idSecaoDestino); // Renamed for clarity
        int encontrarIndiceSecao(int idSecaoDestino); // Renamed for clarity
        Secao* getSecaoPorDestino(int idSecaoDestino);
        const Vector<Secao*>& getSecoes() const;
        int getId() const { return idArmazem; } // Added getter for ID
        
};

#endif