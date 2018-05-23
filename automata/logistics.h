/**
    logistics.h
    Purpose: lays the class definition of logistics automata
    In static context, A logistiscs automaton consist of a set of locations and transitions.
    Additionally, an initial location is requires as well as a set of marked/final states

    @author João Bastos
    @version 1.0 20/05/18
*/

#ifndef JANUS_LOGISTICS_H
#define JANUS_LOGISTICS_H

#include "../graph/graph.h"

/**
    class definition of location (base class Vertex of Graph)
    a location can be: initial, marked and/or final.
    it is defined by a unique identifier, a name and a set of outgoing transitions.

    @todo create the set of outgoing transitions.
*/
class Location {

public:

    // constructor
    Location(string &name, int id, bool initial, bool marked, bool final) : id(id), name(name), initial(initial), marked(marked), final(final), visited(false) {}

    // setters and getters
    bool getInitial() {return this->initial;}
    bool visted() {return visited;};
    void print() { cout << "Location [name] " << this->name << endl; }
    void setName(std::string n_name) { this->name = n_name; }
    std::string getName() { return this->name; }
    void setVisited(bool n_visited) { this->visited = n_visited; }
    bool getVisitied() { return this->visited; }
    int getID() { return this->id; }
private:

    int id;
    std::string name;

    bool initial;
    bool marked;
    bool final;
    bool visited;

};

/**
    class definition of transition (base class Edge of Graph)
    a transition is defined as a Source (location), Destination (location) and Information (EdgeInfo).
*/
class Transition {

    int id;
    Location* src;
    Location* dst;
    EdgeInfo* info;

public:

    Transition(Location *s, Location *d, EdgeInfo *e): src(s), dst(d), info(e), id(0){}

    Location* getSrc() {return this->src;}
    Location* getDst() {return this->dst;}
    EdgeInfo* getInfo() {return this->info;}
    int getID() {return this->id;}
    // constructor




};

/**
    class definition of automata (base class Graph)
    set of locations, marked locations and transitions. Plus an initial location.
*/
class Automata {
public:

    // constructor
    Automata(string &name);
    Automata() : name("") {}

    // setters and getters
    void setInitial(Location* location) {initial = location;};
    Location* getInitial() {return initial;};

    void addMarked(Location* location);
    set<Location*> getMarkedSet() {return markedSet;};

    Location* addLocation(std::string name, bool initial, bool marked, bool final);
    set<Location*> getLocationSet() {return locationSet;};

    bool addTransition(std::string s, std::string d, std::string w);
    set<Transition*> getTransitionSet() {return transSet;};

    // aux functions
    void printAutomataToFile(std::string filename);
    void printAutomata();

    set<Transition*> getLocationsTransitions(Location* src);
    Location* findLocation(std::string name);

    void setName(std::string name) {name = name;}
    std::string getName() {return name;}

private:

    // sets
    set<Location*> locationSet;
    set<Transition*> transSet;
    set<Location*> markedSet;
    std::string name;
    // initial location
    Location* initial;

};



#endif //JANUS_LOGISTICS_H
