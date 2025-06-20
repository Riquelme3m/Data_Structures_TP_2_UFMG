#include<iostream>
#include<chrono>
#include<fstream>
#include"armazem.hpp"
#include"lista_duplamente_encadeada.hpp"
#include"map.hpp"
#include"pacote.hpp"
#include"vector.hpp"
#include "queue.hpp"
#include "lerEntrada.hpp"
#include "escalonador.hpp"

// Algoritmo de Busca em Largura (BFS) para encontrar a menor rota entre origem e destino
DoublyLinkedList<int>* bfs_rota(const Vector<Vector<int>>& adjList, int origem, int destino) {
    int n = adjList.size();

    // Verifica se os índices são válidos
    if (origem < 0 || origem >= n || destino < 0 || destino >= n) {
        return new DoublyLinkedList<int>();
    }
    
    // Se origem é igual ao destino, retorna rota direta
    if (origem == destino){
        DoublyLinkedList<int>* rotaDirect = new DoublyLinkedList<int>();
        rotaDirect->append(origem);
        return rotaDirect;
    }

    // Arrays para controle da Busca em Largura
    Vector<int> prev(n, -1); // Predecessor de cada nó
    Vector<bool> visited(n, false); // Nós já visitados
    Queue<int> q; // Fila para BFS (característica da busca em largura)

    // Inicia busca em largura a partir da origem
    q.enqueue(origem);
    visited[origem] = true;

    bool pathFound = false;
    while (!q.isEmpty()) {
        int u = q.front();
        q.dequeue();

        // Se chegou ao destino, para a busca
        if (u == destino) {
            pathFound = true;
            break;
        }

        // Explora todos os vizinhos do nó atual (característica da busca em largura)
        if (u >= 0 && u < adjList.size()) {
            const Vector<int>& neighbors = adjList[u];
            for (int i = 0; i < neighbors.size(); ++i) {
                int v = neighbors[i];
                if (v >= 0 && v < n && !visited[v]) {
                    visited[v] = true;
                    prev[v] = u; // Registra o predecessor
                    q.enqueue(v);
                }
            }
        }
    }

    // Reconstrói o caminho se foi encontrado
    DoublyLinkedList<int>* rotaDoPacote = new DoublyLinkedList<int>();
    if (pathFound) {
        Vector<int> pathInReverse;
        // Constrói o caminho de trás para frente
        for (int at = destino; at != -1; at = prev[at]) {
            pathInReverse.push_back(at);
        }
        // Inverte para obter a ordem correta
        for (int i = pathInReverse.size() - 1; i >= 0; --i) {
            rotaDoPacote->append(pathInReverse[i]);
        }
    }

    return rotaDoPacote;
}

int main(int argc, char *argv[]){

    auto inicio = std::chrono::high_resolution_clock::now();
    
    // Verifica se foi fornecido o arquivo de entrada
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_entrada.txt>" << std::endl;
        return 1;
    }

    // Parâmetros de configuração
    int capacidadeTransporte;
    int latenciaTransporte;
    int intervaloTransporte;
    int custoRemocao;

    // Estruturas de dados principais
    int numeroDeArmazens;
    Vector<Armazem*>armazens;
    int numeroDePacotes;
    Vector<Pacote*>pacotes;
    
    // Lê dados do arquivo de entrada
    lerEntrada(argv[1], capacidadeTransporte, latenciaTransporte, intervaloTransporte,
               custoRemocao, numeroDeArmazens, armazens, numeroDePacotes, pacotes);

    // Constrói lista de adjacência para o grafo de armazéns
    Vector<Vector<int>> adjList;

    for (int i = 0; i < armazens.size(); ++i) {
        Vector<int> neighbors;
        if (armazens[i]) {
            const Vector<Secao*>& secoes = armazens[i]->getSecoes();
            // Cada seção representa uma conexão para outro armazém
            for (int j = 0; j < secoes.size(); ++j) {
                if (secoes[j]) {
                    neighbors.push_back(secoes[j]->idSecao);
                }
            }
        }
        adjList.push_back(neighbors);
    }

    // Calcula e define a rota para cada pacote
    for (int i = 0; i < pacotes.size(); ++i) {
        if (pacotes[i]) {
            int origem = pacotes[i]->getOrigem();
            int destino = pacotes[i]->getDestinatario();

            // Usa Busca em Largura para encontrar a menor rota
            DoublyLinkedList<int>* rota = bfs_rota(adjList, origem, destino);
            pacotes[i]->setRota(rota);
            pacotes[i]->setCurrentNode(); // Define posição inicial na rota
        }
    }

    // Executa a simulação
    Escalonador escalonador;
    escalonador.inicializar(capacidadeTransporte, latenciaTransporte, intervaloTransporte, custoRemocao, &armazens, &pacotes);
    escalonador.executarSimulacao();

    // Libera memória dos armazéns
    for(int i=0; i < armazens.size(); i++){
        delete armazens[i];
        armazens[i] = nullptr; 
    }

    // Libera memória dos pacotes
    for(int i=0; i < pacotes.size(); i++){
        delete pacotes[i];
        pacotes[i] = nullptr; 
    }
    #include <chrono>


    
    // Finaliza medição de tempo
    auto fim = std::chrono::high_resolution_clock::now();
    
    // Calcula duração em microssegundos para maior precisão
    auto duracao_micro = std::chrono::duration_cast<std::chrono::microseconds>(fim - inicio);
    
    // Converte para segundos com decimais
    double tempo_segundos = duracao_micro.count() / 1000000.0;

    // Salva resultado em CSV (opcional - para análise experimental)
    int numeroArmazens = armazens.size();
    std::ofstream resultados("resultados_armazens.csv", std::ios::app);
    if (resultados.is_open()) {
        resultados << latenciaTransporte << "," << std::fixed << std::setprecision(6) << escalonador.pacotesRearmazenados << std::endl;
        resultados.close();
    }

    // Exibe resultado com 6 casas decimais
    std::cout << "Simulação concluída em " << std::fixed << std::setprecision(6) 
              << tempo_segundos << " segundos" << std::endl;

    // Gera relatórios
    
    
    
    return 0;
}