#include "lerEntrada.hpp"
#include "queue.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "lista_duplamente_encadeada.hpp"
#include<fstream>

// Função para ler dados de entrada do arquivo
void lerEntrada(const char* nomeArquivo, int &capacidadeTransporte,int& latenciaTransporte,int& intervaloTransportes,int& custoRemocao,int& numeroDeArmazens,Vector<Armazem*>& armazens,int& numeroDePacotes,Vector<Pacote*>& pacotes){

    std::ifstream arquivo(nomeArquivo);

    // Verifica se o arquivo foi aberto com sucesso
    if(!arquivo.is_open()){
        std::cerr<<"Erro ao abrir o arquivo: "<<nomeArquivo<<std::endl;
        return;
    }

    // Lê parâmetros de configuração do transporte
    arquivo>>capacidadeTransporte;
    arquivo>>latenciaTransporte;
    arquivo>>intervaloTransportes;
    arquivo>>custoRemocao;

    // Lê número de armazéns e cria os objetos
    arquivo>>numeroDeArmazens;

    for(int i=0;i<numeroDeArmazens;i++){
        Armazem* novoArmazen = new Armazem(i);
        armazens.push_back(novoArmazen);
    };

    // Lê matriz de conexões entre armazéns
    if(numeroDeArmazens>0 && armazens.size() == numeroDeArmazens){
        for(int i=0;i<numeroDeArmazens;++i){
            for(int j=0;j<numeroDeArmazens;++j){
                int temConexao;
                arquivo>>temConexao;

                // Verifica se houve erro na leitura
                if(arquivo.fail()){
                    std::cerr <<"Erro ao ler a matriz de conexões"<<std::endl;
                    arquivo.close();
                    return;
                }

                // Se há conexão (1), adiciona seção no armazém i para destino j
                if(temConexao ==1){
                    armazens[i]->adicionarSecao(j);
                }
            }
        }
    }

    // Lê número de pacotes
    arquivo>>numeroDePacotes;

    // Lê dados de cada pacote
    for(int i=0;i<numeroDePacotes;i++){
        double tempoChegada;
        int id;
        int origem;
        int destinatario;
        std::string dummyString; // Para ignorar strings auxiliares

        // Lê dados do pacote (formato: tempo "para" id "de" origem "para" destinatario)
        arquivo>>tempoChegada;
        arquivo>>dummyString; // ignora "para"
        arquivo>>id;
        arquivo>>dummyString; // ignora "de"
        arquivo>>origem;
        arquivo>>dummyString; // ignora "para"
        arquivo>>destinatario;

        // Cria novo pacote com os dados lidos
        Pacote* novoPacote = new Pacote(tempoChegada,i,origem,destinatario);
        pacotes.push_back(novoPacote);
    }
    arquivo.close();
};



