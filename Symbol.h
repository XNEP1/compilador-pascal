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
    int label;
    int num_parameters;
    // WIP
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
void insert_var_sybTable(Vec_Symbol *sybTable, char *ident, int var_lex_level);
