/**
 * @file : testExept.cpp
   @compilation : g++ testExep.cpp capteurException.cpp -o testExep
*/

#include <iostream>
#include "capteurException.h"

using namespace std;


int division(int a,int b) // Calcule a divisé par b.
{
   if(b==0)
      throw CapteurException(1,"Division par zéro");
   else
      return a/b;
}

int main()
{
   int a,b;
   cout << "Valeur pour a : ";
   cin >> a;
   cout << "Valeur pour b : ";
   cin >> b;

   try
   {
       cout << a << " / " << b << " = " << division(a,b) << endl;
   }
   catch(std::exception const& e)
   {
       cerr << "ERREUR : " << e.what() << endl;
   }

   return 0;
}
