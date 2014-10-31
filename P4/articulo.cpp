
#include <iostream>
#include "articulo.h"

using namespace std;

/*------------------------------------------ Clase Articulo ----------------------------------------------------*/

// Constructor 
Articulo::Articulo(const Autores& autores, const Cadena& ref, const Cadena& tit, const Fecha& f, const double& precio) 
	throw(Autores_vacios): referencia_(ref),titulo_(tit),fechapubl_(f),precio_(precio){
	// En caso de que el conjunto de autores esté vacío lanzamos una excepción Autores_vacios
	if(autores.empty()){
		throw Autores_vacios();
	}
	autores_ = autores;
}

// Operador de inserción de flujo
ostream& operator<<(ostream& flujo, const Articulo& art){
	flujo << "[" << art.referencia() << "] \"" << art.titulo() << "\"";
	for(Articulo::Autores::const_iterator i = art.autores().begin(); i != art.autores().end(); ++i){
		flujo << ", de " /*<< (*i)->nombre() << ", "*/ << (*i)->apellidos() << ". ";
	}
	flujo << art.f_publi().anno() << ". ";
	flujo << fixed << setprecision(2) << art.precio() << "€\n";
	art.imp_esp(flujo);
  	return flujo;
} 

// void Articulo::imp_esp(ostream& flujo) const{
// }

/*------------------------------------------ Clase ArticuloAlmacenable ---------------------------------------*/

// void ArticuloAlmacenable::imp_esp(ostream& flujo) const{
// }


/*------------------------------------------ Clase Libro ------------------------------------------------------*/

void Libro::imp_esp(ostream& flujo) const{
	flujo << "\t" << n_pag() << " págs., " << stock() << " unidades.";
}

/*------------------------------------------ Clase Cederron ---------------------------------------------------*/

void Cederron::imp_esp(ostream& flujo) const{
	flujo << "\t" << tam() << " MB, " << stock() << " unidades.";
}

/*------------------------------------------ Clase InformeDigital ---------------------------------------------*/

void InformeDigital::imp_esp(ostream& flujo) const{
	flujo << "\tA la venta hasta el " << f_expir() << ".";
}