
CXX = g++
CXXFLAGS = -Wall -ansi -pedantic -g
OBJETOS = cadena.o prueba-auto.o prueba-consola.o
EXES = prueba-auto prueba-consola

all: prueba-auto prueba-consola

prueba-auto: prueba-auto.o cadena.o
	$(CXX) -o $@ $(LDFLAGS) prueba-auto.o cadena.o
	
cadena.o: cadena.h
prueba-auto.o: cadena.h fct.h

prueba-consola: prueba-consola.o cadena.o
	$(CXX) -o $@ $(LDFLAGS) prueba-consola.o cadena.o

prueba-consola.o: cadena.h

clean:
	$(RM) $(OBJETOS) $(EXES) core *~
