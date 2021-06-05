#include "Lista.h"
#include "Subformulas.h"
#include "Verificador.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

extern Lista *subf;
extern int complexidade;

/*Função recebe caractere
  e retorna string com caractere
*/
char * char2str(char c){
    char *p = malloc(2*sizeof(char));

    p[0] = c;
    p[1] = '\0';

    return p;
}

/*Função que calcula as subformulas
  de forma recursiva.
*/
void sub (char *exp){
    //Adiconar a lista se já não estiver na lista
    subf = add(subf,exp);

    int tam_exp = strlen(exp);

    char *A = malloc(tam_exp*sizeof(char));
    char *B = malloc(tam_exp*sizeof(char));

    A[0] = '\0';
    B[0] = '\0';

    //caso base
    if (tam_exp == 1 && is_atom(exp[0])){
        complexidade++;
        return;
    }

    //Casos gerais (Quebrar a string) -(a&b)
    if (exp[0] == '-'){
        if (is_atom(exp[1])){
            char *var_temp = char2str(exp[1]);

            strcat(A,var_temp);

            char *temp = part_of_str(exp, 3, tam_exp-1);
            strcat(B, temp);

        }
        if (exp[1] == '('){
            int posi = find_closing_parentheses(exp,1);

            char *tempA = part_of_str(exp, 1, posi);
            char *tempB = part_of_str(exp, posi+2, tam_exp-1);

            strcat(A, tempA);
            strcat(B, tempB);

        }
    }
    
    if (exp[0] == '('){
        if (exp[1] == '('){
            int posi = find_closing_parentheses(exp,1);

            char *tempA = part_of_str(exp, 1, posi);
            char *tempB = part_of_str(exp, posi+2, tam_exp-2);

            strcat(A, tempA);
            strcat(B, tempB);
        }
        if (is_atom(exp[1])){
            char *var_temp = char2str(exp[1]);
            strcat(A,var_temp);

            char *temp = part_of_str(exp, 3, tam_exp-2);
            strcat(B, temp);
        }
        if (exp[1] == '-'){
            if (is_atom(exp[2])){
                char *var_temp = part_of_str(exp, 1, 2);

                strcat(A,var_temp);

                char *temp = part_of_str(exp, 4, tam_exp-2);
                
                strcat(B, temp);
            }
            if (exp[2] == '('){
                int posi = find_closing_parentheses(exp,2);
                
                char *tempA = part_of_str(exp, 1, posi);
                char *tempB = part_of_str(exp, posi+2, tam_exp-2);

                strcat(A, tempA);
                strcat(B, tempB);
            }
        }
    }

   //Chamar a recursão
   complexidade ++;

   if (!(strcmp(A,"")==0))
       sub(A);
   if(!(strcmp(B,"")==0))
       sub(B);
   
}

/* Função que, dado uma expressao, e uma posição
   que contenha a abertura de um parenteses '(',
   retorna a posição referente ao fechamento desse
   parenteses. */
int find_closing_parentheses(char* str, int init){
    int i;
    int closing = -1;
    int open=0;
    for(i = init+1; str[i] != '\0'; i++){
        if(str[i] == ')' && open == 0){
            closing = i;
            break;
        }

        if(str[i] == '(')
            open++;
        else if(i > init+1 && str[i] == ')')
            open--;
    }

    return closing;
}

/* Função que, dado uma expressao, e uma posição
   que contenha o fechamento de um parenseses ')',
   retorna a posição referente a abertura desse
   parenteses. */
int find_opening_parentheses(char* str, int final){
    int i;
    int opening = -1;
    int closing=0;

    for(i = final-1; i >= 0 ; i--){
        if(str[i] == '(' && closing == 0){
            opening = i;
            break;
        }

        if(str[i] == ')')
            closing++;
        else if(i < final-1 && str[i] == '(')
            closing--;
    }

    return opening;
}

/* Função que recebe uma string, e dois pontos
   init e final. Retorna uma string que inicia na
   posição init e finaliza em final. */
char * part_of_str(char *str, int init, int final){
    const int TAM = 1+final-init;

    char *part = malloc(sizeof(char) * (TAM+1));
    int cont = 0;
    int i;

    for(i = init; i <= final; i++, cont++)
        part[cont] = str[i];

    part[cont] = '\0';

    return part;
}
