#ifndef YYERRCODE
#define YYERRCODE 256
#endif

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
typedef union {
    long double dval;
    char *str;
    char whitespace;
    double (*FPT)(double);
    int index;
} YYSTYPE;
extern YYSTYPE yylval;
