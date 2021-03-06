//
// Created by Bastos on 23/04/2018.
//

#ifndef JANUS_VERTEX_H
#define JANUS_VERTEX_H

#include <vector>
#include "edgeinfo.h"
#include <map>

class Vertex {

    bool visited; // visited flag

    // outgoing
    typedef std::map<Vertex*, EdgeInfo*> edgeList;
    edgeList outgoing;


public:

    std::string name;
    const int id;

    Vertex() : id(0), name("dummy"), visited(false) {}
    Vertex(std::string name) : id(0), name(name), visited(false) {}
    Vertex(std::string name, int id) : id(id), name(name), visited(false) {}


    // auxiliary functions
    void print() { cout << "Vertex [name] " << this->name << endl; }
    void setName(std::string n_name) { this->name = n_name; }
    std::string getName() { return this->name; }
    void setVisited(bool n_visited) { this->visited = n_visited; }
    bool getVisitied() { return this->visited; }
    int getID() { return this->id; }
    edgeList getOutgoing() { return this->outgoing;}
};



#endif //JANUS_VERTEX_H
