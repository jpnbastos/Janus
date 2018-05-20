//
// Created by Bastos on 20/05/2018.
//

#ifndef JANUS_SYSTEM_H
#define JANUS_SYSTEM_H

#include <string>
#include <vector>

class Peripheral {
    int id;
    std::string name;
};

class Resource {
    int id;
    std::string name;
    std::vector<Peripheral*> periphals;
};

class System {
    std::vector<Resource*> resources;
};


#endif //JANUS_SYSTEM_H
