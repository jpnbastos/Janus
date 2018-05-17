//
// Created by Bastos on 23/04/2018.
//
#include <vector>
#include "vertex.h"

using namespace std;

template <class V, class E> V Vertex<V,E>::getInfo() const {
    return info;
}

template <class V, class E>
bool Vertex<V,E>::removeEdgeTo(Vertex<V,E> *d) {

    typename std::vector<Edge<V,E>>::iterator it = adj.begin();
    typename std::vector<Edge<V,E>>::iterator ite = adj.end();



    while (adj.begin() != adj.end()) {
        if (adj.begin()->dest == d) {
            adj.erase(it);
            return true;
        }
        else it++;
    }
    return false;
}

template <class V,class E>
Vertex<V,E>::Vertex(V in): info(in), visited(false), path(NULL){}


template <class V,class E>
Vertex<V,E>::Vertex(const Vertex<V,E> & in): info(in.info), visited(in.visited), path(NULL){}

template <class V,class E>
void Vertex<V,E>::addEdge(Vertex<V,E> *dest, E w) {
    Edge<V,E> edgeD(dest,w);
    adj.push_back(edgeD);
}