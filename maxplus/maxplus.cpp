//
// Created by Bastos on 21/05/2018.
//

#include "maxplus.h"
#include <iostream>

void Matrix::print() {
    std::cout << "Matrix " << this->name << std::endl;
    for(int i = 0; i < this->size_r; i++) {
        std::cout << "| ";
        for (int k = 0; k < this->size_c; k++) {
            std::cout << " ";
            printf("%0.3f" ,(*this)(i,k));
            std::cout << " ";
        }
        std::cout << " |" << std::endl;
    }
}


double Matrix::norm() {
    double norm_value;
    //should be a vector!
    for(int i = 0; i < this->size_c; i++){
        norm_value = std::max(norm_value,(*this)(i,0));
    }

    return norm_value;
}