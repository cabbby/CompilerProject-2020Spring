/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "exp.y" /* yacc.c:339  */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include "IR.h"
#include "RHSDecompVisitor.h"
#include "BoundInferenceVisitor.h"
#include "IRPrinter.h"
#include "type.h"

using namespace Boost::Internal;
using std::set;
using std::string;
using std::vector;
using std::map;
using std::stack;
using std::cout;
using std::endl;
using std::stringstream;

#define YYSTYPE string

typedef vector<size_t> CList;
typedef vector<Expr> AList;

struct TRef {
    string id;
    CList *clist;
    AList *alist;
};

struct SRef {
    string id;
};

struct Const {
    void *val;
    int type;
};

Type index_type = Type::int_scalar(32);
Type data_type_i = Type::int_scalar(32);
Type data_type_f = Type::float_scalar(32);
Type var_type = data_type_f;
int temp_num = 0;

stack<void*> st;
stack<Expr> ste;
vector<Expr> cond;
vector<Stmt> result;


map<string, Expr> varMap;



int yyparse();
int yylex(void);
void yyerror(char *msg);

template <typename T>
void printVec(vector<T> vec, bool newline = 1);
void printExpr(const Expr& e);

template<typename T>
T parseConst(string str);

set<string> merge(const set<string>& a, const set<string>& b);
Stmt getMainStmt(TRef& lhs, Expr& rhs);
ExprNode *exprp(Expr &e);
set<string>& usedId(Expr& e);
bool insertExpr(vector<Expr>& arr, Expr& e);


#line 144 "exp.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "exp.tab.h".  */
#ifndef YY_YY_EXP_TAB_H_INCLUDED
# define YY_YY_EXP_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INTV = 259,
    FLOATV = 260,
    EQ = 261,
    PLUS = 262,
    MINUS = 263,
    MUL = 264,
    DIV = 265,
    IDIV = 266,
    MOD = 267
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_EXP_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 208 "exp.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   75

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  21
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  11
/* YYNRULES -- Number of rules.  */
#define YYNRULES  31
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  62

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   267

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      14,    15,     2,     2,    20,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    13,
      16,     2,    17,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    18,     2,    19,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    91,    91,    95,   102,   116,   124,   133,   142,   151,
     160,   169,   178,   185,   195,   202,   217,   242,   254,   260,
     268,   275,   286,   294,   303,   312,   321,   330,   339,   346,
     355,   364
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INTV", "FLOATV", "EQ", "PLUS",
  "MINUS", "MUL", "DIV", "IDIV", "MOD", "';'", "'('", "')'", "'<'", "'>'",
  "'['", "']'", "','", "$accept", "p", "s", "lhs", "rhs", "tref", "sref",
  "clist", "alist", "idexpr", "const", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,    59,    40,    41,    60,    62,    91,    93,
      44
};
# endif

#define YYPACT_NINF -23

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-23)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      27,    22,    42,   -23,    53,   -23,    45,   -23,   -23,    13,
     -23,    43,    38,   -23,   -23,    48,    13,    -6,   -23,   -23,
     -23,    52,    58,    45,   -23,    25,    13,    13,    13,    13,
      13,    13,   -23,    17,   -23,    44,   -23,    14,    14,   -23,
     -23,   -23,   -23,   -23,    17,    49,    39,    52,    32,   -23,
      17,     5,    62,    67,    68,   -23,    39,   -23,    46,   -23,
     -23,   -23
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     3,     0,     5,     0,     1,     2,     0,
      19,     0,     0,    30,    29,     0,     0,     0,    13,    14,
      15,     0,     0,     0,    31,     0,     0,     0,     0,     0,
       0,     0,     4,     0,    18,     0,    12,     6,     8,     7,
       9,    11,    10,    22,     0,     0,    21,    17,     0,    16,
       0,     0,     0,     0,     0,    28,    20,    24,    23,    25,
      26,    27
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -23,   -23,    71,   -23,   -16,    65,   -23,    51,   -23,   -22,
      60
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,    17,    18,    19,    11,    45,    46,
      20
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      25,    26,    27,    28,    29,    30,    31,    32,    43,    57,
      37,    38,    39,    40,    41,    42,    12,    13,    14,    44,
      43,    15,    48,    28,    29,    30,    31,    16,    56,    58,
       1,    44,    26,    27,    28,    29,    30,    31,     6,    51,
      36,    52,     7,    53,    54,     1,    51,    55,    52,    10,
      53,    54,    13,    14,    23,    52,    15,    53,    54,     9,
      21,    47,    34,    22,    22,     5,    59,     5,    49,    50,
      33,    60,    61,     8,    35,    24
};

static const yytype_uint8 yycheck[] =
{
      16,     7,     8,     9,    10,    11,    12,    13,     3,     4,
      26,    27,    28,    29,    30,    31,     3,     4,     5,    14,
       3,     8,    44,     9,    10,    11,    12,    14,    50,    51,
       3,    14,     7,     8,     9,    10,    11,    12,    16,     7,
      15,     9,     0,    11,    12,     3,     7,    15,     9,     4,
      11,    12,     4,     5,    16,     9,     8,    11,    12,     6,
      17,    17,     4,    20,    20,     0,     4,     2,    19,    20,
      18,     4,     4,     2,    23,    15
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    22,    23,    24,    26,    16,     0,    23,     6,
       4,    28,     3,     4,     5,     8,    14,    25,    26,    27,
      31,    17,    20,    16,    31,    25,     7,     8,     9,    10,
      11,    12,    13,    18,     4,    28,    15,    25,    25,    25,
      25,    25,    25,     3,    14,    29,    30,    17,    30,    19,
      20,     7,     9,    11,    12,    15,    30,     4,    30,     4,
       4,     4
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    21,    22,    22,    23,    24,    25,    25,    25,    25,
      25,    25,    25,    25,    25,    25,    26,    27,    28,    28,
      29,    29,    30,    30,    30,    30,    30,    30,    30,    31,
      31,    31
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     4,     1,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     7,     4,     3,     1,
       3,     1,     1,     3,     3,     3,     3,     3,     3,     1,
       1,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 92 "exp.y" /* yacc.c:1646  */
    {
    //cout << "P ::= P S\n";
}
#line 1323 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 96 "exp.y" /* yacc.c:1646  */
    {
    //cout << "P ::= S\n";
}
#line 1331 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 103 "exp.y" /* yacc.c:1646  */
    {
    //cout << "S ::= LHS = RHS;\n";
    Stmt e = getMainStmt(*((TRef*) st.top()), ste.top()); 
    st.pop();
    ste.pop();
    result.push_back(e);
    // cout << endl << IRPrinter().print(e) << endl;
    cond.clear();

}
#line 1346 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 117 "exp.y" /* yacc.c:1646  */
    {
    //cout << "LHS ::= TRef\n";
}
#line 1354 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 125 "exp.y" /* yacc.c:1646  */
    {
    //cout << "RHS ::= RHS + RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make((e1.type() == data_type_f || e2.type() == data_type_f)? data_type_f: data_type_i, BinaryOpType::Add, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
#line 1367 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 134 "exp.y" /* yacc.c:1646  */
    {
    //cout << "RHS ::= RHS * RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make((e1.type() == data_type_f || e2.type() == data_type_f)? data_type_f: data_type_i, BinaryOpType::Mul, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
#line 1380 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 143 "exp.y" /* yacc.c:1646  */
    {
    //cout << "RHS ::= RHS - RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make((e1.type() == data_type_f || e2.type() == data_type_f)? data_type_f: data_type_i, BinaryOpType::Sub, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
#line 1393 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 152 "exp.y" /* yacc.c:1646  */
    {
    // cout << "RHS ::= RHS / RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make(data_type_f, BinaryOpType::Div, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
#line 1406 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 161 "exp.y" /* yacc.c:1646  */
    {
    // cout << "RHS ::= RHS % RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make((e1.type() == data_type_f || e2.type() == data_type_f)? data_type_f: data_type_i, BinaryOpType::Mod, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
#line 1419 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 170 "exp.y" /* yacc.c:1646  */
    {
    // cout << "RHS ::= RHS // RHS\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make(data_type_i, BinaryOpType::IDiv, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
#line 1432 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 179 "exp.y" /* yacc.c:1646  */
    {
    // cout << "RHS ::= (RHS)\n";
    Expr e = ste.top(); ste.pop();
    exprp(e)->bracketed = 1;
    ste.push(e);
}
#line 1443 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 186 "exp.y" /* yacc.c:1646  */
    {
    // cout << "RHS ::= TRef\n";
    TRef *t = (TRef*) st.top(); st.pop();
    Expr e = Var::make(var_type, t->id, *(t->alist), *(t->clist));
    
    for (auto o : *(t->alist))
        usedId(e) = merge(usedId(e), usedId(o));
    ste.push(e);
}
#line 1457 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 196 "exp.y" /* yacc.c:1646  */
    {
    // cout << "RHS ::= SRef\n";
    SRef *t = (SRef*) st.top(); st.pop();
    Expr e = Var::make(var_type, t->id, {0}, {1});
    ste.push(e);
}
#line 1468 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 203 "exp.y" /* yacc.c:1646  */
    {
    // cout << "RHS ::= Const\n";
    Const *t = (Const*) st.top(); st.pop();
    if (t->type == 0) {
        Expr e = IntImm::make(data_type_i, *((int*) t->val));
        ste.push(e);
    } else {
        Expr e = FloatImm::make(data_type_f, *((float*) t->val));
        ste.push(e);
    }
}
#line 1484 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 218 "exp.y" /* yacc.c:1646  */
    {
    // cout << "TRef ::= Id<CList>[Alist]\n";
    TRef *t = new TRef();
    t->id = (yyvsp[-6]);
    t->alist = (AList*) st.top(); st.pop();
    t->clist = (CList*) st.top(); st.pop();

    st.push(t);

    Expr sign_e = Var::make(var_type, t->id, *(t->alist), *(t->clist));
    varMap[t->id] = sign_e;
    
    for (int i = 0; i < t->alist->size(); i++) {
        Expr c1 = Compare::make(index_type, CompareOpType::GE, t->alist->at(i), IntImm::make(index_type, 0));
        usedId(c1) = usedId(t->alist->at(i));
        // cout << IRPrinter().print(c1) << endl;
        insertExpr(cond, c1);
        Expr c2 = Compare::make(index_type, CompareOpType::LT, t->alist->at(i), IntImm::make(index_type, t->clist->at(i)));
        usedId(c2) = usedId(t->alist->at(i));
         // cout << IRPrinter().print(c2) << endl;
        insertExpr(cond, c2);
    }
}
#line 1512 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 243 "exp.y" /* yacc.c:1646  */
    {
    // cout << " SRef ::= Id<CList>\n";
    st.pop(); // clist
    SRef *t = new SRef();
    t->id = (yyvsp[-3]);
    st.push(t);

    Expr sign_e = Var::make(var_type, t->id, {0}, {1});
    varMap[t->id] = sign_e;
}
#line 1527 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 255 "exp.y" /* yacc.c:1646  */
    {
    // cout << "CList ::= CList, " << $3 << endl;
    CList *t = (CList*) st.top(); 
    t->push_back(parseConst<int>((yyvsp[0])));
}
#line 1537 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 261 "exp.y" /* yacc.c:1646  */
    {
    // cout << "CList ::= " << $1 << endl;
    CList *t = new CList();
    t->push_back(parseConst<int>((yyvsp[0])));
    st.push(t);
}
#line 1548 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 269 "exp.y" /* yacc.c:1646  */
    {
    // cout << "AList ::= AList, IdExpr\n";
    AList *t = (AList*) st.top();
    t->push_back(ste.top());
    ste.pop();
}
#line 1559 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 276 "exp.y" /* yacc.c:1646  */
    {
    // cout << "AList ::= IdExpr\n";
    AList *t = new AList();
    t->push_back(ste.top());
    ste.pop();
    st.push(t);
}
#line 1571 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 287 "exp.y" /* yacc.c:1646  */
    {
    // cout << "IdExpr ::= " << $1 << endl;
    Expr dom_t = Dom::make(Type::int_scalar(32), 0, 9);
    Expr t = Index::make(Type::int_scalar(32), (yyvsp[0]), dom_t, IndexType::Spatial);
    usedId(t).insert((yyvsp[0]));
    ste.push(t);
}
#line 1583 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 295 "exp.y" /* yacc.c:1646  */
    {
    // cout << "IdExpr ::= IdExpr + IdExpr\n";
    Expr e2 = ste.top(); ste.pop();
    Expr e1 = ste.top(); ste.pop();
    Expr t = Binary::make(index_type, BinaryOpType::Add, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
#line 1596 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 304 "exp.y" /* yacc.c:1646  */
    {
    // cout << "IdExpr ::= IdExpr + " << $3 << endl;
    Expr e1 = ste.top(); ste.pop();
    Expr e2 = IntImm::make(index_type, parseConst<int>((yyvsp[0])));
    Expr t = Binary::make(index_type, BinaryOpType::Add, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
#line 1609 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 313 "exp.y" /* yacc.c:1646  */
    {
    // cout << "IdExpr ::= IdExpr * " << $3 << endl;
    Expr e1 = ste.top(); ste.pop();
    Expr e2 = IntImm::make(index_type, parseConst<int>((yyvsp[0])));
    Expr t = Binary::make(index_type, BinaryOpType::Mul, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
#line 1622 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 322 "exp.y" /* yacc.c:1646  */
    {
    // cout << "IdExpr ::= IdExpr // " << $3 << endl;
    Expr e1 = ste.top(); ste.pop();
    Expr e2 = IntImm::make(index_type, parseConst<int>((yyvsp[0])));
    Expr t = Binary::make(index_type, BinaryOpType::IDiv, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
#line 1635 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 331 "exp.y" /* yacc.c:1646  */
    {
    //cout << "IdExpr ::= IdExpr % " << $3 << endl;
    Expr e1 = ste.top(); ste.pop();
    Expr e2 = IntImm::make(index_type, parseConst<int>((yyvsp[0])));
    Expr t = Binary::make(index_type, BinaryOpType::Mod, e1, e2);
    usedId(t) = merge(usedId(e1), usedId(e2));
    ste.push(t);
}
#line 1648 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 340 "exp.y" /* yacc.c:1646  */
    {
    //cout << "IdExpr ::= (IdExpr)\n";
}
#line 1656 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 347 "exp.y" /* yacc.c:1646  */
    {
    //cout << "Const ::= " << $1 << endl;
    Const *t = new Const;
    float *v = new float;
    *v = parseConst<float>((yyvsp[0]));
    t->val = v, t->type = 1;
    st.push(t);
}
#line 1669 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 356 "exp.y" /* yacc.c:1646  */
    {
    //cout << "Const ::= " << $1 << endl;
    Const *t = new Const;
    int *v = new int;
    *v = parseConst<int>((yyvsp[0]));
    t->val = v, t->type = 0;
    st.push(t);
}
#line 1682 "exp.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 365 "exp.y" /* yacc.c:1646  */
    {
    Const *t = (Const*) st.top();
    if (t->type == 0) {
        int *v = (int*) t->val;
        *v = -*v;
    } else {
        float *v = (float*) t->val;
        *v = -*v;
    }
}
#line 1697 "exp.tab.c" /* yacc.c:1646  */
    break;


#line 1701 "exp.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 377 "exp.y" /* yacc.c:1906  */



void yyerror(char *msg)
{
    cout << "Error encountered: " << msg << endl; 
}

template <typename T>
void printVec(vector<T> vec, bool newline) {
    for (auto t : vec) {
        cout << t << " ";
    }
    if (newline)
        cout << endl;
}

template<typename T>
T parseConst(string str) {
    stringstream ss;
    T t;
    ss << str;
    ss >> t;
    return t;
}

void printExpr(const Expr& e) {
    IRPrinter printer;
    string code = printer.print(e);
    cout << code << endl;
}

set<string> merge(const set<string>& a, const set<string>& b) {
    set<string> t;
    t.insert(a.begin(), a.end());
    t.insert(b.begin(), b.end());
    return t;
}

bool contain(vector<string>& a, const set<string>& b) {
    for (auto t : b) {
        bool flag = 0;
        for (auto r : a)
            if (t == r) {
                flag = 1; break;
            }
        if (!flag)
            return 0;
    }
    return 1;
}

vector<Expr> mapIdToExpr(map<string, Expr>& mp, vector<string> ids) {
    vector<Expr> res;
    for (auto id : ids)
        res.push_back(mp[id]);
    return res;
}

// 构造整个 Stmt
Stmt getMainStmt(TRef& lhs, Expr& rhs) {
    set<string> leftIdSet;   // 出现在 LHS 的循环变量
    vector<string> leftId, leftId1;   // 出现在 LHS 的循环变量
    map<string, Expr> mp;    // 从循环变量名到对应 Expr 的映射
    vector<Expr> stmtList;   

    for (auto e : *(lhs.alist))
        for (auto t : usedId(e)) {
            leftId.push_back(t);
            leftIdSet.insert(t);
        }

    // 为每个循环变量粗略定界
    BoundInferenceVisitor bv;
    for (auto id : leftId)
        bv.mp[id] = make_pair(0, 1 << 20);
    for (auto id : usedId(rhs))
        bv.mp[id] = make_pair(0, 1 << 20);
        
    for (auto e : cond) {
        // cout << "Condition : " << IRPrinter().print(e) << endl;
        Compare *t = (Compare*) e.get();
        if (t->op_type == CompareOpType::LT) {
            bv.lo = -(1 << 20);
            bv.hi = ((IntImm*) (t->b).get())->value();
            (t->a).visit_expr(&bv);
        } else if (t->op_type == CompareOpType::GE) {
            bv.lo = ((IntImm*) (t->b).get())->value();
            bv.hi = 1 << 20;
            (t->a).visit_expr(&bv);
        }
        /*
        for (auto t : bv.mp) {
            cout << t.first << " : [" << t.second.first << ", " << t.second.second << ")" << endl;
        }
        */
    }

    for (auto id : leftId) {
        Expr dom = Dom::make(index_type, bv.mp[id].first, bv.mp[id].second);
        mp[id] = Index::make(index_type, id, dom, IndexType::Spatial);
    }
    for (auto id : usedId(rhs)) {
        if (mp.find(id) == mp.end()) {
            Expr dom = Dom::make(index_type, bv.mp[id].first, bv.mp[id].second);
            mp[id] = Index::make(index_type, id, dom, IndexType::Reduce);
        }
    }

    // 处理 LHS 的循环变量和条件判断
    for (auto id : leftId) {
        // cout << id << endl;
        leftId1.push_back(id);
        stmtList.push_back(Var::make(index_type, id, {0}, {1}));      // 定义成 Var 只是为了将循环和条件判断区分开，无实际意义

        vector<Expr> nowCond;
        for (auto it = cond.begin(); it != cond.end(); )
            if (contain(leftId1, usedId(*it))) {
                // printExpr(*it);
                nowCond.push_back(*it);
                cond.erase(it);
            } else
                it++;
        
        if (nowCond.size() > 0) {
            Expr e = nowCond[0];
            if (nowCond.size() > 1) {
                for (int i = 1; i < nowCond.size(); i++)
                    e = Binary::make(data_type_i, BinaryOpType::And, e, nowCond[i]);
            }
            stmtList.push_back(e);
            // cout << "sum: ";
            // printExpr(e);
        }
    }

    RHSDecompVisitor visitor;
    rhs.visit_expr(&visitor);

    vector<Stmt> body;


    vector<size_t> shape;
    for (auto id : leftId)
        shape.push_back(bv.mp[id].second);

    Expr dest = Var::make(var_type, lhs.id, mapIdToExpr(mp, leftId), shape);

    // 处理 RHS 的循环变量和条件判断
    for (auto e : visitor.res) {
        

        vector<Expr> stmtList;
        vector<string> curId(leftId.begin(), leftId.end());
        vector<Expr> remCond(cond.begin(), cond.end());

        for (auto id : usedId(e.first)) {
            if (leftIdSet.find(id) != leftIdSet.end())
                continue;
            curId.push_back(id);
            stmtList.push_back(Var::make(index_type, id, {0}, {1}));

            vector<Expr> nowCond;
            for (auto it = remCond.begin(); it != remCond.end(); )
                if (contain(curId, usedId(*it))) {
                    // printExpr(*it);
                    nowCond.push_back(*it);
                    remCond.erase(it);
                } else
                    it++;

            if (nowCond.size() > 0) {
                Expr e = nowCond[0];
                if (nowCond.size() > 1) {
                    for (int i = 1; i < nowCond.size(); i++)
                        e = Binary::make(data_type_i, BinaryOpType::And, e, nowCond[i]);
                }
                stmtList.push_back(e);
            }
        }

        // 生成每个求和部分的 Stmt
        Stmt s = Move::make(
            dest, 
            Binary::make(data_type_i, e.second == 1? BinaryOpType::Add: BinaryOpType::Sub, dest, e.first),
            MoveType::MemToMem
        );

        for (int i = stmtList.size() - 1; i >= 0; i--) {
            if (stmtList[i].node_type() == IRNodeType::Var) {
                // 是循环语句
                string id = ((Var*) stmtList[i].get())->name;
                // cout << id << endl;
                // cout << (mp.find(id) == mp.end()) << endl;
                s = LoopNest::make({mp[id]}, {s});
            } else {
                // 是 if 语句
                s = IfThenElse::make(stmtList[i], s, Stmt());
            }
        }

        body.push_back(s);
        // cout << endl << IRPrinter().print(s) << endl;
    }

    // 套上 LHS 的循环和条件
    Stmt s = StmtList::make(body);
    for (int i = stmtList.size() - 1; i >= 0; i--) {
        if (stmtList[i].node_type() == IRNodeType::Var) {
            // 是循环语句
            string id = ((Var*) stmtList[i].get())->name;
            // cout << id << endl;
            s = LoopNest::make({mp[id]}, {s});
        } else {
            // 是 if 语句
            s = IfThenElse::make(stmtList[i], s, Stmt());
        }
    }

    return s;
}

ExprNode *exprp(Expr &e) {
    return (ExprNode*) e.get();
}

set<string>& usedId(Expr& e) {
    return exprp(e)->usedId;
}

// 用于去除重复的条件判断
bool insertExpr(vector<Expr>& arr, Expr& e) {
    for (auto t : arr) {
        if (IRPrinter().print(t) == IRPrinter().print(e)) {
            return 0;
        }
    }
    arr.push_back(e);
    return 1;
}

