

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylex();
#include "logistics.h"
#include <stack>
void yyerror(Automata* spec, const char* s);

std::string src;
stack <string> eventx;
%}


%parse-param {Automata* spec}

%union {
	int ival;
	float fval;
    char* sval;
}


%token T_REQUIREMENT
%token T_PLANT
%token T_AUTOMATON
%token T_LOCATION
%token T_INITIAL
%token T_MARKED
%token T_EDGE
%token T_GOTO
%token T_EO
%token T_EOL1
%token T_EOL2
%token T_ALPHABET
%token T_COMMA
%token T_CONTROLLABLE
%token T_SUPERVISOR
%token NUMBER
%token UNKNOWN
%token ALPHANUM



%type<sval> ALPHANUM
%type<Automata> specification

%start specification

%%

specification:
	   | lines
;

lines: {}
    | line lines
;

line: {}
    | T_CONTROLLABLE words T_EOL1 {}
    | T_SUPERVISOR ALPHANUM T_EOL2 contents T_EO { printf("ASDSADASDASDSAA"); spec->setName($2); }
    | T_ALPHABET words T_EOL1 {printf("Alphabet! \n");}
;

contents:
    | content contents
;

content:
    | T_LOCATION ALPHANUM T_EOL2 {src = $2; spec->addLocation($2,false,false,false); printf("Found Location! \n");}
    | T_LOCATION ALPHANUM T_EOL2 T_INITIAL T_EOL1 {src = $2; spec->addLocation($2,true,false,false); printf("Found Location1! %s\n",$2);}
    | T_LOCATION ALPHANUM T_EOL2 T_INITIAL T_EOL1 T_MARKED T_EOL1 content {src = $2; spec->addLocation($2,true,true,false); printf("Found Location2! \n");}
    | T_LOCATION ALPHANUM T_EOL2 T_MARKED T_EOL1 {src = $2; spec->addLocation($2,false,true,false); printf("Found Location3! \n");}
    | T_EDGE events T_GOTO ALPHANUM T_EOL1 {

        for(int i = 0; i < eventx.size(); i++){
            std::string a = eventx.top();
            spec->addTransition(src,$4,a);
            cout << "Yeay!" << a << endl;
            eventx.pop();
        }

     printf("Found edge to %s! \n", $4);
     }
;

events:
    | event events {}
;

event:
    | ALPHANUM {std::string name($1); eventx.push(name);}
    | ALPHANUM T_COMMA {std::string name($1); eventx.push(name);}
;

words:
    | word words {}
;

word:
    | ALPHANUM {printf("word: %s\n", $1);}
    | ALPHANUM T_COMMA {printf("word: %s\n", $1);}
;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}





