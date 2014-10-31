
#include "pedido-articulo.h"

using namespace std;

/*-------------------------- Clase LineaPedido -----------------------------------------*/

// Constructor
LineaPedido::LineaPedido(double preciov, int cant): precioventa_(preciov), cantvendida_(cant){}

// Operador de inserción de flujo
ostream& operator<<(ostream& flujo, const LineaPedido& linpedido){
  flujo << fixed << setprecision(2) << linpedido.precio_venta() << "€\t" << linpedido.cantidad();
  return flujo;
}

/*-------------------------- Clase Pedido_Articulo -------------------------------------*/

void Pedido_Articulo::pedir(Pedido& ped, Articulo& art, double preciov, unsigned cant){
  parts[&ped].insert(make_pair(&art, LineaPedido(preciov,cant)));
  artsp[&art].insert(make_pair(&ped, LineaPedido(preciov,cant)));
}

void Pedido_Articulo::pedir(Articulo& art, Pedido& ped, double preciov, unsigned cant){
  pedir(ped,art,preciov,cant);
}

ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& flujo){
  double precioped = 0;
  for(PedidosArticulos::const_iterator i = parts.begin(); i != parts.end(); ++i){
    flujo << "Nº Pedido:    " << i->first->numero() << "\n";
    flujo << "Cliente:      " << i->first->tarjeta()->titular()->nombre() << "\n";
    flujo << "Fecha Pedido: " << i->first->fecha() << "\t" << i->second;
    flujo << "\n";

    precioped += i->first->total();
  }
  flujo << fixed;
  flujo << "Total Ventas:   " << setprecision(2) << precioped << "€";
  return flujo;
}

ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& flujo){
  for(ArticulosPedidos::const_iterator i = artsp.begin(); i != artsp.end(); ++i){
    flujo << "Ventas de articulo: " << "[" << i->first->referencia() << "] ";
    flujo << "\"" << i->first->titulo() << "\" \n" << i->second << endl;
  }
  return flujo;
}

/*

void Pedido_Articulo::mostrarVentasArticulos(ostream& os){
  for(ArticuloPedido::const_iterator i = ap.begin(); i != ap.end(); ++i){
     os << "Ventas de " << "[" << i->first->referencia() << "] ";
     os << "\"" << i->first->titulo() << "\" \n" << i->second << endl;
  }
}

*/

// Sobrecarga del operador de inserción de flujo que mostrará detalles del pedido, importe total 
// y nº de ejemplares del pedido
ostream& operator<<(ostream& flujo, const Pedido_Articulo::ItemsPedido& itemsp){
  double totalart = 0;

  flujo << "\n===================== Detalles del pedido ===============================" << endl;
  flujo << "\t Articulo \t \t Cantidad \t \t PVP \n";
  flujo << "========================================================================="	<< endl;
  for(Pedido_Articulo::ItemsPedido::const_iterator i = itemsp.begin(); i != itemsp.end(); ++i){
    flujo << "[" << i->first->referencia() << "] " << "\"" << i->first->titulo() << "\" \t"; 
    flujo << i->second.cantidad() << "\t \t" << fixed << setprecision(2) << i->second.precio_venta() << "€\n";

    totalart += i->second.precio_venta() * i->second.cantidad();
  }
  flujo << "========================================================================="	<< endl;
  flujo << " Total: \t \t" << fixed << setprecision(2) << totalart << "€" << endl;
  return flujo;
}

// Sobrecarga del operador de inserción de flujo que mostrará importe, cantidad y fecha de cada venta 
// además del total de todas las ventas del artículo
ostream& operator<<(ostream& flujo, const Pedido_Articulo::Pedidos& peds){
  double preciov = 0;
  double totalv = 0;

  flujo << "\n===================== Detalles de venta =================================" << endl;
  flujo << " Nº Pedido \t \t Fecha \t \t \t Cantidad \t PVP \n";
  flujo << "=========================================================================" << endl;
  for(Pedido_Articulo::Pedidos::const_iterator i = peds.begin(); i != peds.end(); ++i){
    flujo << "[" << i->first->numero() << "]\t \t " << i->first->fecha() << " \t ";
    flujo << i->second.cantidad() << "\t \t" << fixed << setprecision(2) << i->second.precio_venta() << "€\n";

    preciov += i->second.precio_venta() * i->second.cantidad();
    totalv += preciov;
  }
  flujo << "=========================================================================" << endl;
  flujo << " Total: \t \t" << fixed << setprecision(2) << preciov << "€\t" << totalv << "€" << endl;
  return flujo;
}
