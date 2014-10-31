
#include "usuario.h"

using namespace std;

// Declaramos un set de identificadores de usuarios 
// para evitar que haya identificadores duplicados
set<Cadena> Usuario::ids_;

//--------------------------------------- Clase Clave ---------------------------------------//

Clave::Clave(const char* cad) throw(Incorrecta){
  // longitud mínima de la cadena que contendrá la clave sin cifrar
  unsigned longitud = 5;
  
  // Lanzamos excepción en caso de que la clave sea demasiado corta
  if(strlen(cad) < longitud){
    throw Incorrecta(Clave::CORTA);
  }
  // Coge la hora actual del sistema para generar una semilla
  srand(time(0));
  
  const char *caracteres_validos = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  char salt[] = { caracteres_validos[rand() % 63], caracteres_validos[rand() % 63]};
  char* clave = new char[strlen(cad)+1];
  // Encriptamos
  clave = crypt(cad,salt);
  // Lanzamos excepción en caso de que la clave no se haya cifrado correctamente
  if(clave == 0){
    throw Incorrecta(Clave::ERROR_CRYPT);
  }
  clave_ = clave;
}

//------------------------------------- Clase Usuario ---------------------------------------//

// Constructor
Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& contrasena) throw(Id_duplicado)
		:id_(id), nombre_(nombre), apellidos_(apellidos),direccion_(direccion), contrasena_(contrasena){
  // Insertamos id en el set
  // Si ese id ya está, 2º campo-> falso; si no 2º campo->verdadero
  // En el caso de que no se inserte, iterador no apuntará a nada
  
  if(! ids_.insert(id).second)
    throw Usuario::Id_duplicado(id);


}

// Destructor
Usuario::~Usuario() throw(){
  // Desligamos al usuario de las tarjetas
  // iteradores no comparaciones <,>
  for(map<Numero, Tarjeta*>::iterator i = tarjetas_.begin(); i != tarjetas_.end(); ++i){
    i->second->anula_titular();
  }
  // Borramos su id
  ids_.erase(id_);
}

void Usuario::es_titular_de(Tarjeta& tarj) throw(){
  tarjetas_[tarj.numero()] = &tarj;
}

void Usuario::no_es_titular_de(Tarjeta& tarj) throw(){
  tarj.anula_titular();
  tarjetas_.erase(tarj.numero());
}

// método modificador
void Usuario::compra(Articulo& art1, unsigned udes) throw(){
  if(udes == 0){
    articulos_.erase(&art1);
  } else{
    // asignamos la nueva cantidad de artículos
      articulos_[&art1] = udes;
  }
}

ostream& operator<<(ostream& flujo, const Usuario& user) throw(){
  flujo << user.id() << "[" << user.contrasena_.clave() << "] " << user.nombre() << " " << user.apellidos() << endl;
  flujo << user.direccion() << endl;
  flujo << "Tarjetas:" << endl;
  for(map<Numero, Tarjeta*>::const_iterator i = user.tarjetas().begin(); i != user.tarjetas().end(); ++i){
    flujo << *(i->second) << endl;
  }
  return flujo;
} 

ostream& mostrar_carro(ostream& flujo, const Usuario& user){
  flujo << "Carrito de compra de " << user.id() << " [Artículos: " << user.n_articulos() << "]" << endl;
  flujo << " Cant. Artículo" << endl;
  flujo << setfill('=') << setw(62) << "" << endl;
  for(map<Articulo*, unsigned>::const_iterator i = user.compra().begin(); i != user.compra().end(); ++i){
    flujo << setfill(' ') << setw(4) << i->second << "[" << i->first->referencia() << "] \"" << i->first->titulo() << "\", " 
          << i->first->f_publi().anno() << ". " << fixed << setprecision(2) << i->first->precio() << "€" << endl;
 }
  return flujo;
}

/*

    os << "[111] \"The Standard Template Library\", " << articulo1.f_publi().anno() << ". 42,10€";

*/
