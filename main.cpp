#include <iostream>
#include "graph/edgeinfo.h"
#include "graph/graph.h"
#include "automata/logistics.h"
#include "activity/activity.h"
#include "maxplus/maxplus.h"
#include "maxplus/statespace.h"
#include "activity/plant.h"

#define N_INF -std::numeric_limits<double>::infinity()


#define YYDEBUG 1 // This is new

// prototype of bison-generated parser function
int yyparse(Automata* spec, set<Activity*>* acts, Plant* sys);

int main(int argc, char **argv){
    extern FILE* yyin;
    Automata spec = Automata();
    Plant sys = Plant();
    ActivitySet acts = ActivitySet();
    cout << "Starting Parser: " << endl;
    yyin = fopen(argv[1], "r");

    do {
        yyparse(&spec,&acts.activitySet,&sys);


    } while (!feof(yyin));

    cout << "Finished Parsing" << endl;
    cout << "Found " << spec.getLocationSet().size() << endl;
    cout << "Found initial " << spec.getInitial()->getName() << endl;
    cout << "Found marked " << spec.getMarkedSet().size() << endl;
    cout << "Found edges: " << spec.getTransitionSet().size() << endl;


    sys.print();

// printing automaton out
    spec.printAutomataToFile("cifout.cif");

    /**
     * @todo implement the state-space algorithm
     * @todo get the results out
     */
    for(auto act : acts.activitySet) {
        cout << "Finished Parsing Activity " << act->getName() << endl;
        cout << "Found " << act->getNodeSet().size() << endl;
        cout << "Found edges: " << act->getDepSet().size() << endl;
        for (auto n : act->nodeSet) {
            cout << "Node : " << n->id << " " << n->namex << " " << n->resource << n->peripheral << endl;
        }
        act->generateActivityMatrix();
        act->activityMatrix->print();

    }


    cout << "trying out matrix! " << endl;
    Matrix test(2,2);
    test(0,0) = 1;
    test(0,1) = 2;
    test(1,0) = N_INF;
    test(1,1) = 4;
    cout << "Values: " << test(1,1) << " " << test(0,0) << endl;
    test.print();

    Matrix vector(2,1);
    vector(0,0) = 2;
    vector(1,0) = 0;
    Matrix result = test*vector;
    result.print();


    ActivitySet a(acts);

    mpSS stsp(spec.getInitial(),2);
    stsp.generateMaxPlusStateSpace(spec,a,2);
    stsp.print();

    return 0;
}

void yyerror(Automata* spec, set<Activity*>* acts, Plant* sys, const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
