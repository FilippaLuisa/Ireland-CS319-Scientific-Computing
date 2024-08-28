// File:     Matrix10.cpp (version: 10.1)
// Author:   Niall Madden
// Date:     Week 10 of 2324-CS319
// What:     Header file for Matrix class
// See also: Matrix10.h

#include <iostream>
#include "Vector10.h"
#include "Matrix10.h"

// Basic constructor. See below for copy constructor.
Matrix::Matrix (unsigned int Size)
{
    N = Size;
    entries = new double [N*N];
}

Matrix::~Matrix(void)
{
    delete [] entries;
}

void Matrix::setij (unsigned int i, unsigned int j, double x)
{
    if (i<N && j<N)
        entries[i*N+j]=x;
    else
        std::cerr << "Matrix::setij(): Index out of bounds.\n";
}

double Matrix::getij (unsigned int i, unsigned int j)
{
    if (i<N && j<N)
        return(entries[i*N+j]);
    else
    {
        std::cerr << "Matrix::getij(): Index out of bounds.\n";
        return(0);
    }
}

void Matrix::print (void)
{
//   std::cout << "Matrix is of size " << M << "-by-" << N << std::endl;
    for (unsigned int i=0; i<N; i++)
    {
        for (unsigned int j=0; j<N; j++)
            std::cout << "[" << entries[i*N+j] << "]";
        std::cout << std::endl;
    }
}

//////////////////////////////////////////
// Everything above this is from Week 9 //
// Everything below this is from Week 10 //
//////////////////////////////////////////

// Matrix copy constructor
Matrix::Matrix (const Matrix &m)
{
    N = m.N;
    entries = new double[N*N];
    for (unsigned int i=0; i<N*N; i++)
        entries[i] = m.entries[i];
}


// Overload the assignment = operator.
Matrix &Matrix::operator=(const Matrix &B)
{
    if (this == &B)
        return(*this); // Taking care for self-assignment

    delete [] entries; // Just in case there was any memory
    // already allocated to this

    entries = new double[(B.N)*(B.N)];
    for (unsigned int i=0; i<N*N; i++)
        entries[i] = B.entries[i];

    return(*this);
}

// Overload the operator multiplication (*) for a Matrix-Vector
// product. Matrix is passed implicitly as "this", the Vector is
// passed explicitly. Will return v=(this)*u
Vector Matrix::operator*(Vector u)
{
    Vector v(N); // v = A*u, where A is the implicitly passed Matrix
    if (N != u.size())
        std::cerr << "Error: Matrix::operator* - dimension mismatch"
                  << std::endl;
    else
        for (unsigned int i=0; i<N; i++)
        {
            double x=0;
            for (unsigned int j=0; j<N; j++)
                x += entries[i*N+j]*u.geti(j);
            v.seti(i,x);
        }
    return(v);
}

Vector operator/(Vector b,Matrix L)
{
    int N = L.size();
    Vector x(N); // x solves L*x=b
    // check all the upper triangular entries (excluding the diagonal entries)
    // if they are 0
    for (unsigned int i = 0; i < N; i++)
    {
        for (unsigned int j = i+1; j < N; j++)
        {
            if (L.getij(i,j)!= 0)
                std::cerr << "Error: This is not a lower triangular matrix.";
        }
    }
    for (unsigned i = 0; i<N;i++)
        x.seti(i,0);
    for (unsigned int i = 0; i < N; i++)
    {
        double sum = 0.0; // we need new sum for every xi
        for (unsigned int j = 0; j < i ; j++)
        {
            sum += L.getij(i,j)*x.geti(j);
        }

        x.seti(i,(b.geti(i)-sum)/L.getij(i,i));

    }
    return(x);
}

Matrix Matrix::operator+(Matrix A)
{
    //add entry wise
    Matrix sum_Matrix(N);
    for (unsigned int i = 0; i < N; ++i)
        for (unsigned int j = 0; j < N; ++j)
            sum_Matrix.setij(i, j, entries[i * N + j] + A.entries[i * N + j]);
    return sum_Matrix;
}

Matrix Matrix::operator-(Matrix A)
{
    //just need to subtract entry-wise
    Matrix sub_Matrix(N);
    for (unsigned int i = 0; i < N; ++i)
        for (unsigned int j = 0; j < N; ++j)
            sub_Matrix.setij(i, j, entries[i * N + j] - A.entries[i * N + j]);
    return sub_Matrix;
}

Vector Matrix::diagonal_entries()
{
    Vector ii_entry(N);
    for (unsigned int i = 0; i < N; ++i)
        ii_entry.seti(i, entries[i * N + i]);
    return ii_entry;
}


