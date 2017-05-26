/********************************************
*   programme exemple
*   g++ test1.cpp Ds1631.o i2c.o -o test1
*********************************************/
#include "Ds1631.h"

using namespace std;

int main()
{
   Ds1631 capteur1(0x4F);
   cout << capteur1 << endl;
   return 0;
}
