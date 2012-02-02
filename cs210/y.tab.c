#ifndef lint
static char const 
yyrcsid[] = "$FreeBSD: src/usr.bin/yacc/skeleton.c,v 1.28 2000/01/17 02:04:06 bde Exp $";
#endif
#include <stdlib.h>
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYLEX yylex()
#define YYEMPTY -1
#define yyclearin (yychar=(YYEMPTY))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING() (yyerrflag!=0)
static int yygrowstack();
#define YYPREFIX "yy"
#line 2 "calc.y"
#include <stdio.h>
#include <math.h>

extern int yylex();
long double variable[26];
long double recent;

#define YYERROR_VERBOSE
    void yyerror(const char *msg) {
        printf("ERROR(PARSER): %s\n", msg);
    }
#line 15 "calc.y"
typedef union {
    long double dval;
    char *str;
    char whitespace;
    double (*FPT)(double);
    int index;
} YYSTYPE;
#line 37 "y.tab.c"
#define YYERRCODE 256
#define NUM 257
#define EXIT 258
#define ABS 259
#define FUNC 260
#define MEASUREMENT 261
#define AS 262
#define STRING 263
#define VAR 264
#define POUND 265
#define NEWLINE 266
#define SPACE 267
const short yylhs[] = {                                        -1,
    0,    8,    8,    8,    1,    1,    1,    2,    2,    3,
    3,    3,    4,    4,    4,    4,    5,    5,    6,    6,
    6,    6,    6,    6,    6,    6,    7,
};
const short yylen[] = {                                         2,
    3,    1,    1,    1,    3,    3,    1,    3,    1,    3,
    3,    1,    3,    2,    3,    1,    3,    1,    1,    1,
    1,    2,    2,    3,    3,    1,    1,
};
const short yydefred[] = {                                      0,
   19,    4,    0,   27,   26,    3,    0,   21,    0,    0,
    0,    0,    0,    0,    0,   18,    0,    0,   20,   23,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   22,    0,    0,    6,    0,   24,   25,    5,    0,    0,
    0,    0,   17,    1,    0,    0,
};
const short yydgoto[] = {                                      11,
   12,   34,   13,   14,   15,   16,   17,   18,
};
const short yysindex[] = {                                    -39,
    0,    0,  -21,    0,    0,    0,  -55,    0,   37,   37,
    0, -247,  -32,  -30,  -78,    0,  -21,   12,    0,    0,
   48,  -34,  -91,   48,  -21,  -21,  -21,  -21,  -78,  -21,
    0,  -39,  -38,    0,  -32,    0,    0,    0,  -30,  -30,
  -78,  -78,    0,    0,  -21,  -32,
};
const short yyrindex[] = {                                      0,
    0,    0,    0,    0,    0,    0,  -10,    0,    0,    0,
    0,   14,    4,   33,   -1,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    8,    0,
    0,    0,  -10,    0,   62,    0,    0,    0,   44,   53,
   17,   26,    0,    0,    0,   65,
};
const short yygindex[] = {                                     -7,
   -6,    2,  -16,   -5,   93,   83,    0,    0,
};
#define YYTABLESIZE 327
const short yytable[] = {                                      20,
    9,   37,   22,   23,   35,   21,   36,   35,   16,    9,
   25,   27,   26,    7,   24,   30,   28,   14,    9,   39,
   40,   32,   45,    2,   44,   38,   13,    0,   46,   20,
   20,   20,   20,    0,   20,   15,   20,    0,   16,   16,
   16,   16,   12,   16,    7,   16,    0,   14,   14,   14,
   14,   10,   14,   10,   14,    0,   13,   13,   13,   13,
   10,   13,   11,   13,    0,   15,   15,   15,   15,   10,
   15,    9,   15,   12,    8,   12,    9,   12,    0,    0,
   20,    0,   20,   20,   10,   20,   10,    9,   10,   16,
    0,   16,    0,   11,    0,   11,    7,   11,   14,   31,
   14,    0,    9,    0,    0,    8,   29,   13,    0,   13,
    0,    0,   43,    0,    0,    0,   15,    0,   15,   41,
   42,    0,    0,    0,    0,   12,    0,   10,    0,    0,
    0,   29,   29,    0,    0,    0,   10,    0,   10,    0,
    0,    0,    0,    0,    0,   11,    0,    0,    0,    0,
    0,    0,    0,    0,    9,    0,    0,    8,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   24,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    1,    2,    3,
    4,    5,    0,    6,    7,    8,    1,   24,    3,    4,
    5,    0,    0,   19,    8,    1,    0,    3,    4,    5,
    0,    0,   19,    8,    0,    0,   20,    0,   20,   20,
   20,   20,    0,   20,   20,   16,    0,   16,   16,   16,
   16,    0,   16,   16,   14,    7,   14,   14,   14,   14,
    0,   14,   14,   13,    0,   13,   13,   13,   13,    0,
   13,   13,   15,    0,   15,   15,   15,   15,    0,   15,
   15,    0,    0,    1,   12,    3,    4,    5,    0,    0,
    7,    8,    0,    0,    1,   10,    3,    4,    5,    0,
    0,   33,    8,    0,   11,    0,    0,    0,    0,    0,
    0,    0,    0,    9,    0,    0,    8,
};
const short yycheck[] = {                                      10,
   40,   93,    9,   10,   21,   61,   41,   24,   10,   40,
   43,   42,   45,   10,  262,   94,   47,   10,   40,   25,
   26,   10,   61,   10,   32,   24,   10,   -1,   45,   40,
   41,   42,   43,   -1,   45,   10,   47,   -1,   40,   41,
   42,   43,   10,   45,   41,   47,   -1,   40,   41,   42,
   43,   91,   45,   10,   47,   -1,   40,   41,   42,   43,
   91,   45,   10,   47,   -1,   40,   41,   42,   43,   91,
   45,   10,   47,   41,   10,   43,   40,   45,   -1,   -1,
   91,   -1,   93,   94,   41,    3,   43,   40,   45,   91,
   -1,   93,   -1,   41,   -1,   43,   93,   45,   91,   17,
   93,   -1,   41,   -1,   -1,   41,   14,   91,   -1,   93,
   -1,   -1,   30,   -1,   -1,   -1,   91,   -1,   93,   27,
   28,   -1,   -1,   -1,   -1,   93,   -1,   91,   -1,   -1,
   -1,   39,   40,   -1,   -1,   -1,   93,   -1,   91,   -1,
   -1,   -1,   -1,   -1,   -1,   93,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   93,   -1,   -1,   93,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  262,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
  260,  261,   -1,  263,  264,  265,  257,  262,  259,  260,
  261,   -1,   -1,  264,  265,  257,   -1,  259,  260,  261,
   -1,   -1,  264,  265,   -1,   -1,  257,   -1,  259,  260,
  261,  262,   -1,  264,  265,  257,   -1,  259,  260,  261,
  262,   -1,  264,  265,  257,  262,  259,  260,  261,  262,
   -1,  264,  265,  257,   -1,  259,  260,  261,  262,   -1,
  264,  265,  257,   -1,  259,  260,  261,  262,   -1,  264,
  265,   -1,   -1,  257,  262,  259,  260,  261,   -1,   -1,
  264,  265,   -1,   -1,  257,  262,  259,  260,  261,   -1,
   -1,  264,  265,   -1,  262,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  262,   -1,   -1,  262,
};
#define YYFINAL 11
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 267
#if YYDEBUG
const char * const yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
0,0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,
"']'","'^'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"NUM","EXIT","ABS","FUNC","MEASUREMENT","AS","STRING","VAR",
"POUND","NEWLINE","SPACE",
};
const char * const yyrule[] = {
"$accept : stmtlist",
"stmtlist : stmt '\\n' stmtlist",
"stmt : exp0",
"stmt : STRING",
"stmt : EXIT",
"exp0 : exp0 AS exp1",
"exp0 : VAR '=' exp1",
"exp0 : exp2",
"exp1 : VAR '=' exp2",
"exp1 : exp2",
"exp2 : exp2 '+' exp3",
"exp2 : exp2 '-' exp3",
"exp2 : exp3",
"exp3 : exp3 '*' exp4",
"exp3 : exp3 exp4",
"exp3 : exp3 '/' exp4",
"exp3 : exp4",
"exp4 : exp4 '^' exp5",
"exp4 : exp5",
"exp5 : NUM",
"exp5 : VAR",
"exp5 : POUND",
"exp5 : func exp5",
"exp5 : ABS exp5",
"exp5 : '(' exp0 ')'",
"exp5 : '[' exp0 ']'",
"exp5 : MEASUREMENT",
"func : FUNC",
};
#endif
#if YYDEBUG
#include <stdio.h>
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH 10000
#endif
#endif
#define YYINITSTACKSIZE 200
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short *yyss;
short *yysslim;
YYSTYPE *yyvs;
int yystacksize;
#line 70 "calc.y"
int main()
{
    yyparse();
    return 0;
}
#line 239 "y.tab.c"
/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack()
{
    int newsize, i;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = yystacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;
    i = yyssp - yyss;
    newss = yyss ? (short *)realloc(yyss, newsize * sizeof *newss) :
      (short *)malloc(newsize * sizeof *newss);
    if (newss == NULL)
        return -1;
    yyss = newss;
    yyssp = newss + i;
    newvs = yyvs ? (YYSTYPE *)realloc(yyvs, newsize * sizeof *newvs) :
      (YYSTYPE *)malloc(newsize * sizeof *newvs);
    if (newvs == NULL)
        return -1;
    yyvs = newvs;
    yyvsp = newvs + i;
    yystacksize = newsize;
    yysslim = yyss + newsize - 1;
    return 0;
}

#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab

#ifndef YYPARSE_PARAM
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG void
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif	/* ANSI-C/C++ */
#else	/* YYPARSE_PARAM */
#ifndef YYPARSE_PARAM_TYPE
#define YYPARSE_PARAM_TYPE void *
#endif
#if defined(__cplusplus) || __STDC__
#define YYPARSE_PARAM_ARG YYPARSE_PARAM_TYPE YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else	/* ! ANSI-C/C++ */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL YYPARSE_PARAM_TYPE YYPARSE_PARAM;
#endif	/* ANSI-C/C++ */
#endif	/* ! YYPARSE_PARAM */

int
yyparse (YYPARSE_PARAM_ARG)
    YYPARSE_PARAM_DECL
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register const char *yys;

    if ((yys = getenv("YYDEBUG")))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    if (yyss == NULL && yygrowstack()) goto yyoverflow;
    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if ((yyn = yydefred[yystate])) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yysslim && yygrowstack())
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#if defined(lint) || defined(__GNUC__)
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#if defined(lint) || defined(__GNUC__)
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yysslim && yygrowstack())
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 2:
#line 32 "calc.y"
{ printf("\n%.9Lg\n", yyvsp[0].dval); recent=yyvsp[0].dval; }
break;
case 3:
#line 33 "calc.y"
{ printf("%s\n", yyvsp[0].str); }
break;
case 4:
#line 34 "calc.y"
{ exit(0); }
break;
case 5:
#line 36 "calc.y"
{ yyval.dval = yyvsp[-2].dval / yyvsp[0].dval; }
break;
case 6:
#line 37 "calc.y"
{ yyval.dval = variable[yyvsp[-2].index] = yyvsp[0].dval; }
break;
case 8:
#line 40 "calc.y"
{ yyval.dval = variable[yyvsp[-2].index] = yyvsp[0].dval; }
break;
case 10:
#line 43 "calc.y"
{ yyval.dval = yyvsp[-2].dval + yyvsp[0].dval; }
break;
case 11:
#line 44 "calc.y"
{ yyval.dval = yyvsp[-2].dval - yyvsp[0].dval; }
break;
case 12:
#line 45 "calc.y"
{ yyval.dval = yyvsp[0].dval; }
break;
case 13:
#line 47 "calc.y"
{ yyval.dval = yyvsp[-2].dval * yyvsp[0].dval; }
break;
case 14:
#line 48 "calc.y"
{ yyval.dval = yyvsp[-1].dval * yyvsp[0].dval; }
break;
case 15:
#line 49 "calc.y"
{ yyval.dval = yyvsp[-2].dval / yyvsp[0].dval; }
break;
case 16:
#line 50 "calc.y"
{ yyval.dval = yyvsp[0].dval; }
break;
case 17:
#line 52 "calc.y"
{ yyval.dval = pow(yyvsp[-2].dval,yyvsp[0].dval); }
break;
case 19:
#line 55 "calc.y"
{yyval.dval=yyvsp[0].dval;}
break;
case 20:
#line 56 "calc.y"
{ yyval.dval = variable[yyvsp[0].index]; }
break;
case 21:
#line 57 "calc.y"
{ yyval.dval = recent; }
break;
case 22:
#line 58 "calc.y"
{ yyval.dval = yyvsp[-1].FPT(yyvsp[0].dval); }
break;
case 23:
#line 59 "calc.y"
{yyval.dval = abs(yyvsp[0].dval); }
break;
case 24:
#line 60 "calc.y"
{ yyval.dval = yyvsp[-1].dval; }
break;
case 25:
#line 61 "calc.y"
{ yyval.dval = yyvsp[-1].dval; }
break;
case 26:
#line 62 "calc.y"
{ yyval.dval = yyvsp[0].dval; }
break;
case 27:
#line 64 "calc.y"
{ yyval.FPT = yyvsp[0].FPT; }
break;
#line 526 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yysslim && yygrowstack())
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
