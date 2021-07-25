#include "Lista.h"
#include <stdio.h>
#include "stdlib.h"
#include "string.h"

/* Função para criar Lista */
Lista* create(void){
    return NULL;
}

/* Função para adicionar valor a uma lista */
Lista* add(Lista* l, char *s){
    if(busca(l, s))
        return l;
        
    Lista* no = (Lista*) malloc(sizeof(Lista));
    no-> complexidade = 0;
    no->sub = malloc((strlen(s) + 1) * sizeof(char));
    strcpy(no->sub, s);
    //printf("\nNO -> SUB LINHA 88: %s\n", no -> sub);

    no->prox = l;

    return no;
}

/* Função que imprime os valores de uma lista */
void print_list(Lista *l){
    Lista* p;

    for(p = l; p != NULL; p=p->prox){
        printf("=> %s \n", p->sub);
    }

    printf("\n");
}

/* Busca valor em uma determinada lista, 
   se encontrar o valor, retorna 1. Se não,
   retorna 0. */
int busca(Lista* l, char *s){
    Lista* p;

    for(p = l; p!= NULL; p=p->prox){
        if(strcmp(p->sub, s) == 0)
            return 1;
    }

    return 0;
}

/*
    Função que retorna o tamanho de uma lista
*/
int tam_list(Lista * l){
    Lista * p;

    int tam = 0;

    for(p = l; p != NULL; p = p->prox, tam++);

    return tam;
}

/*
    Função que limpa uma lista
*/

void free_list(Lista *node) {
    Lista *aux;
    while (node != NULL) {
        aux = node;
        node = node -> prox;
        free(aux);
    }
}