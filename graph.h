//
// Created by Bastos on 23/04/2018.
//

#ifndef JANUS_GRAPH_H
#define JANUS_GRAPH_H

#include <vector>
#include <list>
#include <set>
#include <queue>
#include "vertex.h"
#include "edgeinfo.h"

using namespace std;

class Edge {
    int id;
    Vertex* src;
    Vertex* dst;
    EdgeInfo* info;

public:

    Edge(Vertex* s, Vertex* d, EdgeInfo* e): src(s), dst(d), info(e), id(0){}

    Vertex* getSrc() {return this->src;}
    Vertex* getDst() {return this->dst;}
    EdgeInfo* getInfo() {return this->info;}
    int getID() {return this->id;}

};

class Graph {

    std::string name;
    int id;

    // Set of vertices and edges
    set<Vertex*> vertexSet;
    set<Edge*> edgeSet;


public:

    Graph(std::string name): id(0), name(name){}

    // Make these functions

    bool addVertex(std::string name);
    void removeVertexByName(Vertex* v);
    bool removeVertexByName(std::string name);
    bool addEdge(Vertex &sourc, Vertex &dest, EdgeInfo &w);
    void printGraph();

/*
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
    */
};



#endif //JANUS_GRAPH_H
