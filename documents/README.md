# Trabalho Prático 2 - Sistema de Escalonamento Logístico Armazéns Hanoi

## DCC205/DCC221 – Estruturas de Dados – TP2 v1.0 2025/1
**Profs. Anisio Lacerda / Lucas Ferreira / Wagner Meira Jr. / Washington Cunha**

## 1. Visão Geral
Este projeto consiste na implementação de um sistema de simulação de eventos discretos para gerenciar a logística de pacotes entre os Armazéns Hanoi. O sistema deve rotear pacotes, acompanhar seu progresso através de uma rede de armazéns e coletar estatísticas sobre os tempos de transporte e armazenamento.

A principal característica dos Armazéns Hanoi é a organização interna de suas seções de armazenamento, que operam sob uma lógica LIFO (Last-In First-Out).

## 2. Objetivos
- Implementar um simulador de eventos discretos para o sistema logístico.
- Modelar o comportamento de pacotes, armazéns e o transporte entre eles.
- Calcular rotas ótimas para os pacotes em uma rede de armazéns.
- Gerenciar o armazenamento de pacotes em seções LIFO.
- Simular o transporte diário de pacotes, respeitando capacidades e prioridades.
- Coletar e reportar estatísticas de desempenho para cada pacote, incluindo:
    - Tempo esperado de estadia
    - Tempo armazenado
    - Tempo em trânsito
- Identificar gargalos no sistema.

## 3. Componentes Principais (Tipos Abstratos de Dados - TADs)

### 3.1. Pacote
Representa um item sendo transportado. Contém:
- Informações de origem, destino, remetente, destinatário, tipo.
- Data e hora da postagem.
- Rota calculada (lista de armazéns).
- Estado atual (ex: não postado, em trânsito, armazenado, entregue).
- Estatísticas de tempo (armazenado, em trânsito).

### 3.2. Armazém
Representa uma localidade física. Contém:
- Identificador único.
- Seções de armazenamento para cada armazém conectado.
- Cada seção opera como uma **pilha (LIFO)** para pacotes.
- Operações: `armazenaPacote`, `recuperaPacote` (considerando tempo de manipulação LIFO).

### 3.3. Transporte
Modela o movimento de pacotes entre armazéns.
- Tempo de transporte constante entre armazéns.
- Capacidade diária de transporte entre dois armazéns.
- Implementado através do escalonamento de eventos de chegada de pacotes.

### 3.4. Escalonador
Componente central da simulação de eventos discretos.
- Gerencia uma **fila de prioridade (min-heap)** de eventos.
- Eventos são ordenados cronologicamente.
- Operações: `insereEvento`, `retiraProximoEvento`.

## 4. Arquitetura do Sistema
A simulação é controlada pelo `Escalonador`, que processa eventos em ordem cronológica. Os principais tipos de eventos incluem:
- **Chegada de Pacote:** Um pacote chega a um armazém (seja por postagem inicial ou após transporte).
- **Transporte de Pacotes:** Evento diário que move pacotes entre armazéns conectados.

A topologia da rede de armazéns é um grafo não direcionado, e as rotas são calculadas como o menor caminho (e.g., usando Busca em Largura - BFS).

## 5. Entrada e Saída

### Entrada
Um arquivo contendo informações de pacotes, uma por linha:
- Data hora da postagem
- Nome Remetente
- Nome Destinatário
- Tipo
- Armazém de origem
- Armazém de destino

Também são necessários parâmetros do sistema:
- Topologia da rede de armazéns.
- Tempo de transporte entre armazéns.
- Capacidade de transporte entre armazéns.
- Tempo de manipulação de pacote em uma seção.

### Saída
Para cada pacote, o sistema deve reportar:
- Tempo esperado de estadia
- Tempo armazenado
- Tempo em trânsito

## 6. Estrutura de Implementação Sugerida
1.  Definição das classes/estruturas para os TADs: `Pacote`, `Evento`, `Armazem`.
2.  Implementação do `Escalonador` com uma Min-Heap.
3.  Implementação da representação do grafo da rede de armazéns e do algoritmo de cálculo de rotas (BFS).
4.  Desenvolvimento da lógica de processamento de entrada para criar pacotes e agendar eventos iniciais.
5.  Implementação do ciclo principal da simulação, processando eventos (`CHEGADA_PACOTE_ARMAZEM`, `TRANSPORTE_PACOTES`).
6.  Cálculo e coleta de estatísticas.
7.  Geração do relatório de saída.
