#include "Types.h"

#include <stdlib.h>
#include <string.h>

#include "genericVec.h"

// Implementa as funções para um vector de TypeID
// (new, destroy, pop, push)
IMPL_VEC(Vec_TypeID, TypeID)

// Verifica se um str é um tipo válido (int...boolean...char...)
TypeID is_type(const char* ident) {
    if (strcmp(ident, "integer") == 0)
        return INTEGER;
    if (strcmp(ident, "boolean") == 0)
        return BOOLEAN;
    // if(strcmp(ident,"real") == 0)
    //     return REAL;
    // if(strcmp(ident,"char") == 0)
    //     return CHAR;
    // if(strcmp(ident,"string") == 0)
    //     return STRING;

    return INVALID;
}

// Retorna quantidade de memoria gasta por um enum type.
int type_size(TypeID type) {
    switch (type) {
    case INTEGER:
    case BOOLEAN:
        return 1;
    default:
        assert(0);
    }
}

// Retorna uma str com o nome do tipo.
const char* type_to_str(TypeID type) {
    switch (type) {
    case INTEGER:
        return "Integer";
    case BOOLEAN:
        return "Boolean";
    default:
        assert(0);
    }
}
