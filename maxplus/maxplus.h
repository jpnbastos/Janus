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

    ~Matrix();                              // Destructor
    Matrix(Matrix const& m);               // Copy constructor
    Matrix& operator= (Matrix const& m);   // Assignment operator
    void print();

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

private:
    std::string name;
    unsigned rows_, cols_;
    double* data_;
    int size_c;
    int size_r;
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
Matrix::~Matrix()
{
    delete[] data_;
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
