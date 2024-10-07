#pragma once

#include "Types.h"
#include "genericVec.h"

typedef struct Expression {
    TypeID type;
} Expression;

// Define um vetor para o tipo Expression
DEF_VEC(Vec_Expression, Expression)