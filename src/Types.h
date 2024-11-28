#pragma once

#include "genericVec.h"

typedef enum types_IDs {
    INVALID = 0,
    INTEGER = 1,
    REF_INTEGER,
    BOOLEAN,
    REF_BOOLEAN,
} TypeID;

// Define um vetor para o tipo TypeID
DEF_VEC(Vec_TypeID, TypeID)

// Verifica se um str é um tipo válido (int...boolean...char...)
TypeID is_type(const char* ident);

// Retorna quantidade de memoria gasta por um enum type.
int type_size(TypeID type);

// Retorna uma str com o nome do tipo.
const char* type_to_str(TypeID type);
