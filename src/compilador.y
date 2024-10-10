// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "genericVec.h"
#include "compilador.h"
#include "Symbol.h"

DEF_VEC(Vec_String, char*)
IMPL_VEC(Vec_String, char*)


int num_vars = 0; // Conta o numero de vars alocadas no nivel lexico atual
int lex_level = -1;
int num_rotulos = 0;

// Use e depois devolva para 0
int temp_counter_param = 0;

// Só serve para armazenar temporariamente
// e como meio de nomear e saber o que é cada coisa.
char *rotulo;
char *rotulo_while;
char *rotulo_do;
char *rotulo_endif;
char *rotulo_else;

// Ponteiro auxiliar para armazenar um buffer com uma instrução mepa.
// Após gerar uma instrução, o buffer deve ser liberado.
char* mepaCommand = NULL;

Vec_Symbol sybTable;
Vec_String rotulosStack;

// Prototipos
TypeID gen_carrega_var(const char *ident);
TypeID gen_carrega_numero(const int v);
bool gen_atribuicao(const char *ident, TypeID expressaoTipo);
TypeID gen_operacao(TypeID expressao1, int oper, TypeID expressao2);
void gen_checa_sinal(bool ehNegativo);
char *novo_rotulo();

%}

%code requires {
#include "Types.h"
}

// YYSTYPE union
%union {
  int intV;
  double doubleV;
  char* tptr; 
  bool boolV;
  TypeID typeID; 
  yytoken_kind_t tokenType;
}

// Palavras reservadas
%token PROGRAM VAR LABEL ARRAY TYPE
%token T_BEGIN T_END <intV>NUMBER
%token CASE CONST MOD NOT DOWNTO
%token IF THEN ELSE GOTO WHILE UNTIL DO REPEAT
%token T_FILE FOR FUNCTION PROCEDURE IN NIL T_OF PACKED 
%token RECORD SET T_TO WITH

// Operações
%token <tokenType> SOMA SUB MUL DIV AND OR
%token <tokenType> IGUAL DIFERENTE MENOR MENOR_IGUAL MAIOR MAIOR_IGUAL

// Simbolos/Outros
%token ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token ABRE_COLCHETES FECHA_COLCHETES
%token <tptr>IDENT ATRIBUICAO


%type <tptr> tipo variavel
%type <intV> lista_id_var // quantidade de vars
%type <intV> parametros_formais lista_parametros_formais secao_parametros_formais lista_id_par // qnt de parametros
%type <boolV> sinal // Se for True, consome o sinal e multiplica o termo do lado por -1.
%type <typeID> expressao chamada_funcao
%type <Vec_TypeID> lista_expressoes


%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%left IGUAL DIFERENTE MAIOR MAIOR_IGUAL MENOR MENOR_IGUAL
%left SOMA SUB OR
%left MUL DIV AND
%left NOT
%left EXPRESSAO_PREC

%%

programa:    {
             geraCodigo (NULL, "INPP");
             lex_level++;
             }
             PROGRAM IDENT
             ABRE_PARENTESES lista_id_par FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {geraCodigo (NULL, "PARA");}
;

bloco: {}
       parte_declara_vars
       parte_declara_subrotinas
       {}
       comando_composto
       {lex_level--;}
       ;



parte_declara_vars:  var
;


var: {} VAR declara_vars
   |
   ;

declara_vars: declara_vars declara_var
            | declara_var
;

declara_var: 
            { num_vars = 0; }
            lista_id_var DOIS_PONTOS tipo
            { /* AMEM */
                TypeID varType = is_type($4);
                if (varType == INVALID){
                    fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" não é um tipo válido.", nl, $4);
                    YYERROR;
                }
                
                int qnt_vars = $2;

                // atribui o tipo as variaveis alocadas
                for(int i=sybTable.size-qnt_vars; i<sybTable.size; i++){ 
                    sybTable.data[i].atributes.var_attr.type = varType;
                }

                int amountToAlloc = type_size(varType) * qnt_vars;
                asprintf(&mepaCommand, "AMEM %d", amountToAlloc);
                geraCodigo(NULL, mepaCommand);
                free(mepaCommand);

            }
            PONTO_E_VIRGULA
;

tipo: IDENT {}
;

lista_id_var: lista_id_var VIRGULA IDENT
            { /* insere �ltima vars na tabela de s�mbolos */ 
                insert_var_sybTable(&sybTable, $3, lex_level, num_vars++); // tipo ainda desconhecido.
                $$ = $1 + 1; 
            }
            | IDENT 
            { /* insere vars na tabela de s�mbolos */
                insert_var_sybTable(&sybTable, $1, lex_level, num_vars++); // tipo ainda desconhecido.
                $$ = 1;
            }
            ;

lista_id_par: lista_id_par VIRGULA IDENT
            { // insere os ultimos
                insert_par_sybTable(&sybTable, $3, lex_level, (-4-temp_counter_param++));
                $$ = $1 + 1;
            }
            | IDENT {
                // insere o primeiro parameter na tabela
                insert_par_sybTable(&sybTable, $1, lex_level, (-4-temp_counter_param++));
                $$ = 1;
            }           
            ; 

parte_declara_subrotinas:
                        | parte_declara_subrotinas declaracao_procedimento PONTO_E_VIRGULA
                        | parte_declara_subrotinas declaracao_function PONTO_E_VIRGULA
                        ;

declaracao_procedimento: {lex_level++;} PROCEDURE IDENT parametros_formais
                        {
                            char *rotulo = novo_rotulo();
                            Symbol *proc_syb = insert_proc_sybTable(&sybTable, $3, lex_level, rotulo, $4);
                             
                            for(int i=1; i<=$4; i++){
                                Symbol s=sybTable.data[sybTable.size - i];
                                Vec_TypeID_push(&proc_syb->atributes.proc_attr.tipos_parametros, s.atributes.var_attr.type);
                            }
                            proc_syb->atributes.proc_attr.type = INVALID;
                        }
                        PONTO_E_VIRGULA bloco
                       ;

declaracao_function: {lex_level++;} FUNCTION IDENT parametros_formais DOIS_PONTOS IDENT PONTO_E_VIRGULA bloco
                   ;


parametros_formais: {temp_counter_param = 0;} ABRE_PARENTESES lista_parametros_formais FECHA_PARENTESES
    {$$ = $3;} ;

lista_parametros_formais: secao_parametros_formais
                        | lista_parametros_formais PONTO_E_VIRGULA secao_parametros_formais
                        ;

secao_parametros_formais: VAR lista_id_par DOIS_PONTOS IDENT 
    {
        int qnt_param = $2;
        TypeID paramType = is_type($4);
        if(paramType == INVALID){
            fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" não é um tipo válido.", nl, $4);
            YYERROR;
        }

        for(int i=sybTable.size-qnt_param; i<sybTable.size; i++){ 
            sybTable.data[i].atributes.param_attr.type = paramType;
        }
        $$ = qnt_param;
    }
                        | lista_id_par DOIS_PONTOS IDENT {$$+$1;}
                        | FUNCTION lista_id_par DOIS_PONTOS IDENT {$$=$2;}
                        | PROCEDURE lista_id_par {$$=$2;}
                        ;

atribuicao: IDENT ATRIBUICAO expressao {gen_atribuicao($1, $3);}
          ;

lista_expressoes: expressao
                | lista_expressoes VIRGULA expressao
                ;

expressao: ABRE_PARENTESES expressao FECHA_PARENTESES {$$ = $2;} %prec EXPRESSAO_PREC
         | chamada_funcao                   {/*TODO*/$$ = $1;} %prec EXPRESSAO_PREC
         | sinal expressao                  {$$ = $2; gen_checa_sinal($1);} %prec EXPRESSAO_PREC

         | NOT expressao                    {/*TODO*/$$ = $2;}

         | expressao MUL expressao          {$$ = gen_operacao($1, $2, $3);}
         | expressao DIV expressao          {$$ = gen_operacao($1, $2, $3);}
         | expressao AND expressao          {$$ = gen_operacao($1, $2, $3);}

         | expressao SOMA expressao         {$$ = gen_operacao($1, $2, $3);}
         | expressao SUB expressao          {$$ = gen_operacao($1, $2, $3);}
         | expressao OR expressao           {$$ = gen_operacao($1, $2, $3);}

         | expressao IGUAL expressao        {$$ = gen_operacao($1, $2, $3);}
         | expressao DIFERENTE expressao    {$$ = gen_operacao($1, $2, $3);}
         | expressao MAIOR expressao        {$$ = gen_operacao($1, $2, $3);}
         | expressao MAIOR_IGUAL expressao  {$$ = gen_operacao($1, $2, $3);}
         | expressao MENOR expressao        {$$ = gen_operacao($1, $2, $3);}
         | expressao MENOR_IGUAL expressao  {$$ = gen_operacao($1, $2, $3);}

         | variavel                         { $$ = gen_carrega_var($1); /* TEMPORARIO, FALTA SUPORTE PARA ARRAY */ }
         | NUMBER                           { $$ = gen_carrega_numero($1); }
         ;

sinal: SOMA {$$ = false;}
     | SUB  {$$ = true;}
     ;


variavel: IDENT {$$ = $1;}
        | IDENT ABRE_COLCHETES lista_expressoes FECHA_COLCHETES {$$ = $1;}
        ;

chamada_procedimento: IDENT ABRE_PARENTESES lista_expressoes FECHA_PARENTESES 
                    | IDENT {}
                    ;


// Em pascal, não é obrigatorio o uso de parenteses para chamar uma função.
// Isso cria um problema para o analisar semantico, pois ele não consegue saber
// se é uma chamada de função ou um identificador de variável.
// Isso significa que para toda variável, devemos verificar na tabela de simbolos 
// se não é na verdade uma função. Se for, basta gerar o código para tal.
/*| IDENT */
chamada_funcao: IDENT ABRE_PARENTESES lista_expressoes FECHA_PARENTESES
              ;

desvio: GOTO NUMBER;


if_then: IF expressao 
{
    if($2 != BOOLEAN){
        fprintf(stderr, "Erro ao compilar (linha %d): Expressão não é do tipo booleano.", nl);
        YYERROR;
    }

    rotulo = novo_rotulo();
    Vec_String_push(&rotulosStack, rotulo);
    asprintf(&mepaCommand, "DSVF %s", rotulo);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
}
THEN comando_sem_rotulo 
;

comando_condicional: if_then %prec LOWER_THAN_ELSE
                    {
                        rotulo_endif  = Vec_String_pop(&rotulosStack);
                        geraCodigo(rotulo_endif, "NADA");
                        free(rotulo_endif);
                    }
                   | if_then ELSE 
                   {

                        rotulo_endif  = novo_rotulo();
                        asprintf(&mepaCommand, "DSVS %s", rotulo_endif);
                        geraCodigo(NULL, mepaCommand);
                        free(mepaCommand);

                        rotulo_else = Vec_String_pop(&rotulosStack);
                        geraCodigo(rotulo_else, "NADA");
                        free(rotulo_else);

                        Vec_String_push(&rotulosStack, rotulo_endif);
                   } 
                   comando_sem_rotulo 
                   {
                        rotulo_endif = Vec_String_pop(&rotulosStack);
                        geraCodigo(rotulo_endif, "NADA");
                        free(rotulo_endif);
                   }
                   ;

comando_repititivo: WHILE
{
    rotulo_while = novo_rotulo();
    Vec_String_push(&rotulosStack, rotulo_while);
    geraCodigo(rotulo_while, "NADA");
}
expressao DO 
{
    if($3 != BOOLEAN){
        fprintf(stderr, "Erro ao compilar (linha %d): Expressão não é do tipo booleano.", nl);
        YYERROR;
    }

    rotulo_do = novo_rotulo();
    Vec_String_push(&rotulosStack, rotulo_do);
    asprintf(&mepaCommand, "DSVF %s", rotulo_do);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
} 
comando_sem_rotulo 
{
    rotulo_do = Vec_String_pop(&rotulosStack);
    rotulo_while = Vec_String_pop(&rotulosStack);
    asprintf(&mepaCommand, "DSVS %s", rotulo_while);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);

    geraCodigo(rotulo_do, "NADA");
    free(rotulo_do);
    free(rotulo_while);
}
                  ;

comando_composto: {} T_BEGIN comandos T_END {}
                ;

comandos: comando
        | comandos comando 
        ;

comando: NUMBER comando_sem_rotulo PONTO_E_VIRGULA
       | comando_sem_rotulo PONTO_E_VIRGULA
       ;

comando_sem_rotulo: atribuicao
                  | chamada_procedimento
                  | desvio
                  | comando_composto
                  | comando_condicional
                  | comando_repititivo
                  ;

%%

TypeID gen_carrega_var(const char *ident){
    Symbol* s;
    TypeID returnValue;

    if(strcmp(ident,"true") == 0){
        asprintf(&mepaCommand, "CRCT %d", 1);
        returnValue = BOOLEAN;
    }
    else if(strcmp(ident, "false") == 0){
        asprintf(&mepaCommand, "CRCT %d", 0);
        returnValue = BOOLEAN;
    }
    else if((s = find_syb(&sybTable, ident)) != NULL && lex_level <= s->lex_level){
        asprintf(&mepaCommand, "CRVL %d,%d", s->lex_level, s->atributes.var_attr.offset);
        returnValue = s->atributes.var_attr.type;
    }
    else{
        fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" não declarado.", nl, ident);
        return INVALID;
    }

    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
    return returnValue;
}

TypeID gen_carrega_numero(const int v){
    asprintf(&mepaCommand, "CRCT %d", v);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
    return INTEGER;
}

bool gen_atribuicao(const char *ident, TypeID expressaoTipo){
    // busca na tabela de simbolos e armazena o que estiver no topo da pilha (de execução do MEPA).
    Symbol* s = find_syb(&sybTable, ident);
    if(s == NULL){
        fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" não definido.", nl, ident);
        return false;
    }
    else if(s->category == CAT_VAR)
        asprintf(&mepaCommand, "ARMZ %d,%d", s->lex_level, s->atributes.var_attr.offset);
    else if(s->category == CAT_PAR)
        asprintf(&mepaCommand, "ARMZ %d,%d", s->lex_level, s->atributes.param_attr.offset);
    else if(s->category == CAT_PROC)
        assert(0); // WIP: Ainda não sei oq fazer caso alguem tente atribuir algo ao simbolo de uma função. Pascal suporta isso?
    else{
        fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" não é um simbolo atribuivel.", nl, ident);
        return false;
    }
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
    return true;
}

TypeID gen_operacao(TypeID expressao1, int oper, TypeID expressao2){
    if(expressao1 != expressao2){
        fprintf(stderr, "Erro ao compilar (linha %d): %s e %s não são compatíveis em uma expressão.", nl, type_to_str(expressao1), type_to_str(expressao2));
        return INVALID;
    }

    switch(oper){
        case IGUAL:
            geraCodigo(NULL, "CMIG"); return BOOLEAN;
        case DIFERENTE:
            geraCodigo(NULL, "CMDG"); return BOOLEAN;
        case MAIOR:
            geraCodigo(NULL, "CMMA"); return BOOLEAN;
        case MAIOR_IGUAL:
            geraCodigo(NULL, "CMAG"); return BOOLEAN;
        case MENOR:
            geraCodigo(NULL, "CMME"); return BOOLEAN;
        case MENOR_IGUAL:
            geraCodigo(NULL, "CMEG"); return BOOLEAN;
        case MUL:
            geraCodigo(NULL, "MULT"); return INTEGER;
        case DIV:
            geraCodigo(NULL, "DIVI"); return INTEGER;
        case AND:
            geraCodigo(NULL, "CONJ"); return INTEGER;
        case SOMA:
            geraCodigo(NULL, "SOMA"); return INTEGER;
        case SUB:
            geraCodigo(NULL, "SUBT"); return INTEGER;
        case OR:
            geraCodigo(NULL, "DISJ"); return INTEGER;
        default:
            assert(0);
    }

    fprintf(stderr, "INTERNAL ERROR (gen_operacao)");
    assert(0);
    return INVALID;
}

void gen_checa_sinal(bool ehNegativo){
    if(ehNegativo){
        geraCodigo(NULL, "CRCT -1"); 
        geraCodigo(NULL, "MULT");
    }
}

char *novo_rotulo(){
    char *rotulo; 
    asprintf(&rotulo, "R%d", num_rotulos++);
    return rotulo;
}

int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */
    sybTable = Vec_Symbol_new(100);
    rotulosStack = Vec_String_new(100);

    yyin=fp;
    yyparse();

    return 0;
}
