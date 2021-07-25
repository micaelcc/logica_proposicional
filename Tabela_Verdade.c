#include "Lista.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "Tabela_Verdade.h"
#include "Subformulas.h"

//Tornando o ponteiro subf "visivel" para todo o codigo
extern Lista *subf;
int complexidade = 0;

/*
* Função que recebe uma tabela, numero de linhas e colunas e
* preenche a parte inicial da tabela verdade, que corresponde
* aos atomos.
*/
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


/*
* Função que recebe uma tabela, numero de linhas e colunas e
* imprime na tela, juntamente as subformulas em ordem de complexidade.
*/
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

/*
* Função que recebe uma string (subformula), e retorna
* a coluna daquela subformula.
*/
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

/*
* Função que resolve a tabela verdade. 
*/

void tabela_resolve(int **tabela, int rows, int columns){
    int i,j;

    Lista *aux;
    Lista *p;

    //Atribui a "tam_atoms" o numero de atomos
    int tam_atoms = num_atoms(subf);


    //Posiciona ponteiro onde começa as subformulas compostas
    for(j=0, p = subf; j < tam_atoms; j++){
            p=p->prox;
    }

    //Ponteiros auxiliares A, B, e op    
    char *A, *B, *op;

    //passa por cada coluna
    for(j = num_atoms(subf); j < columns; p=p->prox, j++){
        //Se a subformula daquela coluna nao for um atomo sozinho
        //separa a formula em <A> <op> <B>
        if(strlen(p->sub) > 1){
            
            A = malloc(sizeof(char) * (strlen(p->sub)+1));
            B = malloc(sizeof(char) * (strlen(p->sub)+1));
            op = malloc(sizeof(char) * (strlen(p->sub)+1));

            separa_formula(p->sub, A, B, op); 
        }
        
        //Posicões das subformulas A e B
        int pos_A = busca_pos_sub(A);
        
        //
        int pos_B = busca_pos_sub(B);

        //Passa por cada linha da tabela
        for(i = 0; i < rows; i++){
            //Pega o valor logico de A
            int value_A = tabela[i][pos_A];
            int value_B = -1;

            //Se B existe na tabela, entao pega seu valor logico
            if(pos_B != -1)
                value_B = tabela[i][pos_B];

            //Atribui o operador a variavel "op_char"
            char op_char = op[0];

            //Switch case para, com base no operador, resolver cada operação
            //utilizando a logica da linguagem C
            switch(op_char){
                case '&': tabela[i][j] = value_A & value_B; break;
                case '#': tabela[i][j] = value_A || value_B; break;
                case '-': tabela[i][j] = !value_A; break;
                case '>': tabela[i][j] = !value_A || value_B; break;
            }
        }
    }
}

/*
* Função que classifica a tabela. Recebe a tabela
* ja resolvida, e mostra qual é a classificação com
* base no número de 1's ou 0's na coluna final.
*/
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
    if(isTautology > 0 && isTautology < i)
        printf("Satisfazivel.\n");
    
    else if(isTautology == i)
        printf("Valida | Satisfazivel\n");
    
    if(isFalseble > 0 && isFalseble < i)
        printf("Falsificavel.\n");
    
    else if(isFalseble == i)
        printf("Insatisfazivel | falsificavel\n");
}

//Funcao simples para calcular potencia
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

/*
* Função que inicializa a tabela, alocando
* dinamicamente a matriz e chamando as funções
* que resolvem a tabela.
*/
int **inicializar_tabela(Lista *subf, int rows, int columns) {
    //Ordena a lista com base na complexidade
    bubble_sort(subf);

    //Alocando cada linha da tabela
    int **tabela_vdd = malloc(sizeof(int*) * rows);

    int i,j;

    //Alocando as colunas de cada linha da tabela
    for(i=0; i < rows; i++){
        tabela_vdd[i] = malloc(sizeof(int) * columns);
    }
    
    //Definindo toda a matriz com 0's
    for(i=0; i<rows; i++)
        for(j = 0; j<columns; j++)
            tabela_vdd[i][j] = 0;
        
    //Chama a função para preencher a parte dos atomos
    tabela_preenche_atoms(tabela_vdd, rows, columns);

    //Chama a função para resolver a tabela
    tabela_resolve(tabela_vdd, rows, columns);

    //Retorna ponteiro para a matriz
    return tabela_vdd;
}
