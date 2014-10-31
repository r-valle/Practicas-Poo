
// Práctica 1 Programación orientada a objetos
// Rafael Valle Cabrera
// Clase Cadena

#ifndef _CADENA_H_
#define _CADENA_H_

#include <stdexcept>
// Lo incluimos para que el compilador entienda istream y ostream como tipos
#include <iostream>

class Cadena{
public:
  // Constructor para 0, 1 y 2 parámetros
  // Se impide la conversión implícita de entero en una Cadena
  explicit Cadena(size_t tam_inicial = 0, char relleno = ' ') throw();

  // Constructor de copia
  Cadena(const Cadena&) throw();
  
  // Constructor de conversión
  Cadena(const char*) throw();
  
  // Métodos observadores
  const char* cadena() const { return cadena_;}
  size_t longitud() const throw(){ return tamano_;}
  
  // se distingue entre una versión modificadora y otra observadora de at
  // para impedir modificaciones no deseadas
  char at(size_t) const throw(std::out_of_range);
  char& at(size_t) throw(std::out_of_range);
  Cadena subcadena(size_t, size_t) const throw(std::out_of_range);
  
  // método de conversión char*()
  const char* c_str() const throw();
  
  // Operadores
  // sólo a los operadores declarados dentro de la clase es necesario especificar 
  // si su lista de lanzamiento de excepciones está vacía o no
  
  // Operador de asignación entre objetos Cadena
  Cadena& operator=(const Cadena&) throw();
  
  // Operador de asignación de cadena a Cadena
  Cadena& operator=(const char*) throw();
  
  // Operador de suma con asignación
  Cadena& operator+=(const Cadena&) throw();
  
  // Operador índice [] versión constante
  char operator[](size_t i) const throw(){ return cadena_[i];}
  
  // Operador índice []
  char& operator[](size_t i) throw(){ return cadena_[i];}

  // Destructor
  ~Cadena() throw();
private:
  char* cadena_;
  size_t tamano_;
};

// Operadores que se declaran fuera de la clase para preservar su commutatividad

// Operador de suma
Cadena operator+(const Cadena&, const Cadena&);

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
std::ostream& operator<<(std::ostream&, const Cadena&);

// Operador de extracción de flujo
std::istream& operator>>(std::istream&, Cadena&);

#endif
