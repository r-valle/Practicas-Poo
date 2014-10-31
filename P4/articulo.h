
// Práctica 4 Programación orientada a objetos
// Rafael Valle Cabrera
// Clase Articulo

#ifndef _ARTICULO_H_
#define _ARTICULO_H_

#include "cadena.h"
#include "fecha.h"
#include "autor.h"

#include <set>
// Lo incluimos para luego poder fijar la precisión de 2 decimales del precio
#include <iomanip>

using namespace std;

/*------------------------------------------ Clase Articulo ----------------------------------------------------*/

class Articulo{
public:
  // Clase de excepción lanzada en caso de no encontrar al menos un autor para un artículo
  class Autores_vacios{};

  // Tipo que recoge los autores de un artículo
  typedef set<Autor*> Autores;

  // Constructor
  Articulo(const Autores&, const Cadena&, const Cadena&, const Fecha&, const double&) throw(Autores_vacios);
  
  // Métodos observadores
  Cadena referencia() const { return referencia_;}
  Cadena titulo() const { return titulo_;}
  Fecha f_publi() const { return fechapubl_;}
  double precio() const { return precio_;}
  const Autores& autores() const { return autores_;}
  
  // Métodos modificadores
  // Los métodos modificadores no pueden tener 2º const porque aunque devuelvan una referencia
  // al objeto de la clase, haciendo previamente una copia de éste, no podrían modificar el valor de 
  // dicha copia para luego devolverlo
  double& precio(){ return precio_;}

  // con virtual, no podemos crear objetos de esta clase directamente

  // Método para imprimir los atributos específicos de cada tipo de artículo
  // Declaramos este método como virtual para permitir que el compilador pueda seleccionar 
  // la versión adecuada del mismo en función de la clase derivada con la que esté trabajando
  virtual void imp_esp(ostream&) const=0;

  // Declaramos el destructor como virtual para que el compilador
  // pueda llamarlo en tiempo de ejecución
  virtual ~Articulo(){}
protected:
  Cadena referencia_;
  Cadena titulo_;
  Fecha fechapubl_;
  double precio_;
  Autores autores_;
};
    
// Operador de inserción de flujo
ostream& operator<<(ostream&, const Articulo&); 

/*------------------------------------------ Clase ArticuloAlmacenable ----------------------------------------*/

// Clase derivada de la clase Articulo
class ArticuloAlmacenable: public Articulo{
public:
  // Constructor
  ArticuloAlmacenable(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& f, double precio, unsigned stock): 
    Articulo(autores,ref,tit,f,precio), stock_(stock){}

  // Declaramos este método como virtual para permitir que el compilador pueda seleccionar 
  // la versión adecuada del mismo en función de la clase derivada con la que esté trabajando
  //void imp_esp(ostream&) const;
  
  // Métodos observadores
  unsigned stock() const { return stock_;}

  // Métodos modificadores
  unsigned& stock() { return stock_;}

  // Destructor
  //virtual ~ArticuloAlmacenable(){}
protected:
  unsigned stock_;
};

/*------------------------------------------ Clase Libro ------------------------------------------------------*/

// Clase derivada de la clase ArticuloAlmacenable
class Libro: public ArticuloAlmacenable{
public:
  // Constructor
  Libro(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& f, double precio, const unsigned& numpags, const unsigned& stock): 
    ArticuloAlmacenable(autores,ref,tit,f,precio,stock), numpags_(numpags){}

  // Sobrecarga del método de la clase base para imprimir
  // los atributos especificos de cada tipo de Articulo, en este caso, Libro
  void imp_esp(ostream&) const;
  // Métodos observadores
  unsigned n_pag() const { return numpags_;}
private:
  unsigned numpags_;

};

/*------------------------------------------ Clase Cederron ---------------------------------------------------*/

// Clase derivada de la clase ArticuloAlmacenable
class Cederron: public ArticuloAlmacenable{
public:
  // Constructor
  Cederron(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& f, double precio, const size_t& tamano, const unsigned& stock): 
    ArticuloAlmacenable(autores,ref,tit,f,precio,stock), tamano_(tamano){}

  // Sobrecarga del método de la clase base para imprimir
  // los atributos especificos de cada tipo de Articulo, en este caso, Cederron
  void imp_esp(ostream&) const;
  // Métodos observadores
  size_t tam() const { return tamano_;}
private:
  const size_t tamano_;
};

/*------------------------------------------ Clase InformeDigital ---------------------------------------------*/

// Clase derivada de la clase Articulo
class InformeDigital: public Articulo{
public:
  // Constructor
  InformeDigital(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& fech, double precio, const Fecha& fexp): 
    Articulo(autores,ref,tit,fech,precio), fexp_(fexp){}

  // Sobrecarga del método de la clase base para imprimir
  // los atributos especificos de cada tipo de Articulo, en este caso, InformeDigital
  void imp_esp(ostream&) const;
  // Métodos observadores
  Fecha f_expir() const { return fexp_;}
private:
  Fecha fexp_; 
};

#endif