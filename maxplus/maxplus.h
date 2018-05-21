//
// Created by Bastos on 21/05/2018.
//

#ifndef JANUS_MAXPLUS_H
#define JANUS_MAXPLUS_H

#include <vector>

class MaxPlusMatrix {

    std::vector<std::vector<double>> matrix;

    public:

    MaxPlusMatrix(unsigned int x, unsigned int y) {
        matrix.resize(x, std::vector<double>(y,false));
    }

    MaxPlusMatrix operator+(MaxPlusMatrix m) {
        /** @todo matrix multiplication
            @todo matrix vectro multiplication
            @todo vector definition
            @todo testing
         */
    }

    class matrix_row {

        std::vector<double>& row;

        public:

        matrix_row(std::vector<double>& r) : row(r) {}
        double& operator[](unsigned int y) { return row.at(y); }

    };

    matrix_row& operator[](unsigned int x) { return matrix.at(x); }

};


#endif //JANUS_MAXPLUS_H
