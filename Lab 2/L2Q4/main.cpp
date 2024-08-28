// Author: Filippa Getzner, ID:21123839
// CS319 Lab 2 Question 4
// Date: 02/02/2024

#include <iostream>
#include <cmath>

int main()
{
    // initialize all the variables we need later
    double x = 1.0;
    double y = 1.0;
    double a = 1.0;
    double b = 1.0+a;

    // (i)
    // use a while loop to compute the smallest double
    while (x/2>0){
        x/=2;
    }
    // the loop breaks when the computer thinks x/2 is equal to 0
    // the next line prints the x that was the closest to 0 before the loop ended (ie the smallest double)
    std::cout << "The smallest double is " << x << std::endl;


    // (ii)
    // use a while loop again to compute the largest double
    while (!std::isinf(y*2)){
        y=y*2;
    }
    // the loop breaks when the computer thinks that y*2 is inf and then returns that y (ie the largest double)
    std::cout<< "The largest double is " << y << std::endl;


    // (iii)
    // use a while loop again to compute the machine epsilon for a double
    while (b>1.0){
        a/=2.0;
        b = 1.0 + a/2.0;
    }
    // when the computer can't distinguish between 1 and 1+a/2 the loop breaks and
    // the next line returns the a that we calculated in the last loop (ie the machine epsilon)
    std::cout << "The machine epsilon for the double data type is " << a << std::endl;
}
