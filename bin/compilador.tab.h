/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_BIN_COMPILADOR_TAB_H_INCLUDED
# define YY_YY_BIN_COMPILADOR_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 86 "./src/compilador.y"

#include "Types.h"
DEF_VEC(Vec_String, char*)
DEF_VEC(Vec_Vec_String, Vec_String)

#line 55 "./bin/compilador.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAM = 258,                 /* PROGRAM  */
    VAR = 259,                     /* VAR  */
    LABEL = 260,                   /* LABEL  */
    ARRAY = 261,                   /* ARRAY  */
    TYPE = 262,                    /* TYPE  */
    T_BEGIN = 263,                 /* T_BEGIN  */
    T_END = 264,                   /* T_END  */
    NUMBER = 265,                  /* NUMBER  */
    CASE = 266,                    /* CASE  */
    CONST = 267,                   /* CONST  */
    MOD = 268,                     /* MOD  */
    NOT = 269,                     /* NOT  */
    DOWNTO = 270,                  /* DOWNTO  */
    IF = 271,                      /* IF  */
    THEN = 272,                    /* THEN  */
    ELSE = 273,                    /* ELSE  */
    GOTO = 274,                    /* GOTO  */
    WHILE = 275,                   /* WHILE  */
    UNTIL = 276,                   /* UNTIL  */
    DO = 277,                      /* DO  */
    REPEAT = 278,                  /* REPEAT  */
    T_FILE = 279,                  /* T_FILE  */
    FOR = 280,                     /* FOR  */
    FUNCTION = 281,                /* FUNCTION  */
    PROCEDURE = 282,               /* PROCEDURE  */
    IN = 283,                      /* IN  */
    NIL = 284,                     /* NIL  */
    T_OF = 285,                    /* T_OF  */
    PACKED = 286,                  /* PACKED  */
    RECORD = 287,                  /* RECORD  */
    SET = 288,                     /* SET  */
    T_TO = 289,                    /* T_TO  */
    WITH = 290,                    /* WITH  */
    FORWARD = 291,                 /* FORWARD  */
    SOMA = 292,                    /* SOMA  */
    SUB = 293,                     /* SUB  */
    MUL = 294,                     /* MUL  */
    DIV = 295,                     /* DIV  */
    AND = 296,                     /* AND  */
    OR = 297,                      /* OR  */
    IGUAL = 298,                   /* IGUAL  */
    DIFERENTE = 299,               /* DIFERENTE  */
    MENOR = 300,                   /* MENOR  */
    MENOR_IGUAL = 301,             /* MENOR_IGUAL  */
    MAIOR = 302,                   /* MAIOR  */
    MAIOR_IGUAL = 303,             /* MAIOR_IGUAL  */
    ABRE_PARENTESES = 304,         /* ABRE_PARENTESES  */
    FECHA_PARENTESES = 305,        /* FECHA_PARENTESES  */
    VIRGULA = 306,                 /* VIRGULA  */
    PONTO_E_VIRGULA = 307,         /* PONTO_E_VIRGULA  */
    DOIS_PONTOS = 308,             /* DOIS_PONTOS  */
    PONTO = 309,                   /* PONTO  */
    ABRE_COLCHETES = 310,          /* ABRE_COLCHETES  */
    FECHA_COLCHETES = 311,         /* FECHA_COLCHETES  */
    IDENT = 312,                   /* IDENT  */
    ATRIBUICAO = 313,              /* ATRIBUICAO  */
    LOWER_THAN_ELSE = 314,         /* LOWER_THAN_ELSE  */
    EXPRESSAO_PREC = 315           /* EXPRESSAO_PREC  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 93 "./src/compilador.y"

  int intV;
  double doubleV;
  char* tptr; 
  bool boolV;
  TypeID typeID;
  Vec_TypeID vecType;
  Vec_String vecString;
  yytoken_kind_t tokenType;

#line 143 "./bin/compilador.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_BIN_COMPILADOR_TAB_H_INCLUDED  */
