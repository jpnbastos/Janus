//
// Created by Bastos on 20/05/2018.
//

#ifndef JANUS_ACTIVITY_H
#define JANUS_ACTIVITY_H

#include <string>
#include "system.h"
#include "../graph/vertex.h"
#include "../graph/graph.h"


class Node : public Vertex {
    double duration;
};

class Action : public Node {
    Peripheral p;
};

class Release : public Node {
    Resource r;
};

class Claim : public Node {
    Resource r;
};


class Activity : public Graph {
    // Matrix
};


#endif //JANUS_ACTIVITY_H
