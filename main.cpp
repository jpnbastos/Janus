#include <iostream>
#include "graph/edgeinfo.h"
#include "graph/graph.h"
#include "automata/logistics.h"
#include "activity/activity.h"


#define YYDEBUG 1 // This is new

// prototype of bison-generated parser function
int yyparse(Automata* spec, set<Activity*>* acts);

int main(int argc, char **argv){
    extern FILE* yyin;
    Automata spec = Automata();

    ActivitySet acts = ActivitySet();
    cout << "Starting Parser: " << endl;
    yyin = fopen(argv[1], "r");

    do {
        yyparse(&spec,&acts.activitySet);


    } while (!feof(yyin));
    cout << "Finished Parsing" << endl;
    cout << "Found " << spec.getLocationSet().size() << endl;
    cout << "Found initial " << spec.getInitial()->getName() << endl;
    cout << "Found marked " << spec.getMarkedSet().size() << endl;
    cout << "Found edges: " << spec.getTransitionSet().size() << endl;

// printing automaton out
    spec.printAutomataToFile("cifout.cif");

    /**
     * @todo convert each activity into a matrix
     * @todo implement the state-space algorithm
     * @todo get the results out
     */
    for(auto act : acts.activitySet) {
        cout << "Finished Parsing Activity " << act->getName() << endl;
        cout << "Found " << act->getNodeSet().size() << endl;
        cout << "Found edges: " << act->getDepSet().size() << endl;
    }
    return 0;
}

void yyerror(Automata* spec, set<Activity*>* acts, const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
