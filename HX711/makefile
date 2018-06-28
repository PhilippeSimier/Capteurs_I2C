CXX = g++
EXEC = etalonnage balanceJson main

all: $(EXEC)

# compilation du programme etalonnage 
etalonnage: etalonnage.cpp SimpleIni.o hx711.o
	$(CXX) etalonnage.cpp SimpleIni.o hx711.o spi.o -o etalonnage

# compilation du programme balanceJson
balanceJson: balanceJson.cpp SimpleIni.o hx711.o
	$(CXX) balanceJson.cpp SimpleIni.o hx711.o spi.o -o balanceJson

# compilation du programme main
main: main.cpp SimpleIni.o hx711.o
	$(CXX) main.cpp SimpleIni.o hx711.o spi.o -o main

# compilation de la classe SimpleIni
SimpleIni.o: SimpleIni.cpp SimpleIni.h
	$(CXX) -c SimpleIni.cpp -o SimpleIni.o

# compilation de la classe hx711
hx711.o:  hx711.cpp hx711.h spi.o
	$(CXX) -c hx711.cpp -o hx711.o

# compilation de spi
spi.o: spi.c spi.h
	$(CXX) -c spi.c -o spi.o

.PHONY: clean mrproper

# suppression des fichiers temporaires
clean:
	rm -rf *.o

# pour la reconstruction du projet
mrproper: clean
	rm $(EXEC)

# Install le programme CGI
install:
	cp balanceJson /usr/lib/cgi-bin/balanceJson
	chmod +s /usr/lib/cgi-bin/balanceJson

uninstall:
	rm /usr/lib/cgi-bin/balanceJson

