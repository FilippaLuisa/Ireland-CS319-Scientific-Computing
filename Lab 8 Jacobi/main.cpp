// Author: Filippa Getzner (and Niall Madden)
// ID: 21124839
// File: main.cpp: Jacobi's and Gauss-Seidel's method for solving linear systems
// Date: 22nd of March, 2024.
// What: Solving a linear system of equations with Jacobi's method,
//          using Matrix10 and Vector10 classes

#include <iostream>
#include <cmath>
#include "Vector10.h"
#include "Matrix10.h"

Vector Jacobi(Matrix A, Vector b, Vector xk,unsigned &count, unsigned MaxIts, double TOL);

Vector GaussSeidel(Matrix A, Vector b, Vector xk,unsigned &count, unsigned MaxIts, double TOL);

int main(void )
{
    unsigned int N = 3;
    Matrix A(N);
    Vector x(N), b(N), xkJ(N), xkGS(N);
    for (unsigned i = 0; i<N; i++)
    {
        b.seti(i,15);
        x.seti(i,1);
        xkJ.seti(i,0);
        xkGS.seti(i,0);
        for (unsigned j=0; j<N; j++)
            if (i==j)
                A.setij(i,j,9.0);
            else A.setij(i,j,3.0);
    }

    //----------------JACOBI----------------------
    std::cout<< "JACOBI METHOD";
    unsigned numberofItsJ = 0;
    xkJ.zero();
    xkJ = Jacobi(A, b, xkJ, numberofItsJ, 100, 1e-6);

    Vector ErrorJ(N);
    ErrorJ = x-xkJ;
    std::cout << "\nJacobi Number of iterations: " << numberofItsJ <<
              "\nError = " << ErrorJ.norm() << std::endl;

    std::cout << "Estimate is : " << xkJ << std::endl;

    //------------------TESTING THE / OPERATOR ----------
    std::cout << "\n\nTESTING THE / OPERATOR:" <<
              " \nThis is the lower triangular Matrix L:\n";
    Matrix L(3);
    for (unsigned i = 0; i<3; i++)
        for (unsigned j = 0; j<3; j++)
        {
            if (j<=i)
                L.setij(i,j,1.5);
            else
                L.setij(i,j,0.0);
        }
    L.print();
    Vector B(3);
    for (unsigned i = 0; i<3; i++)
        B.seti(i,3);
    std::cout<<"\nThis is the Vector B:\n";
    B.print();
    Vector x_op_test(3);
    x_op_test = B/L;
    std::cout<<"\nAnd this is the vector x that solves L*x=b\n";
    x_op_test.print();

    //------------------GAUSS-SEIDEL------------------------
    std::cout<< "\n\nGAUSS SEIDEL METHOD";
    unsigned numberofItsGS = 0;
    xkGS.zero();
    xkGS = GaussSeidel(A, b, xkGS, numberofItsGS, 100, 1e-6);

    Vector ErrorGS(N);
    ErrorGS = x-xkGS;
    std::cout << "\nGS Number of iterations: " << numberofItsGS <<
              "\nError = " << ErrorGS.norm() << std::endl;

    std::cout << "Estimate is : " << xkGS << std::endl;

    //------------------VERIFY: GS IS MORE EFFICIENT--------
    std::cout << "\n\nEFFICIENCY:";
    std::cout<< "\n\nWe want to verify that GS is more efficient than J.\n";

    Vector J(N), GS(N);
    J.zero();
    GS.zero();
    double tol = 1.0;
    while (tol > 1e-06)
    {
        std::cout<< "\nTolerance: " << tol << std::endl;

        unsigned int numberofItsJ1 = 0;
        J.zero();
        J = Jacobi(A, b, J, numberofItsJ1, 100, tol);
        std::cout << "J:  Number of iterations " << numberofItsJ1 << std::endl;

        unsigned int numberofItsGS1 = 0;
        GS.zero();
        GS = GaussSeidel(A, b, GS, numberofItsGS1, 100, tol);
        std::cout << "GS: Number of iterations " << numberofItsGS1 << std::endl;

        tol *=0.1;
    }
    return (0);
}

Vector Jacobi(Matrix A, Vector b, Vector xk,unsigned &count, unsigned MaxIts, double TOL)
{
    unsigned int N = A.size();
    double normR = TOL+1;
    Vector R(N);
    Vector xk1(N);

    Matrix Dinv(N), T(N);
    for (unsigned i =0; i<N; i++)
        for (unsigned j = 0; j<N; j++)
            if (i==j)
            {
                Dinv.setij(i,i,1/A.diagonal_entries().geti(i));
                T.setij(i,i,0);
            }
            else
            {
                Dinv.setij(i,j,0.0);
                T.setij(i,j,-A.getij(i,j));
            }

    //T.print();
    //Dinv.print();
    count =0;
    while ((normR > TOL) && (count < MaxIts))
    {
        count ++;
        xk1 = Dinv*(b+T*xk);//b-A*xk
        xk = xk1;
        R = b - A*xk;
        normR = R.norm();
    }

    return xk;
}

Vector GaussSeidel(Matrix A, Vector b, Vector xk,unsigned &count, unsigned MaxIts, double TOL)
{
    unsigned int N = A.size();
    double normR = TOL+1;
    Vector R(N);

    Matrix L(N), U(N);

    for (unsigned i=0; i<N; i++)
        for(unsigned j=0; j<N; j++)
        {
            if (j<=i)
            {
                L.setij(i,j,A.getij(i,j));
                U.setij(i,j,0.0);
            }
            else
            {
                L.setij(i,j,0.0);
                U.setij(i,j,-A.getij(i,j));
            }
        }
    count=0;
    while ((normR > TOL) && (count < MaxIts))
    {
        count ++;
        xk = (b+U*xk)/L;
        R = b - A*xk;
        normR = R.norm();
    }
    return xk;
}


// CEMETERY FOR CODE THAT DIDN'T WORK :(

//trieed to generate a NxN random linear system that is diagonally dominant but it worked terribly - the errors were way too big

//std::cout << "Please enter the dimension N for the NxN linear system: ";
//std::cin >> N;

//for (unsigned i=0; i<N; i++)
    //{
        //double sum=0.0;
        //for (unsigned j=0; j<N; j++)
        //{
            //if (i!=j)
            //{
                //double ij_entry = rand()%20;
                //A.setij(i,j,ij_entry);
                //sum += ij_entry;
            //}
        //}
        //double ii_entry = sum + 1.0;
        //A.setij(i,i,ii_entry);
    //}
    //A.print();
    //for (unsigned i = 0; i<N;i++)
        //b.seti(i,rand()%50);
    //b.print();
