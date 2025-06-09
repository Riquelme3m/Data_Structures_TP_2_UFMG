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
        Vector<Secao> secoes;   
        int numSecoes = 0;       
    public:
        Armazem() : idArmazem(-1) {} // Default constructor
        Armazem(int id);
        void adicionarSecao(int idSecao);
        int encontrarSecao(int idSecao);
        const Vector<Secao>& getSecoes() const;
        
};

#endif












