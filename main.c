#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include "Subformulas.h"
#include "Verificador.h"
#define LENGTH 1000 

Lista *subf;
int complexidade = 0;

void main(){
    char *str = malloc(sizeof(char) * LENGTH);

    printf("Digite a formula: ");
    scanf(" %[^\n]", str);
  
    if(verify(str)){
        printf("Formula valida!\n\n");

        subf = NULL;
        complexidade = 0;
        sub(str);

        printf("::: Subformulas de %s :::\n\n", str);
        print_list(subf);

        printf("::: Fim :::\n\n", complexidade);
        printf("Complexidade: %d\n\n", complexidade);
    }else{
        printf("Formula invalida.\n");
    }
}