#pragma once
#include<iostream>
#include"vector.hpp"
#include "armazem.hpp"
#include "pacote.hpp"

void lerEntrada(std::string nomeArquivo,int &capacidadeTransporte,int& latenciaTransporte,int& intervaloTransportes,int& custoRemocao,int& numeroDeArmazens,Vector<Armazem*>& armazens,int& numeroDePacotes,Vector<Pacote*>& pacotes);