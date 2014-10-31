
// Práctica 4 Programación orientada a objetos
// Rafael Valle Cabrera
// Clase Autor

#ifndef _AUTOR_H_
#define _AUTOR_H_

// Declaración adelantada
class Cadena;

class Autor{
public:
	// Constructor
	Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) throw(): 
		nombre_(nombre), apellidos_(apellidos), direccion_(direccion){}

	// Métodos observadores
	const Cadena& nombre() const{ return nombre_;}
	const Cadena& apellidos() const{ return apellidos_;}
	const Cadena& direccion() const{ return direccion_;}
private:
	Cadena nombre_, 
		   apellidos_,
		   direccion_;
};

#endif