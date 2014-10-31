
// Práctica 3 Programación orientada a objetos
// Rafael Valle Cabrera
// Clases Usuario y Clave

#ifndef _USUARIO_H_
#define _USUARIO_H_

#include <map>
#include <set>

#include <cstring>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

#include "cadena.h"
#include "tarjeta.h"
#include "articulo.h"

using namespace std;

// Declaraciones adelantadas de clases 
class Numero;
class Articulo;
class Tarjeta;

class Clave{
public:
  // Posibles valores válidos para lanzar la excepción Incorrecta
  enum Razon {CORTA, ERROR_CRYPT};
  
  // Clase excepción Incorrecta de la clase Clave
  class Incorrecta{
  public:
    // Constructores
    Incorrecta(const Razon& razon): razon_(razon){}
    
    // Métodos observadores
    inline Razon razon() const { return razon_;}
    
  private:
    Razon razon_;
  };
  
  // Constructor de conversión
  Clave(const char*) throw(Incorrecta);
  
  // Métodos observadores
  inline Cadena clave() const throw(){ return clave_;}
  bool verifica(const char* cadena) const throw(){ return (strcmp(clave_.c_str(), crypt(cadena, clave_.c_str())) == 0);}
private:
  Cadena clave_;
};

//------------------------------------- Clase Usuario --------------------------------------//

class Usuario{
public:
  // Clase de excepción de la clase Usuario
  // Para evitar crear usuarios con identificadores ya existentes
  class Id_duplicado{
  public:
    // Constructor
    Id_duplicado(Cadena repetida): repetida_(repetida){}
    // Método observador
    Cadena idd() const { return repetida_;}
  private:
    Cadena repetida_;
    
  };
  // *Tarjeta el compilador lo tomará como declarar un puntero faltando el tipo de éste
  // Tarjeta* declara un puntero de tipo Tarjeta
  typedef map<Numero, Tarjeta*> Tarjetas;
  typedef map<Articulo*, unsigned> Articulos;
  
  // Constructores
  // Forzamos a que sólo se puedan crear usuarios aportando los 5 parámetros requeridos
  // No necesitamos indicar la clase a la que pertenece la excepción lanzada, ya que estamos dentro de la misma clase
  Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& contrasena) throw(Id_duplicado);

  // Métodos observadores
  Cadena id() const throw() { return id_;}
  Cadena nombre() const throw() { return nombre_;}
  Cadena apellidos() const throw() { return apellidos_;}
  Cadena direccion() const throw() { return direccion_;}
  // Devuelve una copia del objeto original
  // Si devolvemos una referencia, devolveríamos el objeto original modificado si es que se modifica
  // No devolvemos por referencia para asegurarnos de que no se modifica lo que devuelve
  const Articulos& compra() const throw() { return articulos_;}
  // Devuelve el nº de artículos diferentes
  unsigned n_articulos() const throw() { return articulos_.size();}
  
  // Devuelve las tarjetas enlazadas ordenadas por número de tarjeta
  const Tarjetas& tarjetas() const throw(){ return tarjetas_;}
  
  // Métodos modificadores que se encargan de la asociación con la clase Tarjeta
  // Asociar una tarjeta a un usuario
  void es_titular_de(Tarjeta&) throw();
  // Desasociar tarjeta de usuario
  void no_es_titular_de(Tarjeta&) throw();
  
  // Asocia el nº de unidades de un articulo
  void compra(Articulo&, unsigned = 1) throw();
  
  // Operadores
  friend ostream& operator<<(ostream&, const Usuario&) throw();
  
  // Destructor
  ~Usuario() throw();
private:
  Cadena id_,
	 nombre_,
	 apellidos_,
	 direccion_;
  Clave contrasena_;
  Tarjetas tarjetas_;
  Articulos articulos_;
  static set<Cadena> ids_;
  
  // Declaramos el constructor de copia de Usuario y el operador de asignación
  //  en la parte privada para impedir que un objeto Usuario pueda crearse por copia de otro 
  // por tanto no podrá copiarse ni asignarse a otro (según el enunciado)
  Usuario(const Usuario&);
  Usuario operator=(const Usuario&);
};

ostream& mostrar_carro(ostream&, const Usuario&); 

#endif
