/*----------------------------------------------------------------------------------
*  compilation :
*   g++ saveTemp.cpp Ds1631.cpp -o saveTemp -l wiringPi `mysql_config --cflags --libs`
*
*-----------------------------------------------------------------------------------*/
#include <iostream>
#include <iomanip>

#include <my_global.h>
#include <mysql.h>
#include <stdio.h>
#include "Ds1631.h"


void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int enregistre (float valeur)
{
  MYSQL *con = mysql_init(NULL);
  char sqlINSERT[100];

  sprintf(sqlINSERT, "INSERT INTO temperature(date,valeur) VALUES(CURRENT_TIMESTAMP,%.2f)", valeur);
  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }
  // connection à la base mySQL  Valeurs
  if (mysql_real_connect(con, "localhost", "root", "toto", "Valeurs", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  if  (mysql_query(con, sqlINSERT))  {
      finish_with_error(con);
  }
  mysql_close(con);
}



int  main ()
{
   Ds1631 capteur1(0x48);
   float valeur;

  valeur = capteur1.getTemperature();

  printf(" temperature = %.2f \n",valeur);

  enregistre(valeur);
  return 0;
}
