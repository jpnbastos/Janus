#include <iostream>
#include "graph/edgeinfo.h"
#include "graph/graph.h"
#include "automata/logistics.h"
#include "activity/activity.h"


#define YYDEBUG 1 // This is new

// prototype of bison-generated parser function
int yyparse(Automata* spec, Activity* act);

int main(int argc, char **argv){
    extern FILE* yyin;
    Automata spec = Automata();
    Activity act = Activity();
    cout << "Starting Parser: " << endl;
    yyin = fopen(argv[1], "r");

    do {
        yyparse(&spec,&act);


    } while (!feof(yyin));
    cout << "Finished Parsing" << endl;
    cout << "Found " << spec.getLocationSet().size() << endl;
    cout << "Found initial " << spec.getInitial()->getName() << endl;
    cout << "Found marked " << spec.getMarkedSet().size() << endl;
    cout << "Found edges: " << spec.getTransitionSet().size() << endl;

// printing automaton out
    spec.printAutomataToFile("cifout.cif");

    /**
     * @todo make the parser store the info of the activities
     * @todo make it extendable for a list of activities
     * @todo convert each activity into a matrix
     * @todo implement the state-space algorithm
     * @todo get the results out
     */
    cout << "Finished Parsing Activity" << endl;
    cout << "Found " << act.getVertexSet().size() << endl;
    cout << "Found edges: " << act.getEdgeSet().size() << endl;
    return 0;
}

void yyerror(Automata* spec, Activity* act, const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
