//
// Created by João Bastos on 23/04/2018.
//

#ifndef JANUS_EDGE_H
#define JANUS_EDGE_H

#include <string>

template <typename V, typename E> class Vertex;

template <typename V, typename E> class Edge {
    Vertex<V,E>* src;
    Vertex<V,E>* dst;
    E weight;
    bool visited;
    std::string name;

public:

    // default constructor
    Edge(Vertex<V,E> *s,Vertex<V,E> *d, E w, std::string name): src(s), dst(d), weight(w), visited(false), name(name){}
    Edge(Vertex<V,E> *s,Vertex<V,E> *d, E w): src(s), dst(d), weight(w), visited(false), name("tau"){}
    Edge(Vertex<V,E> *s, Vertex<V,E> *d): src(s), dst(d), weight(0.0), visited(false), name("tau"){}




    // auxiliary function
    void printEdge() { printf("Edge: %s", this->name);}

    void setName(std::string n_name) { this->name = n_name;}
    std::string getName() {return this->name;}

    void setWeight(E n_weight) { this->weight = n_weight;}
    E getWeight() {return this->weight;}

    void setVisited(bool n_visited) { this->visited = n_visited;}
    bool getVisited() {return this->visited;}

    void setSrc(Vertex<V,E>* n_src) { this->src = n_src;}
    Vertex<V,E>* getSrc() {return this->src;}

    void setDst(Vertex<V,E>* n_dst) { this->dst = n_dst;}
    Vertex<V,E>* getDst() {return this->dst;}

    // default constructor implementation


};



#endif //JANUS_EDGE_H
