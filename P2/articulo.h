
// Práctica 2 Programación orientada a objetos
// Rafael Valle Cabrera
// Clase Articulo

#ifndef _ARTICULO_H_
#define _ARTICULO_H_

#include "cadena.h"
#include "fecha.h"
// Lo incluimos para luego poder fijar la precisión de 2 decimales del precio
#include <iomanip>

using namespace std;

class Articulo{
public:
  // Constructor
  Articulo(Cadena referencia, Cadena titulo, Fecha fechapubl, double precio, unsigned stock):
		referencia_(referencia),titulo_(titulo),fechapubl_(fechapubl),precio_(precio),stock_(stock){}
  
  // Métodos observadores
  Cadena referencia() const { return referencia_;}
  Cadena titulo() const { return titulo_;}
  Fecha f_publi() const { return fechapubl_;}
  double precio() const { return precio_;}
  unsigned stock() const { return stock_;}
  
  // Métodos modificadores
  // Los métodos modificadores no pueden tener 2º const porque aunque devuelvan una referencia
  // al objeto de la clase, haciendo previamente una copia de éste, no podrían modificar el valor de 
  // dicha copia para luego devolverlo
  double& precio(){ return precio_;}
  unsigned& stock(){ return stock_;}
  
private:
  Cadena referencia_;
  Cadena titulo_;
  Fecha fechapubl_;
  double precio_;
  unsigned stock_;
};
    
  // Operador de inserción de flujo
  ostream& operator<<(ostream&, const Articulo&); 

#endif