#include "Lista.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Consequencia_Logica.h"
#include "Tabela_Verdade.h"

extern Lista * exp_gama;

int logical_consequence(int **tabela, int rows, int columns, Lista *gama, char *B) {
    Lista *head = gama;
    int tam = tam_list(gama);
    int *gama_positions = (int*)malloc(sizeof(int) * tam);
    int *lines = (int*)malloc(sizeof(int) * tam);
    int B_position = busca_pos_sub(B);
    int i, j;
    int aux = 0;
    int vet_test[rows];
    int **gama_lines = (int **) malloc(sizeof(int*) * tam);

    for(i = 0; i<tam; i++){
        gama_lines[i] = malloc(sizeof(int)*rows);
    }

    for(i=0; i < tam; i++) {
        gama_positions[i] = busca_pos_sub(gama -> sub);
        gama = gama -> prox;
    }
    
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
            return 0;
        }
    }
    
    return 1;
}