#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>

#include "gf/GaloisField.h"
#include "gf/GaloisFieldElement.h"
#include "gf/GaloisFieldPolynomial.h"
using namespace galois;

using std::vector;
using std::tuple;

inline unsigned int prim_poly[15] = {1,1,0,1,0,1,0,0,0,0,0,0,0,0,1};
inline GaloisField gf(14, prim_poly);

class Matrix {
private:
    unsigned m_rowSize;
    unsigned m_colSize;
    vector<vector<GaloisFieldElement> > m_matrix;
public:
    Matrix(unsigned, unsigned, GaloisFieldElement);
    Matrix(const Matrix &);
    ~Matrix();
    
    // Matrix Operations
    Matrix operator+(Matrix &);
    Matrix operator*(Matrix &);
    Matrix transpose();
    
    // Scalar Operations
    Matrix operator+(GaloisFieldElement);
    Matrix operator*(GaloisFieldElement);
    Matrix operator/(GaloisFieldElement);
    
    // Aesthetic Methods
    GaloisFieldElement& operator()(const unsigned &, const unsigned &);
    void print() const;
    unsigned getRows() const;
    unsigned getCols() const;
    
    // Deflation
    Matrix deflation(Matrix &, GaloisFieldElement&);
};
#endif /* defined(MATRIX_H) */
