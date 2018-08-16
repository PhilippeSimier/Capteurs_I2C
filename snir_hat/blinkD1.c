/** gcc -Wall blinkD1.c -lwiringPi -o blinkD1
    Led D1 -> 21
    Led D2 -> 26
    Led D3 -> 19
    BP1 -> 13
**/

#define D1  21
#define D2  26
#define D3  19
#define BP1 13

#include <wiringPi.h>

int main (void)
{
    wiringPiSetupGpio();
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(BP1, INPUT);

    while(digitalRead (BP1))
    {
        digitalWrite(D1, HIGH);
        digitalWrite(D2, LOW);
        delay(500);
        digitalWrite(D1, LOW);
        digitalWrite(D2, HIGH);
        delay(500);
    }

    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);

    return 0;
}
