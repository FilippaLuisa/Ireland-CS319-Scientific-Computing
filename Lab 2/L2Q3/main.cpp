// Author: Filippa Getzner, ID:21123839
// CS319 Lab 2 Question 3
// Date: 02/02/2024

#include <iostream>


int main()
{
    float x = 1.0;
    float z = 1.0+x ;
    while (z>1.0){
        x/=2.0;
        z = 1.0 + x/2.0;
    }

    std::cout << "The machine epsilon for the float data type is "<< x << std::endl;

    double a = 1.0;
    double b = 1.0+a;
    while (b>1.0){
        a/=2.0;
        b = 1.0 + a/2.0;
    }

    std::cout << "The machine epsilon for the double data type is " << a << std::endl;
}

