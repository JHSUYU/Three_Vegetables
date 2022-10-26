/* A Bison parser, made by GNU Bison 3.7.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.tab.h"
#include "sql/parser/lex.yy.h"
// #include "common/log/log.h" // 包含C++中的头文件

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ParserContext {
  Query * ssql;
  size_t select_length;
  size_t condition_length;
  size_t from_length;
  size_t value_length;
  Value values[MAX_NUM];
  Condition conditions[MAX_NUM];
  CompOp comp;
	char id[MAX_NUM];
} ParserContext;

//获取子串
char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
{
  char *sp = malloc(sizeof(char) * (n2 - n1 + 2));
  int i, j = 0;
  for (i = n1; i <= n2; i++) {
    sp[j++] = s[i];
  }
  sp[j] = 0;
  return sp;
}

void yyerror(yyscan_t scanner, const char *str)
{
  ParserContext *context = (ParserContext *)(yyget_extra(scanner));
  query_reset(context->ssql);
  context->ssql->flag = SCF_ERROR;
  context->condition_length = 0;
  context->from_length = 0;
  context->select_length = 0;
  context->value_length = 0;
  context->ssql->sstr.insertion.value_num = 0;
  printf("parse sql failed. error=%s", str);
}

ParserContext *get_context(yyscan_t scanner)
{
  return (ParserContext *)yyget_extra(scanner);
}

#define CONTEXT get_context(scanner)


#line 128 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    CREATE = 259,                  /* CREATE  */
    DROP = 260,                    /* DROP  */
    TABLE = 261,                   /* TABLE  */
    TABLES = 262,                  /* TABLES  */
    INDEX = 263,                   /* INDEX  */
    SELECT = 264,                  /* SELECT  */
    DESC = 265,                    /* DESC  */
    SHOW = 266,                    /* SHOW  */
    SYNC = 267,                    /* SYNC  */
    INSERT = 268,                  /* INSERT  */
    DELETE = 269,                  /* DELETE  */
    UPDATE = 270,                  /* UPDATE  */
    LBRACE = 271,                  /* LBRACE  */
    RBRACE = 272,                  /* RBRACE  */
    COMMA = 273,                   /* COMMA  */
    TRX_BEGIN = 274,               /* TRX_BEGIN  */
    TRX_COMMIT = 275,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 276,            /* TRX_ROLLBACK  */
    INT_T = 277,                   /* INT_T  */
    STRING_T = 278,                /* STRING_T  */
    FLOAT_T = 279,                 /* FLOAT_T  */
    DATE_T = 280,                  /* DATE_T  */
    HELP = 281,                    /* HELP  */
    EXIT = 282,                    /* EXIT  */
    DOT = 283,                     /* DOT  */
    INTO = 284,                    /* INTO  */
    VALUES = 285,                  /* VALUES  */
    FROM = 286,                    /* FROM  */
    WHERE = 287,                   /* WHERE  */
    AND = 288,                     /* AND  */
    SET = 289,                     /* SET  */
    ON = 290,                      /* ON  */
    LOAD = 291,                    /* LOAD  */
    DATA = 292,                    /* DATA  */
    INFILE = 293,                  /* INFILE  */
    EQ = 294,                      /* EQ  */
    LT = 295,                      /* LT  */
    GT = 296,                      /* GT  */
    LE = 297,                      /* LE  */
    GE = 298,                      /* GE  */
    NE = 299,                      /* NE  */
    LK = 300,                      /* LK  */
    NLK = 301,                     /* NLK  */
    UNIQUE = 302,                  /* UNIQUE  */
    AGGR_FUNC = 303,               /* AGGR_FUNC  */
    MAX = 304,                     /* MAX  */
    MIN = 305,                     /* MIN  */
    SUM = 306,                     /* SUM  */
    AVG = 307,                     /* AVG  */
    COUNT = 308,                   /* COUNT  */
    COUNTALLXING = 309,            /* COUNTALLXING  */
    COUNTALL1 = 310,               /* COUNTALL1  */
    NUMBER = 311,                  /* NUMBER  */
    FLOAT = 312,                   /* FLOAT  */
    ID = 313,                      /* ID  */
    PATH = 314,                    /* PATH  */
    SSS = 315,                     /* SSS  */
    STAR = 316,                    /* STAR  */
    STRING_V = 317                 /* STRING_V  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define SEMICOLON 258
#define CREATE 259
#define DROP 260
#define TABLE 261
#define TABLES 262
#define INDEX 263
#define SELECT 264
#define DESC 265
#define SHOW 266
#define SYNC 267
#define INSERT 268
#define DELETE 269
#define UPDATE 270
#define LBRACE 271
#define RBRACE 272
#define COMMA 273
#define TRX_BEGIN 274
#define TRX_COMMIT 275
#define TRX_ROLLBACK 276
#define INT_T 277
#define STRING_T 278
#define FLOAT_T 279
#define DATE_T 280
#define HELP 281
#define EXIT 282
#define DOT 283
#define INTO 284
#define VALUES 285
#define FROM 286
#define WHERE 287
#define AND 288
#define SET 289
#define ON 290
#define LOAD 291
#define DATA 292
#define INFILE 293
#define EQ 294
#define LT 295
#define GT 296
#define LE 297
#define GE 298
#define NE 299
#define LK 300
#define NLK 301
#define UNIQUE 302
#define AGGR_FUNC 303
#define MAX 304
#define MIN 305
#define SUM 306
#define AVG 307
#define COUNT 308
#define COUNTALLXING 309
#define COUNTALL1 310
#define NUMBER 311
#define FLOAT 312
#define ID 313
#define PATH 314
#define SSS 315
#define STAR 316
#define STRING_V 317

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 118 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 314 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int yyparse (void *scanner);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_CREATE = 4,                     /* CREATE  */
  YYSYMBOL_DROP = 5,                       /* DROP  */
  YYSYMBOL_TABLE = 6,                      /* TABLE  */
  YYSYMBOL_TABLES = 7,                     /* TABLES  */
  YYSYMBOL_INDEX = 8,                      /* INDEX  */
  YYSYMBOL_SELECT = 9,                     /* SELECT  */
  YYSYMBOL_DESC = 10,                      /* DESC  */
  YYSYMBOL_SHOW = 11,                      /* SHOW  */
  YYSYMBOL_SYNC = 12,                      /* SYNC  */
  YYSYMBOL_INSERT = 13,                    /* INSERT  */
  YYSYMBOL_DELETE = 14,                    /* DELETE  */
  YYSYMBOL_UPDATE = 15,                    /* UPDATE  */
  YYSYMBOL_LBRACE = 16,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 17,                    /* RBRACE  */
  YYSYMBOL_COMMA = 18,                     /* COMMA  */
  YYSYMBOL_TRX_BEGIN = 19,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 20,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 21,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 22,                     /* INT_T  */
  YYSYMBOL_STRING_T = 23,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 24,                   /* FLOAT_T  */
  YYSYMBOL_DATE_T = 25,                    /* DATE_T  */
  YYSYMBOL_HELP = 26,                      /* HELP  */
  YYSYMBOL_EXIT = 27,                      /* EXIT  */
  YYSYMBOL_DOT = 28,                       /* DOT  */
  YYSYMBOL_INTO = 29,                      /* INTO  */
  YYSYMBOL_VALUES = 30,                    /* VALUES  */
  YYSYMBOL_FROM = 31,                      /* FROM  */
  YYSYMBOL_WHERE = 32,                     /* WHERE  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_SET = 34,                       /* SET  */
  YYSYMBOL_ON = 35,                        /* ON  */
  YYSYMBOL_LOAD = 36,                      /* LOAD  */
  YYSYMBOL_DATA = 37,                      /* DATA  */
  YYSYMBOL_INFILE = 38,                    /* INFILE  */
  YYSYMBOL_EQ = 39,                        /* EQ  */
  YYSYMBOL_LT = 40,                        /* LT  */
  YYSYMBOL_GT = 41,                        /* GT  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_GE = 43,                        /* GE  */
  YYSYMBOL_NE = 44,                        /* NE  */
  YYSYMBOL_LK = 45,                        /* LK  */
  YYSYMBOL_NLK = 46,                       /* NLK  */
  YYSYMBOL_UNIQUE = 47,                    /* UNIQUE  */
  YYSYMBOL_AGGR_FUNC = 48,                 /* AGGR_FUNC  */
  YYSYMBOL_MAX = 49,                       /* MAX  */
  YYSYMBOL_MIN = 50,                       /* MIN  */
  YYSYMBOL_SUM = 51,                       /* SUM  */
  YYSYMBOL_AVG = 52,                       /* AVG  */
  YYSYMBOL_COUNT = 53,                     /* COUNT  */
  YYSYMBOL_COUNTALLXING = 54,              /* COUNTALLXING  */
  YYSYMBOL_COUNTALL1 = 55,                 /* COUNTALL1  */
  YYSYMBOL_NUMBER = 56,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 57,                     /* FLOAT  */
  YYSYMBOL_ID = 58,                        /* ID  */
  YYSYMBOL_PATH = 59,                      /* PATH  */
  YYSYMBOL_SSS = 60,                       /* SSS  */
  YYSYMBOL_STAR = 61,                      /* STAR  */
  YYSYMBOL_STRING_V = 62,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 63,                  /* $accept  */
  YYSYMBOL_commands = 64,                  /* commands  */
  YYSYMBOL_command = 65,                   /* command  */
  YYSYMBOL_exit = 66,                      /* exit  */
  YYSYMBOL_help = 67,                      /* help  */
  YYSYMBOL_sync = 68,                      /* sync  */
  YYSYMBOL_begin = 69,                     /* begin  */
  YYSYMBOL_commit = 70,                    /* commit  */
  YYSYMBOL_rollback = 71,                  /* rollback  */
  YYSYMBOL_drop_table = 72,                /* drop_table  */
  YYSYMBOL_show_tables = 73,               /* show_tables  */
  YYSYMBOL_desc_table = 74,                /* desc_table  */
  YYSYMBOL_create_index = 75,              /* create_index  */
  YYSYMBOL_create_unique_index = 76,       /* create_unique_index  */
  YYSYMBOL_show_index = 77,                /* show_index  */
  YYSYMBOL_drop_index = 78,                /* drop_index  */
  YYSYMBOL_create_table = 79,              /* create_table  */
  YYSYMBOL_attr_def_list = 80,             /* attr_def_list  */
  YYSYMBOL_attr_def = 81,                  /* attr_def  */
  YYSYMBOL_number = 82,                    /* number  */
  YYSYMBOL_type = 83,                      /* type  */
  YYSYMBOL_ID_get = 84,                    /* ID_get  */
  YYSYMBOL_insert = 85,                    /* insert  */
  YYSYMBOL_multi_value_list = 86,          /* multi_value_list  */
  YYSYMBOL_brace_value_list = 87,          /* brace_value_list  */
  YYSYMBOL_value_list = 88,                /* value_list  */
  YYSYMBOL_value = 89,                     /* value  */
  YYSYMBOL_delete = 90,                    /* delete  */
  YYSYMBOL_update = 91,                    /* update  */
  YYSYMBOL_select = 92,                    /* select  */
  YYSYMBOL_select_attr = 93,               /* select_attr  */
  YYSYMBOL_aggr = 94,                      /* aggr  */
  YYSYMBOL_attr_list = 95,                 /* attr_list  */
  YYSYMBOL_index_list = 96,                /* index_list  */
  YYSYMBOL_rel_list = 97,                  /* rel_list  */
  YYSYMBOL_where = 98,                     /* where  */
  YYSYMBOL_condition_list = 99,            /* condition_list  */
  YYSYMBOL_condition = 100,                /* condition  */
  YYSYMBOL_comOp = 101,                    /* comOp  */
  YYSYMBOL_load_data = 102                 /* load_data  */
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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   205

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  63
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  40
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  217

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   317


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
      55,    56,    57,    58,    59,    60,    61,    62
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   144,   144,   146,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   172,   177,   182,   188,   194,   200,   206,
     212,   218,   225,   238,   249,   258,   266,   275,   277,   281,
     292,   305,   308,   309,   310,   311,   314,   323,   339,   341,
     344,   346,   348,   353,   356,   359,   366,   376,   386,   405,
     410,   416,   421,   427,   431,   438,   445,   452,   459,   466,
     471,   478,   480,   487,   494,   497,   499,   504,   506,   510,
     512,   516,   518,   523,   544,   564,   584,   606,   627,   648,
     670,   671,   672,   673,   674,   675,   676,   677,   681
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
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "CREATE",
  "DROP", "TABLE", "TABLES", "INDEX", "SELECT", "DESC", "SHOW", "SYNC",
  "INSERT", "DELETE", "UPDATE", "LBRACE", "RBRACE", "COMMA", "TRX_BEGIN",
  "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T", "FLOAT_T", "DATE_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EQ", "LT", "GT", "LE", "GE", "NE", "LK",
  "NLK", "UNIQUE", "AGGR_FUNC", "MAX", "MIN", "SUM", "AVG", "COUNT",
  "COUNTALLXING", "COUNTALL1", "NUMBER", "FLOAT", "ID", "PATH", "SSS",
  "STAR", "STRING_V", "$accept", "commands", "command", "exit", "help",
  "sync", "begin", "commit", "rollback", "drop_table", "show_tables",
  "desc_table", "create_index", "create_unique_index", "show_index",
  "drop_index", "create_table", "attr_def_list", "attr_def", "number",
  "type", "ID_get", "insert", "multi_value_list", "brace_value_list",
  "value_list", "value", "delete", "update", "select", "select_attr",
  "aggr", "attr_list", "index_list", "rel_list", "where", "condition_list",
  "condition", "comOp", "load_data", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317
};
#endif

#define YYPACT_NINF (-179)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -179,    56,  -179,    -2,    22,   -18,   -50,     7,    38,     0,
      11,   -11,    50,    52,    60,    61,    69,    20,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,    15,    21,
      70,    23,    33,    64,    78,    79,    92,    97,  -179,  -179,
      -1,   100,    93,   100,   122,   123,    96,  -179,    71,    72,
      94,  -179,  -179,  -179,  -179,  -179,    95,   115,    99,    74,
     132,   133,    80,    81,    82,    83,    84,    35,    85,  -179,
    -179,    86,  -179,  -179,  -179,    87,   107,   114,    89,    88,
      91,   101,   116,  -179,  -179,   135,   136,   137,   138,   139,
      26,   100,   100,   140,   147,   141,   -47,   157,   124,   142,
    -179,   143,    98,   146,   106,  -179,  -179,  -179,  -179,  -179,
     108,  -179,  -179,  -179,   109,   114,  -179,     2,   150,  -179,
    -179,   -21,  -179,    58,   144,  -179,     2,   159,    91,   152,
    -179,  -179,  -179,  -179,   154,   117,   156,   100,   140,   170,
     158,   141,   171,   120,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,    49,    54,   -47,  -179,   114,   121,   143,   177,
     125,   164,   126,  -179,  -179,  -179,     2,   166,   150,  -179,
      58,  -179,  -179,   160,  -179,   144,   182,   183,  -179,  -179,
    -179,   172,   129,   173,   164,   158,  -179,  -179,    59,   134,
    -179,  -179,  -179,  -179,   164,   188,   176,  -179,   167,  -179,
    -179,  -179,  -179,   191,   145,  -179,  -179
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     3,    20,
      19,    14,    15,    16,    17,     9,    10,    11,    12,    22,
      21,    13,     8,     5,     7,     6,     4,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    69,    70,
      71,    59,     0,    71,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      60,     0,    63,    31,    30,     0,     0,    79,     0,     0,
       0,     0,     0,    29,    35,     0,     0,     0,     0,     0,
      71,    71,    71,    77,     0,     0,     0,     0,     0,     0,
      46,    37,     0,     0,     0,    64,    65,    66,    67,    68,
       0,    72,    74,    62,     0,    79,    34,     0,    48,    53,
      54,     0,    55,     0,    81,    56,     0,     0,     0,     0,
      42,    44,    45,    43,    40,     0,     0,    71,    77,     0,
      51,     0,     0,     0,    90,    91,    92,    93,    94,    95,
      96,    97,     0,     0,     0,    80,    79,     0,    37,     0,
       0,    75,     0,    73,    78,    58,     0,     0,    48,    47,
       0,    85,    83,    86,    84,    81,     0,     0,    38,    36,
      41,     0,     0,     0,    75,    51,    50,    49,     0,     0,
      82,    57,    98,    39,    75,     0,     0,    52,     0,    87,
      88,    76,    32,     0,     0,    33,    89
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,  -179,
    -179,  -179,  -179,  -179,  -179,  -179,  -179,    28,    62,  -179,
    -179,  -179,  -179,    19,    47,     4,  -124,  -179,  -179,  -179,
    -179,   127,   -51,  -178,    53,  -120,    17,    41,  -132,  -179
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,   139,   111,   191,
     144,   112,    33,   152,   128,   177,   133,    34,    35,    36,
      52,    53,    79,   193,   125,   107,   165,   134,   162,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      80,   163,    82,   150,    38,   149,    39,   153,    54,   129,
     130,   131,   166,   132,    55,    56,   206,    77,   154,   155,
     156,   157,   158,   159,   160,   161,   211,    78,    41,    58,
      42,    43,    44,    45,    46,    47,    48,    49,   182,   184,
      50,    57,    59,    51,    77,    40,   186,    60,   198,   121,
     122,   123,   195,    61,   120,    62,     2,    66,   129,   130,
       3,     4,   132,    63,    64,     5,     6,     7,     8,     9,
      10,    11,    65,    67,   209,    12,    13,    14,    69,    68,
      72,    70,    15,    16,    43,    44,    45,    46,    47,    48,
      49,    71,    17,   100,    73,    74,   173,   154,   155,   156,
     157,   158,   159,   160,   161,   129,   130,   181,    75,   132,
     129,   130,   183,    76,   132,   129,   130,   208,    77,   132,
     140,   141,   142,   143,    81,    83,    84,    85,    88,    86,
      87,    90,    92,    89,    91,    93,    94,   105,    95,    96,
      97,    98,    99,   102,   103,   104,   106,   108,   109,   110,
     126,   114,   115,   116,   117,   118,   119,   127,   124,   113,
     135,   138,   145,   136,   146,   167,   147,   148,   151,   169,
     170,   137,   172,   175,   179,   171,   176,   164,   180,   187,
     189,   190,   192,   196,   194,   201,   202,   204,   199,   203,
     205,   212,   210,   213,   215,   214,   188,   197,   178,   207,
     168,   174,   200,   216,   101,   185
};

static const yytype_uint8 yycheck[] =
{
      51,   133,    53,   127,     6,   125,     8,    28,    58,    56,
      57,    58,   136,    60,     7,     8,   194,    18,    39,    40,
      41,    42,    43,    44,    45,    46,   204,    28,     6,    29,
       8,    49,    50,    51,    52,    53,    54,    55,   162,   163,
      58,     3,    31,    61,    18,    47,   166,    58,   180,   100,
     101,   102,   176,     3,    28,     3,     0,    37,    56,    57,
       4,     5,    60,     3,     3,     9,    10,    11,    12,    13,
      14,    15,     3,    58,   198,    19,    20,    21,     8,    58,
      16,    58,    26,    27,    49,    50,    51,    52,    53,    54,
      55,    58,    36,    58,    16,    16,   147,    39,    40,    41,
      42,    43,    44,    45,    46,    56,    57,    58,    16,    60,
      56,    57,    58,    16,    60,    56,    57,    58,    18,    60,
      22,    23,    24,    25,    31,     3,     3,    31,    34,    58,
      58,    16,    58,    38,    35,     3,     3,    30,    58,    58,
      58,    58,    58,    58,    58,    58,    32,    58,    60,    58,
       3,    35,    17,    17,    17,    17,    17,    16,    18,    58,
       3,    18,    16,    39,    58,     6,    58,    58,    18,    17,
      16,    29,    16,     3,     3,    58,    18,    33,    58,    58,
       3,    56,    18,    17,    58,     3,     3,    58,    28,    17,
      17,     3,    58,    17,     3,    28,   168,   178,   151,   195,
     138,   148,   185,    58,    77,   164
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    64,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    36,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    85,    90,    91,    92,   102,     6,     8,
      47,     6,     8,    49,    50,    51,    52,    53,    54,    55,
      58,    61,    93,    94,    58,     7,     8,     3,    29,    31,
      58,     3,     3,     3,     3,     3,    37,    58,    58,     8,
      58,    58,    16,    16,    16,    16,    16,    18,    28,    95,
      95,    31,    95,     3,     3,    31,    58,    58,    34,    38,
      16,    35,    58,     3,     3,    58,    58,    58,    58,    58,
      58,    94,    58,    58,    58,    30,    32,    98,    58,    60,
      58,    81,    84,    58,    35,    17,    17,    17,    17,    17,
      28,    95,    95,    95,    18,    97,     3,    16,    87,    56,
      57,    58,    60,    89,   100,     3,    39,    29,    18,    80,
      22,    23,    24,    25,    83,    16,    58,    58,    58,    98,
      89,    18,    86,    28,    39,    40,    41,    42,    43,    44,
      45,    46,   101,   101,    33,    99,    89,     6,    81,    17,
      16,    58,    16,    95,    97,     3,    18,    88,    87,     3,
      58,    58,    89,    58,    89,   100,    98,    58,    80,     3,
      56,    82,    18,    96,    58,    89,    17,    86,   101,    28,
      99,     3,     3,    17,    58,    17,    96,    88,    58,    89,
      58,    96,     3,    17,    28,     3,    58
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    63,    64,    64,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    80,    81,
      81,    82,    83,    83,    83,    83,    84,    85,    86,    86,
      87,    88,    88,    89,    89,    89,    90,    91,    92,    93,
      93,    93,    93,    93,    94,    94,    94,    94,    94,    94,
      94,    95,    95,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   100,   100,   100,   100,   100,
     101,   101,   101,   101,   101,   101,   101,   101,   102
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     4,
       3,     3,    10,    11,     5,     4,     8,     0,     3,     5,
       2,     1,     1,     1,     1,     1,     1,     7,     0,     3,
       4,     0,     3,     1,     1,     1,     5,     8,     7,     1,
       2,     2,     4,     2,     4,     4,     4,     4,     4,     1,
       1,     0,     3,     5,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     3,     3,     3,     3,     5,     5,     7,
       1,     1,     1,     1,     1,     1,     1,     1,     8
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
        yyerror (scanner, YY_("syntax error: cannot back up")); \
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

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (scanner);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, void *scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, scanner);
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
                 int yyrule, void *scanner)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, scanner); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, void *scanner)
{
  YYUSE (yyvaluep);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void *scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
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
      yychar = yylex (&yylval, scanner);
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
  case 23: /* exit: EXIT SEMICOLON  */
#line 172 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1545 "y.tab.c"
    break;

  case 24: /* help: HELP SEMICOLON  */
#line 177 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1553 "y.tab.c"
    break;

  case 25: /* sync: SYNC SEMICOLON  */
#line 182 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1561 "y.tab.c"
    break;

  case 26: /* begin: TRX_BEGIN SEMICOLON  */
#line 188 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1569 "y.tab.c"
    break;

  case 27: /* commit: TRX_COMMIT SEMICOLON  */
#line 194 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1577 "y.tab.c"
    break;

  case 28: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 200 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1585 "y.tab.c"
    break;

  case 29: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 206 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1594 "y.tab.c"
    break;

  case 30: /* show_tables: SHOW TABLES SEMICOLON  */
#line 212 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1602 "y.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 218 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1611 "y.tab.c"
    break;

  case 32: /* create_index: CREATE INDEX ID ON ID LBRACE ID index_list RBRACE SEMICOLON  */
#line 226 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string));
			create_index_append(&CONTEXT->ssql->sstr.create_index,(yyvsp[-3].string));
			create_index_unset_unique(&CONTEXT->ssql->sstr.create_index);
			

		}
#line 1625 "y.tab.c"
    break;

  case 33: /* create_unique_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID index_list RBRACE SEMICOLON  */
#line 239 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string));
			create_index_append(&CONTEXT->ssql->sstr.create_index,(yyvsp[-3].string));
			create_index_set_unique(&CONTEXT->ssql->sstr.create_index);
		}
#line 1636 "y.tab.c"
    break;

  case 34: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 250 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index,(yyvsp[-1].string));
		}
#line 1645 "y.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 259 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1654 "y.tab.c"
    break;

  case 36: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 267 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1666 "y.tab.c"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 277 "yacc_sql.y"
                                   {    }
#line 1672 "y.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 282 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[-3].number), (yyvsp[-1].number));
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name =(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type = $2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length = $4;
			CONTEXT->value_length++;
		}
#line 1687 "y.tab.c"
    break;

  case 40: /* attr_def: ID_get type  */
#line 293 "yacc_sql.y"
                {
			AttrInfo attribute;
			attr_info_init(&attribute, CONTEXT->id, (yyvsp[0].number), 4);
			create_table_append_attribute(&CONTEXT->ssql->sstr.create_table, &attribute);
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name=(char*)malloc(sizeof(char));
			// strcpy(CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].name, CONTEXT->id); 
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].type=$2;  
			// CONTEXT->ssql->sstr.create_table.attributes[CONTEXT->value_length].length=4; // default attribute length
			CONTEXT->value_length++;
		}
#line 1702 "y.tab.c"
    break;

  case 41: /* number: NUMBER  */
#line 305 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1708 "y.tab.c"
    break;

  case 42: /* type: INT_T  */
#line 308 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1714 "y.tab.c"
    break;

  case 43: /* type: DATE_T  */
#line 309 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1720 "y.tab.c"
    break;

  case 44: /* type: STRING_T  */
#line 310 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1726 "y.tab.c"
    break;

  case 45: /* type: FLOAT_T  */
#line 311 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1732 "y.tab.c"
    break;

  case 46: /* ID_get: ID  */
#line 315 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1741 "y.tab.c"
    break;

  case 47: /* insert: INSERT INTO ID VALUES brace_value_list multi_value_list SEMICOLON  */
#line 324 "yacc_sql.y"
                {
			// CONTEXT->values[CONTEXT->value_length++] = *$6;

			CONTEXT->ssql->flag=SCF_INSERT;//"insert";
			// CONTEXT->ssql->sstr.insertion.relation_name = $3;
			// CONTEXT->ssql->sstr.insertion.value_num = CONTEXT->value_length;
			// for(i = 0; i < CONTEXT->value_length; i++){
			// 	CONTEXT->ssql->sstr.insertion.values[i] = CONTEXT->values[i];
      // }
			inserts_init(&CONTEXT->ssql->sstr.insertion, (yyvsp[-4].string), CONTEXT->values, CONTEXT->value_length);

      //临时变量清零
      CONTEXT->value_length=0;
    }
#line 1760 "y.tab.c"
    break;

  case 49: /* multi_value_list: COMMA brace_value_list multi_value_list  */
#line 341 "yacc_sql.y"
                                                  {}
#line 1766 "y.tab.c"
    break;

  case 50: /* brace_value_list: LBRACE value value_list RBRACE  */
#line 344 "yacc_sql.y"
                                       {}
#line 1772 "y.tab.c"
    break;

  case 52: /* value_list: COMMA value value_list  */
#line 348 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1780 "y.tab.c"
    break;

  case 53: /* value: NUMBER  */
#line 353 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1788 "y.tab.c"
    break;

  case 54: /* value: FLOAT  */
#line 356 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1796 "y.tab.c"
    break;

  case 55: /* value: SSS  */
#line 359 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1805 "y.tab.c"
    break;

  case 56: /* delete: DELETE FROM ID where SEMICOLON  */
#line 367 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1817 "y.tab.c"
    break;

  case 57: /* update: UPDATE ID SET ID EQ value where SEMICOLON  */
#line 377 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			Value *value = &CONTEXT->values[0];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-6].string), (yyvsp[-4].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
		}
#line 1829 "y.tab.c"
    break;

  case 58: /* select: SELECT select_attr FROM ID rel_list where SEMICOLON  */
#line 387 "yacc_sql.y"
                {
			// CONTEXT->ssql->sstr.selection.relations[CONTEXT->from_length++]=$4;
			selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-3].string));

			selects_append_conditions(&CONTEXT->ssql->sstr.selection, CONTEXT->conditions, CONTEXT->condition_length);

			CONTEXT->ssql->flag=SCF_SELECT;//"select";
			// CONTEXT->ssql->sstr.selection.attr_num = CONTEXT->select_length;

			//临时变量清零
			CONTEXT->condition_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
	}
#line 1849 "y.tab.c"
    break;

  case 59: /* select_attr: STAR  */
#line 405 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1859 "y.tab.c"
    break;

  case 60: /* select_attr: STAR attr_list  */
#line 410 "yacc_sql.y"
                        {
			RelAttr attr;
			relation_attr_init(&attr,NULL,"*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);

		}
#line 1870 "y.tab.c"
    break;

  case 61: /* select_attr: ID attr_list  */
#line 416 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1880 "y.tab.c"
    break;

  case 62: /* select_attr: ID DOT ID attr_list  */
#line 421 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1890 "y.tab.c"
    break;

  case 63: /* select_attr: aggr attr_list  */
#line 427 "yacc_sql.y"
                         {}
#line 1896 "y.tab.c"
    break;

  case 64: /* aggr: MAX LBRACE ID RBRACE  */
#line 431 "yacc_sql.y"
                             {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "MAX");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1908 "y.tab.c"
    break;

  case 65: /* aggr: MIN LBRACE ID RBRACE  */
#line 438 "yacc_sql.y"
                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "MIN");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1920 "y.tab.c"
    break;

  case 66: /* aggr: SUM LBRACE ID RBRACE  */
#line 445 "yacc_sql.y"
                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "SUM");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1932 "y.tab.c"
    break;

  case 67: /* aggr: AVG LBRACE ID RBRACE  */
#line 452 "yacc_sql.y"
                               {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "AVG");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1944 "y.tab.c"
    break;

  case 68: /* aggr: COUNT LBRACE ID RBRACE  */
#line 459 "yacc_sql.y"
                                 {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "COUNT");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		relation_attr_init(&attr, NULL, (yyvsp[-1].string));
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1956 "y.tab.c"
    break;

  case 69: /* aggr: COUNTALLXING  */
#line 466 "yacc_sql.y"
                       {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "COUNT(*)");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1966 "y.tab.c"
    break;

  case 70: /* aggr: COUNTALL1  */
#line 471 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "COUNT(1)");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 1976 "y.tab.c"
    break;

  case 72: /* attr_list: COMMA ID attr_list  */
#line 480 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 1988 "y.tab.c"
    break;

  case 73: /* attr_list: COMMA ID DOT ID attr_list  */
#line 487 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2000 "y.tab.c"
    break;

  case 74: /* attr_list: COMMA aggr attr_list  */
#line 494 "yacc_sql.y"
                               {}
#line 2006 "y.tab.c"
    break;

  case 76: /* index_list: COMMA ID index_list  */
#line 499 "yacc_sql.y"
                          {	
				create_index_append(&CONTEXT->ssql->sstr.create_index,(yyvsp[-1].string));
		  }
#line 2014 "y.tab.c"
    break;

  case 78: /* rel_list: COMMA ID rel_list  */
#line 506 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2022 "y.tab.c"
    break;

  case 80: /* where: WHERE condition condition_list  */
#line 512 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2030 "y.tab.c"
    break;

  case 82: /* condition_list: AND condition condition_list  */
#line 518 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2038 "y.tab.c"
    break;

  case 83: /* condition: ID comOp value  */
#line 524 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));

			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name = NULL;
			// $$->left_attr.attribute_name= $1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2063 "y.tab.c"
    break;

  case 84: /* condition: value comOp value  */
#line 545 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 2];
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$ = ( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 0;
			// $$->right_attr.relation_name = NULL;
			// $$->right_attr.attribute_name = NULL;
			// $$->right_value = *$3;

		}
#line 2087 "y.tab.c"
    break;

  case 85: /* condition: ID comOp ID  */
#line 565 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, NULL, (yyvsp[-2].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=$1;
			// $$->comp = CONTEXT->comp;
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;

		}
#line 2111 "y.tab.c"
    break;

  case 86: /* condition: value comOp ID  */
#line 585 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];
			RelAttr right_attr;
			relation_attr_init(&right_attr, NULL, (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp=CONTEXT->comp;
			
			// $$->right_is_attr = 1;
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=$3;
		
		}
#line 2137 "y.tab.c"
    break;

  case 87: /* condition: ID DOT ID comOp value  */
#line 607 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-4].string), (yyvsp[-2].string));
			Value *right_value = &CONTEXT->values[CONTEXT->value_length - 1];

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 0, NULL, right_value);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;

			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp=CONTEXT->comp;
			// $$->right_is_attr = 0;   //属性值
			// $$->right_attr.relation_name=NULL;
			// $$->right_attr.attribute_name=NULL;
			// $$->right_value =*$5;			
							
    }
#line 2162 "y.tab.c"
    break;

  case 88: /* condition: value comOp ID DOT ID  */
#line 628 "yacc_sql.y"
                {
			Value *left_value = &CONTEXT->values[CONTEXT->value_length - 1];

			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 0, NULL, left_value, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 0;//属性值
			// $$->left_attr.relation_name=NULL;
			// $$->left_attr.attribute_name=NULL;
			// $$->left_value = *$1;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;//属性
			// $$->right_attr.relation_name = $3;
			// $$->right_attr.attribute_name = $5;
									
    }
#line 2187 "y.tab.c"
    break;

  case 89: /* condition: ID DOT ID comOp ID DOT ID  */
#line 649 "yacc_sql.y"
                {
			RelAttr left_attr;
			relation_attr_init(&left_attr, (yyvsp[-6].string), (yyvsp[-4].string));
			RelAttr right_attr;
			relation_attr_init(&right_attr, (yyvsp[-2].string), (yyvsp[0].string));

			Condition condition;
			condition_init(&condition, CONTEXT->comp, 1, &left_attr, NULL, 1, &right_attr, NULL);
			CONTEXT->conditions[CONTEXT->condition_length++] = condition;
			// $$=( Condition *)malloc(sizeof( Condition));
			// $$->left_is_attr = 1;		//属性
			// $$->left_attr.relation_name=$1;
			// $$->left_attr.attribute_name=$3;
			// $$->comp =CONTEXT->comp;
			// $$->right_is_attr = 1;		//属性
			// $$->right_attr.relation_name=$5;
			// $$->right_attr.attribute_name=$7;
    }
#line 2210 "y.tab.c"
    break;

  case 90: /* comOp: EQ  */
#line 670 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2216 "y.tab.c"
    break;

  case 91: /* comOp: LT  */
#line 671 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2222 "y.tab.c"
    break;

  case 92: /* comOp: GT  */
#line 672 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2228 "y.tab.c"
    break;

  case 93: /* comOp: LE  */
#line 673 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2234 "y.tab.c"
    break;

  case 94: /* comOp: GE  */
#line 674 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2240 "y.tab.c"
    break;

  case 95: /* comOp: NE  */
#line 675 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2246 "y.tab.c"
    break;

  case 96: /* comOp: LK  */
#line 676 "yacc_sql.y"
             { CONTEXT->comp = LIKE; }
#line 2252 "y.tab.c"
    break;

  case 97: /* comOp: NLK  */
#line 677 "yacc_sql.y"
              { CONTEXT->comp = NOT_LIKE; }
#line 2258 "y.tab.c"
    break;

  case 98: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 682 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2267 "y.tab.c"
    break;


#line 2271 "y.tab.c"

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
      yyerror (scanner, YY_("syntax error"));
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
                      yytoken, &yylval, scanner);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, scanner);
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
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 687 "yacc_sql.y"

//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, Query *sqls){
	ParserContext context;
	memset(&context, 0, sizeof(context));

	yyscan_t scanner;
	yylex_init_extra(&context, &scanner);
	context.ssql = sqls;
	scan_string(s, scanner);
	int result = yyparse(scanner);
	yylex_destroy(scanner);
	return result;
}
