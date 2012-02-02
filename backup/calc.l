%{
	#include <stdio.h>
	#include <stdlib.h>
        double num;
	int var=0;
%}

%%

[0-9]+	 		{ num=atof(yytext); printf("NUMBER:    %10.6f\n", num); }
[0-9]+"."[0-9]+ 	{ num=atof(yytext); printf("NUMBER:    %10.6f\n", num); }
e|pi			{ num=atof(yytext); printf("NUMBER:    %s\n", yytext); }
"."[0-9]+ 		{ num=atof(yytext); printf("NUMBER:    %10.6f\n", num); }
\/\/" "[a-zA-Z0-9 :\?\t]+ 	  { yytext=&yytext[3]; printf("STR: %s\n", yytext); }
\/\/[a-zA-Z0-9 :\?\t]+         { yytext=&yytext[2]; printf("STR: %s\n", yytext); }
\n    	    	 		    { printf("%s\n", "newline:"); }
#				    { printf("NUMBER:\n"); }
[A-Z]				    { var=*yytext-65; printf("VAR:%d\n", var); }
[+\-*/()\^:\?]     	            { printf("%s:\n", yytext); }
(meter)|(m)|(meters)		    { printf("MEASURE: %s\n", "m"); }
(as)				    { printf("%s:\n", "AS"); }
(sqrt)|(ln)|(abs)|(sin)|(cos)|(exp) { printf("FUNCTION: %s\n", yytext); } 
(kg)|(kilo)|(kilogram)|(kilograms)  { printf("MEASURE: %s\n", "kg"); }
(s)|(sec)|(second)|(seconds)	    { printf("MEASURE: %s\n", "s"); }
(radian)|(radians)		    { printf("MEASURE: %s\n", "r"); }
(deg)|(degree)|(degrees)	    { printf("MEASURE: %s\n", "deg"); }
(l)|(liter)|(liters)		    { printf("MEASURE: %s\n", "l"); }
(gal)|(gallon)|(gallons)	    { printf("MEASURE: %s\n", "gal"); }
(lb)|(lbs)|(pound)|(pounds)	    { printf("MEASURE: %s\n", "lb"); }
(g)|(gm)|(gms)|(gram)|(grams)	    { printf("MEASURE: %s\n", "g"); }
(ly)|(lightyear)|(lightyears)	    { printf("MEASURE: %s\n", "ly"); }
(k)|(km)|(kilometer)|(kilometers)   { printf("MEASURE: %s\n", "km"); }
(cm)|(centimeter)|(centimeters)	    { printf("MEASURE: %s\n", "cm"); }
(mm)|(millimeter)|(millimeters)     { printf("MEASURE: %s\n", "mm"); }  
(micron)|(microns)		    { printf("MEASURE: %s\n", "micron"); }
(in)|(inch)|(inches)		    { printf("MEASURE: %s\n", "in"); }
(yd)|(yard)|(yards)		    { printf("MEASURE: %s\n", "yd"); }
(ft)|(feet)|(foot)		    { printf("MEASURE: %s\n", "ft"); }
(mi)|(mile)|(miles)		    { printf("MEASURE: %s\n", "mi"); }
(a)|(ac)|(acre)|(acres)		    { printf("MEASURE: %s\n", "a"); }
(ha)|(hectare)|(hectares)	    { printf("MEASURE: %s\n", "ha"); }
(mph)				    { printf("MEASURE: %s\n", "mph"); }
(kph)				    { printf("MEASURE: %s\n", "kph"); }
(day)|(days)			    { printf("MEASURE: %s\n", "day"); }
(h)|(hr)|(hour)|(hours)		    { printf("MEASURE: %s\n", "h"); }
(min)|(minute)|(minutes)	    { printf("MEASURE: %s\n", "min"); }

. 			;
%%

int main()
{
	yylex();
}
