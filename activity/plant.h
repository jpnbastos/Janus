//
// Created by Bastos on 24/05/2018.
//

#ifndef JANUS_SYSTEM_H
#define JANUS_SYSTEM_H

#include <utility>
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Plant {
public:

    void setNR(int n) { n_r = n;}
    void setNP(int n) { n_p = n;}
    int getNR() {return n_r;}
    int getNP() {return n_p;}

    void setName(std::string n) { name = n;}
    std::string getName() {return name;}

    void setResource(std::string n, std::vector<std::string> per) {resources.insert(std::pair<std::string,std::vector<std::string>>(n,per));}

    void print() {
        std::cout << "System " << name << " has " << n_r << " resources and a total of " << n_p << " peripherals " << std::endl;
        for ( auto m : resources){
            std::cout << "Resource: " << m.first << std::endl;
            for( auto p : m.second){
                std::cout << p << ";" << std::endl;
            }
        }
    }

private:

    std::map<std::string,std::vector<std::string>> resources;
    int n_r;
    int n_p;
    std::string name;
};


#endif //JANUS_SYSTEM_H
