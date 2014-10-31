
// Práctica 2 Programación orientada a objetos
// Rafael Valle Cabrera
// Clase Cadena

#ifndef _CADENA_H_
#define _CADENA_H_

#include <stdexcept>
// Lo incluimos para que el compilador entienda istream y ostream como tipos
#include <iostream>

using namespace std;

class Cadena{
public:
  // Constructor para 0, 1 y 2 parámetros
  // Se impide la conversión implícita de entero en una Cadena
  explicit Cadena(unsigned tam_inicial = 0, const char relleno = ' ') throw();

  // Constructor de copia
  Cadena(const Cadena&) throw();
  
  // Constructor de conversión
  Cadena(const char*) throw();
  
  // Métodos observadores
  inline char* cadena() const { return cadena_;}
  inline unsigned length() const throw(){ return tamano_;}
  
  // se distingue entre una versión modificadora y otra observadora de at
  // para impedir modificaciones no deseadas
  const char at(unsigned int) const throw(out_of_range);
  char& at(unsigned i) throw(out_of_range);
  const Cadena subcadena(int, int) const throw(out_of_range);
  
  // Métodos modificadores
  // No son constantes
  inline void asignar_longitud(unsigned lon){ tamano_ = lon;};
  
  // método de conversión char*()
  const char*c_str() const throw();
  
  // Operadores
  // sólo a los operadores declarados dentro de la clase es necesario especificar 
  // si su lista de lanzamiento de excepciones está vacía o no
  
  // Operador de asignación entre objetos Cadena
  Cadena& operator=(const Cadena&) throw();
  
  // Operador de asignación de cadena a Cadena
  Cadena& operator=(const char*) throw();
  
  // Operador de suma
  Cadena operator+(const Cadena&)const throw();
  
  // Operador de suma con asignación
  Cadena& operator+=(const Cadena&) throw();
  
  // Operador índice [] versión constante
  const char operator[](unsigned i) const throw();
  
  // Operador índice []
  char& operator[](unsigned i) throw();

private:
  char* cadena_;
  unsigned tamano_;
};

// Operadores que se declaran fuera de la clase para preservar su commutatividad

// Operadores relacionales

bool operator==(const Cadena&, const Cadena&);
bool operator!=(const Cadena&, const Cadena&);
bool operator>(const Cadena&, const Cadena&);
bool operator<(const Cadena&, const Cadena&);
bool operator>=(const Cadena&, const Cadena&);
bool operator<=(const Cadena&, const Cadena&);

// Operadores de flujo

// << operador de inserción
// >> operador de extracción

// Operador de inserción de flujo
ostream& operator<<(ostream&, const Cadena&);

// Operador de extracción de flujo
istream& operator>>(istream&, Cadena&);

#endif
