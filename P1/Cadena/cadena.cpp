
#include <iostream>
#include <cstring>
#include "cadena.h"

using namespace std;

// Constructores clase Cadena
// los atributos siempre conviene inicializarlos en la lista de inicialización
Cadena::Cadena(size_t tam_inicial, char relleno) throw(): tamano_(tam_inicial){
  cadena_ = new char[tamano_+1];
  for(size_t i = 0; i < tamano_; i++){
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

char Cadena::at(size_t i) const throw(std::out_of_range){
  if(i >= longitud()){
    throw out_of_range("Fuera de rango");
  }
  return cadena_[i];
}

char& Cadena::at(size_t i) throw(std::out_of_range){
  if(i >= longitud()){
    throw out_of_range("Fuera de rango");
  }
  return cadena_[i];
}

Cadena Cadena::subcadena(size_t i, size_t tamano) const throw(std::out_of_range){
  if(i > longitud() or (tamano+i) > longitud() or tamano+i < tamano){
    throw out_of_range("indice fuera de rango");
  } else{
      Cadena cad(tamano);
      // Copia en cad.cadena_ los primeros n caracteres comenzando por i
      strncpy(cad.cadena_,cadena_+i,tamano);
      return cad;
  }
}

// método de conversión const char*
const char* Cadena::c_str() const throw(){
  return cadena_;
}

// Operadores

// Operador de asignación
Cadena& Cadena::operator=(const Cadena& cad) throw(){
  //evitamos la autoasignación
  if(this != &cad){
    delete[] cadena_;
    cadena_ = new char[cad.tamano_+1];
    tamano_ = cad.tamano_;
    strcpy(cadena_,cad.cadena_);
  }
  return (*this);
}

// Operador de asignación con conversión
Cadena& Cadena::operator=(const char* cad) throw(){
  if(cadena_ != cad){
    delete[] cadena_;
    tamano_ = strlen(cad);
    cadena_ = new char[tamano_+1];
    strcpy(cadena_,cad);
  }
  return *this;
}

// Operador de suma con asignación (concatenación)
Cadena& Cadena::operator+=(const Cadena& cad) throw(){
  tamano_ += cad.tamano_;
  char* aux = cadena_;
  cadena_ = new char[tamano_+1];
  strcpy(cadena_,aux);
  delete[] aux;
  strcat(cadena_,cad.cadena_);
  return *this;
}

// Destructor
Cadena::~Cadena() throw(){
  delete[] cadena_;
  cadena_ = 0;
}

// Operador de suma 
Cadena operator+(const Cadena& cad1, const Cadena& cad2){
  Cadena cad3(cad1);
  cad3 += cad2;
  return cad3;
}

// Operadores relacionales

bool operator==(const Cadena& cad1, const Cadena& cad2){
  // la función strcmp devuelve 0 en caso de que coincidan las cadenas que reciba
  // o un valor mayor que 0 que indicará que el primer carácter distsize_to en cad1 es mayor que en cad2
  return (cad1.longitud() == cad2.longitud() and strcmp(cad1.cadena(),cad2.cadena()) == 0);
}

bool operator!=(const Cadena& cad1, const Cadena& cad2){
  return not(cad1 == cad2); 
}

bool operator<(const Cadena& cad1, const Cadena& cad2){
  // La función strcmp devuelve un valor mayor que 0 en caso de que encuentre un carácter
  // en cad2 cuyo valor es mayor que su correspondiente en cad1, por lo que cad1 sería menor
  return strcmp(cad1.cadena(),cad2.cadena()) < 0;
}

bool operator>(const Cadena& cad1, const Cadena& cad2){
  return cad2 < cad1;
}

bool operator>=(const Cadena& cad1, const Cadena& cad2){
  return not(cad1 < cad2);
}

bool operator<=(const Cadena& cad1, const Cadena& cad2){
  return not(cad2 < cad1);
}

// Operadores de flujo

// Operador de inserción de flujo
ostream& operator<<(ostream& flujo, const Cadena& cad){
  flujo << cad.c_str();
  return flujo;
}

// Operador de extracción de flujo
istream& operator>>(istream& flujo, Cadena& cad){
  const size_t tam = 32;
  char aux[tam+1] = {'\0'};
  flujo.width(tam);
  flujo >> aux;
  // se puede hacer ya que tenemos definido un operador de asignación desde const char*
  cad = aux;
  return flujo;
}
