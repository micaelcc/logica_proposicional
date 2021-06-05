
#include "Verificador.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*Função para verificar abertura e
  fechamento de parenteses, exemplo:
  )(p>q)( retorna erro */
int par_verify_open_close(char *exp){
    int i;

    int aux=0;
    for(i=0; exp[i] != '\0'; i++){
        if(exp[i] == '('){
            aux++;
        }

        if(exp[i] == ')'){
            aux--;
        }

        if(aux < 0)
            return 0;
    }

    return 1;

}

/*Função de verificação geral.
  Return 0: Erro*/
int verify(char *exp){

    remove_spaces(exp);

    //Se o número de atomos for diferente do número de conectores
    // binários + 1, erro
    int num_binary_conn = count_binary_conn(exp);

    if(count_atoms(exp) != num_binary_conn + 1)
        return 0;
    
    
    int num_parentesis = count_parentesis(exp);

    //Se count_parentesis retorna -1, erro.
    //Para cada conector, um par de parenteses
    if(num_parentesis == -1 || num_parentesis != num_binary_conn)
        return 0;
    
    int tam_exp = strlen(exp);
    int i;
	
    if(!par_verify_open_close(exp)){
        return 0;
    }


    //Passa por todos os elementos da fórmula
    for(i = 0; exp[i] != '\0' ; i++){

        //Se um elemento não é atomo, não é conector (nem unário, 
        // nem binário), e se não é abre ou fecha parenteses (),
        // logo erro, pois esse caractere não faz parte da sintaxe.
        if(!is_atom(exp[i]) && !is_conector(exp[i]) && 
           exp[i] != '-' && exp[i] != '(' && exp[i] != ')' ) {
            printf("\n333\n");
            return 0;
        }
        

        //Se o elemento é conector unário
        if(exp[i] == '-'){

            if(i > 0 && exp[i-1] != '(' && !is_conector(exp[i-1])) 
                return 0;
            
            else if(i < tam_exp - 1 &&  exp[i+1] != '(' && !is_atom(exp[i+1]))
                return 0;
            
            else if(i < tam_exp - 1 && (is_conector(exp[i+1]) || exp[i+1] == ')'))
                return 0;
            
        }

        //Se o elemento é um atomo
        if(is_atom(exp[i])){
            if(i > 0 && exp[i-1] != '(' && !is_conector(exp[i-1]) && exp[i-1] != '-')
                return 0;
            
            else if(i < tam_exp - 1 && exp[i+1] != ')' && !is_conector(exp[i+1]))
                return 0;
            
            else if(tam_exp == 1)
                return 1;

        }

        //Se o elemento é um conector (binario)
        if(is_conector(exp[i])){
            if(i > 0 && !is_atom(exp[i-1]) && exp[i-1] != ')')
                return 0;
            
            else if(i < tam_exp -1 && !is_atom(exp[i+1]) && exp[i+1] != '(' && exp[i+1] != '-')
                return 0;
            
        }
        
    }
    
    //Se não houver erros, tudo ok com a formula.
    return 1;
        
}

/*Função que retorna se um caractere é 
  atomo ou nao.*/
int is_atom(char c){
	if(c >= 'a' && c <= 'z')
		return 1;
	return 0;
}

/*Função que retorna de um caractere é
  conector (binario)ou não.*/
int is_conector(char c){
	if(c == '#' || c == '&' || c == '>')
		return 1;
	
	return 0;
}


/*Função que remove espaços de uma expressao,
  evitando alguns erros aleatórios.*/
void remove_spaces(char *exp){
    int i,j;

    for(i = 0; exp[i] != '\0'; i++)
        if(exp[i] == ' '){
            for(j = i; exp[j] != '\0'; j++)
                exp[j] = exp[j+1];
            
            exp[j] = '\0';
            i--;
        }
    
}

/* Função que retorna o número de conectores
   binários em uma expressao. */
int count_binary_conn(char *exp){
    int num_conn = 0;

    int tam_exp = strlen(exp);

    char *last = &exp[tam_exp];
    char *i;

    for(i = exp; i < last; i++)
        if(is_conector(*i))
            num_conn++;
        
    
    return num_conn;
    
}

/* Função que retorna o número de parenteses
  na expressao, ou -1 em caso de erro. Exemplo:
  Numero de ocorrencias de '(' diferentes de ')' */
int count_parentesis(char *exp){
    int num_open = 0;
    int num_close = 0;
    int tam_exp = strlen(exp);

    char *last = &exp[tam_exp];
    char *i;

    for(i = exp; i < last; i++)
        if(*i == '(')
            num_open++;
        else if(*i == ')' && num_open == 0)
            return -1;
        else if(*i == ')')
            num_close++;
    
    return (num_close == num_open) ? num_close : -1;
    
}

//Função que retorna o número de atomos em uma
//expressão. Atomos = {'a' .. 'z'}
int count_atoms(char *exp){
    int num_atoms = 0;
    int tam_exp = strlen(exp);

    char *last = &exp[tam_exp];
    char *i;

    for(i = exp; i < last; i++)
        if(is_atom(*i))
            num_atoms++;
    
    return num_atoms;
} 