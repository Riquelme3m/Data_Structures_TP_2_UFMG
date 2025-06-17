#include<iostream>
#include"armazem.hpp"
#include"lista_duplamente_encadeada.hpp"
#include"map.hpp"
#include"pacote.hpp"
#include"vector.hpp"
#include "queue.hpp"
#include "lerEntrada.hpp"
#include "escalonador.hpp"

// Helper function to perform BFS using adjacency list and return path as DoublyLinkedList<int>*
DoublyLinkedList<int>* bfs_rota(const Vector<Vector<int>>& adjList, int origem, int destino) {
    int n = adjList.size();

    // Basic bounds check for origin and destination
    if (origem < 0 || origem >= n || destino < 0 || destino >= n) {
        std::cerr << "BFS Error: Origem (" << origem << ") ou Destino (" << destino << ") fora dos limites." << std::endl;
        return new DoublyLinkedList<int>(); // Return empty path
    }
    if (origem == destino){
        DoublyLinkedList<int>* rotaDirect = new DoublyLinkedList<int>();
        rotaDirect->append(origem);
        return rotaDirect;
    }


    Vector<int> prev(n, -1); // Stores the predecessor of each node in the path
    Vector<bool> visited(n, false); // Tracks visited nodes
    Queue<int> q; // Queue for BFS

    q.enqueue(origem);
    visited[origem] = true;

    bool pathFound = false;
    while (!q.isEmpty()) {
        int u = q.front();
        q.dequeue();

        if (u == destino) {
            pathFound = true;
            break;
        }

        // Check bounds for adjList[u] access, though adjList should be correctly sized
        if (u >= 0 && u < adjList.size()) {
            const Vector<int>& neighbors = adjList[u];
            for (int i = 0; i < neighbors.size(); ++i) {
                int v = neighbors[i];
                // Check bounds for neighbor v
                if (v >= 0 && v < n && !visited[v]) {
                    visited[v] = true;
                    prev[v] = u;
                    q.enqueue(v);
                }
            }
        }
    }

    DoublyLinkedList<int>* rotaDoPacote = new DoublyLinkedList<int>();
    if (pathFound) {
        // Reconstruct path from destino back to origem
        Vector<int> pathInReverse;
        for (int at = destino; at != -1; at = prev[at]) {
            pathInReverse.push_back(at);
        }
        // Add to DoublyLinkedList in correct order (origem to destino)
        for (int i = pathInReverse.size() - 1; i >= 0; --i) {
            rotaDoPacote->append(pathInReverse[i]);
        }
    } else {
         std::cerr << "BFS Info: Rota não encontrada de " << origem << " para " << destino << std::endl;
    }

    return rotaDoPacote;
}


int main(){

    int capacidadeTransporte;
    int latenciaTransporte;
    int intervaloTransporte;
    int custoRemocao;

    int numeroDeArmazens;
    Vector<Armazem*>armazens;
    int numeroDePacotes;
    Vector<Pacote*>pacotes;
    

    lerEntrada("entrada.txt",capacidadeTransporte,latenciaTransporte,intervaloTransporte,
    custoRemocao,numeroDeArmazens,armazens,numeroDePacotes,pacotes);


    std::cout<<"Capacidade de transporte: "<<capacidadeTransporte<<std::endl;
    std::cout<<"Latencia Transporte: "<<latenciaTransporte<<std::endl;
    std::cout<<"Intervalo Transporte: "<<intervaloTransporte<<std::endl;
    std::cout<<"Custo remocao: "<<custoRemocao<<std::endl;

    std::cout<<"Numero de armazens: "<<numeroDeArmazens<<std::endl;
    std::cout<<"Numero de pacotes: "<<numeroDePacotes<<std::endl;

    // Declare an adjacency list
    // Each element of adjList is a Vector<int> representing the neighbors of an armazem
    Vector<Vector<int>> adjList;

    // Populate the adjacency list from the armazens vector
    for (int i = 0; i < armazens.size(); ++i) {
        Vector<int> neighbors; // Vector to store neighbors of armazem i
        // Ensure armazens[i] is not null before accessing
        if (armazens[i]) {
            const Vector<Secao*>& secoes = armazens[i]->getSecoes();
            for (int j = 0; j < secoes.size(); ++j) {
                // Ensure secoes[j] is not null before accessing
                if (secoes[j]) {
                    neighbors.push_back(secoes[j]->idSecao);
                }
            }
        }
        adjList.push_back(neighbors); // Add the list of neighbors for armazem i
    }

    // Example: Print the adjacency list to verify
    std::cout << "\nAdjacency List:" << std::endl;
    for (int i = 0; i < adjList.size(); ++i) {
        std::cout << "Armazem " << i << " is connected to: ";
        for (int j = 0; j < adjList[i].size(); ++j) {
            std::cout << adjList[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl;

    // Calculate and set route for each pacote
    for (int i = 0; i < pacotes.size(); ++i) {
        if (pacotes[i]) { // Ensure pacote pointer is not null
            int origem = pacotes[i]->getOrigem();
            int destino = pacotes[i]->getDestinatario();

            std::cout << "Calculando rota para Pacote " << pacotes[i]->getId() 
                      << " de " << origem << " para " << destino << std::endl;

            DoublyLinkedList<int>* rota = bfs_rota(adjList, origem, destino);
            pacotes[i]->setRota(rota);
            pacotes[i]->setCurrentNode(); // Initialize currentNode after setting the rota

            // Print the route for testing
            std::cout << "Pacote " << pacotes[i]->getId() << " rota: ";
            if (rota && rota->getHead()) { // Check if rota is not null and not empty
                rota->printForward();
            } else {
                std::cout << "(rota vazia ou nao encontrada)" << std::endl;
            }
        }
    }
    std::cout << "---------------------------------------" << std::endl;


    for(int i=0;i<armazens.size();i++){
        std::cout<<"Armazen: "<<i<<std::endl;
        const Vector<Secao*>& aux = armazens[i]->getSecoes(); 
        for(int j=0;j<aux.size();j++){
            std::cout<<"tem conexao com "<<aux[j]->idSecao<<std::endl;
        }
        std::cout<<"---------------------------------------"<<std::endl;
    }

    DoublyLinkedList<int>* teste = pacotes[4]->getRotaDoPacote();
    teste->printForward();

    

    // Inicializa e executa o escalonador
    Escalonador escalonador;
    escalonador.inicializar(capacidadeTransporte, latenciaTransporte, intervaloTransporte, custoRemocao, &armazens, &pacotes);
    escalonador.executarSimulacao();

    // Correctly delete Armazem objects
    for(int i=0; i < armazens.size(); i++){
        delete armazens[i];
        armazens[i] = nullptr; 
    } // End of armazens deletion loop

    // Correctly delete Pacote objects
    for(int i=0; i < pacotes.size(); i++){
        delete pacotes[i];
        pacotes[i] = nullptr; 
    } // End of pacotes deletion loop
    
   
    return 0;
}