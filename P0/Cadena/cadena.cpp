
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

// Cuando creamos clase con reserva de memoria, necesitamos el destructor

Cadena::Cadena(const char* cadena) throw(){
  tamano_ = strlen(cadena);
  cadena_ = new char[tamano_+1];
  strcpy(cadena_,cadena);
}

const char Cadena::at(unsigned i) const throw(std::out_of_range){
  if(i < 0 or i > length()-1 or cadena_[i] == '\0'){
    throw out_of_range("Fuera de rango");
  }
  return cadena_[i];
}

char& Cadena::at(unsigned i) throw(std::out_of_range){
  if(i < 0 or i > length()-1 or cadena_[i] == '\0'){
    throw out_of_range("Fuera de rango");
  }
  return cadena_[i];
}

const Cadena Cadena::subcadena(int i, int tamano) const throw(std::out_of_range){
  if(i < 0 or tamano < 0 or i > (int)length() or (tamano+i) > (int)length()){
    throw out_of_range("indice fuera de rango");
  } else{
      char* cadena = new char[tamano+1];
      for(int j = 0; j < tamano; j++){
	cadena[j] += cadena_[j+i];
      }
      cadena[tamano] = '\0';
      Cadena cad(cadena);
      delete[] cadena;
      return cad;
  }
}

// Operadores

// Operador de asignación
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

// Operador índice []
const char Cadena::operator[](unsigned i) const throw(){
  return cadena_[i];
}

char& Cadena::operator[](unsigned i) throw(){
  return cadena_[i];
}

// Operador de conversión const char*
Cadena::operator const char*() const throw(){
  return cadena_;
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
  if(cad1.length() == cad2.length() and strcmp(cad1.cadena(),cad2.cadena()) == 0){
      return true;
    } else{
      return false;
    }
}

bool operator!=(const Cadena& cad1, const Cadena& cad2){
  if(cad1 == cad2){
    return false;
  } else{
    return true;
  }
}

bool operator>(const Cadena& cad1, const Cadena& cad2){
  // La función strcmp devuelve un valor mayor que 0 en caso de que encuentre 
  // un carácter en cad1 cuyo valor es mayor que su correspondiente en cad2
  if(cad1.length() > cad2.length() or strcmp(cad1.cadena(),cad2.cadena()) > 0){
    return true;
  } else{
    return false;
  }
}

bool operator<(const Cadena& cad1, const Cadena& cad2){
  // La función strcmp devuelve un valor mayor que 0 en caso de que encuentre un carácter
  // en cad2 cuyo valor es mayor que su correspondiente en cad1, por lo que cad1 sería menor
  if(cad1.length() < cad2.length() or strcmp(cad2.cadena(),cad1.cadena()) > 0){
    return true;
  } else{
    return false;
  }
}

bool operator>=(const Cadena& cad1, const Cadena& cad2){
  if(cad1 > cad2 or cad1 == cad2){
    return true;
  } else{
    return false;
  }
}

bool operator<=(const Cadena& cad1, const Cadena& cad2){
  if(cad1 < cad2 or cad1 == cad2){
    return true;
  } else{
    return false;
  }
}