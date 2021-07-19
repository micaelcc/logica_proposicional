#include <stdio.h>
#include "menu.h"

int menu_etapa_2(){
    puts("\n\n\n::::    Menu Etapa 2    ::::\n");
    puts("[1] Adicionar formula para Gama");
    puts("[2] Adicionar formula B");
    puts("[3] Verificar");
    puts("[0] Sair\n\n");
    
    int op;
    printf("Opcao: ");
    scanf("%d", &op);
    puts("");
    return op;
}

int menu_etapa_1(){
    puts("\n\n\n::::    Menu Etapa 1    ::::\n");
    puts("[1] Verificar formula");
    puts("[2] Subformulas\n\n");

    int op;
    printf("Opcao: ");
    scanf("%d", &op);
    puts("");
    return op;
}

int menu_principal(){
    puts("\n\n\n::::    Menu Principal    ::::\n");
    puts("[1] Etapa 1 (verificador e subformulas)");
    puts("[2] Etapa 2 (tabela verdade e consequencia logica)");
    puts("[0] Exit\n\n");

    int op;
    printf("Opcao: ");
    scanf("%d", &op);
    puts("");
    return op;
}