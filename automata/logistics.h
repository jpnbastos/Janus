//
// Created by Bastos on 17/05/2018.
//

#ifndef JANUS_LOGISTICS_H
#define JANUS_LOGISTICS_H

#include "../graph/graph.h"


class Location : public Vertex {
public:

    Location(string &name, int id, bool initial, bool marked, bool final) : Vertex(name, id), initial(initial), marked(marked), final(final) {}
    bool getInitial() {return this->initial;}

private:

    // possible locations
    vector<string> modularLocs;
    bool initial;
    bool marked;
    bool final;

};

class Transition : public Edge {
public:

    Transition(Location *s, Location *d, EdgeInfo *e);

private:

};

class Automata : public Graph {
public:

    Automata(string &name);
    Automata();

    set<Location*> locationSet;
    set<Transition*> transSet;

    set<Location*> markedSet;
    Location* initial;

    bool addLocation(Location* location) {locationSet.insert(location);};
    bool addLocation(std::string name, bool initial, bool marked, bool final);
    Location* findLocation(std::string name);
    bool removeLocationByName(std::string name);
    void removeLocation(Location* v);
    bool addTransitionByPointer(Location &sourc, Location &dest, EdgeInfo &w);
    bool addTransition(std::string s, std::string d, std::string w);
    void printAutomata();
    void addTransition(std::string name);

    void setInitial(Location* location) {initial = location;};
    Location* getInitial() {return initial;};
    void addMarked(Location* location) {markedSet.insert(location);};
    set<Location*> getMarkedSet() {return markedSet;};
    void addFinal(Location* location);
    Location* getFinalSet();

    set<Transition*> getLocationsTransitions(Location* src);

private:

    Location* initialLoc;
    set<Location*> markedLocs;
    set<Location*> finalLocs;


};



#endif //JANUS_LOGISTICS_H
