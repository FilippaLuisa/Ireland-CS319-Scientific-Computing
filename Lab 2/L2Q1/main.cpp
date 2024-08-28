// Author: Filippa Getzner, ID:21123839
// CS319 Lab 2 Question 1
// Date: 02/02/2024

#include <iostream>

int main()
{
    float x = 1.0;

    while (x/2>0){
        x/=2;
    }
    std::cout << "The smallest float is " << x << std::endl;
}
