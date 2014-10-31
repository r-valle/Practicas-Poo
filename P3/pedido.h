
// Práctica 3 Programación orientada a objetos
// Rafael Valle Cabrera
// Clase Pedido

#ifndef _PEDIDO_H_
#define _PEDIDO_H_

#include "tarjeta.h"
#include "usuario.h"

using namespace std;

// Declaraciones adelantadas
class Usuario_Pedido;
class Pedido_Articulo;

class Pedido{
public:
  // Clase de excepción para evitar crear un pedido vacío
  class Vacio{
  public:
    // Constructor
    Vacio(Usuario* user): usuario_(user){}
    
    // Método observador
    Usuario& usuario() const{ return *usuario_;}
  private:
    Usuario* usuario_;
  };
  
  // Clase de excepción para impedir que no sea otro 
  // sino el usuario titular de la tarjeta quien haga el pedido
  class Impostor{
  public:
    // Constructor
    Impostor(Usuario* user): usuario_(user){}
    
    // Método observador
    Usuario& usuario() const{ return *usuario_;}
  private:
    Usuario* usuario_;
  };
  
  // Clase de excepción para anular el pedido
  // en caso de superar existencias de al menos un artículo del pedido
  class SinStock{
  public:
    // Constructor
    SinStock(Articulo* art): articulo_(art){}
    
    // Método observador
    Articulo& articulo() const{ return *articulo_;}
  private:
    Articulo* articulo_;
  };
  // Constructores
  Pedido(Usuario_Pedido&, Pedido_Articulo&, Usuario&, const Tarjeta&, Fecha fech = Fecha());
  
  // Métodos observadores
  int numero() const{ return num_;}
  const Tarjeta* tarjeta() const{ return tarjeta_;}
  Fecha fecha() const{ return fecha_;}
  double total() const{ return total_;}
  static int n_total_pedidos(){ return N_pedidos;}
private:
  int num_;
  const Tarjeta *tarjeta_;
  Fecha fecha_;
  double total_;
  static int N_pedidos;
};

// Operador de inserción de flujo
ostream& operator<<(ostream&, const Pedido&);

#endif