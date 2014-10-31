
CXX = g++
CXXFLAGS = -Wall -ansi -pedantic -g
OBJETOS = fecha.o prueba-auto.o prueba-consola.o
EXES = prueba-auto prueba-consola

all: prueba-auto prueba-consola

prueba-auto: prueba-auto.o fecha.o
	$(CXX) -o $@ $(LDFLAGS) prueba-auto.o fecha.o

fecha.o: fecha.h
prueba-auto.o: fecha.h fct.h

prueba-consola: prueba-consola.o fecha.o
	$(CXX) -o $@ $(LDFLAGS) prueba-consola.o fecha.o

prueba-consola.o: fecha.h

clean:
	$(RM) $(EXES) $(OBJETOS) core *~