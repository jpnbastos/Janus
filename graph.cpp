//
// Created by Bastos on 23/04/2018.
//

#include "graph.h"


template <class V, class E>
int Graph<V,E>::getNumVertex() const {
    return vertexSet.size();
}

template <class V, class E>
void Graph<V,E>::printGraph() {
    printf("This graph has: %i nodes and %i edges \n", this->vertexSet.size(), this->edgeSet.size());
    return;
}


template <class V, class E>
vector<Vertex<V,E> * > Graph<V,E>::getVertexSet() const {
    return vertexSet;
}

template <class V, class E>
bool Graph<V,E>::addVertex(const V &in) {
    typename vector<Vertex<V,E>*>::iterator it = vertexSet.begin();
    typename vector<Vertex<V,E>*>::iterator ite = vertexSet.end();
    for (; it!=ite; it++)
        if ((*it)->info == in) return false;
    Vertex<V,E> *v1 = new Vertex<V,E>(in);
    vertexSet.push_back(v1);
    return true;
}

template <class V, class E>
bool Graph<V,E>::removeVertex(const V &in) {
    typename vector<Vertex<V,E>*>::iterator it= vertexSet.begin();
    typename vector<Vertex<V,E>*>::iterator ite= vertexSet.end();
    for (; it!=ite; it++) {
        if ((*it)->info == in) {
            Vertex<V,E> * v= *it;
            vertexSet.erase(it);
            typename vector<Vertex<V,E>*>::iterator it1= vertexSet.begin();
            typename vector<Vertex<V,E>*>::iterator it1e= vertexSet.end();
            for (; it1!=it1e; it1++) {
                (*it1)->removeEdgeV,Eo(v);
            }
            delete v;
            return true;
        }
    }
    return false;
}

template <class V, class E>
bool Graph<V,E>::addEdge(const V &sourc, const V &dest, E w) {
    typename vector<Vertex<V,E>*>::iterator it= vertexSet.begin();
    typename vector<Vertex<V,E>*>::iterator ite= vertexSet.end();
    int found=0;
    Vertex<V,E> *edgeS, *edgeD;
    while (found!=2 && it!=ite ) {
        if ( (*it)->info == sourc )
        { edgeS=*it; found++;}
        if ( (*it)->info == dest )
        { edgeD=*it; found++;}
        it ++;
    }
    if (found!=2) return false;
    Edge<V,E>* newEdge = new Edge(edgeS,edgeD, w);
    edgeSet.push_back(newEdge);
    return true;
}

template <class V, class E>
bool Graph<V,E>::removeEdge(const V &sourc, const V &dest) {
    typename vector<Vertex<V,E>*>::iterator it= vertexSet.begin();
    typename vector<Vertex<V,E>*>::iterator ite= vertexSet.end();
    int found=0;
    Vertex<V,E> *edgeS, *edgeD;
    while (found!=2 && it!=ite ) {
        if ( (*it)->info == sourc )
        { edgeS=*it; found++;}
        if ( (*it)->info == dest )
        { edgeD=*it; found++;}
        it ++;
    }
    if (found!=2) return false;
    return edgeS->removeEdgeV,Eo(edgeD);
}

template <class V, class E>
void Graph<V,E>::clone(Graph<V,E> &gr) {
    typename vector<Vertex<V,E>*>::const_iterator it= vertexSet.begin();
    typename vector<Vertex<V,E>*>::const_iterator ite= vertexSet.end();

    // 1. clone vertices
    for (; it !=ite; it++) {
        gr.addVertex((*it)->getInfo());
        gr.vertexSet[gr.getNumVertex()-1]->visited = false;
    }

    // 2. clone edges
    for (it=vertexSet.begin(); it !=ite; it++) {
        typename vector<Edge<V,E> >::iterator edgeIt= ((*it)->adj).begin();
        typename vector<Edge<V,E> >::iterator edgeIte= ((*it)->adj).end();
        for (; edgeIt !=edgeIte; edgeIt++) {
            gr.addEdge((*it)->getInfo(), edgeIt->dest->getInfo(), edgeIt->weight);
        }
    }
}

template <class V, class E>
vector<V,E> Graph<V,E>::dfs() const {
    typename vector<Vertex<V,E>*>::const_iterator it= vertexSet.begin();
    typename vector<Vertex<V,E>*>::const_iterator ite= vertexSet.end();
    for (; it !=ite; it++)
        (*it)->visited=false;
    vector<V,E> res;
    it=vertexSet.begin();
    for (; it !=ite; it++)
        if ( (*it)->visited==false )
            dfs(*it,res);
    return res;
}

template <class V, class E>
void Graph<V,E>::dfs(Vertex<V,E> *v,vector<V,E> &res) const {
    v->visited = true;
    res.push_back(v->info);
    typename vector<Edge<V,E> >::iterator it= (v->adj).begin();
    typename vector<Edge<V,E> >::iterator ite= (v->adj).end();
    for (; it !=ite; it++)
        if ( it->dest->visited == false )
            dfs(it->dest, res);
}

template <class V, class E>
vector<V,E> Graph<V,E>::bfs(Vertex<V,E> *v) const {
    vector<V,E> res;
    queue<Vertex<V,E> *> q;
    q.push(v);
    v->visited = true;
    while (!q.empty()) {
        Vertex<V,E> *v1 = q.front();
        q.pop();
        res.push_back(v1->info);
        typename vector<Edge<V,E> >::iterator it=v1->adj.begin();
        typename vector<Edge<V,E> >::iterator ite=v1->adj.end();
        for (; it!=ite; it++) {
            Vertex<V,E> *d = it->dest;
            if (d->visited==false) {
                d->visited=true;
                q.push(d);
            }
        }
    }
    return res;
}

template <class V, class E>
int Graph<V,E>::maxNewChildren(Vertex<V,E> *v, V &inf) const {
    vector<V,E> res;
    queue<Vertex<V,E> *> q;
    queue<int> level;
    int maxChildren=0;
    inf =v->info;
    q.push(v);
    level.push(0);
    v->visited = true;
    while (!q.empty()) {
        Vertex<V,E> *v1 = q.front();
        q.pop();
        res.push_back(v1->info);
        int l=level.front();
        level.pop(); l++;
        int nChildren=0;
        typename vector<Edge<V,E> >::iterator it=v1->adj.begin();
        typename vector<Edge<V,E> >::iterator ite=v1->adj.end();
        for (; it!=ite; it++) {
            Vertex<V,E> *d = it->dest;
            if (d->visited==false) {
                d->visited=true;
                q.push(d);
                level.push(l);
                nChildren++;
            }
        }
        if (nChildren>maxChildren) {
            maxChildren=nChildren;
            inf = v1->info;
        }
    }
    return maxChildren;
}

template <class V, class E>
vector<V,E> Graph<V,E>::findArt()
{
    counter = 1;

    for (size_t i = 0; i < vertexSet.size(); i++)
    {
        vertexSet[i]->visited = false;
        vertexSet[i]->low = -1;
        vertexSet[i]->num = -1;
    }

    findArt(vertexSet[0]);
    return pontosArt;
}

template <class V, class E>
void Graph<V,E>::findArt(Vertex<V,E>* v)
{
    v->visited = true;
    v->low = v->num = counter++;

    for (size_t i = 0; i < v->adj.size(); i++)
    {
        Vertex<V,E>* w = v->adj[i].dest;
        if (!w->visited)
        {
            w->path = v;
            findArt(w);
            if (w->low >= v->num)
            {
                if (v != vertexSet[0])
                    pontosArt.push_back(v->getInfo());
            }
            v->low = min (v->low, w->low);
        }
        else
        {
            if (v->path != w)
                v->low = min(v->low, w->num);
        }
    }
}

template <class V, class E>
vector<Vertex<V,E>* > Graph<V,E>::npo()
{
    counter = 1;

    for (size_t i = 0; i < vertexSet.size(); i++)
    {
        vertexSet[i]->visited = false;
        vertexSet[i]->num = -1;
    }

    for (size_t i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->visited == false)
            npoAux(vertexSet[i]);
    return vertexSet;
}

template <class V, class E>
void Graph<V,E>::npoAux(Vertex<V,E>* v)
{
    v->visited = true;
    for (size_t i = 0; i < v->adj.size(); i++)
    {
        Vertex<V,E>* w = v->adj[i].dest;
        if (w->visited == false)
            npoAux(w);
    }
    v->num = counter++;
}
