
#include <iostream>
#include "articulo.h"

using namespace std;

// Operador de inserción de flujo
ostream& operator<<(ostream& flujo, const Articulo& art1){
  flujo << "[" << art1.referencia() << "] ";
  flujo << "\"" << art1.titulo() << "\", ";
  flujo << art1.f_publi().anno() << ". " << fixed << setprecision(2) << art1.precio() << "€";
  return flujo;
} 