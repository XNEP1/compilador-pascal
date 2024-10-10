#pragma once

#include "Types.h"
#include "genericVec.h"


enum categories {
    CAT_VAR,
    CAT_PAR,
    CAT_PROC,
};

typedef struct AtributeVar {
    TypeID type;
    int offset;
} AtributeVar;

typedef struct AtributeParameter {
    TypeID type;
    int offset;
    int reference;  // WIP
} AtributeParameter;

typedef struct AtributeProcedure {
    TypeID type; // Só é usado em funções. É INVALID in procedimentos.
    const char *rotulo;
    int num_parameters;
    Vec_TypeID tipos_parametros;
    // falta um vec de mecanismo de passagem dos parameters
} AtributeProcedure;

typedef union Atributes {
    AtributeVar var_attr;
    AtributeParameter param_attr;
    AtributeProcedure proc_attr;
} Atributes;

typedef struct Symbol {
    char *ident;
    int category;
    int lex_level;
    Atributes atributes;
} Symbol;

// Define um vetor para o tipo Symbol
DEF_VEC(Vec_Symbol, Symbol)

// Retorna um ptr pro simbolo com o ident presente na tabela de simbolos
Symbol *find_syb(Vec_Symbol *sybTable, const char *ident);

// Aloca e insere um simbolo de variavel e seus atributos na tabela de simbolos
Symbol *insert_var_sybTable(Vec_Symbol *sybTable, char *ident, int var_lex_level, int offset);

// Aloca e insere um simbolo de parametro e seus atributos na tabela de simbolos
Symbol *insert_par_sybTable(Vec_Symbol *sybTable, char *ident, int par_lex_level, int offset);

// Aloca e insere um simbolo de nome de função/procedimento na tabela de simbolos
Symbol *insert_proc_sybTable(Vec_Symbol *sybTable, char *ident, int proc_lex_level, const char *rotulo, int num_parameters);
