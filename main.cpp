#include <iostream>
#include "graph/edgeinfo.h"
#include "graph/graph.h"
#include "automata/logistics.h"


#define YYDEBUG 1 // This is new

// prototype of bison-generated parser function
int yyparse(Automata* spec);

int main(int argc, char **argv){
    extern FILE* yyin;
    Automata spec = Automata();
    cout << "Starting Parser: " << endl;
    yyin = fopen(argv[1], "r");

    do {
        yyparse(&spec);


    } while (!feof(yyin));
    cout << "Finished Parsing" << endl;
    cout << "Found " << spec.getLocationSet().size() << endl;
    cout << "Found initial " << spec.getInitial()->getName() << endl;
    cout << "Found marked " << spec.getMarkedSet().size() << endl;
    cout << "Found edges: " << spec.getTransitionSet().size() << endl;

// printing automaton out
    spec.printAutomataToFile("cifout.cif");
    return 0;
}

void yyerror(Automata* spec, const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
