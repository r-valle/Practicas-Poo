
#include "tarjeta.h"
#include "luhn.cpp"

using namespace std;

// objeto función EsBlanco
struct EsBlanco: unary_function<char,bool>{
  bool operator()(const char& c) const{ return isspace(c);}
};
  
// objeto función EsDigito  
struct EsDigito: unary_function<char,bool>{
  bool operator()(const char& c) const{ return isdigit(c);}
};

//-------------------------------------- Clase Numero --------------------------------------//

// Constructor
Numero::Numero(const Cadena& num) throw(Incorrecto){
  char * aux = new char[num.longitud()+1];
  strcpy(aux,num.c_str());
  
  // Reimplementamos la eliminación de blancos
  char* numbegin = aux;
  char* numend = aux + num.longitud();
  // Dado un rango de valores, remove_if devuelve un iterador 
  // (actualizando la nueva posición de end) sobre dicho conjunto de valores
  // que resulta de prescindir de aquellos valores para los que el predicado EsBlanco se cumple
  numend = remove_if(numbegin,numend,EsBlanco());
  
  // Metemos el carácter terminador
  *numend = '\0';
  
  // Dado un rango de valores, find_if devuelve un iterador al primer elemento 
  // para el cual se cumple el predicado. Si no encuentra ningún elemento que lo cumpla devuelve end
  // Cuidado!!! C++ ISO prohibe la comparación entre un puntero y un entero
  if(find_if(numbegin,numend,not1(EsDigito())) != numend){
    throw Incorrecto(Numero::DIGITOS);
  }
  
  // Comprobamos que cad sea un nº de tarjeta de crédito de longitud válida
  if(strlen(aux) > 19 or strlen(aux) < 13){
    throw Incorrecto(Numero::LONGITUD);
  }
  
  // Comprobamos que cad sea válido según algoritmo de Luhn
  if(!luhn(aux,strlen(aux))){
    throw Incorrecto(Numero::NO_VALIDO);
  }
  
  num_ = aux;
  delete[] aux;
}

// Operadores

// Operador de conversión a const char*
Numero::operator const char*() const throw(){
  // Nos servimos del método de conversión de Cadena
  return num_.c_str();
}

// Operador menor que
bool operator<(const Numero& num1, const Numero& num2) throw(){
  return (strcmp(num1,num2) < 0);
  //return atol(num1) < atol(num2);
}

//-------------------------------------- Clase Tarjeta --------------------------------------//

Tarjeta::Tarjeta(Numero num, Usuario& titular, Fecha fech) throw(Caducada): 
	numtarjeta_(num), titular_(&titular), caducidad_(fech){
  // Comparamos la fecha de caducidad de la tarjeta con la fecha del sistema
  // llamando al constructor por defecto de Fecha
  // si la fecha de caducidad es inferior a la actual, lanzamos una excepción Caducada
  if(fech < Fecha()){
    throw Caducada(fech);
  }
  // Nos servimos de 3 objetos Cadena auxiliares para construir titular_facial_
  Cadena cad1(titular.nombre().c_str()), cad2(1,' '), cad3(titular.apellidos().c_str());
  // Luego los concatenamos mediante operador suma de Cadena
  titular_facial_ = cad1 + cad2 + cad3;
  
  titular.es_titular_de(*this);
}

// Operador de inserción de flujo
ostream& operator<<(ostream& os, const Tarjeta& tarj){
  os << tarj.numero() << endl;
  os << tarj.titular_facial() << endl;
  os << setfill('0');
  os << "Caduca: " << setw(2) << tarj.caducidad().mes() << "/" << tarj.caducidad().anno() % 100;
  return os;
}

// Operador menor que

bool operator<(const Tarjeta& tarj1, const Tarjeta& tarj2){
  return tarj1.numero() < tarj2.numero();
}

// Destructor
Tarjeta::~Tarjeta() throw(){
  Usuario* user = const_cast<Usuario*>(titular_);
  if(user != 0){
    user->no_es_titular_de(*this);
  }
}