#ifndef _GRAFOLIB_H_
#define _GRAFOLIB_H_

#ifndef MAX_STATIONS

#define MAX_STATIONS 20

#endif

/**
 *
 * Includes de praxe
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/**
 *
 * As linhas da grafolândia
 *
 */

typedef enum {VERMELHA,VERDE,AMARELA,AZUL,ROXA} gLinha;

/**
 *
 * As arestas da grafolândia - caminhos
 *
 */

typedef struct{
    int tempo;
    gLinha linha;
} GrafoAresta;


/**
 *
 * Struct auxiliar para imprimir o caminho encontrado
 *
 */

typedef struct{
    int origem;
    int destino;
    int tempo;
    int espera;
    int tempoTotal;
    gLinha linhaOrigem;
    gLinha linhaDestino;
} prettyPathPrintable;

/**
 *
 * Cria ligação entre as estações
 *
 */

void criaLigacao(GrafoAresta *grafo[MAX_STATIONS][MAX_STATIONS], int estacao1, int estacao2, int tempo, gLinha linha);

/**
 *
 * Mostra os vértices com suas arestas
 *
 */

void mostraGrafo(GrafoAresta *grafo[MAX_STATIONS][MAX_STATIONS],gLinha linha);

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

int distanciaMinima(int *distancia, bool *spfSet);
/**
 *
 * Imprime o caminho encontrado para a estação desejada 
 *
 */

void _imprimeCaminho(int *nosAdjacentes, int destino, bool end);
/**
 *
 * imprime a solução encontrada
 *
 */

void imprimeSolucao(GrafoAresta *grafo[MAX_STATIONS][MAX_STATIONS],int origem, int destino, int *nosAdjacentes, int *distancia);

/**
 *
 * Função de custo modificada para atender aos requisitos do trabalho
 *
 */

int calculaDistancia(gLinha prevLinha, GrafoAresta *next);

/**
 *
 * Algoritmo de dijkstra - Shortest path first
 *
 */

int ShortestPathFirst(GrafoAresta *grafo[MAX_STATIONS][MAX_STATIONS], int estacaoOrigem, int estacaoDestino);

/**
 *
 * Auxiliar de imprimeSolucao, pega a cor da linha
 *
 */

void pegaCor(gLinha linha, char *cor);

/**
 *
 * Imprime coisas bonitinhas na tela
 *
 */

void imprimeBonito(gLinha linha, char *frase);


/**
 *
 * Coleta o caminho, para facilitar a impressão da solução
 *
 */

int coletaCaminho(prettyPathPrintable *stations[MAX_STATIONS], GrafoAresta *grafo[MAX_STATIONS][MAX_STATIONS], int *nosAdjacentes, int destino);

#endif