#define MAX_STATIONS 20
#include "grafolib.h"

int main(int argC, char **argV){

    GrafoAresta *grafo[MAX_STATIONS][MAX_STATIONS] = {{NULL}};
    
    int estacaoOrigem, estacaoDestino;
    
    //adicionando linha vermelha
    
    criaLigacao(grafo,1,2,16,VERMELHA);
    
    criaLigacao(grafo,2,3,14,VERMELHA);
    
    criaLigacao(grafo,3,4,12,VERMELHA);
    
    criaLigacao(grafo,4,5,12,VERMELHA);
    
    criaLigacao(grafo,5,6,14,VERMELHA);
    
    //adicionando linha verde
    
    criaLigacao(grafo,7,8,15,VERDE);
    
    criaLigacao(grafo,8,9,11,VERDE);
    
    criaLigacao(grafo,9,10,13,VERDE);
    
    criaLigacao(grafo,10,11,16,VERDE);
    
    criaLigacao(grafo,11,6,15,VERDE);
    
    //adicionando linha amarela
    
    criaLigacao(grafo,12,8,11,AMARELA);
    
    criaLigacao(grafo,8,2,8,AMARELA);
    
    criaLigacao(grafo,2,15,7,AMARELA);
    
    criaLigacao(grafo,15,16,7,AMARELA);
    
    criaLigacao(grafo,16,17,12,AMARELA);
    
    criaLigacao(grafo,17,18,9,AMARELA);
    
    //adicionando linha azul
    
    criaLigacao(grafo,12,9,17,AZUL);
    
    criaLigacao(grafo,9,13,7,AZUL);
    
    criaLigacao(grafo,13,14,9,AZUL);
    
    criaLigacao(grafo,14,5,9,AZUL);
    
    criaLigacao(grafo,5,17,10,AZUL);
    
    //adicionando linha roxa
    
    criaLigacao(grafo,10,13,11,ROXA);
    
    criaLigacao(grafo,13,3,13,ROXA);
    
    criaLigacao(grafo,3,16,11,ROXA);
    
    criaLigacao(grafo,16,19,13,ROXA);
    
    criaLigacao(grafo,19,20,12,ROXA);
    
    //grafo montado
    
    if(argC >= 2){
    
        /**
         *
         * Fugimos do funcionamento padrão, auto-teste
         *
         */
        
        int i,j,falhas = 0, tempos[MAX_STATIONS][MAX_STATIONS] = {{0}};
        
        char buffer[200];
        
        for(i = 0; i < MAX_STATIONS; i++){
            
            for(j = i+1; j < MAX_STATIONS; j++){
                
                tempos[i][j] = ShortestPathFirst(grafo,i+1,j+1);
                
                tempos[j][i] = ShortestPathFirst(grafo,j+1,i+1);
                
            }
            
        }
        
        for(i = 0; i < MAX_STATIONS;i++){
            
            for(j = i+1; j < MAX_STATIONS; j++){
                
                if(tempos[i][j] != tempos[j][i]){
                    
                    printf("\n\t");
                    
                    snprintf(buffer,200,"Algoritmo falhou: Estação %d -> Estação %d: %d minutos, Estação %d -> Estação %d: %d minutos",i+1,j+1,tempos[i][j],j+1,i+1,tempos[j][i]);
                    
                    imprimeBonito(ROXA+1,buffer);
                    
                    falhas++;
                    
                }
                
            }
            
        }
        
        printf("\n\t");
        
        snprintf(buffer,200,"Total de falhas: %d, %%falhas: %.2f%%, %%acertos: %.2f%%",falhas,100.0*falhas/400.0,100.0*(400-falhas)/400.0);
        
        imprimeBonito(ROXA+1,buffer);
        
        printf("\n\n");
        
    } else {
        
        printf("SMG = Sistema de Metrô da Grafolândia\n");
        
        printf("Linhas da Grafolândia:\n");
        
        mostraGrafo(grafo,VERMELHA);
            
        mostraGrafo(grafo,VERDE);
            
        mostraGrafo(grafo,AMARELA);
            
        mostraGrafo(grafo,AZUL);
            
        mostraGrafo(grafo,ROXA);
        
        while(true){
            
            printf("Digite a estação de origem[1 a 20]:  ");
            
            scanf("%d",&estacaoOrigem);
            
            if(estacaoOrigem  < 1 || estacaoOrigem  > 20)
                break;//se a estação não se encontra dentro dos limites, é hora de dar tchau, é hora de dar tchau, é hora de dar tchau kkkkkkk - momento teletubbie
            
            printf("Digite a estação de destino[1 a 20]:  ");
            
            scanf("%d",&estacaoDestino);
            
            if(estacaoDestino < 1 || estacaoDestino > 20)
                break;//se a estação não se encontra dentro dos limites, é hora de dar tchau, é hora de dar tchau, é hora de dar tchau kkkkkkk - momento teletubbie
            
            ShortestPathFirst(grafo,estacaoOrigem,estacaoDestino);
        
        }
        
    }
    
    return 0;
    
    
}
