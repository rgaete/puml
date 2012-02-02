%{
#include <stdio.h>
#include <math.h>

extern int yylex();
long double variable[26];
long double recent;

#define YYERROR_VERBOSE
    void yyerror(const char *msg) {
        printf("ERROR(PARSER): %s\n", msg);
    }
%}

%union {
    long double dval;
    char *str;
    char whitespace;
    double (*FPT)(double);
    int index;
}

%token NUM EXIT ABS FUNC MEASUREMENT AS STRING VAR POUND NEWLINE SPACE
%type <dval> POUND NUM MEASUREMENT exp0 exp1 exp2 exp3 exp4 exp5
%type <FPT> FUNC func 
%type <str> STRING
%type <index> VAR
%type <whitespace> SPACE
%%
stmtlist : stmt '\n' stmtlist
	 ;
stmt     : exp0   	     { printf("\n%.9Lg\n", $1); recent=$1; }
	 | STRING 	     { printf("%s\n", $1); }
	 | EXIT  	     { exit(0); }
	 ;
exp0	 : exp0 AS exp1      { $$ = $1 / $3; }
	 | VAR '=' exp1      { $$ = variable[$1] = $3; }
	 | exp2
	 ;
exp1	 : VAR '=' exp2	     { $$ = variable[$1] = $3; }
	 | exp2
	 ;
exp2     : exp2 '+' exp3     { $$ = $1 + $3; }
	 | exp2 '-' exp3     { $$ = $1 - $3; }
	 | exp3              { $$ = $1; }
         ;
exp3     : exp3 '*' exp4     { $$ = $1 * $3; }
	 | exp3  exp4        { $$ = $1 * $2; }
         | exp3 '/' exp4     { $$ = $1 / $3; }
         | exp4		     { $$ = $1; }
	 ;
exp4	 : exp4 '^' exp5     { $$ = pow($1,$3); }
	 | exp5
	 ;
exp5     : NUM 		     {$$=$1;}
	 | VAR   	     { $$ = variable[$1]; }
	 | POUND	     { $$ = recent; }
	 | func exp5    { $$ = $1($2); }
	 | ABS exp5	{$$ = abs($2); }
	 | '(' exp0 ')'      { $$ = $2; }
	 | '[' exp0 ']'	     { $$ = $2; }	
	 | MEASUREMENT       { $$ = $1; }
	 ;
func	 : FUNC              { $$ = $1; }
	 ;



%%
int main()
{
    yyparse();
    return 0;
}
