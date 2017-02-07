
# compilation de saveTemp
saveTemp: saveTemp2.cpp Ds1631.o
	g++ saveTemp2.cpp Ds1631.o i2c.o -lmysqlcppconn -o saveTemp

# compilation de LireData
lireData: lireData.cpp Ds1631.o
	g++ lireData.cpp -l mysqlcppconn -o lireData

# compilation de temperature
temperature: temperature.cpp Ds1631.o
	g++ temperature.cpp Ds1631.o i2c.o  -o temperature	

# compilation de la classe Ds1631
Ds1631.o: Ds1631.cpp Ds1631.h i2c.o
	g++ -c Ds1631.cpp  i2c.o -o Ds1631.o

# compilation de la classe i2c
i2c.o: i2c.cpp i2c.h
	g++ -c i2c.cpp  -o i2c.o


# suppression des fichiers temporaires
clean:
	rm -rf *.o

