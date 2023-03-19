//
//  matrix.cpp
//
//  Created by Furkanicus on 12/04/15.
//  Copyright (c) 2015 Furkan. All rights reserved.
//

#include "gf/GaloisField.h"
#include "gf/GaloisFieldElement.h"
#include "gf/GaloisFieldPolynomial.h"
#include "matrix.h"
using namespace galois;

using namespace std;

extern unsigned int prim_poly[9];
extern GaloisField gf;

// Constructor for Any Matrix
Matrix::Matrix(unsigned rowSize, unsigned colSize, GaloisFieldElement initial){
    m_rowSize = rowSize;
    m_colSize = colSize;
    m_matrix.resize(rowSize);
    for (unsigned i = 0; i < m_matrix.size(); i++)
    {
        m_matrix[i].resize(colSize, initial);
    }
}

// Copy Constructor
Matrix::Matrix(const Matrix &B)
{
    this->m_colSize = B.getCols();
    this->m_rowSize = B.getRows();
    this->m_matrix = B.m_matrix;
    
}

Matrix::~Matrix(){
    m_matrix.clear();
    m_matrix.shrink_to_fit();
}

// Addition of Two Matrices
Matrix Matrix::operator+(Matrix &B){
    Matrix sum(m_rowSize, m_colSize, GaloisFieldElement(&gf, 0));
    unsigned i,j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            sum(i,j) = this->m_matrix[i][j] + B(i,j);
        }
    }
    return sum;
}

// Multiplication of Two Matrices
Matrix Matrix::operator*(Matrix & B){
    Matrix multip(m_rowSize,B.getCols(),GaloisFieldElement(&gf, 0));
    if(m_colSize == B.getRows())
    {
        unsigned i,j,k;
        GaloisFieldElement temp(&gf, 0);
        for (i = 0; i < m_rowSize; i++)
        {
            for (j = 0; j < B.getCols(); j++)
            {
                temp = GaloisFieldElement(&gf, 0);
                for (k = 0; k < m_colSize; k++)
                {
                    temp += m_matrix[i][k] * B(k,j);
                }
                multip(i,j) = temp;
                //cout << multip(i,j) << " ";
            }
            //cout << endl;
        }
        return multip;
    }
    else
    {
        throw std::invalid_argument("incompatible matrix");
    }
}

// Scalar Addition
Matrix Matrix::operator+(GaloisFieldElement scalar){
    Matrix result(m_rowSize,m_colSize, GaloisFieldElement(&gf, 0));
    unsigned i,j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            result(i,j) = this->m_matrix[i][j] + scalar;
        }
    }
    return result;
}

// Scalar Multiplication
Matrix Matrix::operator*(GaloisFieldElement scalar){
    Matrix result(m_rowSize,m_colSize,0);
    unsigned i, j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            result(i,j) = this->m_matrix[i][j] * scalar;
        }
    }
    return result;
}

// Scalar Division
Matrix Matrix::operator/(GaloisFieldElement scalar){
    Matrix result(m_rowSize,m_colSize,0);
    unsigned i,j;
    for (i = 0; i < m_rowSize; i++)
    {
        for (j = 0; j < m_colSize; j++)
        {
            result(i,j) = this->m_matrix[i][j] / scalar;
        }
    }
    return result;
}


// Returns value of given location when asked in the form A(x,y)
GaloisFieldElement& Matrix::operator()(const unsigned &rowNo, const unsigned & colNo)
{
    return this->m_matrix[rowNo][colNo];
}

// No brainer - returns row #
unsigned Matrix::getRows() const
{
    return this->m_rowSize;
}

// returns col #
unsigned Matrix::getCols() const
{
    return this->m_colSize;
}

// Take any given matrices transpose and returns another matrix
Matrix Matrix::transpose()
{
    Matrix Transpose(m_colSize,m_rowSize,0);
    for (unsigned i = 0; i < m_colSize; i++)
    {
        for (unsigned j = 0; j < m_rowSize; j++) {
            Transpose(i,j) = this->m_matrix[j][i];
        }
    }
    return Transpose;
}

// Prints the matrix beautifully
void Matrix::print() const
{
    cout << "Matrix: " << endl;
    for (unsigned i = 0; i < m_rowSize; i++) {
        for (unsigned j = 0; j < m_colSize; j++) {
            cout << "[" << m_matrix[i][j] << "] ";
        }
        cout << endl;
    }
}
