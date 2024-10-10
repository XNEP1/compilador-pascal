#include "Symbol.h"

#include <stdlib.h>
#include <string.h>

#include "Types.h"
#include "genericVec.h"

#ifndef NULL
#define NULL 0
#endif

// Implementa as funções para um vector de Symbol
// (new, destroy, pop, push)
IMPL_VEC(Vec_Symbol, Symbol)


// Aloca e insere um simbolo de variavel e seus atributos na tabela de simbolos
Symbol *insert_var_sybTable(Vec_Symbol *sybTable, char *ident, const int var_lex_level, const int offset) {
    Symbol s;
    s.ident = ident;
    s.category = CAT_VAR;
    s.lex_level = var_lex_level;
    s.atributes.var_attr.offset = offset;
    // tipo ainda desconhecido.
    Vec_Symbol_push(sybTable, s);
    return &sybTable->data[sybTable->size-1];
}

Symbol *insert_par_sybTable(Vec_Symbol *sybTable, char *ident, const int par_lex_level, const int offset) {
    Symbol s;
    s.ident = ident;
    s.category = CAT_VAR;
    s.lex_level = par_lex_level;
    s.atributes.param_attr.offset = offset;
    // tipo ainda desconhecido.
    Vec_Symbol_push(sybTable, s);
    return &sybTable->data[sybTable->size-1];
}


Symbol *insert_proc_sybTable(Vec_Symbol *sybTable, char *ident, int proc_lex_level, const char *rotulo, int num_parameters){
    Symbol s;
    s.ident = ident;
    s.category = CAT_PROC;
    s.lex_level = proc_lex_level;
    s.atributes.proc_attr.rotulo = rotulo;
    s.atributes.proc_attr.num_parameters = num_parameters;
    s.atributes.proc_attr.tipos_parametros = Vec_TypeID_new(10);
    // tipo ainda desconhecido.
    Vec_Symbol_push(sybTable, s);
    return &sybTable->data[sybTable->size-1];
}

// Retorna um ptr pro simbolo com o ident presente na tabela de simbolos
Symbol *find_syb(Vec_Symbol *sybTable, const char *ident) {
    for (int i = 0; i < sybTable->size; i++) {
        if (strcmp(sybTable->data[i].ident, ident) == 0)
            return &(sybTable->data[i]);
    }
    return NULL;
}
