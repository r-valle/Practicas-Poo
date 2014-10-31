
CXX = g++
CXXFLAGS = -Wall -ansi -pedantic -g
OBJETOS = fecha.o prueba-auto.o
EXES = prueba-auto

prueba-auto: prueba-auto.o fecha.o
	$(CXX) -o $@ $(LDFLAGS) prueba-auto.o fecha.o

fecha.o: fecha.h
prueba-auto.o: fecha.h fct.h

clean:
	$(RM) $(EXES) $(OBJETOS) core *~