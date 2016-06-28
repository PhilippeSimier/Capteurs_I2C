# création des exécutables 'saveTemp' 'lireData' 'temperature'
all: Ds1631.o
	g++ saveTemp2.cpp Ds1631.o -l wiringPi -lmysqlcppconn -o saveTemp 
	g++ lireData.cpp -l mysqlcppconn -o lireData
	g++ temperature.cpp Ds1631.o -l wiringPi -o temperature 

# compilation de la classe Ds1631
Ds1631.o: Ds1631.cpp
	g++ -c Ds1631.cpp -l wiringPi -o Ds1631.o

# suppression des fichiers temporaires
clean:
	rm -rf *.o

