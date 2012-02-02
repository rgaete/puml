%{
	#include <stdio.h>
	#include <stdlib.h>
        #include "y.tab.h"
	#include <math.h>
	double num;
	double var;
%}

%%
[0-9]+"."?	 		{ yylval.dval=atof(yytext); return NUM; }
[0-9]+"."[0-9]+	 	{ yylval.dval=atof(yytext); return NUM; }
e			{ yylval.dval=2.718281828459045235360287471352662497757; return NUM; }
pi			{ yylval.dval=3.141592653589793238462643383279502884197; return NUM; }
"."[0-9]+ 		{ yylval.dval=atof(yytext); return NUM; }
\/\/" "?[a-zA-Z0-9 :\?\t]+        { yylval.str=&yytext[3]; return STRING; }
#				    { return POUND;}
[ \t]+				    {}
[A-Z]			{ yylval.index=(yytext[0]-65);  return VAR; }	
(as)				    { return AS; }
(abs)				    { return ABS;}
(sqrt)				    { yylval.FPT=sqrt; return FUNC; }
(ln)				    { yylval.FPT=log; return FUNC;}
(sin)			 	    { yylval.FPT=sin; return FUNC; } 
(cos)				    { yylval.FPT=cos; return FUNC; }
(exp)				    { yylval.FPT=exp; return FUNC; }			    
(kg)|(kilo)|(kgms)|(kilogram)|(kilograms)  { yylval.dval=1.0L; return NUM; }
(s)|(sec)|(second)|(seconds)	    { yylval.dval=1.0; return MEASUREMENT; }
(meter)|(m)|(meters)                { yylval.dval=1.0; return MEASUREMENT; }
(ml)                                { yylval.dval=0.44704; return MEASUREMENT; }
(radian)|(radians)		    { yylval.dval=1.0; return MEASUREMENT; }
(deg)|(degree)|(degrees)	    { yylval.dval=0.01745329251994329576923690768488612713443; return MEASUREMENT; }
(l)|(liter)|(liters)		    { yylval.dval=.001; return MEASUREMENT; }
(gal)|(gallon)|(gallons)	    { yylval.dval=.003785412; return MEASUREMENT; }
(lb)|(lbs)|(pound)|(pounds)	    { yylval.dval=.4535924; return MEASUREMENT; }
(g)|(gm)|(gms)|(gram)|(grams)	    { yylval.dval=0.001; return MEASUREMENT; }
(ly)|(lightyear)|(lightyears)	    { yylval.dval= 9.46073E+15; return MEASUREMENT;}
(k)|(km)|(kilometer)|(kilometers)   { yylval.dval=1000.0; return MEASUREMENT;}
(cm)|(centimeter)|(centimeters)	    { yylval.dval=0.01; return MEASUREMENT;}
(mm)|(millimeter)|(millimeters)     { yylval.dval=0.001; return MEASUREMENT; }  
(micron)|(microns)		    { yylval.dval=0.000001; return MEASUREMENT; }
(in)|(inch)|(inches)		    { yylval.dval=0.0254; return MEASUREMENT; }
(yd)|(yard)|(yards)		    { yylval.dval=0.9144; return MEASUREMENT;}
(ft)|(feet)|(foot)		    { yylval.dval=0.3048; return MEASUREMENT;}
(mi)|(mile)|(miles)		    { yylval.dval=1609.344; return MEASUREMENT;}
(a)|(ac)|(acre)|(acres)		    { yylval.dval=4046.8564224; return MEASUREMENT;}
(ha)|(hectare)|(hectares)	    { yylval.dval=10000.0; return MEASUREMENT;}
(mph)				    { yylval.dval=0.44704; return MEASUREMENT;}
(kph)				    { yylval.dval=0.2777778; return MEASUREMENT;}
(day)|(days)			    { yylval.dval=86400.0; return MEASUREMENT;}
(h)|(hr)|(hour)|(hours)		    { yylval.dval=3600.0; return MEASUREMENT;}
(min)|(minute)|(minutes)	    { yylval.dval=60.0; return MEASUREMENT;}
(exit)|(stop)|(quit)		    { return EXIT;}
^"\n"				    {}
.|\n                               {return yytext[0]; }

%%


