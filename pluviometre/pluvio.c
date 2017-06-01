#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>

// Utilise la broche  GPIO 17, qui est nommée Pin 0 par la bibliothèque  wiringPi
#define BUTTON_PIN 0

// Le compteur d'évenement
volatile int eventCounter = 0;

// -------------------------------------------------------------------------

void myInterrupt(void) {
   eventCounter++;
   printf("-  %d\n",eventCounter);
}

// -------------------------------------------------------------------------

int main(void) {
  // sets up the wiringPi library
  if (wiringPiSetup () < 0) {
      fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno));
      return 1;
  }

  // set Pin 17/0 generate an interrupt on high-to-low transitions
  // and attach myInterrupt() to the interrupt
  if ( wiringPiISR (BUTTON_PIN, INT_EDGE_FALLING, &myInterrupt) < 0 ) {
      fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno));
      return 1;
  }

  // affiche le résultat toutes les 2 minutes
  while ( 1 ) {
    printf( "%d\n", eventCounter );
    eventCounter = 0;
    delay( 120000 ); // attendre 2 minutes
  }

  return 0;
}
