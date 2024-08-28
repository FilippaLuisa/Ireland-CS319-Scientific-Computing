// A very basic implementation of a bisection algorithm.
// For Lab 3 of CS319 -- Scientific Computing
// This is loosely based on Shapira "Solving PDEs in C++", Section 1.20
// Author: Niall Madden
// For more, see: https://www.niallmadden.ie/2324-CS319/#lab3

#include <iostream>
#include <iomanip>
#include <math.h>

double Bisection(double Fn(double),double left, double right, unsigned &iterations, unsigned mit);
double f(double x){return(exp(-2*x) - 2*x*x + 4*x );}
double g(double x){return (x+sin(2*x));}
double k(double x){return (-x*x*x*x+x*x+x);}
double h = 1e-6;

int main()
{
    double a=-1.0, b=3.0, c;
    unsigned i;
    unsigned mit=0;

    std::cout << "Please enter the number of maximum iterations: ";
    std::cin >> mit; //mit = max # of iterations

    c = Bisection(g,a,b,i,mit);

    std::cout << "The maximum of the function between "
              << a << " and " << b << " is at "
              << std::setprecision(10) << c << std::endl;
    std::cout << "The number of iterations is: " << i << std::endl;

    return(0);
}


// The objective function

// FUNCTION: Bisection
// ARGUMENTS: (double) a and (double) b
// RETURNS: (double) c, the point where the function f,
//    defined above, achieves its max.
double Bisection(double Fn(double), double a, double b, unsigned &i, unsigned mit)
{
    double c = (a+b)/2.0;
    i=0;
    while ( ((b-a) > h) && (i< mit))
    {
        i++;
        c = (a+b)/2.0;
        double l = (a+c)/2.0, r=(c+b)/2.0;

        if ( (Fn(c) > Fn(l)) && (Fn(c) > Fn(r)) )
        {
            a=l;
            b=r;
        }
        else if ( Fn(l) > Fn(r) )
        {
            b=c;
        }
        else
        {
            a=c;
        }
    }
    return(c);
}
