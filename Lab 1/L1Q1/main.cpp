// L1Q1:
// Input: x and y value
// Output: the quadrant

#include <iostream>

int main(void)
{
    int x;
    int y;

    std::cout << "Please enter an integer for x:";
    std::cin >> x;

    std::cout << "Please enter an integer for y:";
    std::cin >> y;

    if ((x==0) && (y==0))
        std::cout << "This point is the origin";
        else if ((x>0) && (y>0))
            std::cout << "This point lies in the first quadrant.";
        else if ((x<0) && (y>0))
            std::cout << "This point lies in the second quadrant.";
        else if ((x<0) && (y<0))
            std::cout << "This point lies in the third quadrant.";
        else if ((x>0) && (y<0))
            std::cout << "This point lies in the fourth quadrant.";
    return(0);


}
