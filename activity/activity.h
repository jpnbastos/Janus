//
// Created by Bastos on 20/05/2018.
//

#ifndef JANUS_ACTIVITY_H
#define JANUS_ACTIVITY_H

#include <string>
#include "../graph/vertex.h"
#include "../graph/graph.h"


class Node {

public:
    Node(std::string n, int id, double d, std::string p, std::string r, bool cl, bool rl) : id(id), namex(n), duration(d), peripheral(p), resource(p), claim(cl), release(rl) {}
    double duration;
    std::string peripheral;
    std::string resource;
    bool claim;
    bool release;
    int id;
    std::string namex;

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
    Node* addNode(std::string n, int id, double d, std::string p, std::string r, bool cl, bool rl);
    void addNodeByPointer(Node* n) {nodeSet.insert(n);};
    Node* findNode(std::string name);
    Dep* addDepByName(std::string s, std::string d);
    set<Node*> getNodeSet() {return nodeSet;}
    set<Dep*> getDepSet() {return depSet;}
    Activity(std::string n) : Graph(n) {}
    // Matrix

    set<Node*> nodeSet;
    set<Dep*> depSet;

};

class ActivitySet {
public:
    set<Activity*> activitySet;

    Activity* addActivity(std::string n) {Activity* act = new Activity(n); activitySet.insert(act); return act;}
};


#endif //JANUS_ACTIVITY_H
