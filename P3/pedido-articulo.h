
// Práctica 3 Programación orientada a objetos
// Rafael Valle Cabrera
// Clase de asociación Pedido_Articulo

#ifndef _PEDIDO_ARTICULO_H_
#define _PEDIDO_ARTICULO_H_

#include <map>
#include <set>
#include <iostream>
#include <iterator>

#include "fecha.h"
#include "pedido.h"
#include "articulo.h"

using namespace std;

// Declaración objeto función OrdenaArticulos
struct OrdenaArticulos: binary_function<Articulo*,Articulo*,bool>{
  bool operator()(const Articulo* art1, const Articulo* art2) const{ return art1->referencia() < art2->referencia();}
};

// Declaración objeto función OrdenaPedidos
struct OrdenaPedidos: binary_function<Pedido*,Pedido*,bool>{
  bool operator()(const Pedido* ped1, const Pedido* ped2) const{ return ped1->numero() < ped2->numero();}
};

/*--------------------------- Clase LineaPedido ------------------------------------------*/

class LineaPedido{
public:
  // Constructores
  // Se impide la conversión implícita de un precio a LineaPedido
  explicit LineaPedido(double, int cantidad = 1);
  
  // Métodos observadores
  double precio_venta() const{ return precioventa_;}
  int cantidad() const{ return cantvendida_;}
private:
  double precioventa_;
  int cantvendida_;
};

// Operador de inserción de flujo
ostream& operator<<(ostream&, const LineaPedido&);

/*--------------------------- Clase Pedido_Articulo ---------------------------------------*/

class Pedido_Articulo{
public:
  typedef map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
  typedef map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
  typedef map<Pedido*, ItemsPedido, OrdenaPedidos> PedidosArticulos;
  typedef map<Articulo*, Pedidos, OrdenaArticulos> ArticulosPedidos;
  
  // Métodos observadores
  
  // Devuelve la colección de artículos de un pedido con precio de venta y cantidad
  // find devuelve la 1ª (y única en casos de set y map) ocurrencia del elemento buscado en el contenedor
  // En caso de no encontrarlo devuelve la siguiente posición a la última del contenedor
  const ItemsPedido& detalle(Pedido& ped) const{ return parts.find(&ped)->second;}
  
  // Devuelve la colección de pedidos de un artículo con precio de venta y cantidad
  const Pedidos& ventas(Articulo& art) const{ return artsp.find(&art)->second;}
  
  // Métodos modificadores
  void pedir(Pedido&, Articulo&, double, unsigned cant = 1);
  void pedir(Articulo&, Pedido&, double, unsigned cant = 1);
  

  // Métodos de inserción de flujo para mostrar detalles de pedidos y ventas
  ostream& mostrarDetallePedidos(ostream&);
  ostream& mostrarVentasArticulos(ostream&);

private:
  PedidosArticulos parts;
  ArticulosPedidos artsp;
  
};

// Sobrecargas del operador de inserción de flujo
ostream& operator<<(ostream&, const Pedido_Articulo::ItemsPedido&);
ostream& operator<<(ostream&, const Pedido_Articulo::Pedidos&);

#endif