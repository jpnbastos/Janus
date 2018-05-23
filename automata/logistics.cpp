/**
    logistics.cpp
    Purpose: lays the class definition of logistics automata
    In static context, A logistiscs automaton consist of a set of locations and transitions.
    Additionally, an initial location is requires as well as a set of marked/final states

    @author João Bastos
    @version 1.0 20/05/18
*/


#include "logistics.h"
#include <fstream>
#include <iostream>
/**
    constructors
*/
Automata::Automata(string &name) : name(name) {}



/**
    adds a new location to the automaton and returns a pointer to the newly added location.
    @todo solve memory leak here, probalby the share pointer or reference concepts could help here.
*/
Location* Automata::addLocation(std::string name, bool initial, bool marked, bool final) {
    Location* newLoc = new Location(name, locationSet.size(), initial, marked, final);
    locationSet.insert(newLoc);
    return newLoc;
}

/**
    adds a new location to set of marked locations.
*/
void Automata::addMarked(Location* location){
    markedSet.insert(location);
}

/**
    finds a location given a string name from the set of locations of the automata.
*/
Location* Automata::findLocation(std::string name){
    for(std::set<Location*>::const_iterator it = Automata::locationSet.begin(); it != locationSet.end(); it++ ){
        Location* currentLocation = *it;
        if(currentLocation->getName() == name){
            return currentLocation;
        }
    }
    return NULL;
}

/**
    adds a new transition to set of transition of the automaton.
    @todo: check if we can find a different way of dealing with adding transition to yet not existing locations.
*/
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


/**
    prints the automaton to a file
*/
void Automata::printAutomataToFile(std::string filename){

    fstream cifout;
    cifout.open(filename,fstream::out);
    cifout << "supervisor: " << name << ":" << endl;
    for(std::set<Location*>::const_iterator it = locationSet.begin(); it != locationSet.end(); it++ ) {
        Location* cur = *it;
        cifout << "location " << cur->getName() << ": " << endl;
        set<Transition*> local = this->getLocationsTransitions(cur);
        for(std::set<Transition*>::const_iterator ita = local.begin(); ita != local.end(); ita++ )
        { Transition* curt = *ita;
            cifout << "edge " << curt->getInfo()->getName() << " goto " << curt->getDst()->getName() << ";" << endl;
            cifout.flush();
        }
        cifout << endl;
    }

    cifout << "end " <<  endl;
    cifout.close();
}

/**
    prints the automaton
*/
void Automata::printAutomata(){

    cout << "supervisor: " << name << ":" << endl;
    for(std::set<Location*>::const_iterator it = locationSet.begin(); it != locationSet.end(); it++ ) {
        Location* cur = *it;
        cout << "location " << cur->getName() << ": " << endl;
        set<Transition*> local = this->getLocationsTransitions(cur);
        for(std::set<Transition*>::const_iterator ita = local.begin(); ita != local.end(); ita++ )
        { Transition* curt = *ita;
            cout << "edge " << curt->getInfo()->getName() << " goto " << curt->getDst()->getName() << ";" << endl;
            cout.flush();
        }
        cout << endl;
    }

    cout << "end " <<  endl;
}

/**
    finds the outgoing transition for a particular location.
*/
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