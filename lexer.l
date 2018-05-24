%{
#include <stdio.h>
#include "activity.h"


#define YY_DECL int yylex()
#include "parser.hpp"

%}

digit         [0-9]
letter        [a-zA-Z]
underscore [_]

%%

"controllable"  { return T_CONTROLLABLE; }
"supervisor"    { return T_SUPERVISOR; }
"automaton"     { return T_AUTOMATON; }
"plant"         { return T_PLANT; }
"requirement"   { return T_REQUIREMENT; }
"alphabet"      { return T_ALPHABET; }
"location"      { return T_LOCATION; }
"initial"       { return T_INITIAL; }
"marked"        { return T_MARKED; }
"edge"          { return T_EDGE; }
"goto"          { return T_GOTO; }
";"             { return T_EOL1; }
":"             { return T_EOL2; }
","             { return T_COMMA; }
"end"           { return T_EO; }
"!"             { return T_EO; }
"Activities"    { return T_ACTIVITIES;}
"final"         { return T_FINAL;}
"system"        { return T_SYSTEM;}
"resource"      { return T_RESOURCE;}
"activity"      { return T_ACTIVITY; }
"claim"         { return T_CLAIM; }
"release"       { return T_RELEASE; }
"action"        { return T_ACTION; }
"nodes"         { return T_NODES; }
"deps"          { return T_DEPS; }
"dep"           { return T_DEP; }

{letter}({letter}|{digit}|"_")* {
                       yylval.sval = strdup(yytext);
                       return ALPHANUM;      }
{digit}+             { yylval.ival = atoi(yytext);
                       return NUMBER;     }
[ \t\n\r]            /* skip whitespace */
.                    { printf("Unknown character [%c]\n",yytext[0]);
                       return UNKNOWN;    }
%%

int yywrap(void) {
    return 1;
}
