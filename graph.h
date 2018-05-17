//
// Created by Bastos on 23/04/2018.
//

#ifndef JANUS_GRAPH_H
#define JANUS_GRAPH_H

#include <vector>
#include <list>
#include <queue>
#include "vertex.h"
#include "edge.h"

using namespace std;

template <class V, class E>
class Graph {
    vector<Vertex<V,E> *> vertexSet;
    vector<Edge<V,E> *> edgeSet;
    void dfs(Vertex<V,E> *v, vector<V,E> &res) const;
    vector<V,E> pontosArt;
    int counter;

public:
    bool addVertex(const V &in);
    bool addEdge(const V &sourc, const V &dest, E w);

    void printGraph();


    bool removeVertex(const V &in);
    bool removeEdge(const V &sourc, const V &dest);
    vector<V,E> dfs() const;
    vector<V,E> bfs(Vertex<V,E> *v) const;
    int maxNewChildren(Vertex<V,E> *v, V &inf) const;
    vector<Vertex<V,E> * > getVertexSet() const;
    int getNumVertex() const;
    vector<V,E> findArt();
    void findArt(Vertex<V,E>* v);
    vector<Vertex<V,E>* > npo();
    void npoAux(Vertex<V,E>* v);
    void clone(Graph<V,E> &g);
};



#endif //JANUS_GRAPH_H
