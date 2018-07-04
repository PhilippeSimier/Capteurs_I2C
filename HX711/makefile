CXX = g++
EXEC = etalonnage tarage tarageCGI scaleCGI balanceJson main

all: $(EXEC)

# compilation du programme etalonnage 
etalonnage: etalonnage.cpp SimpleIni.o hx711.o
	$(CXX) etalonnage.cpp SimpleIni.o hx711.o spi.o -o etalonnage


# compilation du programme tarage
tarage: tarage.cpp SimpleIni.o hx711.o
	$(CXX) tarage.cpp SimpleIni.o hx711.o spi.o -o tarage

# compilation du programme tarageCGI
tarageCGI: tarageCGI.cpp SimpleIni.o hx711.o
	$(CXX) tarageCGI.cpp SimpleIni.o hx711.o spi.o -o tarageCGI

# compilation du programme scaleCGI
scaleCGI: scaleCGI.cpp SimpleIni.o hx711.o
	$(CXX) scaleCGI.cpp SimpleIni.o hx711.o spi.o -o scaleCGI


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

# Install les programmes CGI
install:
	cp balanceJson /usr/lib/cgi-bin/balanceJson
	chmod +s /usr/lib/cgi-bin/balanceJson
	cp tarageCGI /usr/lib/cgi-bin/tarageCGI
	chmod +s /usr/lib/cgi-bin/tarageCGI
	cp scaleCGI /usr/lib/cgi-bin/scaleCGI
	chmod +s /usr/lib/cgi-bin/scaleCGI
	chmod 777 configuration.ini

uninstall:
	rm /usr/lib/cgi-bin/balanceJson
	rm /usr/lib/cgi-bin/tarageCGI
	rm /usr/lib/cgi-bin/scaleCGI

