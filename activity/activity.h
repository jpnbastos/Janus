//
// Created by Bastos on 20/05/2018.
//

#ifndef JANUS_ACTIVITY_H
#define JANUS_ACTIVITY_H

#define NINF std::numeric_limits<double>::infinity()

#include <string>
#include <stack>
#include "../graph/vertex.h"
#include "../graph/graph.h"
#include "../maxplus/maxplus.h"

class Activity;

class AdjListNode
{
    int v;
    double weight;

public:

    AdjListNode(int _v, int _w)  { v = _v;  weight = _w;}
    int getV()       {  return v;  }
    double getWeight()  {  return weight; }
};

class TopologicalActivity {

    int V;    // No. of vertices'

    // Pointer to an array containing adjacency lists
    list<AdjListNode> *adj;

    // A function used by longestPath
    void topologicalSortUtil(int v, bool visited[], stack<int> &Stack);

public:
    TopologicalActivity(int V);   // Constructor

    // function to add an edge to graph
    void addEdge(int u, int v, int weight);

    // Finds longest distances from given source vertex
    void longestPath(int s, Activity& act);
    int longestPathN2N(int s, int d);
};

class Node {

public:
    Node(std::string n, std::string a, int id, double d, std::string p, std::string r, bool cl, bool rl) : id(id), namex(n), alias(a), duration(d), peripheral(p), resource(r), claim(cl), release(rl) {}
    double duration;
    std::string peripheral;
    std::string resource;
    bool claim;
    bool release;
    int id;
    std::string namex;
    std::string alias;

    std::string getNamex() {return namex;}
};

class Dep {

public:
    Dep(Node* s, Node* d) : src(s), dst(d) {}

    Node* src;
    Node* dst;

};

class Activity : public Graph {

public:
    Node* addNode(std::string n,std::string a, int id, double d, std::string p, std::string r, bool cl, bool rl);
    void addNodeByPointer(Node* n) {nodeSet.insert(n);};
    Node* findNode(std::string name);
    Node* findNodeByID(int id);
    Node* findClaim(std::string r);
    Node* findRelease(std::string r);
    Dep* addDepByName(std::string s, std::string d);
    Dep* addDepByAlias(std::string s, std::string d);
    Node* findNodeByAlias(std::string a);
    set<Node*> getNodeSet() {return nodeSet;}
    set<Dep*> getDepSet() {return depSet;}
    Activity(std::string n) : Graph(n), activityMatrix(NULL) {}


    void generateActivityMatrix();
    TopologicalActivity* convertActivityToTA();
    // Matrix

    Matrix* activityMatrix;
    set<Node*> nodeSet;
    set<Dep*> depSet;

};

class ActivitySet {
public:

    set<Activity*> activitySet;
    ActivitySet() : activitySet() {}
    ActivitySet(set<Activity*> acts) : activitySet(acts) {}

    Activity* addActivity(std::string n) {Activity* act = new Activity(n); activitySet.insert(act); return act;}
    Activity* findByName(std::string n);
};



#endif //JANUS_ACTIVITY_H
