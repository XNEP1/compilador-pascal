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

DEF_VEC(Vec_String, char*)
IMPL_VEC(Vec_String, char*)

int num_vars;
int lex_level = -1;
int num_rotulos = 0;

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


#line 114 "./bin/compilador.tab.c"

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
  YYSYMBOL_65_3 = 65,                      /* $@3  */
  YYSYMBOL_parte_declara_vars = 66,        /* parte_declara_vars  */
  YYSYMBOL_var = 67,                       /* var  */
  YYSYMBOL_68_4 = 68,                      /* $@4  */
  YYSYMBOL_declara_vars = 69,              /* declara_vars  */
  YYSYMBOL_declara_var = 70,               /* declara_var  */
  YYSYMBOL_71_5 = 71,                      /* $@5  */
  YYSYMBOL_72_6 = 72,                      /* $@6  */
  YYSYMBOL_tipo = 73,                      /* tipo  */
  YYSYMBOL_lista_id_var = 74,              /* lista_id_var  */
  YYSYMBOL_lista_idents = 75,              /* lista_idents  */
  YYSYMBOL_parte_declara_subrotinas = 76,  /* parte_declara_subrotinas  */
  YYSYMBOL_declaracao_procedimento = 77,   /* declaracao_procedimento  */
  YYSYMBOL_78_7 = 78,                      /* $@7  */
  YYSYMBOL_declaracao_function = 79,       /* declaracao_function  */
  YYSYMBOL_80_8 = 80,                      /* $@8  */
  YYSYMBOL_parametros_formais = 81,        /* parametros_formais  */
  YYSYMBOL_lista_parametros_formais = 82,  /* lista_parametros_formais  */
  YYSYMBOL_secao_parametros_formais = 83,  /* secao_parametros_formais  */
  YYSYMBOL_atribuicao = 84,                /* atribuicao  */
  YYSYMBOL_lista_expressoes = 85,          /* lista_expressoes  */
  YYSYMBOL_expressao = 86,                 /* expressao  */
  YYSYMBOL_sinal = 87,                     /* sinal  */
  YYSYMBOL_variavel = 88,                  /* variavel  */
  YYSYMBOL_chamada_procedimento = 89,      /* chamada_procedimento  */
  YYSYMBOL_chamada_funcao = 90,            /* chamada_funcao  */
  YYSYMBOL_desvio = 91,                    /* desvio  */
  YYSYMBOL_if_then = 92,                   /* if_then  */
  YYSYMBOL_93_9 = 93,                      /* $@9  */
  YYSYMBOL_comando_condicional = 94,       /* comando_condicional  */
  YYSYMBOL_95_10 = 95,                     /* $@10  */
  YYSYMBOL_comando_repititivo = 96,        /* comando_repititivo  */
  YYSYMBOL_97_11 = 97,                     /* $@11  */
  YYSYMBOL_98_12 = 98,                     /* $@12  */
  YYSYMBOL_comando_composto = 99,          /* comando_composto  */
  YYSYMBOL_100_13 = 100,                   /* $@13  */
  YYSYMBOL_comandos = 101,                 /* comandos  */
  YYSYMBOL_comando = 102,                  /* comando  */
  YYSYMBOL_comando_sem_rotulo = 103        /* comando_sem_rotulo  */
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
#define YYLAST   167

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  60
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
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
       0,    98,    98,    98,   107,   110,   107,   117,   121,   121,
     122,   125,   126,   130,   132,   130,   155,   158,   163,   170,
     171,   174,   175,   176,   179,   179,   182,   182,   186,   189,
     190,   193,   194,   195,   196,   199,   202,   203,   206,   207,
     208,   210,   212,   213,   214,   216,   217,   218,   220,   221,
     222,   223,   224,   225,   227,   228,   231,   232,   236,   237,
     240,   241,   251,   254,   258,   257,   273,   280,   279,   302,
     308,   301,   334,   334,   337,   338,   341,   342,   345,   346,
     347,   348,   349,   350
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
  "EXPRESSAO_PREC", "$accept", "programa", "$@1", "bloco", "$@2", "$@3",
  "parte_declara_vars", "var", "$@4", "declara_vars", "declara_var", "$@5",
  "$@6", "tipo", "lista_id_var", "lista_idents",
  "parte_declara_subrotinas", "declaracao_procedimento", "$@7",
  "declaracao_function", "$@8", "parametros_formais",
  "lista_parametros_formais", "secao_parametros_formais", "atribuicao",
  "lista_expressoes", "expressao", "sinal", "variavel",
  "chamada_procedimento", "chamada_funcao", "desvio", "if_then", "$@9",
  "comando_condicional", "$@10", "comando_repititivo", "$@11", "$@12",
  "comando_composto", "$@13", "comandos", "comando", "comando_sem_rotulo", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-83)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-27)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -83,     6,    29,   -83,   -41,   -19,   -10,   -83,    -1,     3,
      15,   -83,   -83,    35,    90,   -83,   -83,   -83,    91,    47,
     -83,   -83,    45,    72,    49,    77,    48,   -83,    50,   -83,
      94,   -83,    51,   -83,    52,   -83,   -83,   -31,    21,    57,
      57,    53,    55,   -11,    33,   126,   -83,   -37,   -83,   -83,
     -83,   132,   -83,   -83,   -83,    -6,   -83,   100,    12,   101,
     103,   -83,   -83,   -83,   105,   -83,    33,   -83,   -83,    33,
     -36,   102,    33,   -83,   -83,   -83,    33,    33,    33,   -83,
     -83,   -83,   -83,   -10,   -10,   -10,   -27,   -23,   -83,   -83,
      97,   106,   -83,   -83,    88,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    33,    33,    33,    33,    33,   137,
     -83,    76,    26,   102,   102,   -11,   -17,    -8,   108,   104,
     -83,    12,   -83,   110,   -83,   -83,    41,   -33,    13,    13,
     -83,   -83,   -83,    13,    46,    46,    46,    46,    46,    46,
     -11,   -83,   -83,    33,   -83,   107,   109,   -83,   -83,   -83,
     -83,   -83,   -83,   -11,   102,   -83,   -83,   -83,   -83
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    20,     0,     0,
       0,     4,    19,     0,    10,     3,    21,     7,     0,     5,
      13,    72,     0,     0,     0,     0,     9,    12,     0,     6,
       0,    22,     0,    23,     0,    11,    18,     0,    72,     0,
       0,     0,     0,    72,     0,     0,    69,    61,    78,    79,
      80,    66,    82,    83,    81,    72,    74,     0,     0,     0,
       0,    17,    16,    14,     0,    55,     0,    56,    57,     0,
      58,    64,     0,    54,    39,    63,     0,     0,     0,    67,
      73,    75,    77,     0,     0,     0,     0,     0,    29,     4,
       0,     0,    76,    41,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      40,     0,     0,    36,    35,    72,     0,     0,    34,     0,
      28,     0,    25,     0,    15,    38,     0,     0,    45,    46,
      42,    43,    44,    47,    48,    49,    52,    53,    50,    51,
      72,    70,    60,     0,    68,     0,     0,    32,    30,     4,
      62,    59,    65,    72,    37,    31,    33,    27,    71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -83,   -83,   -83,   -82,   -83,   -83,   -83,   -83,   -83,   -83,
     133,   -83,   -83,   -83,   -83,    -5,   -83,   -83,   -83,   -83,
     -83,   122,   -83,    43,   -83,    -3,   -42,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   145,
     -83,   -83,   112,   -43
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    13,    14,    21,    16,    17,    18,    26,
      27,    28,    91,    63,    37,    86,    19,    22,    23,    24,
      25,    59,    87,    88,    48,   112,   113,    72,    73,    49,
      74,    50,    51,   109,    52,   115,    53,    76,   153,    54,
      30,    55,    56,    57
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,     8,    71,    80,    43,    44,     3,   122,    45,    46,
      44,    77,    95,    45,    46,     5,    83,   143,    96,    41,
      78,    42,   151,    10,    93,   119,   120,    94,   121,     6,
     110,    43,     4,    10,   111,   145,   114,    44,    84,    85,
      45,    46,    10,    65,   146,    47,     7,    66,     9,    10,
      47,    99,   100,   101,    11,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   157,     7,    67,
      68,    12,   144,   -26,   -24,   142,   143,    47,   116,   117,
     118,    69,    97,    98,    99,   100,   101,   102,    15,    70,
     150,   143,   126,   127,    -8,    20,    31,   152,   141,    32,
      33,   154,    38,    34,   -13,    58,    36,    39,    40,    61,
     158,    62,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,    75,   125,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      79,    82,    89,   123,   140,    90,    92,   124,    10,    35,
     147,   149,    60,   155,   148,   156,    29,    81
};

static const yytype_uint8 yycheck[] =
{
      43,     6,    44,     9,    10,    16,     0,    89,    19,    20,
      16,    48,    48,    19,    20,    56,     4,    50,    54,    50,
      57,    52,    55,    50,    66,    52,    49,    69,    51,    48,
      72,    10,     3,    50,    76,    52,    78,    16,    26,    27,
      19,    20,    50,    10,    52,    56,    56,    14,    49,    50,
      56,    38,    39,    40,    51,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   149,    56,    36,
      37,    56,   115,    26,    27,    49,    50,    56,    83,    84,
      85,    48,    36,    37,    38,    39,    40,    41,    53,    56,
      49,    50,    95,    96,     4,     4,    51,   140,    22,    27,
      51,   143,     8,    26,    56,    48,    56,    56,    56,    56,
     153,    56,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    10,    49,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      18,    51,    51,    56,    17,    52,    51,    51,    50,    26,
      56,    51,    40,    56,   121,    56,    21,    55
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    61,    62,     0,     3,    56,    48,    56,    75,    49,
      50,    51,    56,    63,    64,    53,    66,    67,    68,    76,
       4,    65,    77,    78,    79,    80,    69,    70,    71,    99,
     100,    51,    27,    51,    26,    70,    56,    74,     8,    56,
      56,    50,    52,    10,    16,    19,    20,    56,    84,    89,
      91,    92,    94,    96,    99,   101,   102,   103,    48,    81,
      81,    56,    56,    73,   103,    10,    14,    36,    37,    48,
      56,    86,    87,    88,    90,    10,    97,    48,    57,    18,
       9,   102,    51,     4,    26,    27,    75,    82,    83,    51,
      52,    72,    51,    86,    86,    48,    54,    36,    37,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    93,
      86,    86,    85,    86,    86,    95,    75,    75,    75,    52,
      49,    51,    63,    56,    51,    49,    85,    85,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      17,    22,    49,    50,   103,    52,    52,    56,    83,    51,
      49,    55,   103,    98,    86,    56,    56,    63,   103
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    60,    62,    61,    64,    65,    63,    66,    68,    67,
      67,    69,    69,    71,    72,    70,    73,    74,    74,    75,
      75,    76,    76,    76,    78,    77,    80,    79,    81,    82,
      82,    83,    83,    83,    83,    84,    85,    85,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    87,    87,    88,    88,
      89,    89,    90,    91,    93,    92,    94,    95,    94,    97,
      98,    96,   100,    99,   101,   101,   102,   102,   103,   103,
     103,   103,   103,   103
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     0,     0,     5,     1,     0,     3,
       0,     2,     1,     0,     0,     6,     1,     3,     1,     3,
       1,     0,     3,     3,     0,     6,     0,     8,     3,     1,
       3,     4,     3,     4,     2,     3,     1,     3,     3,     1,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     4,
       4,     1,     4,     2,     0,     5,     1,     0,     4,     0,
       0,     6,     0,     4,     1,     2,     3,     2,     1,     1,
       1,     1,     1,     1
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
#line 98 "./src/compilador.y"
             {
             geraCodigo (NULL, "INPP");
             lex_level++;
             }
#line 1325 "./bin/compilador.tab.c"
    break;

  case 3: /* programa: $@1 PROGRAM IDENT ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO  */
#line 104 "./src/compilador.y"
                         {geraCodigo (NULL, "PARA");}
#line 1331 "./bin/compilador.tab.c"
    break;

  case 4: /* $@2: %empty  */
#line 107 "./src/compilador.y"
       {}
#line 1337 "./bin/compilador.tab.c"
    break;

  case 5: /* $@3: %empty  */
#line 110 "./src/compilador.y"
       {}
#line 1343 "./bin/compilador.tab.c"
    break;

  case 8: /* $@4: %empty  */
#line 121 "./src/compilador.y"
     {}
#line 1349 "./bin/compilador.tab.c"
    break;

  case 13: /* $@5: %empty  */
#line 130 "./src/compilador.y"
            { }
#line 1355 "./bin/compilador.tab.c"
    break;

  case 14: /* $@6: %empty  */
#line 132 "./src/compilador.y"
            { /* AMEM */
                int varType = is_type((yyvsp[0].tptr));
                if (!(varType)){
                    fprintf(stderr, "Erro ao compilar (linha %d): \"%s\" não é um tipo válido.", nl, (yyvsp[0].tptr));
                    YYERROR;
                }
                
                int qnt_vars = (yyvsp[-2].intV);

                // atribui o tipo as variaveis alocadas
                for(int i=sybTable.size-qnt_vars; i<sybTable.size; i++){ 
                    sybTable.data[i].atributes.var_attr.type = varType;
                }

                int amountToAlloc = type_size(varType) * qnt_vars;
                asprintf(&mepaCommand, "AMEM %d", amountToAlloc);
                geraCodigo(NULL, mepaCommand);
                free(mepaCommand);

            }
#line 1380 "./bin/compilador.tab.c"
    break;

  case 16: /* tipo: IDENT  */
#line 155 "./src/compilador.y"
            {}
#line 1386 "./bin/compilador.tab.c"
    break;

  case 17: /* lista_id_var: lista_id_var VIRGULA IDENT  */
#line 159 "./src/compilador.y"
            { /* insere �ltima vars na tabela de s�mbolos */ 
                insert_var_sybTable(&sybTable, (yyvsp[0].tptr), lex_level); // tipo ainda desconhecido.
                (yyval.intV) = (yyvsp[-2].intV) + 1; 
            }
#line 1395 "./bin/compilador.tab.c"
    break;

  case 18: /* lista_id_var: IDENT  */
#line 164 "./src/compilador.y"
            { /* insere vars na tabela de s�mbolos */
                insert_var_sybTable(&sybTable, (yyvsp[0].tptr), lex_level); // tipo ainda desconhecido.
                (yyval.intV) = 1;
            }
#line 1404 "./bin/compilador.tab.c"
    break;

  case 24: /* $@7: %empty  */
#line 179 "./src/compilador.y"
                         {lex_level++;}
#line 1410 "./bin/compilador.tab.c"
    break;

  case 26: /* $@8: %empty  */
#line 182 "./src/compilador.y"
                     {lex_level++;}
#line 1416 "./bin/compilador.tab.c"
    break;

  case 35: /* atribuicao: IDENT ATRIBUICAO expressao  */
#line 199 "./src/compilador.y"
                                       {gen_atribuicao((yyvsp[-2].tptr), (yyvsp[0].typeID));}
#line 1422 "./bin/compilador.tab.c"
    break;

  case 38: /* expressao: ABRE_PARENTESES expressao FECHA_PARENTESES  */
#line 206 "./src/compilador.y"
                                                      {(yyval.typeID) = (yyvsp[-1].typeID);}
#line 1428 "./bin/compilador.tab.c"
    break;

  case 39: /* expressao: chamada_funcao  */
#line 207 "./src/compilador.y"
                                            {/*TODO*/(yyval.typeID) = (yyvsp[0].typeID);}
#line 1434 "./bin/compilador.tab.c"
    break;

  case 40: /* expressao: sinal expressao  */
#line 208 "./src/compilador.y"
                                            {(yyval.typeID) = (yyvsp[0].typeID); gen_checa_sinal((yyvsp[-1].boolV));}
#line 1440 "./bin/compilador.tab.c"
    break;

  case 41: /* expressao: NOT expressao  */
#line 210 "./src/compilador.y"
                                            {/*TODO*/(yyval.typeID) = (yyvsp[0].typeID);}
#line 1446 "./bin/compilador.tab.c"
    break;

  case 42: /* expressao: expressao MUL expressao  */
#line 212 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1452 "./bin/compilador.tab.c"
    break;

  case 43: /* expressao: expressao DIV expressao  */
#line 213 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1458 "./bin/compilador.tab.c"
    break;

  case 44: /* expressao: expressao AND expressao  */
#line 214 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1464 "./bin/compilador.tab.c"
    break;

  case 45: /* expressao: expressao SOMA expressao  */
#line 216 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1470 "./bin/compilador.tab.c"
    break;

  case 46: /* expressao: expressao SUB expressao  */
#line 217 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1476 "./bin/compilador.tab.c"
    break;

  case 47: /* expressao: expressao OR expressao  */
#line 218 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1482 "./bin/compilador.tab.c"
    break;

  case 48: /* expressao: expressao IGUAL expressao  */
#line 220 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1488 "./bin/compilador.tab.c"
    break;

  case 49: /* expressao: expressao DIFERENTE expressao  */
#line 221 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1494 "./bin/compilador.tab.c"
    break;

  case 50: /* expressao: expressao MAIOR expressao  */
#line 222 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1500 "./bin/compilador.tab.c"
    break;

  case 51: /* expressao: expressao MAIOR_IGUAL expressao  */
#line 223 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1506 "./bin/compilador.tab.c"
    break;

  case 52: /* expressao: expressao MENOR expressao  */
#line 224 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1512 "./bin/compilador.tab.c"
    break;

  case 53: /* expressao: expressao MENOR_IGUAL expressao  */
#line 225 "./src/compilador.y"
                                            {(yyval.typeID) = gen_operacao((yyvsp[-2].typeID), (yyvsp[-1].tokenType), (yyvsp[0].typeID));}
#line 1518 "./bin/compilador.tab.c"
    break;

  case 54: /* expressao: variavel  */
#line 227 "./src/compilador.y"
                                            { (yyval.typeID) = gen_carrega_var((yyvsp[0].tptr)); /* TEMPORARIO, FALTA SUPORTE PARA ARRAY */ }
#line 1524 "./bin/compilador.tab.c"
    break;

  case 55: /* expressao: NUMBER  */
#line 228 "./src/compilador.y"
                                            { (yyval.typeID) = gen_carrega_numero((yyvsp[0].intV)); }
#line 1530 "./bin/compilador.tab.c"
    break;

  case 56: /* sinal: SOMA  */
#line 231 "./src/compilador.y"
            {(yyval.boolV) = false;}
#line 1536 "./bin/compilador.tab.c"
    break;

  case 57: /* sinal: SUB  */
#line 232 "./src/compilador.y"
            {(yyval.boolV) = true;}
#line 1542 "./bin/compilador.tab.c"
    break;

  case 58: /* variavel: IDENT  */
#line 236 "./src/compilador.y"
                {(yyval.tptr) = (yyvsp[0].tptr);}
#line 1548 "./bin/compilador.tab.c"
    break;

  case 59: /* variavel: IDENT ABRE_COLCHETES lista_expressoes FECHA_COLCHETES  */
#line 237 "./src/compilador.y"
                                                                {(yyval.tptr) = (yyvsp[-3].tptr);}
#line 1554 "./bin/compilador.tab.c"
    break;

  case 61: /* chamada_procedimento: IDENT  */
#line 241 "./src/compilador.y"
                            {}
#line 1560 "./bin/compilador.tab.c"
    break;

  case 64: /* $@9: %empty  */
#line 258 "./src/compilador.y"
{
    if((yyvsp[0].typeID) != BOOLEAN){
        fprintf(stderr, "Erro ao compilar (linha %d): Expressão não é do tipo booleano.", nl);
        YYERROR;
    }

    rotulo = novo_rotulo();
    Vec_String_push(&rotulosStack, rotulo);
    asprintf(&mepaCommand, "DSVF %s", rotulo);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
}
#line 1577 "./bin/compilador.tab.c"
    break;

  case 66: /* comando_condicional: if_then  */
#line 274 "./src/compilador.y"
                    {
                        rotulo_endif  = Vec_String_pop(&rotulosStack);
                        geraCodigo(rotulo_endif, "NADA");
                        free(rotulo_endif);
                    }
#line 1587 "./bin/compilador.tab.c"
    break;

  case 67: /* $@10: %empty  */
#line 280 "./src/compilador.y"
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
#line 1605 "./bin/compilador.tab.c"
    break;

  case 68: /* comando_condicional: if_then ELSE $@10 comando_sem_rotulo  */
#line 294 "./src/compilador.y"
                   {
                        rotulo_endif = Vec_String_pop(&rotulosStack);
                        geraCodigo(rotulo_endif, "NADA");
                        free(rotulo_endif);
                   }
#line 1615 "./bin/compilador.tab.c"
    break;

  case 69: /* $@11: %empty  */
#line 302 "./src/compilador.y"
{
    rotulo_while = novo_rotulo();
    Vec_String_push(&rotulosStack, rotulo_while);
    geraCodigo(rotulo_while, "NADA");
}
#line 1625 "./bin/compilador.tab.c"
    break;

  case 70: /* $@12: %empty  */
#line 308 "./src/compilador.y"
{
    if((yyvsp[-1].typeID) != BOOLEAN){
        fprintf(stderr, "Erro ao compilar (linha %d): Expressão não é do tipo booleano.", nl);
        YYERROR;
    }

    rotulo_do = novo_rotulo();
    Vec_String_push(&rotulosStack, rotulo_do);
    asprintf(&mepaCommand, "DSVF %s", rotulo_do);
    geraCodigo(NULL, mepaCommand);
    free(mepaCommand);
}
#line 1642 "./bin/compilador.tab.c"
    break;

  case 71: /* comando_repititivo: WHILE $@11 expressao DO $@12 comando_sem_rotulo  */
#line 321 "./src/compilador.y"
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
#line 1658 "./bin/compilador.tab.c"
    break;

  case 72: /* $@13: %empty  */
#line 334 "./src/compilador.y"
                  {}
#line 1664 "./bin/compilador.tab.c"
    break;

  case 73: /* comando_composto: $@13 T_BEGIN comandos T_END  */
#line 334 "./src/compilador.y"
                                            {}
#line 1670 "./bin/compilador.tab.c"
    break;


#line 1674 "./bin/compilador.tab.c"

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

#line 353 "./src/compilador.y"


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
