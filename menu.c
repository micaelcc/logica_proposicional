#include <stdio.h>
#include "menu.h"

//Menu da etapa 2
int menu_2(){
    puts("\n\n\n::::    Consequencia Logica    ::::\n");
    puts("[1] Adicionar formula para Gama");
    puts("[2] Adicionar formula A");
    puts("[3] Verificar");
    puts("[0] Sair\n\n");
    
    int op;
    printf("Opcao: ");
    scanf("%d", &op);
    puts("");
    return op;
}

//Função de menu principal
int menu_principal(){
    puts("\n\n\n::::    Menu Principal    ::::\n");
    puts("[1] Tabela Verdade");
    puts("[2] Consequencia Logica");
    puts("[0] Exit\n\n");

    int op;
    printf("Opcao: ");
    scanf("%d", &op);
    puts("");
    return op;
}