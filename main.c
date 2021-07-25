#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include "Subformulas.h"
#include "Verificador.h"
#include "Consequencia_Logica.h"
#include "Tabela_Verdade.h"
#include "menu.h"

#define LENGTH 1000 

Lista *subf;
Lista *exp_gama;


void main(){
    //Ponteiros para formula e exp_A
    char *formula = malloc(sizeof(char) * LENGTH);
    char *exp_A = malloc(sizeof(char) * LENGTH);

    exp_gama = NULL;
    subf = NULL;

    int n_atoms;
    int num_lines;
    int tam_subf;

    int **tabela_vdd;

    //Chama o menu principal, e obtem uma opção
    int op = menu_principal();

    if(op == 1) {
        while(1) {
            printf("\nDigite a formula: ");
            scanf(" %[^\n]", formula);

            if(verify(formula)) {
                sub(formula);
                att_complexidade(subf);
                bubble_sort(subf);

                n_atoms = num_atoms(subf);
                num_lines = potencia(2, n_atoms);
                tam_subf = tam_list(subf);

                printf("\n::::    Tabela Verdade    ::::\n");
                tabela_vdd = inicializar_tabela(subf, num_lines, tam_subf);
                tabela_imprime(tabela_vdd, num_lines, tam_subf);
                printf("\nClassificacao da formula: ");
                exp_classification(tabela_vdd, num_lines, tam_subf);
                free_list(subf);
                subf = NULL;
            }else {
                printf("\n\n**** AVISO: Formula Invalida! ****\n\n");
            }
        }
    }else if(op == 2) {
        while(1){
        op = menu_2();
        switch(op){
            case 1: 
                printf("Digite uma formula para o conjunto GAMA: ");
                scanf(" %[^\n]", formula);
                    
                if(verify(formula)) {
                        exp_gama = add(exp_gama, formula);
                        sub(exp_gama -> sub);
                    }else {
                        printf("\nAVISO: Formula invalida!\n");
                    }
                    break;
                    
            case 2:
                printf("Digite a formula A: ");
                scanf(" %[^\n]", exp_A);

                if(verify(exp_A)) {
                    subf = add(subf, exp_A);
                    sub(exp_A);
                }else {
                    printf("\n\n**** AVISO: Formula invalida! ****\n\n");
                }
                break;
            case 3:
                n_atoms = num_atoms(subf);
                num_lines = potencia(2, n_atoms);
                tam_subf = tam_list(subf);
                att_complexidade(subf);
                
                printf("\nConjunto GAMA: ");
                print_list(exp_gama);
                printf("GAMA |= %s ?\n\n", exp_A);

                tabela_vdd = inicializar_tabela(subf, num_lines, tam_subf);
                tabela_imprime(tabela_vdd, num_lines, tam_subf);
                if(logical_consequence(tabela_vdd, num_lines, tam_subf, exp_gama, exp_A)){
                    printf("\nGama |= A\n");
                    printf("Portanto, %s e consequencia logica\n", exp_A);
                }else{
                    printf("\nGama nao |= A\n");
                    printf("%s nao e consequencia logica\n", exp_A);
                }
                free_list(exp_gama);
                free_list(subf);
                exp_gama = NULL;
                subf = NULL;
                break;
            case 0:
                return;
            default: printf("Opcao invalida!\n"); break;
            }
        }
    }
}