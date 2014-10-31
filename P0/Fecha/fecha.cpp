
#include <iostream>
#include <cstdio>
#include <ctime>
#include "fecha.h"

using namespace std;

// Constructores clase Fecha

Fecha::Fecha(int dia, int mes, int anno) throw(Invalida): dia_(dia), mes_(mes), anno_(anno){  
  int dia_sis, mes_sis, anno_sis;
  
  // Obtenemos la fecha con tipo time_t
  time_t hoy = time(NULL);
  
  // Convertimos a estructura tm
  struct tm* info = localtime(&hoy);
  
  dia_sis = info->tm_mday;
  mes_sis = info->tm_mon+1;
  anno_sis = info->tm_year+1900;
  
  // Inicializamos según la fecha del sistema los parámetros a 0
  if(dia == 0)
    dia_ = dia_sis;
  
  if(mes == 0)
    mes_ = mes_sis;
    
  if(anno == 0)
    anno_ = anno_sis;
  
  if(!ValidarFecha(*this))
    throw Invalida("Fecha invalida");
}

Fecha::Fecha(const char* cadena) throw(Invalida){
  if(sscanf(cadena,"%d/%d/%d",&dia_,&mes_,&anno_) != 3)
    throw Invalida("Error de formato");
  if(!ValidarFecha(*this))
    throw Invalida("Fecha invalida");
}

bool Fecha::ValidarFecha(const Fecha& f){
  tm timeinfo = {0,0,0,dia_,mes_-1,anno_-1900,0,0,-1};
  mktime(&timeinfo);
  if(f.dia() >= 1 and f.dia() <= 31 and f.mes() >= 1 and f.mes() <= 12 and f.anno() >= AnnoMinimo and f.anno() <= AnnoMaximo){
	if(f.dia() == timeinfo.tm_mday and f.mes() == timeinfo.tm_mon+1 and f.anno() == timeinfo.tm_year+1900){
	     return true;
	}
  }
  return false;
}

// ajustamos los nuevos valores de la fecha
Fecha& Fecha::ajustar(Fecha& f1) const{
  tm timeinfo = {0,0,0,f1.dia_,f1.mes_-1,f1.anno_-1900,0,0,-1};
  mktime(&timeinfo);
  f1.dia_ = timeinfo.tm_mday;
  f1.mes_ = timeinfo.tm_mon+1;
  f1.anno_ = timeinfo.tm_year+1900;
  return f1;
}

// Operadores clase Fecha
// cuando usamos estos operadores, se presuponen bien construidos, 
// por lo que no hace falta hacer comprobaciones tipo año bisiesto

// operador incremento prefijo (pre-incremento)
Fecha& Fecha::operator++() throw(){
  dia_++;
  ajustar(*this);
  return (*this);
}

// operador suma
Fecha Fecha::operator+(int dias) const throw(){
  Fecha aux(*this);
  aux.dia_ += dias;
  ajustar(aux);
  return aux;
}

// si se crea un nuevo objeto, no tiene sentido devolver una referencia a él, 
// sino devolver el mismo objeto

Fecha Fecha::operator++(int xxx) throw(){
  Fecha aux(*this);
  dia_++;
  ajustar(*this);
  return aux;
}

// operador decremento prefijo
Fecha& Fecha::operator--() throw(){
  dia_--;
  ajustar(*this);
  return (*this);
} 

// operador decremento sufijo
Fecha Fecha::operator--(int xxx) throw(){
  Fecha aux(*this);
  dia_--;
  ajustar(*this);
  return aux;
}

// Aunque sea definido como constante, el operador sigue pudiendo llamar a constructores
// y modificar atributos clase

// operador decremento fecha menos nº de días, el cual llama al operador decremento sufijo
// ya declarado

Fecha Fecha::operator-(int dias) const throw(){
  Fecha aux(*this);
  aux.dia_-=dias;
  ajustar(aux);
  return aux;
}

// trabajamos sobre el mismo objeto, con *this, devolviendo una referencia a él

Fecha& Fecha::operator+=(int dias) throw(Invalida){
  dia_+=dias;
  ajustar(*this);
  if(!ValidarFecha(*this))
    throw Invalida("fecha fuera de rango");
  return (*this);
}

Fecha& Fecha::operator-=(int dias) throw(Invalida){
  dia_-=dias;
  ajustar(*this);
  if(!ValidarFecha(*this))
    throw Invalida("fecha fuera de rango");
  return (*this);
}

// estos métodos no necesitan especificar lista throw porque están fuera de la clase

bool operator<(const Fecha& f1, const Fecha& f2){
  if((f1.anno() < f2.anno()) or
     (f1.anno() == f2.anno() and f1.mes() < f2.mes()) or
     (f1.anno() == f2.anno() and f1.mes() == f2.mes() and f1.dia() < f2.dia()) ){
       return true;
    } else{
	return false;
    }
}

bool operator<=(const Fecha& f1, const Fecha& f2){
  return (f1 < f2) or (f1 == f2); 
}

bool operator>(const Fecha& f1, const Fecha& f2) {
  if (not((f1 < f2) or (f1 == f2)) ){
    return true;
  } else{
    return false;
  }
}

bool operator>=(const Fecha& f1, const Fecha& f2){
  return !(f1 < f2);
}

// Devolvemos verdadero en caso de que la fecha del objeto NO sea igual que otra fecha f2
// Así, aprovechamos el operador == ya definido. En caso contrario, devolvemos falso

bool operator!=(const Fecha& f1, const Fecha& f2){
  return !( f1 == f2);
}

// operador de igualdad
bool operator==(const Fecha& f1, const Fecha& f2){
  return (f1.dia() == f2.dia() && f1.mes() == f2.mes() && f1.anno() == f2.anno());
}

Fecha::operator const char*() const throw(){
  const char* const meses[] = {"enero","febrero","marzo","abril","mayo","junio","julio","agosto",
		  "septiembre","octubre","noviembre","diciembre"};
  const char* const dias[] = {"domingo","lunes","martes","miercoles","jueves","viernes","sabado"};
  // vamos a trabajar siempre sobre la misma cadena para todos los objetos
  static char* cad = new char[40];
  tm timeinfo = {0,0,0,dia_,mes_-1,anno_-1900,0,0,-1};
  mktime(&timeinfo);
  sprintf(cad,"%s %d de %s de %d",dias[timeinfo.tm_wday],dia_,meses[timeinfo.tm_mon],anno_);
  return cad;
}