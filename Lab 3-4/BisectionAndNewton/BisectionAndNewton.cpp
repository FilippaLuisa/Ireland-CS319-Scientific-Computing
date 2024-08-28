//Author: Filippa Getzner
//ID: 21124839
//Date: 16/02/2024
//CS319 Lab 3-4

#include <iostream>
#include <iomanip>
#include <math.h>

//Declarations for Bisection Algorithm
double Bisection(double Fn(double),double left, double right, unsigned &i, unsigned maxitB);
double h = 1e-6;

//Declarations for the Newton Algorithm
double Newton(double Fn(double), double dFn(double), double ddFn(double), double initial, unsigned &j, unsigned maxitN);
double g(double x){return(x+sin(2*x));}
double dg(double x){return (2.0*cos(2.0*x)+1.0);}
double ddg(double x){return (-4.0*sin(2.0*x));}

int main()
{
    //for Bisection
    double a=-1.0, b=2.0, c;
    unsigned i, maxitB=0;
    //for Newton
    double x0; //starting point
    double y;
    unsigned j, maxitN=30;


    std::cout << "BISECTION \nPlease enter the number of maximum iterations: ";
    std::cin >> maxitB; //mitB = max # of iterations for Bisection

    c = Bisection(g,a,b,i,maxitB);

    std::cout << "The maximum of the function between "
              << a << " and " << b << " is at "
              << std::setprecision(10) << c << std::endl;
    std::cout << "The number of iterations is: " << i << std::endl;

    //Newton
    std::cout<< "\nNEWTON \nWe use one iteration of the Bisection algorithm to get a good initial guess for the Newton algorithm.\n";
    x0 = Bisection(g,a,b,i,1);
    std::cout<< "x0 = " << std::setprecision(10) << x0 << std::endl;
    std::cout << "Please enter the number of maximum iterations for the Newton Algorithm: ";
    std::cin >> maxitN; // mitB = max # of iterations for Newton

    y = Newton(g,dg,ddg,x0,j,maxitN);

    std::cout << "The maximum of the function between "
              << a << " and " << b << " is at "
              << std::setprecision(10) << y << std::endl;
    std::cout << "The number of iterations is: " << j << std::endl;

    return(0);
}


// FUNCTION: Bisection
// ARGUMENTS: objective function, (double) a and (double) b, number of iterations, max number of iterations
// RETURNS: (double) c, the point where the function f,
//          defined above, achieves its max after i iterations of the while loop
double Bisection(double FnB(double), double a, double b, unsigned &i, unsigned maxitB)
{
    double c = (a+b)/2.0;
    i=0;
    while ( ((b-a) > h) && (i< maxitB))
    {
        i++;
        c = (a+b)/2.0;
        double l = (a+c)/2.0, r=(c+b)/2.0;

        if ( (FnB(c) > FnB(l)) && (FnB(c) > FnB(r)) )
        {
            a=l;
            b=r;
        }
        else if ( FnB(l) > FnB(r) )
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

//FUNCTION: Newton
//ARGUMENTS: objective function, first & second derivative of the objective function, initial value, number of iterations, max number of iterations
//RETURNS: (double) c, the point where the function f,
//          defined above, achieves its max after j iterations of the while loop
double Newton(double Fn(double), double dFn(double), double ddFn(double), double x0, unsigned &j, unsigned maxitN)
{
    double xk, xk1;
    xk = x0;
    xk1 = xk - dFn(xk)/ddFn(xk);
    j = 1; //we have already done an iteration
    while ((j<maxitN)&&(fabs(xk-xk1)>h))
    {
        xk=xk1;
        xk1 = xk - dFn(xk)/ddFn(xk);
        j++;
    }
    return (xk1);
}
