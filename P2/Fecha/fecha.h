
// Práctica 2 Programación orientada a objetos
// Rafael Valle Cabrera
// Clase Fecha

#ifndef _FECHA_H_
#define _FECHA_H_

// Lo incluimos para que el compilador entienda como tipos istream y ostream
#include <iostream>

using namespace std;

#define AnnoMinimo 1600
#define AnnoMaximo 2200

class Fecha{
public:
  // métodos dentro de la clase deben tener la lista throw, aunque esté vacía
  class Invalida{
  public:
    // Constructor
    // El constructor en sí es una definición completa
    // No es necesario reservar memoria, simplemente asignamos 
    // el parámetro del constructor al atributo de la clase
    // al ser constante, sólo se puede inicializar en la lista de inicialización
    Invalida(const char* mensaje): porque_(mensaje){}
    
    //Métodos observadores
    inline const char* por_que() const { return porque_;}
  private:
    const char* porque_;
  };
  
  // Constructor predeterminado y para 0, 1, 2 y 3 parámetros
  // además, se impide la conversión implícita de entero a Fecha
  explicit Fecha(int dia = 0, int mes = 0, int anno = 0) throw(Invalida);
  
  // Al no estar manejando punteros, nos serviremos del constructor de copia por defecto
  
  // Constructor de conversión que recibe como parámetro una cadena
  Fecha(const char* cadena) throw(Invalida);
  
  // Métodos observadores
  inline int dia() const { return dia_;}
  inline int mes() const { return mes_;}
  inline int anno() const { return anno_;}
  
  // Métodos modificadores
  
  // método de conversión a const char*
  const char* cadena() const throw();
  
  // Operadores
  
  // Operador de incremento sufijo
  // Cuando es operador es binario, se declara fuera con 2 operandos o 
  // si se trabaja con *this, se declara dentro con
  // operador unario -> no necesita referencia y no tiene que ser friend, 
  // como tiene que ser propio de la clase, por comodidad por *this
  Fecha& operator++() throw();
  
  // Operador de incremento con una fecha más un nº de días
  // este devuelve un nuevo objeto Fecha
  Fecha operator+(int) const throw();
  
  // Operador de incremento prefijo
  Fecha operator++(int) throw();
  
  // Operador de decremento sufijo, se devuelve *this, referencia al propio objeto
  Fecha& operator--() throw(); 
  
  // Operador de decremento de una fecha menos un nº de días
  Fecha operator-(int) const throw();
  
  // Operador de decremento prefijo
  Fecha operator--(int) throw();
  
  // Operador de incremento con asignación
  Fecha& operator+=(int) throw(Invalida);
  
  // Operador de decremento con asignación
  Fecha& operator-=(int) throw(Invalida);
  
  //(No hace falta, ya que no vamos a trabajar con punteros) Operador de asignación, no puede ser amigo
  //Fecha operator=(const Fecha&); //me bastaría en este caso con el predeterminado, hace lo mismo

private:
  int dia_,
      mes_,
      anno_;
      
  bool ValidarFecha(const Fecha&);
  Fecha& ajustar(Fecha&) const;
};

// Operadores relacionales

// no hace falta dentro, se declara fuera para permitir la conmutabilidad, es decir, 
// que sea posible que el objeto esté a la izqda o a la drcha del operador
bool operator==(const Fecha&, const Fecha&);

bool operator>(const Fecha&, const Fecha&);
bool operator<(const Fecha&, const Fecha&);
bool operator>=(const Fecha&, const Fecha&);
bool operator<=(const Fecha&, const Fecha&);
bool operator!=(const Fecha&, const Fecha&);

// Operadores de flujo

// Operador de inserción de flujo
ostream& operator<<(ostream&, const Fecha&);

// Operador de extracción de flujo
istream& operator>>(istream&, Fecha&);

#endif