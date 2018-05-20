%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylex();
#include "logistics.h"
#include "activity.h"
#include <stack>



void yyerror(Automata* spec, Activity* act,  const char* s);

std::string src;
stack <string> eventx;
%}

%parse-param {Automata* spec}
%parse-param {Activity* act}

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
%token T_EO2
%token T_EOL1
%token T_EOL2
%token T_ALPHABET
%token T_COMMA
%token T_CONTROLLABLE
%token T_SUPERVISOR
%token NUMBER
%token UNKNOWN
%token ALPHANUM

%token T_ACTIVITY
%token T_CLAIM
%token T_RELEASE
%token T_ACTION
%token T_NODES
%token T_DEPS
%token T_DEP

%type<sval> ALPHANUM
%type<Automata> specification

%error-verbose

%start specification

%%

specification:
	   | lines
;

lines: {}
    | line lines
;

line: {}
    | T_CONTROLLABLE words T_EOL1 { printf("YIIII");}
    | T_SUPERVISOR ALPHANUM T_EOL2 contents T_EO {spec->setName($2); }
    | T_ALPHABET words T_EOL1 {}
    | T_ACTIVITY ALPHANUM T_EOL2 lines T_EO {printf("YasdasdsadsadaI"); }
;

lines:
    | line lines
;

line:
    | T_CLAIM ALPHANUM ALPHANUM T_EOL1 line { printf("Found a claim! \n");}
    | T_RELEASE ALPHANUM ALPHANUM T_EOL1 line {printf("Found a release! \n");}
    | T_ACTION ALPHANUM ALPHANUM NUMBER T_EOL1 line {printf("Found a action! \n");}
    | T_DEP ALPHANUM ALPHANUM line T_EOL1 {printf("Found a edge! \n");}
;

contents:
    | content contents
;

content:
    | T_LOCATION ALPHANUM T_EOL2 {src = $2; spec->addLocation($2,false,false,false);}
    | T_LOCATION ALPHANUM T_EOL2 T_INITIAL T_EOL1 {src = $2; Location* newLoc = spec->addLocation($2,true,false,false); spec->setInitial(newLoc); }
    | T_LOCATION ALPHANUM T_EOL2 T_INITIAL T_EOL1 T_MARKED T_EOL1 content {src = $2; Location* newLoc = spec->addLocation($2,true,true,false); spec->addMarked(newLoc);}
    | T_LOCATION ALPHANUM T_EOL2 T_MARKED T_EOL1 {src = $2; Location* newLoc = spec->addLocation($2,false,true,false); spec->addMarked(newLoc);}
    | T_EDGE events T_GOTO ALPHANUM T_EOL1 {

        for(int i = 0; i < eventx.size(); i++){
            std::string a = eventx.top();
            spec->addTransition(src,$4,a);
            eventx.pop();
        }
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
    | ALPHANUM {}
    | ALPHANUM T_COMMA {}
;


%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}





