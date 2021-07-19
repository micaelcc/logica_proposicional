#include "Lista.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Consequencia_Logica.h"
#include "Tabela_Verdade.h"

extern Lista * exp_gama;

/*
* Recebe um conjunto de formulas GAMA e uma formula B, e diz se 
* a fórmula B é ou não consequencia lógica
*/
int logical_consequence(int **tabela, int rows, int columns, Lista *gama, char *B) {
    int tam = tam_list(gama); // quantidade de formulas do gama
    int *gama_positions = (int*)malloc(sizeof(int) * tam); //vetor para as colunas do gama na tabela
    int B_position = busca_pos_sub(B); // Coluna da formula B na tabela
    int i, j;
    
    //Vetor que armazena o numero das linhas onde as formulas do conjunto gama são simultaneamente satisfeitas
    int *lines = (int*)malloc(sizeof(int) * rows);  
    int aux = 0;

    // Armazenando o numero das colunas das fomulas gama
    for(i=0; i < tam; i++) {
        gama_positions[i] = busca_pos_sub(gama -> sub);
        gama = gama -> prox;
    }

    // Armazenando as linhas da tabela onde o conjunto gama é satisfeito
    for(i = 0; i < rows; i++) {
        int res = 0;
        int k = 0;
        for(j = 0; j < tam; j++) {
            k = gama_positions[j];
            if(tabela[i][k] == 1) {
                res++;
            }
        }

        if(res == tam) {
            lines[aux] = i;
            aux++;
        }
    }

    int cont = 0;
    for(i = 0; i < aux; i++) {
        if(tabela[lines[i]][B_position] == 0) {
            return 0; // Retorna 0 quando não é consequencia logica
        }
    }
    
    return 1; // Retorna 1 quando B é consequencia
}