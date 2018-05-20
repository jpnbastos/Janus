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
class Location : public Vertex {

public:

    // constructor
    Location(string &name, int id, bool initial, bool marked, bool final) : Vertex(name, id), initial(initial), marked(marked), final(final) {}

    // setters and getters
    bool getInitial() {return this->initial;}

private:

    bool initial;
    bool marked;
    bool final;

};

/**
    class definition of transition (base class Edge of Graph)
    a transition is defined as a Source (location), Destination (location) and Information (EdgeInfo).
*/
class Transition : public Edge {
public:

    // constructor
    Transition(Location *s, Location *d, EdgeInfo *e);

private:

};

/**
    class definition of automata (base class Graph)
    set of locations, marked locations and transitions. Plus an initial location.
*/
class Automata : public Graph {
public:

    // constructor
    Automata(string &name);
    Automata();

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

private:

    // sets
    set<Location*> locationSet;
    set<Transition*> transSet;
    set<Location*> markedSet;

    // initial location
    Location* initial;

};



#endif //JANUS_LOGISTICS_H
