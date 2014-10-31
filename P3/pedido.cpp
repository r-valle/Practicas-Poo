
#include <iostream>
#include "pedido.h"
#include "pedido-articulo.h"
#include "usuario-pedido.h"

using namespace std;

int Pedido::N_pedidos = 0;

// Constructor
Pedido::Pedido(Usuario_Pedido& userped, Pedido_Articulo& pedart, Usuario& user, const Tarjeta& tarj, const Fecha fech)
              :fecha_(fech), total_(0.0){
  // En caso de que el carrito de compra esté vacío, lanzamos una excepción de clase Vacio
  if(user.compra().begin() == user.compra().end()){
    throw Vacio(&user);
  }

  // Si la fecha de caducidad es anterior a la del pedido, damos por caducada dicha tarjeta
  // lanzando excepción de clase Caducada de la clase Tarjeta
  if(tarj.caducidad() < fecha_){
    throw Tarjeta::Caducada(fech);
  }

  // Comprobamos si user es el titular de la tarjeta asociada al pedido
  // En caso de no serlo, lanzamos excepción de clase Impostor
  if(user.nombre() != tarj.titular()->nombre()){
    throw Impostor(&user);
  }
  tarjeta_ = &tarj;

  for(Usuario::Articulos::const_iterator i = user.compra().begin(); i != user.compra().end(); ++i){
    // Si el nº de unidades a comprar supera el stock, lanzamos excepción de clase SinStock
    if(i->second > i->first->stock()){
      Articulo* art = i->first;
      // "Vaciamos" el carrito de compra
      for(Usuario::Articulos::const_iterator i = user.compra().begin(); i != user.compra().end(); ++i){
        user.compra(*(i->first),0);
      }
      throw SinStock(art);
    }
  }

  N_pedidos++;
  num_ = N_pedidos;
  // Asociamos un pedido con un usuario
  userped.asocia(*this,user);

  for(Usuario::Articulos::const_iterator i = user.compra().begin(); i != user.compra().end(); ++i){
    // Obtenemos el importe total de la compra
    total_ += i->first->precio() * (i->second);

    // "Creamos" el pedido del artículo creando los enlaces correspondientes,
    // dados el pedido, el artículo, su precio y cantidad
    pedart.pedir(*this,*(i->first),i->first->precio(),i->second);
    
    // Actualizamos el stock del articulo
    i->first->stock() = i->first->stock() - i->second;
    // (*i).first y *i.first equivalen a i->first

    // Quitamos el artículo del carro de compra
    user.compra(*(i->first),0);
  }
}

// Operador de inserción de flujo
ostream& operator<<(ostream& flujo, const Pedido& ped){
  flujo << "Núm. pedido: " << ped.numero() << endl;
  flujo << "Fecha:       " << ped.fecha() << endl;
  flujo << "Pagado con:  " << ped.tarjeta()->numero() << endl;
  flujo << "Importe:     " << fixed << setprecision(2) << ped.total() << "€" << endl;
  return flujo;
}