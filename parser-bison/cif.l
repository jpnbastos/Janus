%{
#include <stdio.h>

#define YY_DECL int yylex()
#include "cif.tab.h"

%}


digit         [0-9]
letter        [a-zA-Z]


%%

"controllable" { return T_CONTROLLABLE; }
"supervisor"   { T_SUPERVISOR; }


{letter}({letter}|{digit})* {
                       yylval.sval = strdup(yytext);
                       return ALPHANUM;      }
{digit}+             { yylval.ival = atoi(yytext);
                       return NUMBER;     }
[ \t\n\r]            /* skip whitespace */
.                    { printf("Unknown character [%c]\n",yytext[0]);
                       return UNKNOWN;    }
%%

int yywrap(void){return 1;}
