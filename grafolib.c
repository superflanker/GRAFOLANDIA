#include "grafolib.h"

/**
 *
 * Cria ligação entre as estações
 *
 */

void criaLigacao(GrafoAresta *grafo[MAX_STATIONS][MAX_STATIONS], int estacao1, int estacao2, int tempo, gLinha linha){
    
    /**
     *
     * Alocando memória para a aresta do grafo...
     *
     * já que a matriz grafo em si guarda somente ponteiros para arestas, temos 2 opções óbvias....
     *
     * Uma: declarar uma aresta estática e guardar somente o endereço - pouco profissional,
     * pois esta alternativa supõe que sempre há memória - pode levar o programa a dar segfault
     *
     * Dois: alocar o espaço necessário para a struct aresta e fazer todas as verificações necessárias
     * para saber se há memória disponível - e sair graciosamente caso não haja. maneira mais profissional
     *
     * Escolhemos a segunda pois somos durões - ninguém mexe com o Band of Brothers
     *
     */
        
    GrafoAresta *aresta = (GrafoAresta *)(malloc(sizeof(GrafoAresta)));
    
    if(aresta == NULL){
        
        printf("Falta de memória. saindo.....");
        
        exit(-1);
        
    }
    
    /**
     *
     *  Espaço alocado - seguimos em frente
     *
     */
    
    aresta->linha = linha;
    aresta->tempo = tempo;
    
    grafo[estacao1-1][estacao2-1] = aresta;
    grafo[estacao2-1][estacao1-1] = aresta;
    
    /**
     *
     * That's all folks
     *
     */
    
}

/**
 *
 * Mostra os vértices com suas arestas
 *
 */

void mostraGrafo(GrafoAresta *grafo[MAX_STATIONS][MAX_STATIONS],gLinha linha){

    int i,j;

    char buffer[200];
    
    char *linhasChar[] =  {"VERMELHA","VERDE","AMARELA","AZUL","ROXA"};
          
    printf("\n\t");
    
    snprintf(buffer,200,"Linha %s", linhasChar[linha]);
    
    imprimeBonito (linha, buffer);

    for (i=0; i < MAX_STATIONS; i++){
        
        for(j=i+1; j < MAX_STATIONS; j++){

            if(grafo[i][j]!=NULL){
                
                if(grafo[i][j]->linha == linha){
            
                    printf("\n\t\t");
                    
                    snprintf(buffer,200,"Estação %d -> Estação %d: tempo %d minutos",i+1, j+1, grafo[i][j]->tempo);
                    
                    imprimeBonito (linha, buffer);
                    
                }
                
            }
            
        }
        
    }
    printf("\n");
}

/**
 *
 * Inspirado em http://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/
 *
 *
 */

/**
 *
 * entre todos os vizinhos, retorna o que tiver o menor caminho
 * 
 */

int distanciaMinima(int *distancia, bool *spfSet){
    
    int min = INT_MAX, min_idx, i;
    
    for(i = 0; i < MAX_STATIONS; i++){
        
        if((distancia[i] <= min) && (spfSet[i] == false)){
            
            min = distancia[i];
            
            min_idx = i;
            
        }
        
    }
    
    return min_idx;
    
}

/**
 *
 * Imprime o caminho encontrado para a estação desejada - obsoleta
 *
 */

void _imprimeCaminho(int *nosAdjacentes, int destino, bool end){
    
    if(nosAdjacentes[destino] == -1){
        
        /**
         *
         * o nó é a própria origem
         *
         */
        
        printf("Partiu de Estação %d -> ",destino+1);
        
        return;
        
    }
    
    _imprimeCaminho(nosAdjacentes,nosAdjacentes[destino],false);
    
    if(end)
    
        printf(" Parou em Estação %d -> ", destino+1);
    
    else
    
        printf(" Passou por Estação %d -> ",destino+1);
    
}

/**
 *
 * imprime a solução encontrada
 *
 */

void imprimeSolucao(GrafoAresta *grafo[MAX_STATIONS][MAX_STATIONS],int origem, int destino, int *nosAdjacentes, int *distancia){
    
    int i, numStations;
    
    char *linhasChar[] =  {"VERMELHA","VERDE","AMARELA","AZUL","ROXA"};
    
    prettyPathPrintable *stations[MAX_STATIONS] = {NULL};
    
    char buffer[200];
    
    printf("Estação de origem: %d\n",origem+1);
    
    printf("Estação de destino: %d\n",destino+1);
    
    printf("Caminho: ");
    
    /**
     *
     * Imprimindo o resumo
     *
     */
    
    _imprimeCaminho(nosAdjacentes,destino,true);
    
    printf("Chegou!!\n");
    
    printf("Tempo estimado: %d minutos\n",distancia[destino]);
    
    printf("Detalhamento do trajeto:\n\n");
    
    numStations = coletaCaminho(stations,grafo,nosAdjacentes,destino);
    
    snprintf(buffer,200,"Partindo da Estação %d",stations[0]->origem);
    
    printf("\t");
    
    imprimeBonito(ROXA+1,buffer);
    
    printf("\n\t\t");
    
    for(i = 0; i < numStations -1; i++){
        
        /**
         *
         * Estação de origem - estação de destino
         *
         * Tempo de espera - Tempo do trajeto, tempo total
         *
         */
        
        if(stations[i]->linhaDestino != stations[i]->linhaOrigem){
            
            snprintf(buffer,200,"Em estação %d, Mude de linha %s para linha %s",stations[i]->origem, linhasChar[stations[i]->linhaOrigem], linhasChar[stations[i]->linhaDestino]);
            
            printf("\n\t\t");
            
            imprimeBonito(stations[i]->linhaOrigem,buffer);
            
            snprintf(buffer,200,"Tempo de espera: %d minutos, tempo de trajeto: %d minutos",stations[i]->espera,stations[i]->tempo);
            
            printf("\n\t\t");
            
            imprimeBonito(stations[i]->linhaOrigem,buffer);
            
        }
        
        printf("\n\t\t");
        
        snprintf(buffer,200,"Estação %d -> Estação %d => Tempo de trajeto: %d minutos, linha %s",stations[i]->origem,stations[i]->destino,stations[i]->tempoTotal,linhasChar[stations[i]->linhaDestino]);
        
        imprimeBonito(stations[i]->linhaDestino,buffer);
        
        /**
         *
         * liberando memória alocada por coletaCaminho - boa prática
         *
         */
        
        free(stations[i]);
        
    }
    
    printf("\n\n\t");
    
    snprintf(buffer,200,"Você chegou ao seu destino em %d minutos!!",distancia[destino]);
    
    imprimeBonito(ROXA+1,buffer);
    
    printf("\n");
    
}

/**
 *
 * Função de custo modificada para atender aos requisitos do trabalho
 *
 */

int calculaDistancia(gLinha prevLinha, GrafoAresta *next){
    
    int distancia = 0;
    
    if(next == NULL){
       
        return INT_MAX; 
        
    }
    
    if(prevLinha != next->linha){
        
        distancia+=6;
        
    }
    
    distancia+=next->tempo;
    
    return distancia;
    
}

/**
 *
 * Algoritmo de dijkstra - Shortest path first
 *
 */

int ShortestPathFirst(GrafoAresta *grafo[MAX_STATIONS][MAX_STATIONS], int estacaoOrigem, int estacaoDestino){
    
    int count, i, v;
    /**
     *
     * Distância entre os nós
     *
     */
    
    int distancia[MAX_STATIONS];
    
    /**
     *
     * array para marcar os nós que estão inclusos no memor caminho
     *
     */
    
    bool spfSet[MAX_STATIONS];
    
    /**
     *
     * guarda os nós adjacentes à medida que caminhamos no grafo
     *
     */
    int nosAdjacentes[MAX_STATIONS];
    
    /**
     *
     * inicializando os vetores
     *
     */
    
    for (i = 0; i < MAX_STATIONS; i++)
    {
    
        nosAdjacentes[i] = -1;
    
        distancia[i] = INT_MAX;
    
        spfSet[i] = false;
        
    }
    
    //a distância da estação de origem para ela mesma é sempre zero
    
    distancia[estacaoOrigem-1] = 0;
    
    /**
     *
     * Computando a distância mínima da estação de origem à todas as outras estações
     *
     */
    
    for (count = 0; count < MAX_STATIONS-1; count++)
    {
        /**
         *
         * Retorna o vértice com distância mínima entre os vértices não
         *
         * processados. Na primeira iteração, o nó será sempre a estação de origem, logo, não
         *
         * precisamos de lógica adicional para, primeiro, selecionar a estação de origem e depois seus nós
         *
         * adjacentes
         *
         */
        int u = distanciaMinima(distancia, spfSet);
 
        /**
         *
         * marcando o nó como processado
         *
         */
 
        spfSet[u] = true;
 
        /**
         *
         * Atualizando as distâncias, ou melhor, tempos de trânsito(ou custo, se assim desejar)
         *
         * para os outros vértices a partir do vértice selecionado
         *
         */
        
        for (v = 0; v < MAX_STATIONS; v++){
            
            /**
             *
             * Vamos perguntar ao grafo se há ligação entre u e v
             *
             * somente atualizo distâncias nos nós que ainda não foram processados....
             *
             * assim, evito deadlocks em caminhos circulares
             *
             */
            
            if(!spfSet[v] && grafo[u][v] != NULL){
                
                /**
                 *
                 * Que beleza, existe uma linha, pelo menos, que vai de u a v
                 *
                 * Obtendo a linha do trajeto anterior - necessária para o cálculo de distãncias
                 *
                 */
                
                gLinha linhaOrigem;// do no adjacente de u para u
                
                gLinha linhaDestino = grafo[u][v]->linha;// da possível linha de u para v
                
                if(nosAdjacentes[u] != -1){
                    
                    linhaOrigem = grafo[nosAdjacentes[u]][u]->linha;
                    
                } else {
                    
                    linhaOrigem = linhaDestino;//o nó u é o nó de origem e não um do meio do caminho, portanto, não há nexo em dizer que
                    
                    //o ilustre passageiro veio de outra linha......
                    
                }
                
                if(distancia[u] + calculaDistancia(linhaOrigem, grafo[u][v]) < distancia[v]){ 
                    
                    nosAdjacentes[v] = u;
                    
                    distancia[v] = distancia[u] + calculaDistancia(linhaOrigem, grafo[u][v]);
                    
                }
                
            }
            
        }
         
    }
    
    /**
     *
     * Árvore pronta, imprimindo o caminho desejado
     *
     */
    
    printf("\n");
    
    imprimeSolucao(grafo, estacaoOrigem-1,estacaoDestino-1, nosAdjacentes, distancia);
    
    printf("\n");
    
    return distancia[estacaoDestino-1];
; 
}

/**
 *
 * Auxiliar de imprimeSolucao, pega a cor da linha
 *
 */

void pegaCor(gLinha linha, char *cor){
    
    static char *cores[] = {"\x1b[31m %s \x1b[0m","\x1b[32m %s \x1b[0m","\x1b[33m %s \x1b[0m","\x1b[34m %s \x1b[0m","\x1b[35m %s \x1b[0m","\x1b[36m %s \x1b[0m"};
    
    strcpy(cor,cores[linha]);
    
}

/**
 *
 * Imprime coisas bonitinhas na tela
 *
 */

void imprimeBonito(gLinha linha, char *frase){
    
    char cor[50];
    
    pegaCor(linha,cor);
    
    printf(cor,frase);
    
}

/**
 *
 * Coleta o caminho, para facilitar a impressão da solução
 *
 */

int coletaCaminho(prettyPathPrintable *stations[MAX_STATIONS], GrafoAresta *grafo[MAX_STATIONS][MAX_STATIONS], int *nosAdjacentes, int destino){
    
    int temp[MAX_STATIONS];
    
    int i = 0, j = 0, quantidade = 0;
    
    int parent = destino;
    
    temp[i] = destino;
    
    i++;
    
    quantidade++;
    
    /**
     *
     * Coletando a cadeira de nós do caminho
     *
     */
    
    do{
        temp[i] = nosAdjacentes[parent];
        
        parent = temp[i];
        
        i++;
        
        if(parent != -1)
        
            quantidade++;
        
    } while(parent != -1);
    
    /**
     *
     * Perfazendo o caminho e colocando-o em stations
     *
     * tenho de ler o vetor de trás para frente
     *
     */
    
    for(i = quantidade-1; i > 0; i--){
        
        int origem = temp[i];
        
        int destino = temp[i-1];
        
        prettyPathPrintable *subpath = (prettyPathPrintable *)(malloc(sizeof(prettyPathPrintable)));
        
        if(subpath == NULL){
            
            printf("Falta de memória. saindo....");
            
            exit(-1);
            
        }
        
        subpath->origem = origem+1;
        
        subpath->destino = destino+1;
        
        subpath->tempo = grafo[origem][destino]->tempo;
        
        subpath->linhaDestino = grafo[origem][destino]->linha;
        
        subpath->espera = 0;
        
        /**
         *
         * Coletando a informação de mudança de linha
         *
         */
        
        if(i != quantidade-1){
            
            /**
             *
             * Temos de verificar a linha do subcaminho anterior, para informar a espera
             *
             */
            
            subpath->linhaOrigem = stations[j-1]->linhaDestino;
            
        } else {
            
            subpath->linhaOrigem = subpath->linhaDestino;
            
        }
        
        if(subpath->linhaDestino != subpath->linhaOrigem){
            
            subpath->espera = 6;
            
        }
        
        subpath->tempoTotal = subpath->tempo+subpath->espera;
        
        stations[j] = subpath;
        
        j++;
        
    }
    
    return quantidade;
    
}