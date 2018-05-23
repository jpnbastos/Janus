//
// Created by Bastos on 22/05/2018.
//

#ifndef JANUS_STATESPACE_H
#define JANUS_STATESPACE_H

#include <string>
#include <activity.h>
#include <logistics.h>
#include "maxplus.h"

class mpSSNode {
public:
    void setID(int i) {id = i;}
    void setName(std::string n) {name = n;}
    void setLocation(Location* n) {location = n;}
    void setMatrix(Matrix m) { time_stamp = m;}
    int getID() const {return id;}
    std::string getName() {return name;}
    Location* getLocation() {return location;}
    Matrix getMatrix() {return time_stamp;}

    bool getVisited() {return visited;}
    void setVisited(bool m) { visited = m;}

    mpSSNode(Location* l) : id(0), name(""), location(l), time_stamp(Matrix(1,1)) {}
    mpSSNode(int i,std::string n,Location* l, Matrix m) : id(i), name(n), location(l), time_stamp(m) {}



private:
    int id;
    std::string name;
    Location* location;
    Matrix time_stamp;
    bool visited;

    bool operator==(const mpSSNode& other) const
    {
        if(this->time_stamp == other.time_stamp && this->location == other.location)
            return true;
        else
            return false;
    }

};

namespace std {
    template<>
    struct less<mpSSNode> {
        bool operator()(const mpSSNode &k1, const mpSSNode &k2) const {
            return k1.getID() < k2.getID();
        }
    };
}

class mpSSEdge{

public:
    void setID(int i) {id = i;}
    void setActivity(std::string n) {activity = n;}
    void setWeight(double m) { weight = m;}
    int getID() const {return id;}
    std::string getActivity() {return activity;}
    double getweight() {return weight;}

    mpSSNode* src;
    mpSSNode* dst;

    mpSSEdge() : id(0), activity(""), weight(0.0), src(NULL), dst(NULL) {}
    mpSSEdge(int i, std::string act, double w, mpSSNode* s, mpSSNode* d) : id(i), activity(act), weight(w), src(s), dst(d) {}





private:
    int id;
    std::string activity;
    double weight;

};

namespace std {
    template<>
    struct less<mpSSEdge> {
        bool operator()(const mpSSEdge &k1, const mpSSEdge &k2) const {
            return k1.getID() < k2.getID();
        }
    };
}

class mpSS {

public:
    set<mpSSNode*> nodes;
    set<mpSSEdge*> edges;
    set<Activity*> activities;


    mpSSNode initial;

    mpSS(Location* ini,int resources) : initial(mpSSNode(0,"initial",ini,Matrix(resources,1))) {}

    void generateMaxPlusStateSpace(Automata& fsm, ActivitySet& activities,int n);
    void dfs(Automata &fsm, stack<mpSSNode*>& query, mpSS &res, ActivitySet &activities);
    mpSSNode* mpSSAddNode(std::string name, Location* location, Matrix ts) {

        mpSSNode* newNode = new mpSSNode(nodes.size(),name,location,ts);
        if(exists(newNode) == NULL) {
            nodes.insert(newNode);
            return newNode;
        } else
            return exists(newNode);
    }

    mpSSEdge* mpSSAddEdge(std::string act,double w, mpSSNode* s, mpSSNode* d) { mpSSEdge* newEdge = new mpSSEdge(edges.size(),act, w, s, d); edges.insert(newEdge); return newEdge; }
    mpSSNode* findNodeByName(std::string name) { for( auto n : nodes) { if(n->getName() == name) return n; } return NULL;}
    mpSSNode* exists(mpSSNode* newly) {
        for( auto n : nodes) {
            if(n == newly)
                return n;
        }
        return NULL;
    }
    void print();
};


#endif //JANUS_STATESPACE_H
