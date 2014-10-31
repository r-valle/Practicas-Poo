#include <cmath>
#include <iostream>
#include <locale>
#include <sstream>
using namespace std;

#include "fct.h"
#include "test-auto.h"

#include "articulo.h"
#include "autor.h"
#include "cadena.h"
#include "fecha.h"
#include "pedido.h"
#include "pedido-articulo.h"
#include "tarjeta.h"
#include "usuario.h"
#include "usuario-pedido.h"

namespace {

  // Para pruebas de Autor
  const Cadena sNombreAutor1 = "Nobuo",
    sApellidosAutor1 = "Uematsu",
    sDireccionAutor1 = "Tokyo, Japón";

  // Para pruebas de Libro
  Autor autor1(sNombreAutor1, sApellidosAutor1, sDireccionAutor1);
  Articulo::Autores autores = crea_autores(autor1);

  const Cadena sReferenciaLibro = "110", sTituloLibro = "Fundamentos de C++";
  const Fecha  fechaLibro(1,1,1998);
  const double precioLibro = 35.95;
  const unsigned paginasLibro = 650, stockLibro = 100;

  // Para pruebas de Cederron
  const Cadena
    sReferenciaCederron("404"),
    sTituloCederron("Ubuntu Hysterical Hyena");
  const Fecha fechaCederron(8, 4, 2005);
  const double precioCederron    = 0.01;
  const unsigned tamanyoCederron = 400;
  const unsigned stockCederron   = 1000;

  // Para pruebas de InformeDigital
  const Cadena sReferenciaInforme("4337"),
    sTituloInforme("Minority Report");
  const Fecha fechaInforme(9,9,2009);
  const double precioInforme = 9000;

  // Hay que usar punteros, o puede haber un fallo de segmentación si
  // el orden de inicialización de los atributos estáticos no es el
  // apropiado
  Usuario *pUsuarioPedido;
  Tarjeta *pTarjetaPedido;
  Pedido_Articulo pedArt;
  Usuario_Pedido  usuPed;

  Cederron cdrom(autores, sReferenciaCederron, sTituloCederron,
                 fechaCederron, precioCederron, tamanyoCederron,
                 stockCederron);
  InformeDigital informeNoExpirado(autores, sReferenciaInforme,
                                   sTituloInforme, fechaInforme,
                                   precioInforme, Fecha() + 7);
  InformeDigital informeExpirado(autores, sReferenciaInforme,
                                 sTituloInforme, fechaInforme,
                                 precioInforme, Fecha() - 7);

  // Parte común
  bool bPrimera = true;
}

FCTMF_FIXTURE_SUITE_BGN(test_p4) {

  if (bPrimera) {
    bPrimera = false;
    cerr << endl
         << "---------- PRÁCTICA 4 ----------"
         << endl << endl;
  }

  FCT_SETUP_BGN() {
    pUsuarioPedido = new Usuario("fjord", "Franz", "Jordan",
                                 "Rue del Percebe, 13", Clave("supersecreta"));
    pTarjetaPedido = new Tarjeta(Numero("11234567890126"), *pUsuarioPedido,
                                 Fecha() + 7);
  }
  FCT_SETUP_END();

  FCT_TEARDOWN_BGN() {
    delete pUsuarioPedido;
    delete pTarjetaPedido;
  }
  FCT_TEARDOWN_END();

  FCT_TEST_BGN(AUTOR - observadores) {
    const Autor autor(sNombreAutor1, sApellidosAutor1, sDireccionAutor1);
    chk_eq_str(autor.nombre(), sNombreAutor1);
    chk_eq_str(autor.apellidos(), sApellidosAutor1);
    chk_eq_str(autor.direccion(), sDireccionAutor1);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(LIBRO - observadores) {
    const Libro libro(autores, sReferenciaLibro, sTituloLibro, fechaLibro,
                      precioLibro, paginasLibro, stockLibro);

    fct_chk_eq_int(autores.size(), 1);
    fct_chk_eq_int(libro.autores().count(&autor1), 1);

    chk_eq_str(libro.referencia(), sReferenciaLibro);
    chk_eq_str(libro.titulo(), sTituloLibro);
    fct_chk(libro.f_publi() == fechaLibro);
    fct_chk_eq_dbl(libro.precio(), precioLibro);
    fct_chk_eq_int(libro.n_pag(), paginasLibro);
    fct_chk_eq_int(libro.stock(), stockLibro);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(LIBRO - insercion en flujo) {
    const Libro libro(autores, sReferenciaLibro, sTituloLibro, fechaLibro,
                      precioLibro, paginasLibro, stockLibro);

    ostringstream os;
    os << libro;
    const string sLibro = os.str();

    fct_chk_eq_str(sLibro.c_str(),
                   "[110] \"Fundamentos de C++\", de Uematsu. 1998. 35,95€\n"
                   "\t650 págs., 100 unidades.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(LIBRO - modificacion) {
    Libro libro(autores, sReferenciaLibro, sTituloLibro, fechaLibro,
                precioLibro, paginasLibro, stockLibro);

    const double nuevoPrecio  = 10.5;
    const unsigned nuevoStock = libro.stock() + 1;
    libro.precio() = nuevoPrecio;
    libro.stock()  = nuevoStock;
    fct_chk_eq_int(libro.precio(), nuevoPrecio);
    fct_chk_eq_int(libro.stock(), nuevoStock);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(CEDERRON - observadores) {
    const Cederron cdrom(autores, sReferenciaCederron, sTituloCederron,
                         fechaCederron, precioCederron, tamanyoCederron,
                         stockCederron);

    fct_chk_eq_int(autores.size(), 1);
    fct_chk_eq_int(cdrom.autores().count(&autor1), 1);

    chk_eq_str(cdrom.referencia(), sReferenciaCederron);
    chk_eq_str(cdrom.titulo(), sTituloCederron);
    fct_chk(cdrom.f_publi() == fechaCederron);
    fct_chk_eq_dbl(cdrom.precio(), precioCederron);
    fct_chk_eq_int(cdrom.tam(), tamanyoCederron);
    fct_chk_eq_int(cdrom.stock(), stockCederron);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(CEDERRON - insercion en flujo) {
    const Cederron cdrom(autores, sReferenciaCederron, sTituloCederron,
                         fechaCederron, precioCederron, tamanyoCederron,
                         stockCederron);

    ostringstream os;
    os << cdrom;
    const string sCdrom = os.str();

    fct_chk_eq_str(sCdrom.c_str(),
                   "[404] \"Ubuntu Hysterical Hyena\", de Uematsu. 2005. 0,01€\n"
                   "\t400 MB, 1000 unidades.");
  }
  FCT_TEST_END();

  FCT_TEST_BGN(CEDERRON - modificacion) {
    Cederron cdrom(autores, sReferenciaCederron, sTituloCederron,
                   fechaCederron, precioCederron, tamanyoCederron,
                   stockCederron);

    const double nuevoPrecio = 10.5;
    const unsigned nuevoStock = cdrom.stock() + 1;
    cdrom.precio() = nuevoPrecio;
    cdrom.stock() = nuevoStock;
    fct_chk_eq_int(cdrom.precio(), nuevoPrecio);
    fct_chk_eq_int(cdrom.stock(), nuevoStock);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(INFORMEDIGITAL - observadores) {
    const Fecha fManyana = Fecha() + 1;
    const InformeDigital informe(autores, sReferenciaInforme, sTituloInforme,
                                 fechaInforme, precioInforme, fManyana);

    fct_chk_eq_int(autores.size(), 1);
    fct_chk_eq_int(informe.autores().count(&autor1), 1);

    chk_eq_str(informe.referencia(), sReferenciaInforme);
    chk_eq_str(informe.titulo(), sTituloInforme);
    fct_chk(informe.f_publi() == fechaInforme);
    fct_chk(informe.f_expir() == fManyana);
    fct_chk_eq_dbl(informe.precio(), precioInforme);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(INFORMEDIGITAL - insercion en flujo) {
    const Fecha fExpiracion = Fecha() + 1;
    const InformeDigital informe(autores, sReferenciaInforme, sTituloInforme,
                                 fechaInforme, precioInforme, fExpiracion);

    ostringstream os;
    os << informe;
    const string sInforme = os.str();

    os.str("");
    os << "[4337] \"Minority Report\", de Uematsu. 2009. 9000,00€\n"
      "\tA la venta hasta el "
       << fExpiracion
       << ".";
    const string sEsperado = os.str();

    fct_chk_eq_str(sInforme.c_str(), sEsperado.c_str());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(INFORMEDIGITAL - modificacion) {
    InformeDigital informe(autores, sReferenciaInforme, sTituloInforme,
                           fechaInforme, precioInforme, Fecha() + 1);

    const double nuevoPrecio = 10.5;
    informe.precio() = nuevoPrecio;
    fct_chk_eq_int(informe.precio(), nuevoPrecio);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(INFORMEDIGITAL - compra de informe no expirado) {
    pUsuarioPedido->compra(cdrom, 1);
    pUsuarioPedido->compra(informeNoExpirado, 1);
    Pedido p(usuPed, pedArt, *pUsuarioPedido, *pTarjetaPedido);

    // Cálculo en coma flotante con precisión limitada: no se puede
    // usar == directamente. Hay que permitir un cierto margen de
    // diferencia, debido al error de aproximación.
    const double totalEsperado = cdrom.precio() + informeNoExpirado.precio();
    fct_chk_eq_dbl(p.total(), totalEsperado);
  }
  FCT_TEST_END();

  FCT_TEST_BGN(INFORMEDIGITAL - informe expirado y carrito no queda vacio) {
    pUsuarioPedido->compra(cdrom, 1);
    pUsuarioPedido->compra(informeExpirado, 1);
    Pedido p(usuPed, pedArt, *pUsuarioPedido, *pTarjetaPedido);

    fct_chk_eq_dbl(p.total(), cdrom.precio());
  }
  FCT_TEST_END();

  FCT_TEST_BGN(INFORMEDIGITAL - informe expirado y carrito queda vacio) {
    pUsuarioPedido->compra(informeExpirado, 1);
    try {
      Pedido p(usuPed, pedArt, *pUsuarioPedido, *pTarjetaPedido);
      fct_chk(!"Se esperaba una excepción");
    } catch (const Pedido::Vacio& ex) {}
  }
  FCT_TEST_END();

}
FCTMF_FIXTURE_SUITE_END()
