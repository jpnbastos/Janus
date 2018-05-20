//
// Created by Bastos on 17/05/2018.
//

#include "logistics.h"

Automata::Automata(string &name) : Graph(name) {}
Automata::Automata() : Graph() {}

Transition::Transition(Location *s, Location *d, EdgeInfo *e): Edge(s, d, e) {}

bool Automata::addLocation(std::string name, bool initial, bool marked, bool final) {
    Location *newLoc = new Location(name, locationSet.size(), initial, marked, final);
    locationSet.insert(newLoc);
    return true;
}

Location* Automata::findLocation(std::string name){
    for(std::set<Location*>::const_iterator it = Automata::locationSet.begin(); it != locationSet.end(); it++ ){
        Location* currentLocation = *it;
        if(currentLocation->getName() == name){
            return currentLocation;
        }
    }
    return NULL;
}

bool Automata::removeLocationByName(std::string name) {
    bool found = false;
    for(std::set<Location*>::const_iterator it = Automata::locationSet.begin(); it != locationSet.end(); it++ ){
        Location* currentLocation = *it;
        if(currentLocation->getName() == name){
            found = true;
            locationSet.erase(currentLocation);
        }
    }
    return found;
}

void Automata::removeLocation(Location* v) {
    locationSet.erase(v);
}

bool Automata::addTransitionByPointer(Location &sourc, Location &dest, EdgeInfo &w){
    Transition* newTransition = new Transition(&sourc,&dest,&w);
    transSet.insert(newTransition);
    return true;
}

bool Automata::addTransition(std::string s, std::string d, std::string w){
    Location* src = findLocation(s);
    if(src == NULL){
        Location* newLoc = new Location(s,0,false,false,false);
        src = newLoc;
    }


    Location* dst = findLocation(d);
    if(dst == NULL){
        Location* newLoc = new Location(d,0,false,false,false);
        dst = newLoc;
    }
    EdgeInfo* nInfo = new EdgeInfo(transSet.size(),w);
    if(src != NULL && dst != NULL){
        Transition* newTransition = new Transition(src,dst,nInfo);
        transSet.insert(newTransition);
        return true;
    }
    return false;
}

void Automata::printAutomata(){
    cout << "Automata is being printed: " << endl;

    // Vertices
    cout << "List of Vertices (size: " << locationSet.size() << ") " << endl;
    for(std::set<Location*>::const_iterator it = Automata::locationSet.begin(); it != locationSet.end(); it++ ){
        Location* currentLocation = *it;
        cout << "Location[" << currentLocation->getID() << "]: " << currentLocation->getName();
        if(currentLocation->getInitial()){
            cout << " and it is an initial location";
        }
        cout << endl;
    }

    // Transitions
    cout << "List of Transitions (size: " << transSet.size() << ") " << endl;
    for(std::set<Transition*>::const_iterator it = Automata::transSet.begin(); it != transSet.end(); it++ ){
        Transition* currentTransition = *it;
        cout << "Transition[" << currentTransition->getInfo()->getID() << "]: " << currentTransition->getInfo()->getName() << " source: "
             << currentTransition->getSrc()->getName() << " and destination: " << currentTransition->getDst()->getName() << endl;
    }
    cout << "End of graph" << endl;
}

set<Transition*> Automata::getLocationsTransitions(Location* src){
    set<Transition*> local;
    for(std::set<Transition*>::const_iterator it = Automata::transSet.begin(); it != transSet.end(); it++ ){
        Transition* currentTransition = *it;
        if(currentTransition->getSrc()->getName() == src->getName()){
            local.insert(currentTransition);
        }
    }
    return local;
}