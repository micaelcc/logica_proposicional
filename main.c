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

extern int complexidade;




void main(){
    char *formula = malloc(sizeof(char) * LENGTH);
    char *exp_B = malloc(sizeof(char) * LENGTH);
    exp_gama = NULL;
    subf = NULL;

    int **tabela_vdd;


    while(1){
        int op = menu_etapa_2();
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
                    printf("Digite a formula: ");
                    scanf(" %[^\n]", exp_B);

                    if(verify(exp_B)) {
                        subf = add(subf, exp_B);
                        sub(exp_B);
                    }else {
                        printf("\nAVISO: Formula invalida!\n");
                    }
                    break;
                case 3:
                    print_list(subf);
                    int n_atoms = num_atoms(subf);
                    int num_lines = potencia(2, n_atoms);
                    int tam_subf = tam_list(subf);

                    tabela_vdd = inicializar_tabela(subf, num_lines, tam_subf);
                    tabela_imprime(tabela_vdd, num_lines, tam_subf);
                    if(logical_consequence(tabela_vdd, num_lines, tam_subf, exp_gama, exp_B)){
                        printf("\nGama |= B\n");
                    }else{
                            printf("\nGama nao |= B\n");
                    }
                    
                    break;
                case 0:
                    return;
                default: printf("Opcao invalida!\n"); break;
            }
        }
    
 
}