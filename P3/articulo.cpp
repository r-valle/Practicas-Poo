
#include <iostream>
#include "articulo.h"

using namespace std;

// Operador de inserción de flujo
ostream& operator<<(ostream& flujo, const Articulo& art1){
  flujo << "[" << art1.referencia() << "] ";
  flujo << "\"" << art1.titulo() << "\", ";
  //cout << "annnnno: " << art1.f_publi().anno() << endl;
  flujo << art1.f_publi().anno() << ". ";
  flujo << fixed << setprecision(2) << art1.precio() << "€";
  return flujo;
} 

// código fichero prueba
// "[1234XYZ] \"Prueba\", 2000. 20,40€"

