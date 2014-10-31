
CXX = g++
CXXFLAGS = -Wall -ansi -pedantic -g
OBJETOS = cadena.o prueba-auto.o
EXES = prueba-auto

prueba-auto: prueba-auto.o cadena.o
	$(CXX) -o $@ $(LDFLAGS) prueba-auto.o cadena.o
	
cadena.o: cadena.h
prueba-auto.o: cadena.h fct.h

clean:
	$(RM) $(OBJETOS) $(EXES) core *~
