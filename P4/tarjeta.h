
// Práctica 3 Programación orientada a objetos
// Rafael Valle Cabrera
// Clases Tarjeta y Numero

#ifndef _TARJETA_H_
#define _TARJETA_H_

#include <algorithm>
#include <functional>

#include "fecha.h"
#include "cadena.h"
#include "usuario.h"

using namespace std;

// Declaraciones adelantadas de clases
class Usuario;

//-------------------------------------- Clase Numero ---------------------------------------//

class Numero{
public:
  // Posibles valores para lanzar una excepción de clase Incorrecto
  enum Razon {LONGITUD,DIGITOS,NO_VALIDO};
  
  // Clase de excepción a lanzar para un nº incorrecto
  class Incorrecto{
  public:
    // Constructor
    Incorrecto(const Razon razon): razon_(razon){}
    
    // Métodos observadores
    inline Razon razon() const{ return razon_;}
  private:
    Razon razon_;
  };
  
  // Constructores
  // Se declara explicit para obligar a usar un parámetro de tipo Cadena
  // para crear un objeto de clase Numero mediante el constructor de conversión
  explicit Numero(const Cadena&) throw(Incorrecto);
  
  // Operadores
  
  // Operador de conversión a const char*
  operator const char*() const throw();
  
private:
  Cadena num_;
};

  // Operador menor que
  bool operator<(const Numero&, const Numero&) throw();
  
//--------------------------------- Clase Tarjeta ------------------------------------------//
  
  
class Tarjeta{
public:
  // clase de la excepción Caducada
  class Caducada{
  public:
    // Constructores
    Caducada(const Fecha& caducada): caducada_(caducada){}
    
    // Métodos observadores
    Fecha cuando() const { return caducada_;}
  private:
    Fecha caducada_;
  };
  
  // Constructores
  Tarjeta(Numero, Usuario&, Fecha) throw(Caducada);
  
  // Métodos observadores
  Numero numero() const { return numtarjeta_;}
  // si devuelvo *titular_, estaría devolviendo lo que apunta el puntero, el objeto Usuario
  const Usuario* titular() const { return titular_;}
  Fecha caducidad() const { return caducidad_;}
  Cadena titular_facial() const { return titular_facial_;}
  
  // Métodos modificadores
  void anula_titular() throw(){ titular_ = NULL;}
  
  // Destructor
  ~Tarjeta() throw();
private:
  Numero numtarjeta_;
  const Usuario* titular_;
  Fecha caducidad_;
  Cadena titular_facial_;
  
  // Declaramos el constructor de copia de Tarjeta y el operador de asignación en la parte privada
  // para impedir que pueda crearse una tarjeta como copia de otra o
  // asignándose una tarjeta a otra, ambos casos no se permiten
  Tarjeta(Tarjeta&) throw();
  Tarjeta& operator=(const Tarjeta&);
};

// Operador de inserción de flujo
ostream& operator<<(ostream&, const Tarjeta&);

// Operador menor que
bool operator<(const Tarjeta&, const Tarjeta&);

#endif