%{

#include <stdio.h>
#include <stdlib.h>



extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
	int ival;
	float fval;
    char* sval;
}


%token T_CONTROLLABLE
%token T_SUPERVISOR
%token NUMBER
%token UNKNOWN
%token ALPHANUM

%type<sval> ALPHANUM

%start specification

%%

specification:
	   | line
;

line:
    | T_CONTROLLABLE ALPHANUM line {printf("\tResult: %s\n", $2);}
;

%%

int main() {

    yyin = fopen("example.cif", "r");

    do {
        yyparse();
    } while (!feof(yyin));

    return 0;
}

void yyerror(const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}







