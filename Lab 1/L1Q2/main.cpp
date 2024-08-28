// L1Q2:
// Input: integer
// Output: while n<0 or n>10 output something like please enter another integer
// as soon as n<=10 output something like congrats

#include <iostream>

int main()
{
    int n;

    std::cout << "Please enter an integer between 1 and 10 (inclusive): ";
    std::cin >> n;

    while ((n<0) || (n>10))
    {
         std::cout << "This integer doesn't lie between 1 and 10 you idiot, please enter another integer: ";
         std::cin >> n;
    }

    std::cout << "The number " << n << " is a number between 1 and 10";
    return 0;

}
