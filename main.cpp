#include <iostream>
#include <fstream>
// Testing
#include "graph/edgeinfo.h"
#include "graph/graph.h"
#include "automata/logistics.h"

/*int main() {
    std::cout << "Hello, World!" << std::endl;

    Graph* test = new Graph("test");
    test->addVertex("1");
    test->addVertex("2");
    test->addVertex("3");

    test->addEdge("1","2","a");
    test->addEdge("2","3","b");
    test->addEdge("3","1","c");

    test->printGraph();


    Automata* test2 = new Automata("test");
    test2->addLocation("1", false, false, false);
    test2->addLocation("2", true, false, true);
    test2->addLocation("3", false, true, true);

    test2->addTransition("1","2","a");
    test2->addTransition("2","3","b");
    test2->addTransition("3","1","c");

    test2->printAutomata();
    return 0;
}*/

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
    cout << "Finished" << endl;
    cout << "Found " << spec.locationSet.size() << endl;
    //cout << "Found initial " << spec.initial->getName() << endl;
    cout << "Found marked " << spec.markedSet.size() << endl;
    cout << "Found edges: " << spec.transSet.size() << endl;


    cout << "Printing the edges " << endl;
    for(std::set<Transition*>::const_iterator it = spec.transSet.begin(); it != spec.transSet.end(); it++ ) {
        Transition* cur = *it;
        cout << "Transition with name: " << cur->getInfo()->getName() << " and Src: " << cur->getSrc()->getName() << " and Dst: " << cur->getDst()->getName() << endl;

    }

    fstream cifout;
    cifout.open("out.cif",ios_base::out);
    cifout << "supervisor: " << spec.getName() << ":" << endl;
    for(std::set<Location*>::const_iterator it = spec.locationSet.begin(); it != spec.locationSet.end(); it++ ) {
        Location* cur = *it;
        cifout << "location " << cur->getName() << ": " << endl;
        set<Transition*> local = spec.getLocationsTransitions(cur);
        for(std::set<Transition*>::const_iterator ita = local.begin(); ita != local.end(); ita++ )
        { Transition* curt = *ita;
            cifout << "edge " << curt->getInfo()->getName() << " goto " << curt->getDst()->getName() << ";" << endl;
            cifout.flush();
        }
        cifout << endl;
    }

    cifout << "end " <<  endl;
    cifout.close();
    return 0;
}

void yyerror(Automata* spec, const char* s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
