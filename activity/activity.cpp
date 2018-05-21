//
// Created by Bastos on 20/05/2018.
//

#include "activity.h"

Node* Activity::addNode(std::string n, int id, double d, std::string p, std::string r, bool cl, bool rl) {
    Node* newNode = new Node(n,id,d,p,r,cl,rl);
    nodeSet.insert(newNode);
    return newNode;
}

Node* Activity::findNode(std::string name){
    for(std::set<Node*>::const_iterator it = Activity::nodeSet.begin(); it != nodeSet.end(); it++ ){
        Node* currentNode = *it;
        if(currentNode->getNamex() == name){
            return currentNode;
        }
    }
    return NULL;
}

Dep* Activity::addDepByName(std::string s, std::string d){

    Node* src = findNode(s);
    Node* dst = findNode(d);


   if(src != NULL && dst != NULL){
        Dep* newDep = new Dep(src,dst);
        depSet.insert(newDep);
        return newDep;
    }
    return NULL;
}