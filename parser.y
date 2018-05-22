%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern int yylex();
#include "logistics.h"
#include "activity.h"
#include <stack>



void yyerror(Automata* spec, set<Activity*>* acts,  const char* s);
int id = 0;
std::string src;
Activity* act = NULL;
stack <string> eventx;
stack <Activity*> activitiesx;
stack <Node*> nodesx;

struct superDep {
    std::string src;
    std::string dst;
};

stack <superDep> depsx;
%}

%parse-param {Automata* spec}
%parse-param {set<Activity*>* acts}

%union {
	int ival;
	float fval;
    char* sval;
    Activity* activity;
    Node* node;
    Dep* dep;
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
%token T_ACTIVITIES
%token T_FINAL
%type<sval> ALPHANUM
%type<ival> NUMBER
%type<activity> activities
%type<activity> activity
%type<node> node
%type<dep> deps

%error-verbose

%start lines

%%

lines: {}
    | line lines
;

line: {}
    | T_CONTROLLABLE words T_EOL1 {}
    | T_SUPERVISOR ALPHANUM T_EOL2 contents T_EO {spec->setName($2); }
    | T_ALPHABET words T_EOL1 {}
    | T_ACTIVITIES T_EOL2 activities T_FINAL {}
;

activities: {}
    | activity activities { acts->insert($1); }
;

activity:
    | T_ACTIVITY ALPHANUM T_EOL2 T_NODES T_EOL2 nodes T_DEPS T_EOL2 deps T_EO {
        Activity* act1 = new Activity($2);

          int n_size = nodesx.size();
          for(int f = 0; f < n_size; f++){
                    Node* a = nodesx.top();
                    act1->addNodeByPointer(a);
                    nodesx.pop();
         }
         int d_size = depsx.size();
         for(int w = 0; w < d_size; w++){
                    superDep a = depsx.top();
                    act1->addDepByName(a.src.c_str(),a.dst.c_str());
                    depsx.pop();
         }
     $$ = act1;
     id = 0;
    }
;


nodes: {}
    | node nodes { nodesx.push($1);}
;

node: {}
    |  T_CLAIM ALPHANUM ALPHANUM T_EOL1  { Node* node = new Node($2,id,0.0,"",$3,true,false); $$ = node; id++; }
    |  T_RELEASE ALPHANUM ALPHANUM T_EOL1 { Node* node = new Node($2,id,0.0,"",$3,false,true); $$ = node; id++; }
    |  T_ACTION ALPHANUM ALPHANUM ALPHANUM NUMBER T_EOL1 { Node* node = new Node($2,id,$5,$3,$4,false,false); $$ = node; id++; }
;

deps: {}
    | dep deps {}
;
dep: {}
    |  T_DEP ALPHANUM ALPHANUM T_EOL1  { superDep temp; temp.src = $2; temp.dst = $3; depsx.push(temp); }
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
        int e_size = eventx.size();
        for(int i = 0; i < e_size; i++){
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





