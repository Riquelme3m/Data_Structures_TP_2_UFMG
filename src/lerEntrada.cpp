#include "lerEntrada.hpp"
#include "queue.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "lista_duplamente_encadeada.hpp"
#include<fstream>



// Função para calcular a rota mais curta entre dois armazéns usando BFS
DoublyLinkedList<int>* calcularRotaBFS(int origem, int destino, int numeroDeArmazens, const Vector<Armazem>& armazens) {
    if (origem < 0 || origem >= numeroDeArmazens || destino < 0 || destino >= numeroDeArmazens) {
        std::cerr << "BFS Error: IDs invalidos. Origem: " << origem << ", Destino: " << destino << std::endl;
        return nullptr;
    }
    if (origem == destino) {
        auto* rota = new DoublyLinkedList<int>();
        rota->append(origem);
        return rota;
    }

    Vector<bool> visitado(numeroDeArmazens, false);
    Vector<int> pai(numeroDeArmazens, -1);

    Queue<int> fila;
    fila.enqueue(origem);
    visitado[origem] = true;

    bool encontrou = false;
    while (!fila.isEmpty()) {
        int atual = fila.front();
        fila.dequeue();

        if (atual == destino) {
            encontrou = true;
            break;
        }

        Vector<Secao> secoes = armazens[atual].getSecoes();
        for (int i = 0; i < secoes.size(); ++i) {
            int vizinho = secoes[i].idSecao;
            if (vizinho >= 0 && vizinho < numeroDeArmazens && !visitado[vizinho]) {
                visitado[vizinho] = true;
                pai[vizinho] = atual;
                fila.enqueue(vizinho);
            }
        }
    }

    if (!encontrou) {
        return nullptr;
    }

    // Reconstruir caminho: do destino até a origem, depois inverter para ordem correta
    Vector<int> caminho;
    int atual = destino;
    while (atual != -1) {
        caminho.push_back(atual);
        if (atual == origem) break;
        atual = pai[atual];
    }
    // O vetor caminho está do destino para a origem, então inserimos na lista do fim para o início
    DoublyLinkedList<int>* rota = new DoublyLinkedList<int>();
    for (int i = caminho.size() - 1; i >= 0; --i) {
        rota->append(caminho[i]);
    }
    return rota;
}

void lerEntrada(std::string nomeArquivo,int &capacidadeTransporte,int& latenciaTransporte,int& intervaloTransportes,int& custoRemocao,int& numeroDeArmazens,Vector<Armazem>& armazens,int& numeroDePacotes,Vector<Pacote>& pacotes){

    std::ifstream arquivo(nomeArquivo);

    if(!arquivo.is_open()){
        std::cerr<<"Erro ao abrir o arquivo: "<<nomeArquivo<<std::endl;
        return;
    }

    arquivo>>capacidadeTransporte;
    arquivo>>latenciaTransporte;
    arquivo>>intervaloTransportes;
    arquivo>>custoRemocao;
    arquivo>>numeroDeArmazens;

    /*Criando os armazéns*/
    for(int i=0;i<numeroDeArmazens;i++){
        Armazem novoArmazen(i);
        armazens.push_back(novoArmazen);
    };

    /*Criando armazens e secões de acordo com o grafo recebido*/

    if(numeroDeArmazens>0 && armazens.size() == numeroDeArmazens){
        for(int i=0;i<numeroDeArmazens;++i){
            for(int j=0;j<numeroDeArmazens;++j){
                int temConexao;
                arquivo>>temConexao;

                if(arquivo.fail()){
                    std::cerr <<"Erro ao ler a matriz de conexões"<<std::endl;
                    arquivo.close();
                    return;
                }

                if(temConexao ==1){
                    armazens[i].adicionarSecao(j);
                }
            }
        }
    }

    /*Criando pacotes de acordo com a entrada*/
    arquivo>>numeroDePacotes;

    for(int i=0;i<numeroDePacotes;i++){
        double tempoChegada;
        int id;
        int origem;
        int destinatario;
        std::string dummyString;

        arquivo>>tempoChegada;

        arquivo>>dummyString;

        arquivo>>id;
        arquivo>>dummyString;
        arquivo>>origem;
        arquivo>>dummyString;
        arquivo>>destinatario;

        Pacote novoPacote(tempoChegada,id,origem,destinatario);
        pacotes.push_back(novoPacote);
    }
    arquivo.close();


    // Improved printing of armazéns and their sections
    std::cout << "\nResumo dos Armazéns e suas Seções:\n";
    for(int i=0; i<armazens.size(); i++) {
        const Vector<Secao>& secoes = armazens[i].getSecoes();
        std::cout << "Armazém " << i << " seções: ";
        for(int j=0; j<secoes.size(); j++) {
            std::cout << secoes[j].idSecao;
            if(j < secoes.size() - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;

    /*Definindo a rota de cada pacote*/


    // for(int i=0;i<numeroDePacotes;i++){
    //     pacotes[i].setRota(calcularRotaBFS(pacotes[i].getOrigem(),pacotes[i].getDestinatario(),numeroDeArmazens,armazens));
    // }

    // // Test: print routes for each package
    // for(int i=0;i<numeroDePacotes;i++){
    //     std::cout << "Pacote " << pacotes[i].getId() << " rota: ";
    //     DoublyLinkedList<int>* rota = pacotes[i].getRotaDoPacote();
    //     if(rota) {
    //         if(rota->getHead() == nullptr) {
    //             std::cout << "(rota vazia)" << std::endl;
    //         } else {
    //             rota->printForward();
    //         }
    //     }
    //     else std::cout << "Nenhuma rota encontrada." << std::endl;
    // }
    
    // Print all pacotes and their information
    std::cout << "\nPacotes lidos:\n";
    for(int i=0; i<numeroDePacotes; i++) {
        std::cout << "Pacote ID: " << pacotes[i].getId()
                  << " | Tempo Chegada: " << pacotes[i].getTempoChegada()
                  << " | Origem: " << pacotes[i].getOrigem()
                  << " | Destino: " << pacotes[i].getDestinatario()
                  << std::endl;
    }
    
};


