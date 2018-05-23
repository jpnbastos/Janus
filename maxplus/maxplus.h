//
// Created by Bastos on 21/05/2018.
//

#ifndef JANUS_MAXPLUS_H
#define JANUS_MAXPLUS_H

#define N_INF -std::numeric_limits<double>::infinity()

#include <vector>
#include <iostream>
#include <string>
class Matrix {

public:
    Matrix(unsigned rows, unsigned cols);
    double& operator() (unsigned row, unsigned col);
    double  operator() (unsigned row, unsigned col) const;
    int getVectorSize() { return size_c;}

    int size_c;
    int size_r;

    void print();
    double norm();

    Matrix operator*(Matrix &m) {
        Matrix result = Matrix(this->size_r, m.size_c);
        for(int i = 0; i < this->size_r; i++) {
            for(int k = 0; k < m.size_c; k++) {
                for (int j = 0; j < this->size_c; j++) {
                    double res = (*this)(i,j) + m(j,k);
                    result(i,k) = std::max(result(i,k),res);
                }
            }
        }
        return result;
    }

    bool operator==(const Matrix& other) const {
        bool flag = false;
        if (this->size_r == other.size_r && this->size_c == other.size_c) {
            for (int i = 0; i < this->size_r; i++) {
                for (int k = 0; k < this->size_c; k++) {
                    if((*this)(i,k) == other(i,k))
                        flag = true;
                    else
                        flag = false;
                }
            }
        }
        return flag;
    }

private:
    std::string name;
    unsigned rows_, cols_;
    double* data_;



};

inline
Matrix::Matrix(unsigned rows, unsigned cols)
        : rows_ (rows)
        , cols_ (cols)
{
    if (rows == 0 || cols == 0)
        std::cout << "Matrix constructor has 0 size" << std::endl;
    data_ = new double[rows * cols];
    for(int i = 0; i < rows; i++) {
        for (int k = 0; k < cols; k++) {
            data_[cols_ * i + k] = 0.0;
        }
    }
    size_r = rows;
    size_c = cols;
}



inline
double& Matrix::operator() (unsigned row, unsigned col)
{
    if (row >= rows_ || col >= cols_)
        std::cout << "Matrix subscript out of bounds" << std::endl;
    return data_[cols_*row + col];
}

inline
double Matrix::operator() (unsigned row, unsigned col) const
{
    if (row >= rows_ || col >= cols_)
        std::cout << "const Matrix subscript out of bounds" << std::endl;
    return data_[cols_*row + col];
}



#endif //JANUS_MAXPLUS_H
