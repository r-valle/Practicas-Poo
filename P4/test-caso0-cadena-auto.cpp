#include <cstdlib>
#include <iostream>
#include <sstream>
#include "fct.h"
using namespace std;

#include "cadena.h"

namespace {
  bool bPrimera = true;
}

FCTMF_SUITE_BGN(test_cadena) {

  if (bPrimera) {
    bPrimera = false;
    cerr << endl
         << "---------- PRÁCTICA 1: CADENA ----------"
         << endl << endl;
  }

  FCT_TEST_BGN(Ctor: repetir caracter ciertas veces) {
    const Cadena a(5, '*');
    fct_chk(strcmp(a.c_str(), "*****") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Ctor: entero - repite espacios) {
    const Cadena a(10);
    fct_chk(strcmp(a.c_str(), "          ") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Ctor: sin parametros - vacia) {
    const Cadena a;
    fct_chk(strcmp(a.c_str(), "") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Ctor: por copia de otra cadena) {
    const Cadena a(3);
    const Cadena b(a);
    fct_chk(strcmp(b.c_str(), "   ") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Ctor: desde cadena de bajo nivel) {
    const Cadena a("hola");
    fct_chk(strcmp(a.c_str(), "hola") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Asignar una cadena a otra) {
    Cadena a("adios");
    const Cadena b;
    a = b;
    fct_chk(strcmp(a.c_str(), b.c_str()) == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Asignar una cadena de bajo nivel) {
    Cadena a;
    a = "lembas";
    fct_chk(strcmp(a.c_str(), "lembas") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Observadora de longitud: cadena vacia) {
    const Cadena a;
    fct_chk(a.longitud() == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Observadora de longitud: cadena no vacia) {
    const char *s = "saludos cordiales";
    const Cadena a(s);
    fct_chk(a.longitud() == strlen(s));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Concatenacion: con +=) {
    Cadena a("cram");
    a += Cadena(" y lembas");
    fct_chk(strcmp(a.c_str(), "cram y lembas") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Concatenacion: con +) {
    const Cadena a("hola"), b("adios");
    Cadena c = a + b;
    fct_chk(strcmp((a + b).c_str(), "holaadios") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Comparacion: igualdad) {
    fct_chk(Cadena("hola") == Cadena("hola"));
    fct_chk(!(Cadena("hola") == Cadena("adios")));
    fct_chk(!(Cadena("hola") == Cadena("holas")));
    fct_chk(!(Cadena("holas") == Cadena("hola")));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Comparacion: desigualdad) {
    fct_chk(!(Cadena("hola") != Cadena("hola")));
    fct_chk(Cadena("hola")  != Cadena("adios"));
    fct_chk(Cadena("hola")  != Cadena("holas"));
    fct_chk(Cadena("holas") != Cadena("hola"));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Comparacion: menor que) {
    fct_chk(Cadena("") < Cadena("x"));
    fct_chk(Cadena("a") < Cadena("b"));
    fct_chk(!(Cadena("ab") < Cadena("ab")));
    fct_chk(!(Cadena("ca") < Cadena("aa")));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Comparacion: menor o igual que) {
    fct_chk(Cadena("") <= Cadena("x"));
    fct_chk(Cadena("a") <= Cadena("b"));
    fct_chk(Cadena("ab") <= Cadena("ab"));
    fct_chk(!(Cadena("ca") <= Cadena("aa")));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Comparacion: mayor que) {
    fct_chk(!(Cadena("") > Cadena("x")));
    fct_chk(!(Cadena("a") > Cadena("b")));
    fct_chk(!(Cadena("ab") > Cadena("ab")));
    fct_chk(Cadena("ca") > Cadena("aa"));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Comparacion: mayor o igual que) {
    fct_chk(!(Cadena("") >= Cadena("x")));
    fct_chk(!(Cadena("a") >= Cadena("b")));
    fct_chk(Cadena("ab") >= Cadena("ab"));
    fct_chk(Cadena("ca") >= Cadena("aa"));
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Leer caracter: [] y posicion valida) {
    const Cadena a("abcd");
    fct_chk(a.operator[](0) == 'a');
    fct_chk(a.operator[](3) == 'd');
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Leer caracter: [] y posicion no valida) {
    const Cadena a;
    a.operator[](0);
    fct_chk(true);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Leer caracter: at y posicion valida) {
    const Cadena a("abcd");
    fct_chk(a.at(0) == 'a');
    fct_chk(a.at(3) == 'd');
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Leer caracter: at y posicion no valida) {
    const Cadena a;
    try {
      a.at(0);
      fct_chk(!"Se esperaba excepción");
    } catch (out_of_range) {}
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Escribir caracter: []) {
    Cadena a("abcd");
    a.operator[](2) = 'x';
    fct_chk(strcmp(a.c_str(), "abxd") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Escribir caracter: at()) {
    Cadena a("abcd");
    a.at(2) = 'x';
    fct_chk(strcmp(a.c_str(), "abxd") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Subcadena: caso normal) {
    const Cadena a("eenie meenie moe");
    fct_chk(strcmp(a.subcadena(6,6).c_str(), "meenie") == 0);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Subcadena: posicion inicial mayor que longitud) {
    const Cadena a("0123456789");
    try {
      a.subcadena(10, 10);
      fct_chk(!"Se esperaba excepción");
    } catch (out_of_range) {}
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Subcadena: posicion inicial negativa) {
    const Cadena a("0123456789");
    try {
      a.subcadena(-1, 10);
      fct_chk(!"Se esperaba excepción");
    } catch (out_of_range) {}
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Subcadena: tamanyo mayor que longitud restante) {
    const Cadena a("0123456789");
    try {
      a.subcadena(9,2);
      fct_chk(!"Se esperaba excepción");
    } catch (out_of_range) {}
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Subcadena: tamanyo negativo) {
    const Cadena a("0123456789");
    try {
      a.subcadena(9,-1);
      fct_chk(!"Se esperaba excepción");
    } catch (out_of_range) {}
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Subcadena: tamanyo excesivo) {
    const Cadena a("0123456789");
    try {
      a.subcadena(9,1000);
      fct_chk(!"Se esperaba excepción");
    } catch (out_of_range) {}
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Extraccion: entrada vacia) {
    istringstream is("");
    Cadena c("algo");
    is >> c;
    fct_chk(c == "");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Extraccion: solo espacios) {
    istringstream is(" \t\r\n\v");
    Cadena c("algo");
    is >> c;
    fct_chk(c == "");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Extraccion: hasta fin de entrada) {
    istringstream is("prueba");
    Cadena c;
    is >> c;
    fct_chk(c == "prueba");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Extraccion: una palabra) {
    istringstream is("bueno bonito barato");
    Cadena c;
    is >> c;
    fct_chk(c == "bueno");
    fct_chk(is.peek() == ' ');
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Extraccion: una palabra con espaciado inicial) {
    istringstream is("   hola adiós");
    Cadena c;
    is >> c;
    fct_chk(c == "hola");
    fct_chk(is.peek() == ' ');
  }
  FCT_TEST_END();

  FCT_TEST_BGN(Insercion) {
    ostringstream os;
    const char *s = "probando";
    const Cadena c(s);
    os << c;
    fct_chk(os.str() == s);
  }
  FCT_TEST_END();
}
FCTMF_SUITE_END()
