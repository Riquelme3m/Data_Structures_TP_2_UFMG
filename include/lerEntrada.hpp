#ifndef LER_ENTRADA_HPP
#define LER_ENTRADA_HPP

#include "vector.hpp"
#include "armazem.hpp"
#include "pacote.hpp"
#include <iostream>

void lerEntrada(const char* nomeArquivo, int &capacidadeTransporte, int& latenciaTransporte, int& intervaloTransportes, int& custoRemocao, int& numeroDeArmazens, Vector<Armazem*>& armazens, int& numeroDePacotes, Vector<Pacote*>& pacotes);

#endif