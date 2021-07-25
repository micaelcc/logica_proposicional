#include "Lista.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Tabela_Verdade.h"
#include "Subformulas.h"

int complexidade = 0;
extern Lista *subf;

void tabela_preenche_atoms(int **tabela, int rows, int columns){
    int i,j;

    int num_atom = num_atoms(subf);

    int coeficiente = potencia(2, 0);
    

    for(j = 0; j<num_atom; j++, coeficiente = potencia(2, j)){

        for(i=0; i<rows; i+=coeficiente){
            int k;
            if(i+coeficiente < rows){
                for(k = i; k < i+coeficiente; k++){
                    tabela[k][j] = 1;
                }
                i = i +coeficiente;
            }
            
        }
        
    }

}

void tabela_imprime(int **tabela, int rows, int columns){
    int i,j;

    Lista * p;
    Lista * aux;
    Lista * l;

    for(p=subf; p != NULL; p=p->prox){
        if(strstr(p->sub, "-"))
            printf(" | %s|  ", p->sub);
        else
            printf(" |%s|  ", p->sub);

        aux = p;
    }

    printf("\n\n");


    for(i=0; i<rows; i++, puts(""))
        for(l = subf, j = 0; j<columns; j++, l = l->prox){
            if(j >= num_atoms(subf)){           
                int x = strlen(l->sub);

                char c = ' ';
                printf(" |%*c%d%*c|  ", x/2, c, tabela[i][j], x/2, c);
            }
            else
                printf(" |%d|  ", tabela[i][j]);
        }
}

int busca_pos_sub(char *str){
    Lista *p;
    int i;

    for(p=subf, i = 0; p!=NULL; i++, p=p->prox){
        if(strcmp(p->sub, str) == 0){
            return i;
        }
    }

    return -1;
}

void tabela_resolve(int **tabela, int rows, int columns){
    int i,j;

    Lista *aux;
    Lista *p;

    int tam_atoms = num_atoms(subf);


    //Posiciona ponteiro onde começa as subformulas compostas
    for(j=0, p = subf; j < tam_atoms; j++){
            p=p->prox;
    }

    
    //(((p > q) & r) # s)
    char *A, *B, *op;

    //passa por cada coluna
    for(j = num_atoms(subf); j < columns; p=p->prox, j++){
        if(strlen(p->sub) > 1){
            
            A = malloc(sizeof(char) * (strlen(p->sub)+1));
            B = malloc(sizeof(char) * (strlen(p->sub)+1));
            op = malloc(sizeof(char) * (strlen(p->sub)+1));

            separa_formula(p->sub, A, B, op); 
        }
        
        int pos_A = busca_pos_sub(A);
        
        int pos_B = busca_pos_sub(B);

        for(i = 0; i < rows; i++){
            int value_A = tabela[i][pos_A];
            int value_B = -1;

            if(pos_B != -1)
                value_B = tabela[i][pos_B];

            char op_char = op[0];
            switch(op_char){
                case '&': tabela[i][j] = value_A & value_B; break;
                case '#': tabela[i][j] = value_A || value_B; break;
                case '-': tabela[i][j] = !value_A; break;
                case '>': tabela[i][j] = !value_A || value_B; break;
            }
        }
    }
}

void exp_classification(int **tabela, int rows, int columns) {
    int i;
    int isTautology = 0, isFalseble = 0;

    for(i=0; i<rows; i++){
        if(tabela[i][columns-1] == 1){
            isTautology++;
        }else{
            isFalseble++;
        }
    }
    printf("\nI = %d | Taut = %d\n", i, isTautology);
    if(isTautology > 0 && isTautology < i)
        printf("Satisfazivel.\n");
    
    else if(isTautology == i)
        printf("Valida | Satisfazivel\n");
    
    if(isFalseble > 0 && isFalseble < i)
        printf("Falsificavel.\n");
    
    else if(isFalseble == i)
        printf("Insatisfazivel | falsificavel\n");
}

int potencia(int base, int exp){
    int i;

    if(exp == 0)
        return 1;

    int mult = base;
    for(i=1; i < exp; i++){
        mult = mult*base;
    }

    return mult;
}

int **inicializar_tabela(Lista *subf, int rows, int columns) {
    bubble_sort(subf);

    int **tabela_vdd = malloc(sizeof(int*) * rows);
    int i,j;

    for(i=0; i < rows; i++){
        tabela_vdd[i] = malloc(sizeof(int) * columns);
    }
    
    for(i=0; i<rows; i++)
        for(j = 0; j<columns; j++)
            tabela_vdd[i][j] = 0;
        
    tabela_preenche_atoms(tabela_vdd, rows, columns);

    tabela_resolve(tabela_vdd, rows, columns);


    return tabela_vdd;
}