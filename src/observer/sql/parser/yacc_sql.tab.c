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
  size_t select_sub_condition_length;
  Condition select_sub_conditions[MAX_NUM];
  CompOp comp;
	char id[MAX_NUM];
  size_t values_for_update_length;
  Value values_for_update[MAX_NUM];
  size_t index_for_value;
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


#line 133 "y.tab.c"

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
    MAX = 303,                     /* MAX  */
    MIN = 304,                     /* MIN  */
    SUM = 305,                     /* SUM  */
    AVG = 306,                     /* AVG  */
    COUNT = 307,                   /* COUNT  */
    COUNTALLXING = 308,            /* COUNTALLXING  */
    COUNTALL1 = 309,               /* COUNTALL1  */
    NUMBER = 310,                  /* NUMBER  */
    FLOAT = 311,                   /* FLOAT  */
    ID = 312,                      /* ID  */
    PATH = 313,                    /* PATH  */
    SSS = 314,                     /* SSS  */
    STAR = 315,                    /* STAR  */
    STRING_V = 316                 /* STRING_V  */
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
#define MAX 303
#define MIN 304
#define SUM 305
#define AVG 306
#define COUNT 307
#define COUNTALLXING 308
#define COUNTALL1 309
#define NUMBER 310
#define FLOAT 311
#define ID 312
#define PATH 313
#define SSS 314
#define STAR 315
#define STRING_V 316

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 122 "yacc_sql.y"

  struct _Attr *attr;
  struct _Condition *condition1;
  struct _Value *value1;
  char *string;
  int number;
  float floats;
	char *position;

#line 317 "y.tab.c"

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
  YYSYMBOL_MAX = 48,                       /* MAX  */
  YYSYMBOL_MIN = 49,                       /* MIN  */
  YYSYMBOL_SUM = 50,                       /* SUM  */
  YYSYMBOL_AVG = 51,                       /* AVG  */
  YYSYMBOL_COUNT = 52,                     /* COUNT  */
  YYSYMBOL_COUNTALLXING = 53,              /* COUNTALLXING  */
  YYSYMBOL_COUNTALL1 = 54,                 /* COUNTALL1  */
  YYSYMBOL_NUMBER = 55,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 56,                     /* FLOAT  */
  YYSYMBOL_ID = 57,                        /* ID  */
  YYSYMBOL_PATH = 58,                      /* PATH  */
  YYSYMBOL_SSS = 59,                       /* SSS  */
  YYSYMBOL_STAR = 60,                      /* STAR  */
  YYSYMBOL_STRING_V = 61,                  /* STRING_V  */
  YYSYMBOL_YYACCEPT = 62,                  /* $accept  */
  YYSYMBOL_commands = 63,                  /* commands  */
  YYSYMBOL_command = 64,                   /* command  */
  YYSYMBOL_exit = 65,                      /* exit  */
  YYSYMBOL_help = 66,                      /* help  */
  YYSYMBOL_sync = 67,                      /* sync  */
  YYSYMBOL_begin = 68,                     /* begin  */
  YYSYMBOL_commit = 69,                    /* commit  */
  YYSYMBOL_rollback = 70,                  /* rollback  */
  YYSYMBOL_drop_table = 71,                /* drop_table  */
  YYSYMBOL_show_tables = 72,               /* show_tables  */
  YYSYMBOL_desc_table = 73,                /* desc_table  */
  YYSYMBOL_create_index = 74,              /* create_index  */
  YYSYMBOL_create_unique_index = 75,       /* create_unique_index  */
  YYSYMBOL_show_index = 76,                /* show_index  */
  YYSYMBOL_drop_index = 77,                /* drop_index  */
  YYSYMBOL_create_table = 78,              /* create_table  */
  YYSYMBOL_attr_def_list = 79,             /* attr_def_list  */
  YYSYMBOL_attr_def = 80,                  /* attr_def  */
  YYSYMBOL_number = 81,                    /* number  */
  YYSYMBOL_type = 82,                      /* type  */
  YYSYMBOL_ID_get = 83,                    /* ID_get  */
  YYSYMBOL_insert = 84,                    /* insert  */
  YYSYMBOL_multi_value_list = 85,          /* multi_value_list  */
  YYSYMBOL_brace_value_list = 86,          /* brace_value_list  */
  YYSYMBOL_value_list = 87,                /* value_list  */
  YYSYMBOL_value = 88,                     /* value  */
  YYSYMBOL_value_update = 89,              /* value_update  */
  YYSYMBOL_update_sub_rel_list = 90,       /* update_sub_rel_list  */
  YYSYMBOL_select_attr_update_sub = 91,    /* select_attr_update_sub  */
  YYSYMBOL_delete = 92,                    /* delete  */
  YYSYMBOL_update = 93,                    /* update  */
  YYSYMBOL_select = 94,                    /* select  */
  YYSYMBOL_select_attr = 95,               /* select_attr  */
  YYSYMBOL_aggr = 96,                      /* aggr  */
  YYSYMBOL_attr_list = 97,                 /* attr_list  */
  YYSYMBOL_index_list = 98,                /* index_list  */
  YYSYMBOL_update_id_list = 99,            /* update_id_list  */
  YYSYMBOL_rel_list = 100,                 /* rel_list  */
  YYSYMBOL_where = 101,                    /* where  */
  YYSYMBOL_condition_list = 102,           /* condition_list  */
  YYSYMBOL_condition = 103,                /* condition  */
  YYSYMBOL_comOp = 104,                    /* comOp  */
  YYSYMBOL_load_data = 105                 /* load_data  */
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
typedef yytype_int16 yy_state_t;

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
#define YYLAST   303

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  117
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  259

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


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
      55,    56,    57,    58,    59,    60,    61
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   148,   148,   150,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   176,   181,   186,   192,   198,   204,   210,
     216,   222,   229,   242,   253,   262,   270,   279,   281,   285,
     296,   309,   312,   313,   314,   315,   318,   327,   343,   345,
     348,   350,   352,   357,   360,   363,   367,   386,   389,   392,
     396,   414,   416,   422,   427,   433,   438,   443,   447,   457,
     473,   492,   497,   503,   508,   513,   517,   522,   527,   532,
     537,   542,   547,   552,   557,   562,   567,   572,   581,   583,
     590,   597,   600,   602,   607,   609,   616,   618,   622,   624,
     628,   630,   635,   656,   676,   696,   718,   739,   760,   782,
     783,   784,   785,   786,   787,   788,   789,   793
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
  "NLK", "UNIQUE", "MAX", "MIN", "SUM", "AVG", "COUNT", "COUNTALLXING",
  "COUNTALL1", "NUMBER", "FLOAT", "ID", "PATH", "SSS", "STAR", "STRING_V",
  "$accept", "commands", "command", "exit", "help", "sync", "begin",
  "commit", "rollback", "drop_table", "show_tables", "desc_table",
  "create_index", "create_unique_index", "show_index", "drop_index",
  "create_table", "attr_def_list", "attr_def", "number", "type", "ID_get",
  "insert", "multi_value_list", "brace_value_list", "value_list", "value",
  "value_update", "update_sub_rel_list", "select_attr_update_sub",
  "delete", "update", "select", "select_attr", "aggr", "attr_list",
  "index_list", "update_id_list", "rel_list", "where", "condition_list",
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
     315,   316
};
#endif

#define YYPACT_NINF (-215)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -215,     8,  -215,     1,    31,   134,   -32,     3,    40,    21,
      20,    -5,    54,    57,    66,    67,    70,    38,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    25,    34,
      86,    43,    53,    79,    95,    98,   100,   101,  -215,  -215,
      -4,   110,    93,   110,   126,   135,   120,  -215,    80,    97,
     118,  -215,  -215,  -215,  -215,  -215,   117,   141,   123,   102,
     161,   165,    14,    36,    55,    82,    96,   160,   112,  -215,
    -215,   122,  -215,  -215,  -215,   133,   150,   157,   136,   143,
     146,   148,   171,  -215,  -215,  -215,   175,  -215,   198,  -215,
     199,  -215,   218,  -215,   219,    -2,   110,   110,   220,   234,
     223,   -10,   237,   202,   213,  -215,   225,   209,   228,   188,
    -215,  -215,  -215,  -215,  -215,   189,  -215,  -215,  -215,   190,
     157,  -215,    42,   230,   240,  -215,  -215,   132,  -215,   179,
     217,  -215,   111,   245,   146,   235,  -215,  -215,  -215,  -215,
     238,   196,   239,   110,   220,   253,   241,   223,   254,   147,
     201,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    22,
      64,   -10,  -215,   251,  -215,  -215,  -215,   243,   205,   225,
     260,   210,   246,   211,  -215,  -215,  -215,    42,   249,   230,
    -215,    12,   110,   236,   110,   179,  -215,  -215,   242,  -215,
     217,   147,   212,   157,   268,  -215,  -215,  -215,   255,   216,
     257,   246,   241,  -215,  -215,   221,  -215,  -215,   222,  -215,
     106,   224,  -215,   244,   247,   273,  -215,  -215,   246,   274,
     263,  -215,   110,   264,   256,  -215,  -215,   226,   111,  -215,
    -215,  -215,   282,  -215,   231,   157,   232,   264,   243,  -215,
     264,   270,  -215,   157,  -215,  -215,  -215,   275,  -215
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
       0,     0,     0,     0,     0,     0,     0,     0,    81,    82,
      88,    71,     0,    88,     0,     0,     0,    25,     0,     0,
       0,    26,    27,    28,    24,    23,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    73,
      72,     0,    75,    31,    30,     0,     0,    98,     0,     0,
       0,     0,     0,    29,    35,    83,     0,    84,     0,    86,
       0,    85,     0,    87,     0,    88,    88,    88,    96,     0,
       0,     0,     0,     0,     0,    46,    37,     0,     0,     0,
      76,    77,    78,    79,    80,     0,    89,    91,    74,     0,
      98,    34,     0,    48,     0,    53,    54,     0,    55,     0,
     100,    68,     0,     0,     0,     0,    42,    44,    45,    43,
      40,     0,     0,    88,    96,     0,    51,     0,     0,     0,
       0,   109,   110,   111,   112,   113,   114,   115,   116,     0,
       0,     0,    99,     0,    57,    58,    59,    94,     0,    37,
       0,     0,    92,     0,    90,    97,    70,     0,     0,    48,
      47,    88,    63,     0,    88,     0,   104,   102,   105,   103,
     100,     0,     0,    98,     0,    38,    36,    41,     0,     0,
       0,    92,    51,    50,    49,     0,    65,    64,     0,    67,
       0,     0,   101,     0,     0,     0,   117,    39,    92,     0,
       0,    52,    88,    61,     0,   106,   107,     0,     0,    69,
      93,    32,     0,    66,     0,    98,     0,    61,    94,    33,
      61,     0,   108,    98,    95,    62,    56,     0,    60
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,   114,   151,  -215,
    -215,  -215,  -215,   105,   139,    78,  -128,    59,  -214,    90,
    -215,  -215,  -215,   154,   -76,   -51,  -196,    50,   145,  -127,
     103,   129,  -134,  -215
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,   145,   116,   208,
     150,   117,    33,   158,   133,   188,   139,   177,   245,   193,
      34,    35,    36,    52,    53,    79,   210,   203,   130,   112,
     172,   140,   169,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      80,   106,    82,   155,   156,   170,   134,    38,     2,    39,
      55,    56,     3,     4,    77,   230,    77,     5,     6,     7,
       8,     9,    10,    11,    78,    54,   125,    12,    13,    14,
      77,    95,   240,   253,    15,    16,   255,    41,   134,    42,
     215,   197,   199,    57,    17,   135,   136,   137,    40,   138,
      58,    59,    60,    97,   126,   127,   128,    61,   134,   212,
      62,   220,    43,    44,    45,    46,    47,    48,    49,    63,
      64,    50,    99,    65,    51,    66,   225,   135,   136,   196,
     134,   138,    67,   194,    43,    44,    45,    46,    47,    48,
      49,    68,   235,    50,    69,    72,    51,   135,   136,   101,
      70,   138,   184,    43,    44,    45,    46,    47,    48,    49,
      71,    73,    50,   103,    74,    51,    75,    76,   251,   135,
     136,   198,   134,   138,    81,   194,   257,   173,    77,    83,
      43,    44,    45,    46,    47,    48,    49,    86,    84,    50,
     216,   217,    51,   219,    43,    44,    45,    46,    47,    48,
      49,    85,    88,    50,    87,    89,    51,    90,    91,    92,
     160,   135,   136,   234,    93,   138,   174,   175,    94,   107,
     176,   161,   162,   163,   164,   165,   166,   167,   168,   108,
     110,   243,    43,    44,    45,    46,    47,    48,    49,   111,
     109,    50,   120,   113,    51,    43,    44,    45,    46,    47,
      48,    49,   114,   115,   191,   118,   119,   192,    43,    44,
      45,    46,    47,    48,    49,   121,   122,   105,   161,   162,
     163,   164,   165,   166,   167,   168,    96,    98,   100,   102,
     104,   146,   147,   148,   149,   123,   124,   131,   129,   132,
     141,   142,   143,   144,   151,   152,   153,   154,   157,   159,
     171,   178,   180,   182,   181,   183,   186,   190,   195,   187,
     201,   202,   204,   206,   209,   207,   213,   218,   211,   224,
     221,   226,   227,   228,   229,   237,   239,   241,   232,   233,
     242,   236,   244,   247,   246,   249,   238,   256,   250,   252,
     231,   223,   258,   205,   214,   179,   189,   248,   254,   185,
     200,     0,     0,   222
};

static const yytype_int16 yycheck[] =
{
      51,    77,    53,   130,   132,   139,    16,     6,     0,     8,
       7,     8,     4,     5,    18,   211,    18,     9,    10,    11,
      12,    13,    14,    15,    28,    57,    28,    19,    20,    21,
      18,    17,   228,   247,    26,    27,   250,     6,    16,     8,
      28,   169,   170,     3,    36,    55,    56,    57,    47,    59,
      29,    31,    57,    17,   105,   106,   107,     3,    16,   187,
       3,   195,    48,    49,    50,    51,    52,    53,    54,     3,
       3,    57,    17,     3,    60,    37,   203,    55,    56,    57,
      16,    59,    57,   159,    48,    49,    50,    51,    52,    53,
      54,    57,   220,    57,     8,    16,    60,    55,    56,    17,
      57,    59,   153,    48,    49,    50,    51,    52,    53,    54,
      57,    16,    57,    17,    16,    60,    16,    16,   245,    55,
      56,    57,    16,    59,    31,   201,   253,    16,    18,     3,
      48,    49,    50,    51,    52,    53,    54,    57,     3,    57,
     191,   192,    60,   194,    48,    49,    50,    51,    52,    53,
      54,    31,    34,    57,    57,    38,    60,    16,    35,    57,
      28,    55,    56,    57,     3,    59,    55,    56,     3,    57,
      59,    39,    40,    41,    42,    43,    44,    45,    46,    57,
      30,   232,    48,    49,    50,    51,    52,    53,    54,    32,
      57,    57,    17,    57,    60,    48,    49,    50,    51,    52,
      53,    54,    59,    57,    57,    57,    35,    60,    48,    49,
      50,    51,    52,    53,    54,    17,    17,    57,    39,    40,
      41,    42,    43,    44,    45,    46,    72,    73,    74,    75,
      76,    22,    23,    24,    25,    17,    17,     3,    18,    16,
       3,    39,    29,    18,    16,    57,    57,    57,    18,     9,
      33,     6,    17,    57,    16,    16,     3,     3,    57,    18,
       9,    18,    57,     3,    18,    55,    17,    31,    57,    57,
      28,     3,    17,    57,    17,    31,     3,     3,    57,    57,
      17,    57,    18,    57,    28,     3,    39,    17,    57,    57,
     212,   201,    17,   179,   189,   144,   157,   238,   248,   154,
     171,    -1,    -1,   200
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    63,     0,     4,     5,     9,    10,    11,    12,    13,
      14,    15,    19,    20,    21,    26,    27,    36,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    84,    92,    93,    94,   105,     6,     8,
      47,     6,     8,    48,    49,    50,    51,    52,    53,    54,
      57,    60,    95,    96,    57,     7,     8,     3,    29,    31,
      57,     3,     3,     3,     3,     3,    37,    57,    57,     8,
      57,    57,    16,    16,    16,    16,    16,    18,    28,    97,
      97,    31,    97,     3,     3,    31,    57,    57,    34,    38,
      16,    35,    57,     3,     3,    17,    95,    17,    95,    17,
      95,    17,    95,    17,    95,    57,    96,    57,    57,    57,
      30,    32,   101,    57,    59,    57,    80,    83,    57,    35,
      17,    17,    17,    17,    17,    28,    97,    97,    97,    18,
     100,     3,    16,    86,    16,    55,    56,    57,    59,    88,
     103,     3,    39,    29,    18,    79,    22,    23,    24,    25,
      82,    16,    57,    57,    57,   101,    88,    18,    85,     9,
      28,    39,    40,    41,    42,    43,    44,    45,    46,   104,
     104,    33,   102,    16,    55,    56,    59,    89,     6,    80,
      17,    16,    57,    16,    97,   100,     3,    18,    87,    86,
       3,    57,    60,    91,    96,    57,    57,    88,    57,    88,
     103,     9,    18,    99,    57,    79,     3,    55,    81,    18,
      98,    57,    88,    17,    85,    28,    97,    97,    31,    97,
     104,    28,   102,    91,    57,   101,     3,    17,    57,    17,
      98,    87,    57,    57,    57,    88,    57,    31,    39,     3,
      98,     3,    17,    97,    18,    90,    28,    57,    89,     3,
      57,   101,    57,    90,    99,    90,    17,   101,    17
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    63,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    79,    80,
      80,    81,    82,    82,    82,    82,    83,    84,    85,    85,
      86,    87,    87,    88,    88,    88,    88,    89,    89,    89,
      89,    90,    90,    91,    91,    91,    91,    91,    92,    93,
      94,    95,    95,    95,    95,    95,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    97,    97,
      97,    97,    98,    98,    99,    99,   100,   100,   101,   101,
     102,   102,   103,   103,   103,   103,   103,   103,   103,   104,
     104,   104,   104,   104,   104,   104,   104,   105
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     2,     2,     2,     4,
       3,     3,    10,    11,     5,     4,     8,     0,     3,     5,
       2,     1,     1,     1,     1,     1,     1,     7,     0,     3,
       4,     0,     3,     1,     1,     1,     8,     1,     1,     1,
       8,     0,     3,     1,     2,     2,     4,     2,     5,     9,
       7,     1,     2,     2,     4,     2,     4,     4,     4,     4,
       4,     1,     1,     3,     3,     3,     3,     3,     0,     3,
       5,     3,     0,     3,     0,     5,     0,     3,     0,     3,
       0,     3,     3,     3,     3,     3,     5,     5,     7,     1,
       1,     1,     1,     1,     1,     1,     1,     8
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
#line 176 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_EXIT;//"exit";
    }
#line 1592 "y.tab.c"
    break;

  case 24: /* help: HELP SEMICOLON  */
#line 181 "yacc_sql.y"
                   {
        CONTEXT->ssql->flag=SCF_HELP;//"help";
    }
#line 1600 "y.tab.c"
    break;

  case 25: /* sync: SYNC SEMICOLON  */
#line 186 "yacc_sql.y"
                   {
      CONTEXT->ssql->flag = SCF_SYNC;
    }
#line 1608 "y.tab.c"
    break;

  case 26: /* begin: TRX_BEGIN SEMICOLON  */
#line 192 "yacc_sql.y"
                        {
      CONTEXT->ssql->flag = SCF_BEGIN;
    }
#line 1616 "y.tab.c"
    break;

  case 27: /* commit: TRX_COMMIT SEMICOLON  */
#line 198 "yacc_sql.y"
                         {
      CONTEXT->ssql->flag = SCF_COMMIT;
    }
#line 1624 "y.tab.c"
    break;

  case 28: /* rollback: TRX_ROLLBACK SEMICOLON  */
#line 204 "yacc_sql.y"
                           {
      CONTEXT->ssql->flag = SCF_ROLLBACK;
    }
#line 1632 "y.tab.c"
    break;

  case 29: /* drop_table: DROP TABLE ID SEMICOLON  */
#line 210 "yacc_sql.y"
                            {
        CONTEXT->ssql->flag = SCF_DROP_TABLE;//"drop_table";
        drop_table_init(&CONTEXT->ssql->sstr.drop_table, (yyvsp[-1].string));
    }
#line 1641 "y.tab.c"
    break;

  case 30: /* show_tables: SHOW TABLES SEMICOLON  */
#line 216 "yacc_sql.y"
                          {
      CONTEXT->ssql->flag = SCF_SHOW_TABLES;
    }
#line 1649 "y.tab.c"
    break;

  case 31: /* desc_table: DESC ID SEMICOLON  */
#line 222 "yacc_sql.y"
                      {
      CONTEXT->ssql->flag = SCF_DESC_TABLE;
      desc_table_init(&CONTEXT->ssql->sstr.desc_table, (yyvsp[-1].string));
    }
#line 1658 "y.tab.c"
    break;

  case 32: /* create_index: CREATE INDEX ID ON ID LBRACE ID index_list RBRACE SEMICOLON  */
#line 230 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string));
			create_index_append(&CONTEXT->ssql->sstr.create_index,(yyvsp[-3].string));
			create_index_unset_unique(&CONTEXT->ssql->sstr.create_index);
			

		}
#line 1672 "y.tab.c"
    break;

  case 33: /* create_unique_index: CREATE UNIQUE INDEX ID ON ID LBRACE ID index_list RBRACE SEMICOLON  */
#line 243 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_CREATE_INDEX;//"create_index";
			create_index_init(&CONTEXT->ssql->sstr.create_index, (yyvsp[-7].string), (yyvsp[-5].string), (yyvsp[-3].string));
			create_index_append(&CONTEXT->ssql->sstr.create_index,(yyvsp[-3].string));
			create_index_set_unique(&CONTEXT->ssql->sstr.create_index);
		}
#line 1683 "y.tab.c"
    break;

  case 34: /* show_index: SHOW INDEX FROM ID SEMICOLON  */
#line 254 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_SHOW_INDEX;
			show_index_init(&CONTEXT->ssql->sstr.show_index,(yyvsp[-1].string));
		}
#line 1692 "y.tab.c"
    break;

  case 35: /* drop_index: DROP INDEX ID SEMICOLON  */
#line 263 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_DROP_INDEX;//"drop_index";
			drop_index_init(&CONTEXT->ssql->sstr.drop_index, (yyvsp[-1].string));
		}
#line 1701 "y.tab.c"
    break;

  case 36: /* create_table: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE SEMICOLON  */
#line 271 "yacc_sql.y"
                {
			CONTEXT->ssql->flag=SCF_CREATE_TABLE;//"create_table";
			// CONTEXT->ssql->sstr.create_table.attribute_count = CONTEXT->value_length;
			create_table_init_name(&CONTEXT->ssql->sstr.create_table, (yyvsp[-5].string));
			//临时变量清零	
			CONTEXT->value_length = 0;
		}
#line 1713 "y.tab.c"
    break;

  case 38: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 281 "yacc_sql.y"
                                   {    }
#line 1719 "y.tab.c"
    break;

  case 39: /* attr_def: ID_get type LBRACE number RBRACE  */
#line 286 "yacc_sql.y"
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
#line 1734 "y.tab.c"
    break;

  case 40: /* attr_def: ID_get type  */
#line 297 "yacc_sql.y"
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
#line 1749 "y.tab.c"
    break;

  case 41: /* number: NUMBER  */
#line 309 "yacc_sql.y"
                       {(yyval.number) = (yyvsp[0].number);}
#line 1755 "y.tab.c"
    break;

  case 42: /* type: INT_T  */
#line 312 "yacc_sql.y"
              { (yyval.number)=INTS; }
#line 1761 "y.tab.c"
    break;

  case 43: /* type: DATE_T  */
#line 313 "yacc_sql.y"
                    { (yyval.number)=DATES; }
#line 1767 "y.tab.c"
    break;

  case 44: /* type: STRING_T  */
#line 314 "yacc_sql.y"
                  { (yyval.number)=CHARS; }
#line 1773 "y.tab.c"
    break;

  case 45: /* type: FLOAT_T  */
#line 315 "yacc_sql.y"
                 { (yyval.number)=FLOATS; }
#line 1779 "y.tab.c"
    break;

  case 46: /* ID_get: ID  */
#line 319 "yacc_sql.y"
        {
		char *temp=(yyvsp[0].string); 
		snprintf(CONTEXT->id, sizeof(CONTEXT->id), "%s", temp);
	}
#line 1788 "y.tab.c"
    break;

  case 47: /* insert: INSERT INTO ID VALUES brace_value_list multi_value_list SEMICOLON  */
#line 328 "yacc_sql.y"
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
#line 1807 "y.tab.c"
    break;

  case 49: /* multi_value_list: COMMA brace_value_list multi_value_list  */
#line 345 "yacc_sql.y"
                                                  {}
#line 1813 "y.tab.c"
    break;

  case 50: /* brace_value_list: LBRACE value value_list RBRACE  */
#line 348 "yacc_sql.y"
                                       {}
#line 1819 "y.tab.c"
    break;

  case 52: /* value_list: COMMA value value_list  */
#line 352 "yacc_sql.y"
                              { 
  		// CONTEXT->values[CONTEXT->value_length++] = *$2;
	  }
#line 1827 "y.tab.c"
    break;

  case 53: /* value: NUMBER  */
#line 357 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].number));
		}
#line 1835 "y.tab.c"
    break;

  case 54: /* value: FLOAT  */
#line 360 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].floats));
		}
#line 1843 "y.tab.c"
    break;

  case 55: /* value: SSS  */
#line 363 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values[CONTEXT->value_length++], (yyvsp[0].string));
		}
#line 1852 "y.tab.c"
    break;

  case 56: /* value: LBRACE SELECT select_attr_update_sub FROM ID update_sub_rel_list where RBRACE  */
#line 368 "yacc_sql.y"
        {	

		value_init_select_sub(&CONTEXT->values[CONTEXT->value_length],&CONTEXT->ssql->sstr.selection);
		selects_append_relation((Selects *)CONTEXT->values[CONTEXT->value_length].select_sub_data,(yyvsp[-3].string));
		selects_append_conditions((Selects*)CONTEXT->values[CONTEXT->value_length].select_sub_data,CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->value_length++;

		// CONTEXT->ssql->flag=SCF_SELECT;//"select";
		CONTEXT->condition_length=0;
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		CONTEXT->ssql->sstr.selection.attr_num=0;
		CONTEXT->ssql->sstr.selection.relation_num=0;
		CONTEXT->ssql->sstr.selection.condition_num=0;
	}
#line 1872 "y.tab.c"
    break;

  case 57: /* value_update: NUMBER  */
#line 386 "yacc_sql.y"
          {	
  		value_init_integer(&CONTEXT->values_for_update[CONTEXT->values_for_update_length++], (yyvsp[0].number));
		}
#line 1880 "y.tab.c"
    break;

  case 58: /* value_update: FLOAT  */
#line 389 "yacc_sql.y"
          {
  		value_init_float(&CONTEXT->values_for_update[CONTEXT->values_for_update_length++], (yyvsp[0].floats));
		}
#line 1888 "y.tab.c"
    break;

  case 59: /* value_update: SSS  */
#line 392 "yacc_sql.y"
         {
			(yyvsp[0].string) = substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
  			value_init_string(&CONTEXT->values_for_update[CONTEXT->values_for_update_length++], (yyvsp[0].string));
		}
#line 1897 "y.tab.c"
    break;

  case 60: /* value_update: LBRACE SELECT select_attr_update_sub FROM ID update_sub_rel_list where RBRACE  */
#line 397 "yacc_sql.y"
        {	

		value_init_select_sub(&CONTEXT->values_for_update[CONTEXT->values_for_update_length],&CONTEXT->ssql->sstr.selection);
		selects_append_relation((Selects *)CONTEXT->values_for_update[CONTEXT->values_for_update_length].select_sub_data,(yyvsp[-3].string));
		selects_append_conditions((Selects*)CONTEXT->values_for_update[CONTEXT->values_for_update_length].select_sub_data,CONTEXT->conditions, CONTEXT->condition_length);
		CONTEXT->values_for_update_length++;
		// CONTEXT->ssql->flag=SCF_SELECT;//"select";
		CONTEXT->condition_length=0;
		CONTEXT->from_length=0;
		CONTEXT->select_length=0;
		CONTEXT->ssql->sstr.selection.attr_num=0;
		CONTEXT->ssql->sstr.selection.relation_num=0;
		CONTEXT->ssql->sstr.selection.condition_num=0;
		CONTEXT->value_length = 0;
	}
#line 1917 "y.tab.c"
    break;

  case 62: /* update_sub_rel_list: COMMA ID update_sub_rel_list  */
#line 416 "yacc_sql.y"
                                   {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 1925 "y.tab.c"
    break;

  case 63: /* select_attr_update_sub: STAR  */
#line 422 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1935 "y.tab.c"
    break;

  case 64: /* select_attr_update_sub: STAR attr_list  */
#line 427 "yacc_sql.y"
                        {
			RelAttr attr;
			relation_attr_init(&attr,NULL,"*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);

		}
#line 1946 "y.tab.c"
    break;

  case 65: /* select_attr_update_sub: ID attr_list  */
#line 433 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1956 "y.tab.c"
    break;

  case 66: /* select_attr_update_sub: ID DOT ID attr_list  */
#line 438 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 1966 "y.tab.c"
    break;

  case 67: /* select_attr_update_sub: aggr attr_list  */
#line 443 "yacc_sql.y"
                         {}
#line 1972 "y.tab.c"
    break;

  case 68: /* delete: DELETE FROM ID where SEMICOLON  */
#line 448 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_DELETE;//"delete";
			deletes_init_relation(&CONTEXT->ssql->sstr.deletion, (yyvsp[-2].string));
			deletes_set_conditions(&CONTEXT->ssql->sstr.deletion, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;	
    }
#line 1984 "y.tab.c"
    break;

  case 69: /* update: UPDATE ID SET ID EQ value_update update_id_list where SEMICOLON  */
#line 458 "yacc_sql.y"
                {
			CONTEXT->ssql->flag = SCF_UPDATE;//"update";
			CONTEXT->index_for_value+=1;
			Value *value = &CONTEXT->values_for_update[CONTEXT->values_for_update_length-CONTEXT->index_for_value];
			updates_init(&CONTEXT->ssql->sstr.update, (yyvsp[-7].string), (yyvsp[-5].string), value, 
					CONTEXT->conditions, CONTEXT->condition_length);
			CONTEXT->condition_length = 0;
			CONTEXT->index_for_value=0;
			CONTEXT->values_for_update_length=0;
			CONTEXT->from_length=0;
			CONTEXT->select_length=0;
			CONTEXT->value_length = 0;
		}
#line 2002 "y.tab.c"
    break;

  case 70: /* select: SELECT select_attr FROM ID rel_list where SEMICOLON  */
#line 474 "yacc_sql.y"
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
#line 2022 "y.tab.c"
    break;

  case 71: /* select_attr: STAR  */
#line 492 "yacc_sql.y"
         {  
			RelAttr attr;
			relation_attr_init(&attr, NULL, "*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2032 "y.tab.c"
    break;

  case 72: /* select_attr: STAR attr_list  */
#line 497 "yacc_sql.y"
                        {
			RelAttr attr;
			relation_attr_init(&attr,NULL,"*");
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);

		}
#line 2043 "y.tab.c"
    break;

  case 73: /* select_attr: ID attr_list  */
#line 503 "yacc_sql.y"
                   {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2053 "y.tab.c"
    break;

  case 74: /* select_attr: ID DOT ID attr_list  */
#line 508 "yacc_sql.y"
                              {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
		}
#line 2063 "y.tab.c"
    break;

  case 75: /* select_attr: aggr attr_list  */
#line 513 "yacc_sql.y"
                         {}
#line 2069 "y.tab.c"
    break;

  case 76: /* aggr: MAX LBRACE select_attr RBRACE  */
#line 517 "yacc_sql.y"
                                      {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "MAX");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2079 "y.tab.c"
    break;

  case 77: /* aggr: MIN LBRACE select_attr RBRACE  */
#line 522 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "MIN");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2089 "y.tab.c"
    break;

  case 78: /* aggr: SUM LBRACE select_attr RBRACE  */
#line 527 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "SUM");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2099 "y.tab.c"
    break;

  case 79: /* aggr: AVG LBRACE select_attr RBRACE  */
#line 532 "yacc_sql.y"
                                        {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "AVG");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2109 "y.tab.c"
    break;

  case 80: /* aggr: COUNT LBRACE select_attr RBRACE  */
#line 537 "yacc_sql.y"
                                          {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "COUNT");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2119 "y.tab.c"
    break;

  case 81: /* aggr: COUNTALLXING  */
#line 542 "yacc_sql.y"
                       {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "COUNT(*)");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2129 "y.tab.c"
    break;

  case 82: /* aggr: COUNTALL1  */
#line 547 "yacc_sql.y"
                    {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "COUNT(1)");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2139 "y.tab.c"
    break;

  case 83: /* aggr: MAX LBRACE RBRACE  */
#line 552 "yacc_sql.y"
                            {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "NONE");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2149 "y.tab.c"
    break;

  case 84: /* aggr: MIN LBRACE RBRACE  */
#line 557 "yacc_sql.y"
                            {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "NONE");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2159 "y.tab.c"
    break;

  case 85: /* aggr: AVG LBRACE RBRACE  */
#line 562 "yacc_sql.y"
                            {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "NONE");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2169 "y.tab.c"
    break;

  case 86: /* aggr: SUM LBRACE RBRACE  */
#line 567 "yacc_sql.y"
                            {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "NONE");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2179 "y.tab.c"
    break;

  case 87: /* aggr: COUNT LBRACE RBRACE  */
#line 572 "yacc_sql.y"
                              {
		RelAttr attr;
		relation_attr_init(&attr, NULL, "NONE");
		selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
	}
#line 2189 "y.tab.c"
    break;

  case 89: /* attr_list: COMMA ID attr_list  */
#line 583 "yacc_sql.y"
                         {
			RelAttr attr;
			relation_attr_init(&attr, NULL, (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
     	  // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].relation_name = NULL;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].attribute_name=$2;
      }
#line 2201 "y.tab.c"
    break;

  case 90: /* attr_list: COMMA ID DOT ID attr_list  */
#line 590 "yacc_sql.y"
                                {
			RelAttr attr;
			relation_attr_init(&attr, (yyvsp[-3].string), (yyvsp[-1].string));
			selects_append_attribute(&CONTEXT->ssql->sstr.selection, &attr);
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length].attribute_name=$4;
        // CONTEXT->ssql->sstr.selection.attributes[CONTEXT->select_length++].relation_name=$2;
  	  }
#line 2213 "y.tab.c"
    break;

  case 91: /* attr_list: COMMA aggr attr_list  */
#line 597 "yacc_sql.y"
                               {}
#line 2219 "y.tab.c"
    break;

  case 93: /* index_list: COMMA ID index_list  */
#line 602 "yacc_sql.y"
                          {	
				create_index_append(&CONTEXT->ssql->sstr.create_index,(yyvsp[-1].string));
		  }
#line 2227 "y.tab.c"
    break;

  case 95: /* update_id_list: COMMA ID EQ value_update update_id_list  */
#line 609 "yacc_sql.y"
                                              {
			CONTEXT->index_for_value+=1;				
			Value *value = &CONTEXT->values_for_update[CONTEXT->values_for_update_length-CONTEXT->index_for_value];
			updates_append_id_values(&CONTEXT->ssql->sstr.update,(yyvsp[-3].string),value);
		  }
#line 2237 "y.tab.c"
    break;

  case 97: /* rel_list: COMMA ID rel_list  */
#line 618 "yacc_sql.y"
                        {	
				selects_append_relation(&CONTEXT->ssql->sstr.selection, (yyvsp[-1].string));
		  }
#line 2245 "y.tab.c"
    break;

  case 99: /* where: WHERE condition condition_list  */
#line 624 "yacc_sql.y"
                                     {	
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2253 "y.tab.c"
    break;

  case 101: /* condition_list: AND condition condition_list  */
#line 630 "yacc_sql.y"
                                   {
				// CONTEXT->conditions[CONTEXT->condition_length++]=*$2;
			}
#line 2261 "y.tab.c"
    break;

  case 102: /* condition: ID comOp value  */
#line 636 "yacc_sql.y"
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
#line 2286 "y.tab.c"
    break;

  case 103: /* condition: value comOp value  */
#line 657 "yacc_sql.y"
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
#line 2310 "y.tab.c"
    break;

  case 104: /* condition: ID comOp ID  */
#line 677 "yacc_sql.y"
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
#line 2334 "y.tab.c"
    break;

  case 105: /* condition: value comOp ID  */
#line 697 "yacc_sql.y"
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
#line 2360 "y.tab.c"
    break;

  case 106: /* condition: ID DOT ID comOp value  */
#line 719 "yacc_sql.y"
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
#line 2385 "y.tab.c"
    break;

  case 107: /* condition: value comOp ID DOT ID  */
#line 740 "yacc_sql.y"
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
#line 2410 "y.tab.c"
    break;

  case 108: /* condition: ID DOT ID comOp ID DOT ID  */
#line 761 "yacc_sql.y"
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
#line 2433 "y.tab.c"
    break;

  case 109: /* comOp: EQ  */
#line 782 "yacc_sql.y"
             { CONTEXT->comp = EQUAL_TO; }
#line 2439 "y.tab.c"
    break;

  case 110: /* comOp: LT  */
#line 783 "yacc_sql.y"
         { CONTEXT->comp = LESS_THAN; }
#line 2445 "y.tab.c"
    break;

  case 111: /* comOp: GT  */
#line 784 "yacc_sql.y"
         { CONTEXT->comp = GREAT_THAN; }
#line 2451 "y.tab.c"
    break;

  case 112: /* comOp: LE  */
#line 785 "yacc_sql.y"
         { CONTEXT->comp = LESS_EQUAL; }
#line 2457 "y.tab.c"
    break;

  case 113: /* comOp: GE  */
#line 786 "yacc_sql.y"
         { CONTEXT->comp = GREAT_EQUAL; }
#line 2463 "y.tab.c"
    break;

  case 114: /* comOp: NE  */
#line 787 "yacc_sql.y"
         { CONTEXT->comp = NOT_EQUAL; }
#line 2469 "y.tab.c"
    break;

  case 115: /* comOp: LK  */
#line 788 "yacc_sql.y"
             { CONTEXT->comp = LIKE; }
#line 2475 "y.tab.c"
    break;

  case 116: /* comOp: NLK  */
#line 789 "yacc_sql.y"
              { CONTEXT->comp = NOT_LIKE; }
#line 2481 "y.tab.c"
    break;

  case 117: /* load_data: LOAD DATA INFILE SSS INTO TABLE ID SEMICOLON  */
#line 794 "yacc_sql.y"
                {
		  CONTEXT->ssql->flag = SCF_LOAD_DATA;
			load_data_init(&CONTEXT->ssql->sstr.load_data, (yyvsp[-1].string), (yyvsp[-4].string));
		}
#line 2490 "y.tab.c"
    break;


#line 2494 "y.tab.c"

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

#line 799 "yacc_sql.y"

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
