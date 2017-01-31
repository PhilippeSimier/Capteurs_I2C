
# compilation de saveTemp
saveTemp: saveTemp2.cpp Ds1631.o
	g++ saveTemp2.cpp Ds1631.o -l wiringPi -lmysqlcppconn -o saveTemp

# compilation de LireData
lireData: lireData.cpp Ds1631.o
	g++ lireData.cpp -l mysqlcppconn -o lireData

# compilation de temperature
temperature: temperature.cpp Ds1631.o
	g++ temperature.cpp Ds1631.o -l wiringPi -o temperature	

# compilation de la classe Ds1631
Ds1631.o: Ds1631.cpp Ds1631.h
	g++ -c Ds1631.cpp -l wiringPi -o Ds1631.o

# suppression des fichiers temporaires
clean:
	rm -rf *.o

