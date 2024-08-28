/* FILE  : Lab1-Q3.cpp
   Author: Niall Madden
   Date  : Feb 2021
   For   : CS319, Lab 1
   What  :  Find the largest integer correctly representable,
            and time how long it takes.
*/

#include <iostream>
#include <time.h>

int main(void)
{
   std::cout << std::endl <<
     "---------------------------------\n" <<
     "| CS319  Lab 1, Q3(a),  Jan 2020 |\n" <<
     "---------------------------------\n";
   clock_t start;
   float diff, diff_seconds;
   start=clock();

   unsigned int i=1,j=i+1;

   while ( i<j )
   {
      i++;
      j=i+1;
   }
   diff = (float)(clock()-start);
   diff_seconds = diff/CLOCKS_PER_SEC;
   std::cout << "Overflow at i="<< i << std::endl;
   std::cout << "Computation took " << diff_seconds
        << " seconds."  << std::endl;
   return(0);
}

// with int:
// overflow: i=2147483647
// time: 6.24 s

// with short int:
// overflow: 32767
// time: 0 s

// with unsigned int:
// overflow: 4294967295 (double of int)
// time: 12.466 s
// unsigned int means we have no + or- before the number, so we have one more byte to store the number in

// long int:
// would take 2^8 times the amount of time to compute





