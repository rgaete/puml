calc : lex.yy.c y.tab.c
	gcc lex.yy.c y.tab.c -lfl -lm -o calc
y.tab.c: calc.y
	yacc -d calc.y
lex.yy.c : calc.l
	flex calc.l

