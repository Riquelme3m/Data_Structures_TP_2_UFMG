#include "lerEntrada.hpp"
#include "queue.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "lista_duplamente_encadeada.hpp"
#include<fstream>





void lerEntrada(std::string nomeArquivo,int &capacidadeTransporte,int& latenciaTransporte,int& intervaloTransportes,int& custoRemocao,int& numeroDeArmazens,Vector<Armazem*>& armazens,int& numeroDePacotes,Vector<Pacote*>& pacotes){

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
        Armazem* novoArmazen = new Armazem(i);
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
                    armazens[i]->adicionarSecao(j);
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

        Pacote* novoPacote = new Pacote(tempoChegada,id,origem,destinatario);
        pacotes.push_back(novoPacote);
    }
    arquivo.close();
    
   
};


