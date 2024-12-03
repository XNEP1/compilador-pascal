/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "./src/compilador.y"

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


#line 145 "./bin/compilador.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "compilador.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
  YYSYMBOL_LABEL = 5,                      /* LABEL  */
  YYSYMBOL_ARRAY = 6,                      /* ARRAY  */
  YYSYMBOL_TYPE = 7,                       /* TYPE  */
  YYSYMBOL_T_BEGIN = 8,                    /* T_BEGIN  */
  YYSYMBOL_T_END = 9,                      /* T_END  */
  YYSYMBOL_NUMBER = 10,                    /* NUMBER  */
  YYSYMBOL_CASE = 11,                      /* CASE  */
  YYSYMBOL_CONST = 12,                     /* CONST  */
  YYSYMBOL_MOD = 13,                       /* MOD  */
  YYSYMBOL_NOT = 14,                       /* NOT  */
  YYSYMBOL_DOWNTO = 15,                    /* DOWNTO  */
  YYSYMBOL_IF = 16,                        /* IF  */
  YYSYMBOL_THEN = 17,                      /* THEN  */
  YYSYMBOL_ELSE = 18,                      /* ELSE  */
  YYSYMBOL_GOTO = 19,                      /* GOTO  */
  YYSYMBOL_WHILE = 20,                     /* WHILE  */
  YYSYMBOL_UNTIL = 21,                     /* UNTIL  */
  YYSYMBOL_DO = 22,                        /* DO  */
  YYSYMBOL_REPEAT = 23,                    /* REPEAT  */
  YYSYMBOL_T_FILE = 24,                    /* T_FILE  */
  YYSYMBOL_FOR = 25,                       /* FOR  */
  YYSYMBOL_FUNCTION = 26,                  /* FUNCTION  */
  YYSYMBOL_PROCEDURE = 27,                 /* PROCEDURE  */
  YYSYMBOL_IN = 28,                        /* IN  */
  YYSYMBOL_NIL = 29,                       /* NIL  */
  YYSYMBOL_T_OF = 30,                      /* T_OF  */
  YYSYMBOL_PACKED = 31,                    /* PACKED  */
  YYSYMBOL_RECORD = 32,                    /* RECORD  */
  YYSYMBOL_SET = 33,                       /* SET  */
  YYSYMBOL_T_TO = 34,                      /* T_TO  */
  YYSYMBOL_WITH = 35,                      /* WITH  */
  YYSYMBOL_SOMA = 36,                      /* SOMA  */
  YYSYMBOL_SUB = 37,                       /* SUB  */
  YYSYMBOL_MUL = 38,                       /* MUL  */
  YYSYMBOL_DIV = 39,                       /* DIV  */
  YYSYMBOL_AND = 40,                       /* AND  */
  YYSYMBOL_OR = 41,                        /* OR  */
  YYSYMBOL_IGUAL = 42,                     /* IGUAL  */
  YYSYMBOL_DIFERENTE = 43,                 /* DIFERENTE  */
  YYSYMBOL_MENOR = 44,                     /* MENOR  */
  YYSYMBOL_MENOR_IGUAL = 45,               /* MENOR_IGUAL  */
  YYSYMBOL_MAIOR = 46,                     /* MAIOR  */
  YYSYMBOL_MAIOR_IGUAL = 47,               /* MAIOR_IGUAL  */
  YYSYMBOL_ABRE_PARENTESES = 48,           /* ABRE_PARENTESES  */
  YYSYMBOL_FECHA_PARENTESES = 49,          /* FECHA_PARENTESES  */
  YYSYMBOL_VIRGULA = 50,                   /* VIRGULA  */
  YYSYMBOL_PONTO_E_VIRGULA = 51,           /* PONTO_E_VIRGULA  */
  YYSYMBOL_DOIS_PONTOS = 52,               /* DOIS_PONTOS  */
  YYSYMBOL_PONTO = 53,                     /* PONTO  */
  YYSYMBOL_ABRE_COLCHETES = 54,            /* ABRE_COLCHETES  */
  YYSYMBOL_FECHA_COLCHETES = 55,           /* FECHA_COLCHETES  */
  YYSYMBOL_IDENT = 56,                     /* IDENT  */
  YYSYMBOL_ATRIBUICAO = 57,                /* ATRIBUICAO  */
  YYSYMBOL_LOWER_THAN_ELSE = 58,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_EXPRESSAO_PREC = 59,            /* EXPRESSAO_PREC  */
  YYSYMBOL_YYACCEPT = 60,                  /* $accept  */
  YYSYMBOL_programa = 61,                  /* programa  */
  YYSYMBOL_62_1 = 62,                      /* $@1  */
  YYSYMBOL_bloco = 63,                     /* bloco  */
  YYSYMBOL_64_2 = 64,                      /* $@2  */
  YYSYMBOL_parte_declara_vars = 65,        /* parte_declara_vars  */
  YYSYMBOL_var = 66,                       /* var  */
  YYSYMBOL_declara_vars = 67,              /* declara_vars  */
  YYSYMBOL_declara_var = 68,               /* declara_var  */
  YYSYMBOL_69_3 = 69,                      /* $@3  */
  YYSYMBOL_lista_id_var = 70,              /* lista_id_var  */
  YYSYMBOL_lista_id_par = 71,              /* lista_id_par  */
  YYSYMBOL_montando_lista_id_par = 72,     /* montando_lista_id_par  */
  YYSYMBOL_parte_declara_subrotinas = 73,  /* parte_declara_subrotinas  */
  YYSYMBOL_declaracao_procedimento = 74,   /* declaracao_procedimento  */
  YYSYMBOL_75_4 = 75,                      /* $@4  */
  YYSYMBOL_76_5 = 76,                      /* $@5  */
  YYSYMBOL_declaracao_function = 77,       /* declaracao_function  */
  YYSYMBOL_78_6 = 78,                      /* $@6  */
  YYSYMBOL_parametros_formais = 79,        /* parametros_formais  */
  YYSYMBOL_lista_parametros_formais = 80,  /* lista_parametros_formais  */
  YYSYMBOL_secao_parametros_formais = 81,  /* secao_parametros_formais  */
  YYSYMBOL_atribuicao = 82,                /* atribuicao  */
  YYSYMBOL_lista_expressoes = 83,          /* lista_expressoes  */
  YYSYMBOL_84_7 = 84,                      /* $@7  */
  YYSYMBOL_85_8 = 85,                      /* $@8  */
  YYSYMBOL_expressao = 86,                 /* expressao  */
  YYSYMBOL_sinal = 87,                     /* sinal  */
  YYSYMBOL_variavel = 88,                  /* variavel  */
  YYSYMBOL_chamada_procedimento = 89,      /* chamada_procedimento  */
  YYSYMBOL_90_9 = 90,                      /* $@9  */
  YYSYMBOL_91_10 = 91,                     /* $@10  */
  YYSYMBOL_92_11 = 92,                     /* $@11  */
  YYSYMBOL_93_12 = 93,                     /* $@12  */
  YYSYMBOL_chamada_funcao = 94,            /* chamada_funcao  */
  YYSYMBOL_desvio = 95,                    /* desvio  */
  YYSYMBOL_if_then = 96,                   /* if_then  */
  YYSYMBOL_97_13 = 97,                     /* $@13  */
  YYSYMBOL_comando_condicional = 98,       /* comando_condicional  */
  YYSYMBOL_99_14 = 99,                     /* $@14  */
  YYSYMBOL_comando_repititivo = 100,       /* comando_repititivo  */
  YYSYMBOL_101_15 = 101,                   /* $@15  */
  YYSYMBOL_102_16 = 102,                   /* $@16  */
  YYSYMBOL_comando_composto = 103,         /* comando_composto  */
  YYSYMBOL_comandos = 104,                 /* comandos  */
  YYSYMBOL_comando = 105,                  /* comando  */
  YYSYMBOL_comando_sem_rotulo = 106        /* comando_sem_rotulo  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   163

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  85
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  159

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   314


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   136,   136,   136,   147,   145,   169,   173,   174,   177,
     178,   181,   181,   184,   189,   196,   199,   204,   211,   212,
     213,   216,   216,   216,   220,   220,   223,   225,   226,   229,
     230,   231,   241,   244,   244,   245,   245,   248,   249,   250,
     252,   254,   255,   256,   258,   259,   260,   262,   263,   264,
     265,   266,   267,   269,   270,   273,   274,   278,   279,   282,
     282,   282,   283,   283,   283,   293,   296,   299,   299,   302,
     303,   303,   306,   306,   306,   309,   312,   313,   316,   317,
     320,   321,   322,   323,   324,   325
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "VAR",
  "LABEL", "ARRAY", "TYPE", "T_BEGIN", "T_END", "NUMBER", "CASE", "CONST",
  "MOD", "NOT", "DOWNTO", "IF", "THEN", "ELSE", "GOTO", "WHILE", "UNTIL",
  "DO", "REPEAT", "T_FILE", "FOR", "FUNCTION", "PROCEDURE", "IN", "NIL",
  "T_OF", "PACKED", "RECORD", "SET", "T_TO", "WITH", "SOMA", "SUB", "MUL",
  "DIV", "AND", "OR", "IGUAL", "DIFERENTE", "MENOR", "MENOR_IGUAL",
  "MAIOR", "MAIOR_IGUAL", "ABRE_PARENTESES", "FECHA_PARENTESES", "VIRGULA",
  "PONTO_E_VIRGULA", "DOIS_PONTOS", "PONTO", "ABRE_COLCHETES",
  "FECHA_COLCHETES", "IDENT", "ATRIBUICAO", "LOWER_THAN_ELSE",
  "EXPRESSAO_PREC", "$accept", "programa", "$@1", "bloco", "$@2",
  "parte_declara_vars", "var", "declara_vars", "declara_var", "$@3",
  "lista_id_var", "lista_id_par", "montando_lista_id_par",
  "parte_declara_subrotinas", "declaracao_procedimento", "$@4", "$@5",
  "declaracao_function", "$@6", "parametros_formais",
  "lista_parametros_formais", "secao_parametros_formais", "atribuicao",
  "lista_expressoes", "$@7", "$@8", "expressao", "sinal", "variavel",
  "chamada_procedimento", "$@9", "$@10", "$@11", "$@12", "chamada_funcao",
  "desvio", "if_then", "$@13", "comando_condicional", "$@14",
  "comando_repititivo", "$@15", "$@16", "comando_composto", "comandos",
  "comando", "comando_sem_rotulo", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-134)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-60)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -134,     7,    11,  -134,   -46,   -23,   -13,  -134,    -3,     8,
      18,    30,    85,  -134,    36,    37,  -134,  -134,  -134,    36,
    -134,   -28,  -134,    40,  -134,    46,    60,    83,    79,   104,
      81,   107,  -134,  -134,     1,  -134,  -134,    78,  -134,    80,
      84,    32,     5,   127,  -134,     2,  -134,  -134,  -134,   120,
    -134,  -134,  -134,    -6,  -134,  -134,    91,    91,  -134,  -134,
    -134,     5,  -134,  -134,     5,     6,    82,     5,  -134,  -134,
    -134,     5,     5,    92,  -134,  -134,  -134,     1,    12,  -134,
      89,  -134,    68,  -134,  -134,     5,     5,     5,     5,     5,
       5,     5,     5,     5,     5,     5,     5,   125,  -134,    34,
      82,  -134,  -134,    32,  -134,   -13,   -13,    93,    -2,  -134,
      95,    87,  -134,    33,     5,   -11,    25,    25,  -134,  -134,
    -134,    25,    58,    58,    58,    58,    58,    58,    32,  -134,
      35,  -134,    96,    97,    88,  -134,    12,    85,    99,  -134,
    -134,    82,  -134,  -134,    32,  -134,    98,   100,  -134,  -134,
    -134,    85,     5,  -134,  -134,  -134,  -134,  -134,    82
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    17,     0,    15,
       0,     0,     8,    16,     0,     0,    18,     6,    14,     7,
      10,     0,     3,     4,     9,     0,     0,     0,     0,     0,
       0,     0,    13,    11,     0,     5,    19,     0,    20,     0,
       0,     0,     0,     0,    72,    62,    80,    81,    82,    69,
      84,    85,    83,     0,    76,    79,     0,     0,    12,    78,
      54,     0,    55,    56,     0,    57,    67,     0,    53,    38,
      66,     0,     0,     0,    63,    70,    75,     0,     0,    22,
       0,    40,     0,    33,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,     0,
      32,    33,    64,     0,    77,     0,     0,     0,     0,    27,
       0,     0,    37,     0,     0,     0,    44,    45,    41,    42,
      43,    46,    47,    48,    51,    52,    49,    50,     0,    73,
       0,    71,     0,     0,     0,    26,     0,     8,     0,    65,
      35,    34,    58,    68,     0,    60,     0,     0,    30,    28,
      23,     8,     0,    74,    61,    29,    31,    25,    36
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -134,  -134,  -134,  -133,  -134,  -134,  -134,  -134,   128,  -134,
    -134,    -5,  -134,  -134,  -134,  -134,  -134,  -134,  -134,    94,
    -134,    16,  -134,   -78,  -134,  -134,   -59,  -134,  -134,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,   126,  -134,    86,   -41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    15,    27,    16,    17,    19,    20,    40,
      21,   107,     9,    23,    28,    29,   110,    30,    31,    79,
     108,   109,    46,   113,   114,   152,    66,    67,    68,    47,
      73,   154,    74,   102,    69,    48,    49,    97,    50,   103,
      51,    71,   144,    52,    53,    54,    55
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      59,     8,    81,    76,   150,    82,   115,     3,    98,    34,
       5,    41,    99,   100,     4,    60,   105,    42,   157,    61,
      43,    44,    25,   130,    26,     6,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   106,   140,
      34,    62,    63,     7,   142,    77,    10,   135,    42,   136,
     -59,    43,    44,    64,    83,   141,   129,    45,    11,    72,
      84,    65,   131,    87,    88,    89,   -24,   -21,     7,    12,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,   139,   140,   145,   140,    13,   143,    45,    14,
      22,    34,    18,   158,    85,    86,    87,    88,    89,    90,
     132,   133,    32,   153,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    33,   112,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      36,    37,    38,    39,    56,    58,    57,    70,    75,    78,
     101,   111,   128,   138,   148,   134,   137,    24,   146,   147,
     151,    80,   149,    35,   155,     0,   156,     0,     0,     0,
       0,     0,     0,   104
};

static const yytype_int16 yycheck[] =
{
      41,     6,    61,     9,   137,    64,    84,     0,    67,     8,
      56,    10,    71,    72,     3,    10,     4,    16,   151,    14,
      19,    20,    50,   101,    52,    48,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    26,    50,
       8,    36,    37,    56,    55,    51,    49,    49,    16,    51,
      48,    19,    20,    48,    48,   114,    22,    56,    50,    57,
      54,    56,   103,    38,    39,    40,    26,    27,    56,    51,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    49,    50,    49,    50,    56,   128,    56,     4,
      53,     8,    56,   152,    36,    37,    38,    39,    40,    41,
     105,   106,    56,   144,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    56,    49,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      51,    27,    51,    26,    56,    51,    56,    10,    18,    48,
      48,    52,    17,    56,    56,    52,    51,    19,    52,    52,
      51,    57,   136,    27,    56,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    61,    62,     0,     3,    56,    48,    56,    71,    72,
      49,    50,    51,    56,     4,    63,    65,    66,    56,    67,
      68,    70,    53,    73,    68,    50,    52,    64,    74,    75,
      77,    78,    56,    56,     8,   103,    51,    27,    51,    26,
      69,    10,    16,    19,    20,    56,    82,    89,    95,    96,
      98,   100,   103,   104,   105,   106,    56,    56,    51,   106,
      10,    14,    36,    37,    48,    56,    86,    87,    88,    94,
      10,   101,    57,    90,    92,    18,     9,    51,    48,    79,
      79,    86,    86,    48,    54,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    97,    86,    86,
      86,    48,    93,    99,   105,     4,    26,    71,    80,    81,
      76,    52,    49,    83,    84,    83,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    17,    22,
      83,   106,    71,    71,    52,    49,    51,    51,    56,    49,
      50,    86,    55,   106,   102,    49,    52,    52,    56,    81,
      63,    51,    85,   106,    91,    56,    56,    63,    86
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    62,    61,    64,    63,    65,    66,    66,    67,
      67,    69,    68,    70,    70,    71,    72,    72,    73,    73,
      73,    75,    76,    74,    78,    77,    79,    80,    80,    81,
      81,    81,    82,    84,    83,    85,    83,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    87,    87,    88,    88,    90,
      91,    89,    92,    93,    89,    94,    95,    97,    96,    98,
      99,    98,   101,   102,   100,   103,   104,   104,   105,   105,
     106,   106,   106,   106,   106,   106
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     0,     4,     1,     2,     0,     2,
       1,     0,     5,     3,     1,     1,     3,     1,     0,     3,
       3,     0,     0,     7,     0,     8,     3,     1,     3,     4,
       3,     4,     3,     0,     2,     0,     4,     3,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     4,     0,
       0,     6,     0,     0,     3,     4,     2,     0,     5,     1,
       0,     4,     0,     0,     6,     3,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 136 "./src/compilador.y"
             {
             geraCodigo (NULL, "INPP");
             lex_level++;
             }
#line 1360 "./bin/compilador.tab.c"
    break;

  case 3: /* programa: $@1 PROGRAM IDENT ABRE_PARENTESES lista_id_par FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO  */
#line 142 "./src/compilador.y"
                         {geraCodigo (NULL, "PARA");}
#line 1366 "./bin/compilador.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 147 "./src/compilador.y"
       {}
#line 1372 "./bin/compilador.tab.c"
    break;

  case 5: /* bloco: parte_declara_vars parte_declara_subrotinas $@2 comando_composto  */
#line 149 "./src/compilador.y"
{
    int qnt_mems = (yyvsp[-3].intV);
    if(qnt_mems > 0){
        asprintf(&mepaCommand, "DMEM %d", qnt_mems);
        geraCodigo(rotulo, mepaCommand);
        free(mepaCommand);
    }
    for(int i=0; i<(yyvsp[-2].intV); i++){
        Symbol s = Vec_Symbol_pop(&sybTable);
        printf("DROP SYMB: subrotina %s\n", s.ident);
    }
    for(int i=0; i<(yyvsp[-3].intV); i++){
        Symbol s = Vec_Symbol_pop(&sybTable);
        printf("DROP SYMB: var %s\n", s.ident);
    }
}
#line 1393 "./bin/compilador.tab.c"
    break;

  case 6: /* parte_declara_vars: var  */
#line 169 "./src/compilador.y"
                         {(yyval.intV) = (yyvsp[0].intV);}
#line 1399 "./bin/compilador.tab.c"
    break;

  case 7: /* var: VAR declara_vars  */
#line 173 "./src/compilador.y"
                      {(yyval.intV) = (yyvsp[0].intV);}
#line 1405 "./bin/compilador.tab.c"
    break;

  case 8: /* var: %empty  */
#line 174 "./src/compilador.y"
     {(yyval.intV) = 0;}
#line 1411 "./bin/compilador.tab.c"
    break;

  case 9: /* declara_vars: declara_vars declara_var  */
#line 177 "./src/compilador.y"
                                       {(yyval.intV) = (yyvsp[-1].intV) + (yyvsp[0].intV);}
#line 1417 "./bin/compilador.tab.c"
    break;

  case 10: /* declara_vars: declara_var  */
#line 178 "./src/compilador.y"
                          {(yyval.intV) = (yyvsp[0].intV);}
#line 1423 "./bin/compilador.tab.c"
    break;

  case 11: /* $@3: %empty  */
#line 181 "./src/compilador.y"
                                            {gen_amem((yyvsp[-2].intV), (yyvsp[0].tptr));}
#line 1429 "./bin/compilador.tab.c"
    break;

  case 12: /* declara_var: lista_id_var DOIS_PONTOS IDENT $@3 PONTO_E_VIRGULA  */
#line 181 "./src/compilador.y"
                                                                                {(yyval.intV) = (yyvsp[-4].intV);}
#line 1435 "./bin/compilador.tab.c"
    break;

  case 13: /* lista_id_var: lista_id_var VIRGULA IDENT  */
#line 185 "./src/compilador.y"
            { /* insere �ltima vars na tabela de s�mbolos */ 
                (yyval.intV) = (yyvsp[-2].intV) + 1;
                insert_var_sybTable(&sybTable, (yyvsp[0].tptr), lex_level, (yyval.intV)-1); // tipo ainda desconhecido. 
            }
#line 1444 "./bin/compilador.tab.c"
    break;

  case 14: /* lista_id_var: IDENT  */
#line 190 "./src/compilador.y"
            { /* insere vars na tabela de s�mbolos */
                (yyval.intV) = 1;
                insert_var_sybTable(&sybTable, (yyvsp[0].tptr), lex_level, (yyval.intV)-1); // tipo ainda desconhecido.
            }
#line 1453 "./bin/compilador.tab.c"
    break;

  case 15: /* lista_id_par: montando_lista_id_par  */
#line 196 "./src/compilador.y"
                                    {(yyval.vecString) = (yyvsp[0].vecString);}
#line 1459 "./bin/compilador.tab.c"
    break;

  case 16: /* montando_lista_id_par: montando_lista_id_par VIRGULA IDENT  */
#line 200 "./src/compilador.y"
            { // insere os ultimos
                (yyval.vecString) = (yyvsp[-2].vecString);
                Vec_String_push(&(yyval.vecString), (yyvsp[0].tptr));
            }
#line 1468 "./bin/compilador.tab.c"
    break;

  case 17: /* montando_lista_id_par: IDENT  */
#line 204 "./src/compilador.y"
                    {
                // insere o primeiro parameter na tabela
                (yyval.vecString) = Vec_String_new(10);
                Vec_String_push(&(yyval.vecString), (yyvsp[0].tptr));
            }
#line 1478 "./bin/compilador.tab.c"
    break;

  case 18: /* parte_declara_subrotinas: %empty  */
#line 211 "./src/compilador.y"
                          {(yyval.intV) = 0;}
#line 1484 "./bin/compilador.tab.c"
    break;

  case 19: /* parte_declara_subrotinas: parte_declara_subrotinas declaracao_procedimento PONTO_E_VIRGULA  */
#line 212 "./src/compilador.y"
                                                                                           {(yyval.intV) = (yyvsp[-2].intV) + 1;}
#line 1490 "./bin/compilador.tab.c"
    break;

  case 20: /* parte_declara_subrotinas: parte_declara_subrotinas declaracao_function PONTO_E_VIRGULA  */
#line 213 "./src/compilador.y"
                                                                                       {(yyval.intV) = (yyvsp[-2].intV) + 1;}
#line 1496 "./bin/compilador.tab.c"
    break;

  case 21: /* $@4: %empty  */
#line 216 "./src/compilador.y"
                         {lex_level++;}
#line 1502 "./bin/compilador.tab.c"
    break;

  case 22: /* $@5: %empty  */
#line 216 "./src/compilador.y"
                                                                           {gen_declara_procedimento_entrar((yyvsp[-1].tptr), (yyvsp[0].intV));}
#line 1508 "./bin/compilador.tab.c"
    break;

  case 23: /* declaracao_procedimento: $@4 PROCEDURE IDENT parametros_formais $@5 PONTO_E_VIRGULA bloco  */
#line 217 "./src/compilador.y"
                                               {gen_declara_procedimento_retorna((yyvsp[-3].intV)); lex_level--;}
#line 1514 "./bin/compilador.tab.c"
    break;

  case 24: /* $@6: %empty  */
#line 220 "./src/compilador.y"
                     {lex_level++;}
#line 1520 "./bin/compilador.tab.c"
    break;

  case 26: /* parametros_formais: ABRE_PARENTESES lista_parametros_formais FECHA_PARENTESES  */
#line 223 "./src/compilador.y"
                                                                              {(yyval.intV) = insertFormalParamInSymbolTable();}
#line 1526 "./bin/compilador.tab.c"
    break;

  case 29: /* secao_parametros_formais: VAR lista_id_par DOIS_PONTOS IDENT  */
#line 229 "./src/compilador.y"
                                                             {Vec_String_push(&(yyvsp[-2].vecString), (yyvsp[0].tptr)); insertParamIdentListInStack((void*)&(yyvsp[-2].vecString), true);}
#line 1532 "./bin/compilador.tab.c"
    break;

  case 30: /* secao_parametros_formais: lista_id_par DOIS_PONTOS IDENT  */
#line 230 "./src/compilador.y"
                                                         {Vec_String_push(&(yyvsp[-2].vecString), (yyvsp[0].tptr)); insertParamIdentListInStack((void*)&(yyvsp[-2].vecString), false);}
#line 1538 "./bin/compilador.tab.c"
    break;

  case 31: /* secao_parametros_formais: FUNCTION lista_id_par DOIS_PONTOS IDENT  */
#line 231 "./src/compilador.y"
                                                                  {Vec_String_push(&(yyvsp[-2].vecString), (yyvsp[0].tptr)); insertParamIdentListInStack((void*)&(yyvsp[-2].vecString), false);}
#line 1544 "./bin/compilador.tab.c"
    break;

  case 32: /* atribuicao: IDENT ATRIBUICAO expressao  */
#line 241 "./src/compilador.y"
                                       {gen_atribuicao((yyvsp[-2].tptr), (yyvsp[0].typeID));}
#line 1550 "./bin/compilador.tab.c"
    break;

  case 33: /* $@7: %empty  */
#line 244 "./src/compilador.y"
                  {exprList_size = 1;}
#line 1556 "./bin/compilador.tab.c"
    break;

  case 34: /* lista_expressoes: $@7 expressao  */
#line 244 "./src/compilador.y"
                                                 {(yyval.vecType) = Vec_TypeID_new(10); Vec_TypeID_push(&(yyval.vecType), (yyvsp[0].typeID));}
#line 1562 "./bin/compilador.tab.c"
    break;

  case 35: /* $@8: %empty  */
#line 245 "./src/compilador.y"
                                           {exprList_size += 1;}
#line 1568 "./bin/compilador.tab.c"
    break;

  case 36: /* lista_expressoes: lista_expressoes VIRGULA $@8 expressao  */
#line 245 "./src/compilador.y"
                                                                           {(yyval.vecType)=(yyvsp[-3].vecType); Vec_TypeID_push(&(yyval.vecType), (yyvsp[0].typeID));}
#line 1574 "./bin/compilador.tab.c"
    break;

  case 37: /* expressao: ABRE_PARENTESES expressao FECHA_PARENTESES  */
#line 248 "./src/compilador.y"
                                                      {(yyval.typeID) = (yyvsp[-1].typeID);}
#line 1580 "./bin/compilador.tab.c"
    break;

  case 38: /* expressao: chamada_funcao  */
#line 249 "./src/compilador.y"
                                            {/*TODO*/(yyval.typeID) = (yyvsp[0].typeID);}
#line 1586 "./bin/compilador.tab.c"
    break;

  case 39: /* expressao: sinal expressao  */
#line 250 "./src/compilador.y"
                                            {(yyval.typeID) = (yyvsp[0].typeID); gen_checa_sinal((yyvsp[-1].boolV));}
#line 1592 "./bin/compilador.tab.c"
    break;

  case 40: /* expressao: NOT expressao  */
#line 252 "./src/compilador.y"
                                            {(yyval.typeID) = gen_not((yyvsp[0].typeID));}
#line 1598 "./bin/compilador.tab.c"
    break;

  case 41: /* expressao: expressao MUL expressao  */
#line 254 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1604 "./bin/compilador.tab.c"
    break;

  case 42: /* expressao: expressao DIV expressao  */
#line 255 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1610 "./bin/compilador.tab.c"
    break;

  case 43: /* expressao: expressao AND expressao  */
#line 256 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1616 "./bin/compilador.tab.c"
    break;

  case 44: /* expressao: expressao SOMA expressao  */
#line 258 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1622 "./bin/compilador.tab.c"
    break;

  case 45: /* expressao: expressao SUB expressao  */
#line 259 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1628 "./bin/compilador.tab.c"
    break;

  case 46: /* expressao: expressao OR expressao  */
#line 260 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1634 "./bin/compilador.tab.c"
    break;

  case 47: /* expressao: expressao IGUAL expressao  */
#line 262 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1640 "./bin/compilador.tab.c"
    break;

  case 48: /* expressao: expressao DIFERENTE expressao  */
#line 263 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1646 "./bin/compilador.tab.c"
    break;

  case 49: /* expressao: expressao MAIOR expressao  */
#line 264 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1652 "./bin/compilador.tab.c"
    break;

  case 50: /* expressao: expressao MAIOR_IGUAL expressao  */
#line 265 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1658 "./bin/compilador.tab.c"
    break;

  case 51: /* expressao: expressao MENOR expressao  */
#line 266 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1664 "./bin/compilador.tab.c"
    break;

  case 52: /* expressao: expressao MENOR_IGUAL expressao  */
#line 267 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1670 "./bin/compilador.tab.c"
    break;

  case 53: /* expressao: variavel  */
#line 269 "./src/compilador.y"
                                            { (yyval.typeID) = gen_carrega_var((yyvsp[0].tptr)); /* TEMPORARIO, FALTA SUPORTE PARA ARRAY */ }
#line 1676 "./bin/compilador.tab.c"
    break;

  case 54: /* expressao: NUMBER  */
#line 270 "./src/compilador.y"
                                            { (yyval.typeID) = gen_carrega_numero((yyvsp[0].intV)); }
#line 1682 "./bin/compilador.tab.c"
    break;

  case 55: /* sinal: SOMA  */
#line 273 "./src/compilador.y"
            {(yyval.boolV) = false;}
#line 1688 "./bin/compilador.tab.c"
    break;

  case 56: /* sinal: SUB  */
#line 274 "./src/compilador.y"
            {(yyval.boolV) = true;}
#line 1694 "./bin/compilador.tab.c"
    break;

  case 57: /* variavel: IDENT  */
#line 278 "./src/compilador.y"
                {(yyval.tptr) = (yyvsp[0].tptr);}
#line 1700 "./bin/compilador.tab.c"
    break;

  case 58: /* variavel: IDENT ABRE_COLCHETES lista_expressoes FECHA_COLCHETES  */
#line 279 "./src/compilador.y"
                                                                {(yyval.tptr) = (yyvsp[-3].tptr);}
#line 1706 "./bin/compilador.tab.c"
    break;

  case 59: /* $@9: %empty  */
#line 282 "./src/compilador.y"
                            {setCallingProc((yyvsp[0].tptr));}
#line 1712 "./bin/compilador.tab.c"
    break;

  case 60: /* $@10: %empty  */
#line 282 "./src/compilador.y"
                                                                                                    {gen_chama_procedimento((yyvsp[-4].tptr), (yyvsp[-1].vecType));}
#line 1718 "./bin/compilador.tab.c"
    break;

  case 61: /* chamada_procedimento: IDENT $@9 ABRE_PARENTESES lista_expressoes FECHA_PARENTESES $@10  */
#line 282 "./src/compilador.y"
                                                                                                                                      {callingProc = NULL; allParamRef_flag = false;}
#line 1724 "./bin/compilador.tab.c"
    break;

  case 62: /* $@11: %empty  */
#line 283 "./src/compilador.y"
                            {setCallingProc((yyvsp[0].tptr));}
#line 1730 "./bin/compilador.tab.c"
    break;

  case 63: /* $@12: %empty  */
#line 283 "./src/compilador.y"
                                                 {gen_chama_procedimento((yyvsp[-1].tptr),Vec_TypeID_new(0));}
#line 1736 "./bin/compilador.tab.c"
    break;

  case 64: /* chamada_procedimento: IDENT $@11 $@12  */
#line 283 "./src/compilador.y"
                                                                                                 {callingProc = NULL; allParamRef_flag = false;}
#line 1742 "./bin/compilador.tab.c"
    break;

  case 67: /* $@13: %empty  */
#line 299 "./src/compilador.y"
                      {gen_if_then((yyvsp[0].typeID));}
#line 1748 "./bin/compilador.tab.c"
    break;

  case 69: /* comando_condicional: if_then  */
#line 302 "./src/compilador.y"
                                                   {gen_if_without_else();}
#line 1754 "./bin/compilador.tab.c"
    break;

  case 70: /* $@14: %empty  */
#line 303 "./src/compilador.y"
                                  {gen_if_with_else_part1();}
#line 1760 "./bin/compilador.tab.c"
    break;

  case 71: /* comando_condicional: if_then ELSE $@14 comando_sem_rotulo  */
#line 303 "./src/compilador.y"
                                                                                 {gen_if_with_else_part2();}
#line 1766 "./bin/compilador.tab.c"
    break;

  case 72: /* $@15: %empty  */
#line 306 "./src/compilador.y"
                          {gen_while_part1();}
#line 1772 "./bin/compilador.tab.c"
    break;

  case 73: /* $@16: %empty  */
#line 306 "./src/compilador.y"
                                                            {gen_while_part2((yyvsp[-1].typeID));}
#line 1778 "./bin/compilador.tab.c"
    break;

  case 74: /* comando_repititivo: WHILE $@15 expressao DO $@16 comando_sem_rotulo  */
#line 306 "./src/compilador.y"
                                                                                                      {gen_while_part3();}
#line 1784 "./bin/compilador.tab.c"
    break;


#line 1788 "./bin/compilador.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 328 "./src/compilador.y"


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
