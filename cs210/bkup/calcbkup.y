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
    double (*FPT)(double);
    int index;
}

%token NUM EXIT FUNC MEASUREMENT AS STRING VAR POUND
%type <dval> POUND NUM MEASUREMENT measure exp0 exp1 exp2 exp3 exp4
%type <FPT> FUNC func 
%type <str> STRING
%type <index> VAR
%%
stmtlist : stmt '\n'
         | stmt '\n' stmtlist 
         ;
stmt     : exp0   	     { printf("Answer is %10.6Lf\n", $1); recent=$1; }
	 | STRING 	     { printf("%s\n", $1); }
	 | EXIT  	     { exit(0); }
	 ;
exp0	 : exp0 AS exp1      { $$ = $1 / $3; }
	 | VAR '=' exp1      { $$ = variable[$1] = $3; }
	 | exp1
	 ;
exp1     : exp1 '+' exp2     { $$ = $1 + $3; }
	 | exp1 '-' exp2     { $$ = $1 - $3; }
	 | exp2              { $$ = $1; }
         ;
exp2     : exp2 '*' exp3     { $$ = $1 * $3; }
	 | exp2 ' ' exp3     { $$ = $1 * $3; }
         | exp2 '/' exp3     { $$ = $1 / $3; }
         | exp3		     { $$ = $1; }
	 ;
exp3	 : exp3 '^' exp4     { $$ = pow($1,$3); }
	 | func'('exp4')'    { $$ = $1($3); }
	 | exp4
	 ;
exp4     : NUM               { $$ = $1; }
	 | VAR   	     { $$ = variable[$1]; }
	 | POUND	     { $$ = recent; }
	 | '(' exp0 ')'      { $$ = $2; }
	 | '[' exp0 ']'	     { $$ = $2; }
	 | NUM measure	     { $$ = $1 * $2; }	
	 | measure
	 ;
func	 : FUNC		     { $$ = $1; }
	 ;
measure  : MEASUREMENT       { $$ = $1; }
	 ;


%%
int main()
{
    yyparse();
    return 0;
}
