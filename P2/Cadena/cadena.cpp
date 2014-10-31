
#include <iostream>
#include <cstring>
#include "cadena.h"

using namespace std;

// Constructores clase Cadena
// los atributos siempre conviene inicializarlos en la lista de inicialización
Cadena::Cadena(unsigned tam_inicial, char relleno) throw(): tamano_(tam_inicial){
  cadena_ = new char[tamano_+1];
  for(unsigned i = 0; i < tamano_; i++){
    cadena_[i] = relleno;
  }
  cadena_[tamano_] = '\0';
}

Cadena::Cadena(const Cadena& cad) throw(){
  tamano_ = cad.tamano_;
  cadena_ = new char[tamano_+1];
  strcpy(cadena_,cad.cadena_);
}

Cadena::Cadena(const char* cadena) throw(){
  tamano_ = strlen(cadena);
  cadena_ = new char[tamano_+1];
  strcpy(cadena_,cadena);
}

const char Cadena::at(unsigned i) const throw(out_of_range){
  if(i < 0 or i > length()-1 or cadena_[i] == '\0'){
    throw out_of_range("Fuera de rango");
  }
  return cadena_[i];
}

char& Cadena::at(unsigned i) throw(out_of_range){
  if(i < 0 or i > length()-1 or cadena_[i] == '\0'){
    throw out_of_range("Fuera de rango");
  }
  return cadena_[i];
}

const Cadena Cadena::subcadena(int i, int tamano) const throw(out_of_range){
  if(i < 0 or tamano < 0 or i > (int)length() or (tamano+i) > (int)length()){
    throw out_of_range("indice fuera de rango");
  } else{
      char* cadena = new char[tamano];
      for(int j = 0; j < tamano; j++){
	cadena[j] += cadena_[j+i];
      }
      cadena[tamano] = '\0';
      Cadena cad(cadena);
      delete[] cadena;
      return cad;
  }
}

// método de conversión const char*
const char* Cadena::c_str() const throw(){
  return cadena_;
}

// Operadores

// Operador de asignación con Const Cadena
Cadena& Cadena::operator=(const Cadena& cad1) throw(){
  //evitamos la autoasignación
  if(this != &cad1){
    delete[] cadena_;
    cadena_ = new char[cad1.tamano_+1];
    tamano_ = cad1.tamano_;
    strcpy(cadena_,cad1.cadena_);
  }
  return (*this);
}

// Operador de asignación con const char*
Cadena& Cadena::operator=(const char* cad) throw(){
  Cadena cad3(cad);
  *this = cad3;
  return (*this);
}

// Operador de suma con asignación (concatenación)
Cadena& Cadena::operator+=(const Cadena& cad1) throw(){
  Cadena cad3 = *this + cad1;
  (*this) = cad3;
  return (*this);
}

// Operador índice [] versión constante
const char Cadena::operator[](unsigned i) const throw(){
  return cadena_[i];
}

// Operador índice [] versión no constante
char& Cadena::operator[](unsigned i) throw(){
  return cadena_[i];
}

// Operador de suma 
Cadena Cadena::operator+(const Cadena& cad2)const throw(){
  Cadena cad3(tamano_+cad2.tamano_);
  strcpy(cad3.cadena_,cadena_);
  strcat(cad3.cadena_,cad2.cadena_);
  return cad3;
}

// Operadores relacionales

bool operator==(const Cadena& cad1, const Cadena& cad2){
  // la función strcmp devuelve 0 en caso de que coincidan las cadenas que reciba
  // o un valor mayor que 0 que indicará que el primer carácter distinto en cad1 es mayor que en cad2
  return (strcmp(cad1.cadena(),cad2.cadena()) == 0);
}

bool operator!=(const Cadena& cad1, const Cadena& cad2){
  return (strcmp(cad1.cadena(),cad2.cadena()) != 0);
}

bool operator>(const Cadena& cad1, const Cadena& cad2){
  // La función strcmp devuelve un valor mayor que 0 en caso de que encuentre 
  // un carácter en cad1 cuyo valor es mayor que su correspondiente en cad2
  return (strcmp(cad1.cadena(),cad2.cadena()) > 0);
}

bool operator<(const Cadena& cad1, const Cadena& cad2){
  // La función strcmp devuelve un valor mayor que 0 en caso de que encuentre un carácter
  // en cad2 cuyo valor es mayor que su correspondiente en cad1, por lo que cad1 sería menor
  return (strcmp(cad1.cadena(),cad2.cadena()) < 0);
}

bool operator>=(const Cadena& cad1, const Cadena& cad2){
  return (cad1 > cad2 or cad1 == cad2);
}

bool operator<=(const Cadena& cad1, const Cadena& cad2){
  return (cad1 < cad2 or cad1 == cad2);
}

// Operadores de flujo

// Operador de inserción de flujo
ostream& operator<<(ostream& flujo, const Cadena& cad1){
  flujo << cad1.c_str();
  return flujo;
}

// Operador de extracción de flujo
istream& operator>>(istream& flujo, Cadena& cad1){
  unsigned tamano = 32;
  char* cadena = new char[tamano];
  // Insertamos el carácter terminador
  cadena[0] = '\0';
  // Usamos la función miembro width() para leer flujo dado su tamaño
  // gracias a un operador de la clase istream que transforma istream a void*
  // el puntero void* se transforma luego a bool, sirviendo como valor booleano
  flujo.width(tamano);
  flujo >> cadena;
  // aux se borrará por sí sola recurriendo a su destructor
  Cadena aux(cadena);
  cad1 = aux;
  delete[] cadena;
  return flujo;
}
