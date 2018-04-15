/*******************************************************************************************
*   Compilation :  g++ main.cpp hx711.cpp  spi.c -o main
*******************************************************************************************/

#include <iostream>
#include <iomanip>
#include "hx711.h"
#include <unistd.h>

using namespace std;

int main()
{

    hx711 balance;
    float xn, yn, yn_1;
    yn   = 0.0;
    yn_1 = 0.0;

    balance.effectuerTarage();
    while(1)
    {
	xn = balance.obtenirPoids();
	// Filtrage passe bas du premier ordre constante de temps 2.Te  (20ms)
	yn = 0.33 * xn + 0.66 * yn_1;
	yn_1 = yn;

        cout << yn << fixed << setprecision (1) << " g" << endl;
        usleep(100000);
        system("clear");
    }
}
