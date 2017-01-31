# compilation de l'exemple main
exemple: main.cpp bm280.o
	g++ main.cpp bm280.o -l wiringPi -o exemple	

# compilation de la classe bm280
bm280.o: bm280.cpp bm280.h
	g++ -c bm280.cpp -l wiringPi -o bm280.o

# suppression des fichiers temporaires
clean:
	rm -rf *.o
