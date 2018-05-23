//
// Created by Bastos on 22/05/2018.
//

#include "statespace.h"





void mpSS::dfs(Automata &fsm, stack<mpSSNode*>& query, mpSS &res, ActivitySet &activities) {
    mpSSNode* current = query.top();

    current->setVisited(true);
    set<Transition*> outgoing = fsm.getLocationsTransitions(query.top()->getLocation());
    query.pop();
    for ( auto t : outgoing ){
        // find matching activity to transition name
        std::string test = t->getInfo()->getName();
        Activity* match = activities.findByName(test);
        Matrix t_m = *(match->activityMatrix);
        Matrix t_s = current->getMatrix();
        Matrix n_ts = t_m*t_s;
        mpSSNode* newNode = res.mpSSAddNode(t->getDst()->getName(),t->getDst(),n_ts);
        res.mpSSAddEdge(t->getInfo()->getName(),n_ts.norm(),current,newNode);
        query.push(res.findNodeByName(t->getDst()->getName()));
    }
}

void mpSS::generateMaxPlusStateSpace(Automata &fsm, ActivitySet& activities, int n) {

    // create empty mpSS

    stack<mpSSNode*> query;
    mpSSNode a = this->initial;
    this->mpSSAddNode(a.getLocation()->getName(),a.getLocation(),a.getMatrix());
    query.push(this->findNodeByName(a.getLocation()->getName()));
    while(!query.empty()) {
        dfs(fsm, query, (*this), activities);
        cout << " " << query.size() << endl;
    }
    return;
}

void mpSS::print() {
    cout << "The state-space has " << this->nodes.size() << " states and " << this->edges.size() << " edges!" << endl;
    for( auto s : nodes){
        cout << s->getName() << " " << s->getID() << endl;
        s->getMatrix().print();
        cout << endl;
    }
    for( auto e : edges){
        cout << e->src->getLocation()->getName() << "-" << e->src->getID() << " " << e->dst->getLocation()->getName() << "-" << e->dst->getID() << " " << e->getActivity() << endl;
    }
}