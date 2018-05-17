//
// Created by Bastos on 23/04/2018.
//

#ifndef JANUS_VERTEX_H
#define JANUS_VERTEX_H

#include <vector>
#include "edge.h"



template <class V, class E>
class Vertex {

    V info; // payload info
    int id;
    std::vector<Edge<V,E>> adj; // adjency list
    bool visited; // visited flag

    void addEdge(Vertex<V,E> *dest, E w);
    bool removeEdgeTo(Vertex<V,E> *d);

    // path
    Vertex<V,E>* path;

public:
    Vertex(V in);
    Vertex(const Vertex<V,E> &v);
    V getInfo() const;
    int getID() {return id;}
//    friend class Graph<V,E>;
};


#endif //JANUS_VERTEX_H
