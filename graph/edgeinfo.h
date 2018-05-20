//
// Created by João Bastos on 23/04/2018.
//

#ifndef JANUS_EDGE_H
#define JANUS_EDGE_H

#include <string>
#include <iostream>

using namespace std;

class Vertex;

class EdgeInfo {

    bool taken;

    int id;
    string name;

public:

    // default constructor
    EdgeInfo(int id, std::string name): taken(false), id(id), name(name){}
    EdgeInfo(): taken(false), id(0), name("tau"){}

    // auxiliary function
    void printEdge() { cout << "Edge [name] " << this->name << endl;}

    void setName(std::string n_name) { this->name = n_name;}
    std::string getName() {return this->name;}

    void setTaken(bool n_visited) { this->taken = n_visited;}
    bool getTaken() {return this->taken;}

    int getID() { return this->id;}

};



#endif //JANUS_EDGE_H
