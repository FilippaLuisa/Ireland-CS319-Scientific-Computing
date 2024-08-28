// Author: Filippa Getzner, ID:21123839
// CS319 Lab 2 Question 2
// Date: 02/02/2024

#include <iostream>
#include <cmath>

int main()
{
    float x=1.0;

    while (!std::isinf(x*2)){
        x=x*2;
    }
    std::cout<< "The largest float is " << x << std::endl;
}
