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

int num_vars = 0; // Conta o numero de vars alocadas no nivel lexico atual
int lex_level = -1;
int num_rotulos = 0;
int exprList_size = 0; // tamanho atual da lista de expressões que está sendo montada.

// Só serve para armazenar temporariamente
// e como meio de nomear e saber o que é cada coisa.
char *rotulo;
char *rotulo_while;
char *rotulo_do;
char *rotulo_endif;
char *rotulo_else;

// Variavel global que armazena o simbolo de um procedimento sendo chamado.
// Serve para lidar com listas de expressões: ter uma referencia para checar os tipos dos parametros
// E para gerar o código correto no caso de parametro por referecia.
// É igual a NULL quando não estamos lidando com geração de código de chamada de procedimento ou
// quando quando a função em questão é especial.
Symbol *callingProc = NULL;

// Pode se tornar true na função setCallingProc.
// Caso seja true, significa que uma função especial (como read ou write) está sendo chamada.
// Faz com que todos os parametros usados na função sejam referencias.
// As funções especiais precisam ter um mecanismo especial para lidar com parametros
// e eu não quero declarar essas duas funções implicitamente.
// Usar todos os parametros não é uma solução eficiente em questão de numero de instruções, porém, é fácil.
// A função gen_special_functions retorna o valor para false.
bool allParamRef_flag = false;

// Ponteiro auxiliar para armazenar um buffer com uma instrução mepa.
// Após gerar uma instrução, o buffer deve ser liberado.
char* mepaCommand = NULL;

Vec_Symbol sybTable;

// Prototipos
TypeID gen_carrega_var(const char *ident);
TypeID gen_carrega_numero(const int v);
void gen_atribuicao(const char *ident, TypeID expressaoTipo);
TypeID gen_operacao(TypeID expressao1, int oper, TypeID expressao2);
TypeID gen_not(TypeID expressao1);
void gen_checa_sinal(bool ehNegativo);
char *novo_rotulo();
int set_param_types(int qnt_param, char *typeIdent, bool isRef);
void gen_amem(int qnt_vars, char *typeIdent);
void gen_if_then(TypeID expressionType);
void gen_if_without_else();
void gen_if_with_else_part1();
void gen_if_with_else_part2();
void gen_while_part1();
void gen_while_part2(TypeID expressionType);
void gen_while_part3();
void gen_declara_procedimento_entrar(char *proc_name, int qnt_param);
void gen_declara_procedimento_retorna(int qnt_param);
void gen_chama_procedimento(char *proc_name, Vec_TypeID expressionType_list);
bool gen_special_functions(char *proc_name, Vec_TypeID expressionType_list);
bool exprShouldBeRef();
void setCallingProc(char *proc_name);
int insertFormalParamInSymbolTable();
void insertParamIdentListInStack(void *paramList, bool isRef);

%}

%code requires {
#include "Types.h"
DEF_VEC(Vec_String, char*)
DEF_VEC(Vec_Vec_String, Vec_String)
}

// YYSTYPE union
%union {
  int intV;
  double doubleV;
  char* tptr; 
  bool boolV;
  TypeID typeID;
  Vec_TypeID vecType;
  Vec_String vecString;
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


%type <tptr> variavel
%type <intV> lista_id_var // quantidade de vars
%type <intV> parametros_formais // qnt de parametros
%type <vecString> montando_lista_id_par lista_id_par // armazena os indentificadores para inserir na tabela de simbolo depois na ordem correta
%type <boolV> sinal // Se for True, consome o sinal e multiplica o termo do lado por -1.
%type <typeID> expressao chamada_funcao
%type <vecType> lista_expressoes
%type <intV> declara_var declara_vars var parte_declara_vars parte_declara_subrotinas

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

bloco: parte_declara_vars
       parte_declara_subrotinas
       {}
       comando_composto
{
    int qnt_mems = $1;
    if(qnt_mems > 0){
        asprintf(&mepaCommand, "DMEM %d", qnt_mems);
        geraCodigo(rotulo, mepaCommand);
        free(mepaCommand);
    }
    for(int i=0; i<$2; i++){
        Symbol s = Vec_Symbol_pop(&sybTable);
        printf("DROP SYMB: subrotina %s\n", s.ident);
    }
    for(int i=0; i<$1; i++){
        Symbol s = Vec_Symbol_pop(&sybTable);
        printf("DROP SYMB: var %s\n", s.ident);
    }
}   
    ;



parte_declara_vars:  var {$$ = $1;}
;


var: VAR declara_vars {$$ = $2;}
   | {$$ = 0;}
   ;

declara_vars: declara_vars declara_var {$$ = $1 + $2;}
            | declara_var {$$ = $1;}
            ;

declara_var: lista_id_var DOIS_PONTOS IDENT {gen_amem($1, $3);} PONTO_E_VIRGULA {$$ = $1;}
           ;

lista_id_var: lista_id_var VIRGULA IDENT
            { /* insere �ltima vars na tabela de s�mbolos */ 
                $$ = $1 + 1;
                insert_var_sybTable(&sybTable, $3, lex_level, $$-1); // tipo ainda desconhecido. 
            }
            | IDENT 
            { /* insere vars na tabela de s�mbolos */
                $$ = 1;
                insert_var_sybTable(&sybTable, $1, lex_level, $$-1); // tipo ainda desconhecido.
            }
            ;

lista_id_par: montando_lista_id_par {$$ = $1;}
            ;

montando_lista_id_par: montando_lista_id_par VIRGULA IDENT
            { // insere os ultimos
                $$ = $1;
                Vec_String_push(&$$, $3);
            }
            | IDENT {
                // insere o primeiro parameter na tabela
                $$ = Vec_String_new(10);
                Vec_String_push(&$$, $1);
            }           
            ; 

parte_declara_subrotinas: {$$ = 0;}
                        | parte_declara_subrotinas declaracao_procedimento PONTO_E_VIRGULA {$$ = $1 + 1;}
                        | parte_declara_subrotinas declaracao_function PONTO_E_VIRGULA {$$ = $1 + 1;}
                        ;

declaracao_procedimento: {lex_level++;} PROCEDURE IDENT parametros_formais {gen_declara_procedimento_entrar($3, $4);}
                         PONTO_E_VIRGULA bloco {gen_declara_procedimento_retorna($4); lex_level--;}
                       ;

declaracao_function: {lex_level++;} FUNCTION IDENT parametros_formais DOIS_PONTOS IDENT PONTO_E_VIRGULA bloco
                   ;

parametros_formais: ABRE_PARENTESES lista_parametros_formais FECHA_PARENTESES {$$ = insertFormalParamInSymbolTable();};

lista_parametros_formais: secao_parametros_formais
                        | lista_parametros_formais PONTO_E_VIRGULA secao_parametros_formais
                        ;

secao_parametros_formais: VAR lista_id_par DOIS_PONTOS IDENT {Vec_String_push(&$2, $4); insertParamIdentListInStack((void*)&$2, true);}
                        | lista_id_par DOIS_PONTOS IDENT {Vec_String_push(&$1, $3); insertParamIdentListInStack((void*)&$1, false);} 
                        | FUNCTION lista_id_par DOIS_PONTOS IDENT {Vec_String_push(&$2, $4); insertParamIdentListInStack((void*)&$2, false);}
//                      | PROCEDURE lista_id_par {$$ = $2;} // TODO Como isso funciona??
                        ;

// secao_parametros_formais: VAR lista_id_par DOIS_PONTOS IDENT {$$ = set_param_types($2, $4, true);}
//                         | lista_id_par DOIS_PONTOS IDENT {$$ = set_param_types($1, $3, false);} 
//                         | FUNCTION lista_id_par DOIS_PONTOS IDENT {$$ = set_param_types($2, $4, false);}
//                         | PROCEDURE lista_id_par {$$ = $2;} // TODO Como isso funciona??
//                         ;

atribuicao: IDENT ATRIBUICAO expressao {gen_atribuicao($1, $3);}
          ;

lista_expressoes: {exprList_size = 1;} expressao {$$ = Vec_TypeID_new(10); Vec_TypeID_push(&$$, $2);}
                | lista_expressoes VIRGULA {exprList_size += 1;} expressao {$$=$1; Vec_TypeID_push(&$$, $4);}
                ;

expressao: ABRE_PARENTESES expressao FECHA_PARENTESES {$$ = $2;} %prec EXPRESSAO_PREC
         | chamada_funcao                   {/*TODO*/$$ = $1;} %prec EXPRESSAO_PREC
         | sinal expressao                  {$$ = $2; gen_checa_sinal($1);} %prec EXPRESSAO_PREC

         | NOT expressao                    {$$ = gen_not($2);}

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

chamada_procedimento: IDENT {setCallingProc($1);} ABRE_PARENTESES lista_expressoes FECHA_PARENTESES {gen_chama_procedimento($1, $4);} {callingProc = NULL; allParamRef_flag = false;} 
                    | IDENT {setCallingProc($1);}{gen_chama_procedimento($1,Vec_TypeID_new(0));} {callingProc = NULL; allParamRef_flag = false;}
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


if_then: IF expressao {gen_if_then($2);} THEN comando_sem_rotulo 
       ;

comando_condicional: if_then %prec LOWER_THAN_ELSE {gen_if_without_else();}
                   | if_then ELSE {gen_if_with_else_part1();} comando_sem_rotulo {gen_if_with_else_part2();}
                   ;

comando_repititivo: WHILE {gen_while_part1();} expressao DO {gen_while_part2($3);} comando_sem_rotulo {gen_while_part3();}
                  ;

comando_composto: T_BEGIN comandos T_END
                ;

comandos: comando
        | comandos PONTO_E_VIRGULA comando 
        ;

comando: NUMBER comando_sem_rotulo
       | comando_sem_rotulo
       ;

comando_sem_rotulo: atribuicao
                  | chamada_procedimento
                  | desvio
                  | comando_composto
                  | comando_condicional
                  | comando_repititivo
                  ;

%%

// ===============
// Segundo bloco de variaveis globais
// Esse é apos o compilador.tab.h
// culpa do bison...

IMPL_VEC(Vec_String, char*)
IMPL_VEC(Vec_Vec_String, Vec_String)

Vec_String rotulosStack;

Vec_Vec_String param_ident_stack;
Vec_bool param_isRef_stack;

// =========================

TypeID gen_carrega_var(const char *ident){
    Symbol* s;
    TypeID returnValue;

    s = find_syb(&sybTable, ident);

    if(exprShouldBeRef() && (strcmp(ident,"true") == 0 || strcmp(ident, "false") == 0)){
        fprintf(stderr, "Erro ao compilar (linha %d): Parametro %d deveria ser uma referencia, mas a expressão não é referenciável.", exprList_size);
        exit(-1);
    }

    if(exprShouldBeRef()){
        asprintf(&mepaCommand, "CREN %d,%d", s->lex_level, s->atributes.var_attr.offset);
        returnValue = s->atributes.var_attr.type;
        goto gen_carrega_var_EXIT;
    }

    if(strcmp(ident,"true") == 0){
        asprintf(&mepaCommand, "CRCT %d", 1);
        returnValue = BOOLEAN;
        goto gen_carrega_var_EXIT;
    }
    else if(strcmp(ident, "false") == 0){
        asprintf(&mepaCommand, "CRCT %d", 0);
        returnValue = BOOLEAN;
        goto gen_carrega_var_EXIT;
    }

    if(s == NULL || lex_level > s->lex_level){
        fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" não declarado. (Nivel lexico Atual = %d)", nl, ident, lex_level);
        exit(-1);
    }

    if(s->category == CAT_VAR || (s->category == CAT_PAR && !s->atributes.param_attr.isRef)){
        asprintf(&mepaCommand, "CRVL %d,%d", s->lex_level, s->atributes.var_attr.offset);
        returnValue = s->atributes.var_attr.type;
        goto gen_carrega_var_EXIT;
    } else { // é um parametro por referencia
        asprintf(&mepaCommand, "CRVI %d,%d", s->lex_level, s->atributes.var_attr.offset);
        returnValue = s->atributes.var_attr.type;
        goto gen_carrega_var_EXIT;
    }

    gen_carrega_var_EXIT:
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
    return returnValue;
}

TypeID gen_carrega_numero(const int v){
    if(exprShouldBeRef()){
        fprintf(stderr, "Erro ao compilar (linha %d): Parametro %d deveria ser uma referencia, mas a expressão não é referenciável.", exprList_size);
        exit(-1);
    }

    asprintf(&mepaCommand, "CRCT %d", v);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
    return INTEGER;
}

void gen_atribuicao(const char *ident, TypeID expressaoTipo){
    // busca na tabela de simbolos e armazena o que estiver no topo da pilha (de execução do MEPA).
    Symbol* s = find_syb(&sybTable, ident);
    if(s == NULL){
        fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" não definido.", nl, ident);
        exit(-1);
    }

    if(s->category == CAT_PROC){
        fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" é um procedimento e não é atribuivel.", nl, ident);
        exit(-1);
    }

    if(s->category == CAT_PAR && s->atributes.param_attr.isRef){
        asprintf(&mepaCommand, "ARMI %d,%d", s->lex_level, s->atributes.param_attr.offset);
    } else if (s->category == CAT_PAR){
        asprintf(&mepaCommand, "ARMZ %d,%d", s->lex_level, s->atributes.param_attr.offset);
    } else if(s->category == CAT_VAR) {
        asprintf(&mepaCommand, "ARMZ %d,%d", s->lex_level, s->atributes.var_attr.offset);
    } else {
        fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" não é um simbolo atribuivel.", nl, ident);
        exit(-1);
    }

    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
}

TypeID gen_operacao(TypeID expressao1, int oper, TypeID expressao2){
    if(expressao1 != expressao2){
        fprintf(stderr, "Erro ao compilar (linha %d): %s e %s não são compatíveis em uma expressão.", nl, type_to_str(expressao1), type_to_str(expressao2));
        exit(-1);
    }

    if(exprShouldBeRef()){
        fprintf(stderr, "Erro ao compilar (linha %d): Parametro %d deveria ser uma referencia, mas a expressão não é referenciável.", exprList_size);
        exit(-1);
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
            break;
    }

    fprintf(stderr, "INTERNAL ERROR (gen_operacao)");
    assert(0);
    return INVALID;
}

TypeID gen_not(TypeID expressao1){
    if(expressao1 != BOOLEAN){
        fprintf(stderr, "Erro ao compilar (linha %d): a operação NOT não pode ser usada em algo que não é uma expressão booleana.", nl);
        exit(-1);
    }

    geraCodigo(NULL, "NEGA");
    return BOOLEAN;
}

void gen_checa_sinal(bool ehNegativo){
    if(ehNegativo){
        geraCodigo(NULL, "INVR"); 
    }
}

void gen_amem(int qnt_vars, char *typeIdent){
    TypeID varType = is_type(typeIdent);
    if (varType == INVALID){
        fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" não é um tipo válido.", nl, typeIdent);
        exit(-1);
    }

    // atribui o tipo as variaveis alocadas
    for(int i=sybTable.size-qnt_vars; i<sybTable.size; i++){ 
        sybTable.data[i].atributes.var_attr.type = varType;
    }

    int amountToAlloc = type_size(varType) * qnt_vars;
    asprintf(&mepaCommand, "AMEM %d", amountToAlloc);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
}

void gen_if_then(TypeID expressionType){
    if(expressionType != BOOLEAN){
        fprintf(stderr, "Erro ao compilar (linha %d): Expressão não é do tipo booleano.", nl);
        exit(-1);
    }

    rotulo = novo_rotulo();
    Vec_String_push(&rotulosStack, rotulo);
    asprintf(&mepaCommand, "DSVF %s", rotulo);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
}

void gen_if_without_else(){
    rotulo_endif  = Vec_String_pop(&rotulosStack);
    geraCodigo(rotulo_endif, "NADA");
    free(rotulo_endif);
}

void gen_if_with_else_part1(){
    rotulo_endif  = novo_rotulo();
    asprintf(&mepaCommand, "DSVS %s", rotulo_endif);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);

    rotulo_else = Vec_String_pop(&rotulosStack);
    geraCodigo(rotulo_else, "NADA");
    free(rotulo_else);

    Vec_String_push(&rotulosStack, rotulo_endif);
}

void gen_if_with_else_part2(){
    rotulo_endif = Vec_String_pop(&rotulosStack);
    geraCodigo(rotulo_endif, "NADA");
    free(rotulo_endif);
}

void gen_while_part1(){
    rotulo_while = novo_rotulo();
    Vec_String_push(&rotulosStack, rotulo_while);
    geraCodigo(rotulo_while, "NADA");
}

void gen_while_part2(TypeID expressionType){
    if(expressionType != BOOLEAN){
        fprintf(stderr, "Erro ao compilar (linha %d): Expressão não é do tipo booleano.", nl);
        exit(-1);
    }
    rotulo_do = novo_rotulo();
    Vec_String_push(&rotulosStack, rotulo_do);
    asprintf(&mepaCommand, "DSVF %s", rotulo_do);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
}

void gen_while_part3(){
    rotulo_do = Vec_String_pop(&rotulosStack);
    rotulo_while = Vec_String_pop(&rotulosStack);
    asprintf(&mepaCommand, "DSVS %s", rotulo_while);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);

    geraCodigo(rotulo_do, "NADA");
    free(rotulo_do);
    free(rotulo_while);
}

bool gen_special_functions(char *proc_name, Vec_TypeID expressionType_list){
    int qnt_param = expressionType_list.size;
    char *tempCommandString;
    if(strcmp(proc_name, "read") == 0){
        
        //asprintf(&mepaCommand, "DMEM %d", qnt_param);
        // geraCodigo(NULL, mepaCommand);
        // free(mepaCommand);

        for(int i=2; i<=qnt_param+1; i++){
            geraCodigo(NULL, "LEIT");
            Symbol s=sybTable.data[sybTable.size - i];
            asprintf(&mepaCommand, "ARMI %d,%d", s.lex_level, s.atributes.param_attr.offset);
            geraCodigo(NULL, mepaCommand);
            free(mepaCommand);
        }
    } else if(strcmp(proc_name, "write") == 0){

        for(int i=0; i<qnt_param; i++){
            geraCodigo(NULL, "IMPR");
        }
    } else 
        return false;

    return true;
}

void gen_declara_procedimento_entrar(char *proc_name, int qnt_param){
    char *rotulo = novo_rotulo();
    Symbol *proc_syb = insert_proc_sybTable(&sybTable, proc_name, lex_level, rotulo, qnt_param);
        
    for(int i=2; i<=qnt_param+1; i++){
        Symbol s=sybTable.data[sybTable.size - i];
        Vec_TypeID_push(&proc_syb->atributes.proc_attr.tipos_parametros, s.atributes.param_attr.type);
        bool paramIsRef = s.atributes.param_attr.isRef;
        Vec_bool_push(&proc_syb->atributes.proc_attr.isRef, paramIsRef);
    }
    proc_syb->atributes.proc_attr.type = INVALID;

    char *rotulo_skip_proc = novo_rotulo();
    Vec_String_push(&rotulosStack, rotulo_skip_proc);
    asprintf(&mepaCommand, "DSVS %s", rotulo_skip_proc);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);   

    asprintf(&mepaCommand, "ENPR %d", lex_level);
    geraCodigo(rotulo, mepaCommand);
    free(mepaCommand);   
}

void gen_declara_procedimento_retorna(int qnt_param){
    asprintf(&mepaCommand, "RTPR %d,%d", lex_level, qnt_param);
    geraCodigo(rotulo, mepaCommand);
    free(mepaCommand);

    char *rotulo_skip_proc = Vec_String_pop(&rotulosStack);
    geraCodigo(rotulo_skip_proc, "NADA");

    Symbol proc_syb = Vec_Symbol_pop(&sybTable);
    for(int i=0; i<qnt_param; i++){
        Symbol s = Vec_Symbol_pop(&sybTable);
        printf("Drop SYMB: param %s\n", s.ident);
    }
    Vec_Symbol_push(&sybTable, proc_syb);
}

void gen_chama_procedimento(char *proc_name, Vec_TypeID expressionType_list){
    if(gen_special_functions(proc_name, expressionType_list))
        return;

    Symbol *s = find_syb(&sybTable, proc_name);
    if(s == NULL || s->category != CAT_PROC){
        fprintf(stderr, "Erro ao compilar (linha %d): Procedimento %s não foi declarado.", nl, proc_name);
        exit(-1);
    }

    int qnt_param = expressionType_list.size;
    int proc_num_param = s->atributes.proc_attr.num_parameters;
    if(qnt_param != proc_num_param){
        fprintf(stderr, "Erro ao compilar (linha %d): O procedimento %s precisa de %d parametros (%d foram passados).", nl, proc_name, proc_num_param, qnt_param);
        exit(-1);
    }
    for(int i=0; i<qnt_param; i++){
        if(expressionType_list.data[i] != s->atributes.proc_attr.tipos_parametros.data[i]){
            fprintf(stderr, "Erro ao compilar (linha %d): o %do parametro do procedimento %s deveria ser do tipo %s (é do tipo %s).\n", nl, i+1, s->ident, type_to_str(s->atributes.proc_attr.tipos_parametros.data[i]),type_to_str(expressionType_list.data[i]));
            exit(-1);
        }
    }

    asprintf(&mepaCommand, "CHPR %s,%d", s->atributes.proc_attr.rotulo,lex_level);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
}

int set_param_types(int qnt_param, char *typeIdent, bool isRef){
    TypeID paramType = is_type(typeIdent);
    if(paramType == INVALID){
        fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" não é um tipo válido.", nl, typeIdent);
        exit(-1);
    }
    
    for(int i=sybTable.size-qnt_param; i<sybTable.size; i++){ 
        if(sybTable.data[i].category == CAT_PAR){
            sybTable.data[i].atributes.param_attr.type = paramType;
            sybTable.data[i].atributes.param_attr.isRef = isRef;
        }
        else if(sybTable.data[i].category == CAT_PROC){ // é function
            sybTable.data[i].atributes.proc_attr.type = paramType;
        }    
    }
    return qnt_param;
}

bool exprShouldBeRef(){
    // É usado na regra de lista de expressões para definir se o código usará carrega ou carrega indiretamente.
    if(callingProc == NULL)
        return false;

    if(allParamRef_flag){
        printf("FLAAAAAAAAAAAAAAAAAAAAAAAAAAAG\n");
        return true;
    }

    int q = callingProc->atributes.proc_attr.isRef.size;

    return callingProc->atributes.proc_attr.isRef.data[exprList_size - 1];
}

int insertFormalParamInSymbolTable(){
    int total_param_qnt = 0;
    int i = 0;
    while(param_ident_stack.size > 0){
        Vec_String list = Vec_Vec_String_pop(&param_ident_stack);
        char *typeIdent = Vec_String_pop(&list);
        int paramQnt = list.size;
        bool isRef = Vec_bool_pop(&param_isRef_stack);
        total_param_qnt += paramQnt;
        while(list.size > 0){
            char *ParamIdent = Vec_String_pop(&list);
            insert_par_sybTable(&sybTable, ParamIdent, lex_level, -4-(i++));
        }
        set_param_types(paramQnt, typeIdent, isRef);
    }
    return total_param_qnt;
}

void insertParamIdentListInStack(void *paramList, bool isRef){
    Vec_String pl = *((Vec_String *)paramList);
    Vec_Vec_String_push(&param_ident_stack, pl);
    Vec_bool_push(&param_isRef_stack, isRef);
    // Se vc está se pergutando qual a utilidade dessa função,
    // é por que o bison não me deixa organizar o arquivo de um jeito
    // que me permita usar param_ident_stack dentro dos blocos de código
    // das regras.
}

void setCallingProc(char *proc_name){
    if(strcmp(proc_name, "read") == 0){
        allParamRef_flag = true;
    } else if(strcmp(proc_name, "write") == 0){
        allParamRef_flag = false;
    } else 
        callingProc = find_syb(&sybTable, proc_name);
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
    param_ident_stack = Vec_Vec_String_new(100);
    param_isRef_stack = Vec_bool_new(100);

    yyin=fp;
    yyparse();

    return 0;
}
