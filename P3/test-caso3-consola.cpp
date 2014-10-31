/* Prueba de la clase Pedido
 *
 * LIBRERÍA
 * ©2009,2011 Inma, Juanma, Fidel, Gerardo
 */

#include <cstdlib>
#include <exception>
#include <iostream>
#include "usuario.h"
#include "tarjeta.h"
#include "articulo.h"
#include "pedido.h"
#include "usuario-pedido.h"
#include "pedido-articulo.h"

#define AZUL  "\033[0m\033[01;34m"
#define NORMAL "\033[0m"

int main()
{
    // Constructor de usuario: id, nombre, apellidos, dirección, clave
    Usuario 
	    lucas("lucas", "Lucas", "Grijánder", 
		      "Avda. Generalísimo, 654 (Barbate)", "vaeg0Quo"),
	    krispin("krispin", "Crispín", "Klánder", 
		        "C/ del Jurel, 876 (Barbate)", "Pheaj9li"),
	    hanna("hannah", "Hannah", "Montana", 
	          "Santa Monica Blvd., Los Ángeles, CA", "ahxo2Aht"),
	    rosa("rosa", "Rosita", "de Jericó",
		     "C/ de Sor Sofía, 345 (2 Hermanas)", "Roh9aa5v");
    // Constructor de Tarjeta: Numero, Usuario, fecha de caducidad
    Tarjeta 
	    visa1(Numero("4539 4512 0398 7356"), lucas, "31/12/2014"),
	    american_express(Numero("378282246310005"), hanna, "30/11/2014"),
	    dinners_club(Numero("30569309025904"), rosa, "13/7/2014"),
	    mastercard(Numero("555555555555 4444  "), krispin, "1/10/2014"),
	    australian_bank_card(Numero("5610591081018250"), krispin, "2/12/2014"),
	    jcb(Numero("3530111333300000"), rosa, "7/7/2017"),
	    visa2(Numero(" 4222222222222"), lucas, "4/12/2014");

    // Constructor de Articulo: referencia, título, fecha de publicación,
    // precio, stock
    Articulo
        poo("100", "Programación Orientada a Objetos", "1/8/2000", 32.50, 5),
        cpp("110", "Fundamentos de C++", "20/6/1998)", 35.95, 10),
        stl("111", "The Standard Template Library", "5/10/2002", 42.10, 3),
        ada("103", "Análisis y Diseño de Algoritmos", "1/2/2001", 39.95, 2);

    // Añadir y quitar artículos al carrito y ver el carrito
    // Comprar: Articulo, Cantidad (1 por omisión, 0 elimina el artículo)
    // Factura: Usuario_Pedido, Pedido_Articulo, Usuario, Tarjeta, Fecha [hoy]
    Usuario_Pedido usuario_ped;
    Pedido_Articulo pedido_art;

    std::cout << std::endl << std::endl << "CARRITOS VACÍOS" 
              << std::endl << std::endl;
    mostrar_carro(std::cout, lucas);
    mostrar_carro(std::cout, krispin);
    mostrar_carro(std::cout, hanna);
    mostrar_carro(std::cout, rosa);
    std::cout << std::endl;

    lucas.compra(cpp, 3);
    lucas.compra(stl, 1);
    mostrar_carro(std::cout, lucas);
    Pedido p1(usuario_ped, pedido_art, lucas, visa1, Fecha(10, 8));

    std::cout << "*** Cambio de precio de CPP y STL\n\n";
    cpp.precio() = 29.95;	// cambiar precios
    stl.precio() = 44.50; 
    krispin.compra(cpp, 2);
    krispin.compra(stl, 2);
    mostrar_carro(std::cout, krispin);
    std::cout << "\n*** krispin devuelve STL y compra POO\n";
    krispin.compra(stl, 0); // quita stl del carrito
    krispin.compra(poo);    // un ejemplar
    mostrar_carro(std::cout, krispin);
    std::cout << "\n*** No se comprueba stock\n"
	      << "*** stock de ADA = " << ada.stock() << std::endl;
    hanna.compra(ada, 6);	// no se comprueban las existencias
    mostrar_carro(std::cout, hanna);
    std::cout << "\n*** hanna devuelve 4 ADA\n";
    hanna.compra(ada, 2);	// quita 4 del carrito
    mostrar_carro(std::cout, hanna);
    Pedido p3(usuario_ped, pedido_art, hanna, american_express, 
	      --Fecha());	// pedido ayer
    Pedido p2(usuario_ped, pedido_art, krispin, mastercard, "5/7/2014");
    std::cout << "*** Cambio de precio de POO y ADA\n\n";
    poo.precio() = 35.20;	// cambiar precios
    ada.precio() = 34.90; 
    rosa.compra(poo, 2);
    rosa.compra(cpp, 3);
    rosa.compra(stl);
    rosa.compra(ada, 0); // no hace nada, ada no está en el carro
    mostrar_carro(std::cout, rosa);
    Pedido p4(usuario_ped, pedido_art, rosa, jcb, "5/8/2014");

    std::cout << p1 << std::endl << p2 << std::endl 
	      << p3 << std::endl << p4 << std::endl;

    // Recepción de mercancías
    poo.stock() += 5; cpp.stock() *= 4; stl.stock() += 2; ada.stock() += 2;
    
    rosa.compra(stl); rosa.compra(ada);
    Pedido p5(usuario_ped, pedido_art, rosa, jcb); // pedido hoy
    rosa.compra(cpp, 3);
    Pedido p6(usuario_ped, pedido_art, rosa, dinners_club); // pedido hoy
    krispin.compra(ada); krispin.compra(stl); krispin.compra(poo, 3);
    Pedido p7(usuario_ped, pedido_art, krispin, australian_bank_card, 
	      "5/9/2014");
    hanna.compra(poo, 2); hanna.compra(cpp);
    Pedido p8(usuario_ped, pedido_art, hanna, american_express, "5/10/2014");

    std::cout << p5 << std::endl << p6 << std::endl
	      << p7 << std::endl << p8 << std::endl

	      << "\n" AZUL "-------------------DETALLE DE PEDIDOS--------------"
	NORMAL  << std::endl;
    pedido_art.mostrarDetallePedidos(std::cout);
    std::cout << "\n" AZUL "------------------VENTAS DE ARTÍCULOS--------------"
	NORMAL << std::endl;
    pedido_art.mostrarVentasArticulos(std::cout);
    
    // Pruebas de excepciones
    try {
	   Pedido nulo(usuario_ped, pedido_art, lucas, visa2);
    }
    catch(Pedido::Vacio& e) {
	   std::cerr << "Error de pedido: el carrito de " << e.usuario().id() 
	             << " está vacío. " << std::endl;
    }
    try {
       krispin.compra(cpp);
       Pedido farsante(usuario_ped, pedido_art, krispin, visa2);
    }
    catch(Pedido::Impostor& e) {
       std::cerr << "Error de pedido: la tarjeta de pago no es de " 
		 << e.usuario().id() << std::endl;
    }
    try {
       rosa.compra(poo, 2); rosa.compra(stl, 4); rosa.compra(ada, 5);
       Pedido no_disponible(usuario_ped, pedido_art, rosa, dinners_club);
    }
    catch(Pedido::SinStock& e) {
       std::cerr << "Error de pedido: no hay existencias del artículo [" 
                 << e.articulo().referencia() << "]" << std::endl;
    }
    try {
	// Creamos una tarjeta que caducó ayer. ¿Qué pasa? ¡No somos un
	// maldito banco, esto es una prueba!
	Tarjeta caduca(Numero("4222222222222"), lucas, Fecha() - 1); 
	lucas.compra(poo, 2);
	Pedido no_pagado(usuario_ped, pedido_art, lucas, caduca); // pedido hoy
    }
    catch(Tarjeta::Caducada& e) {
	   std::cerr << "Error de pedido: tarjeta caducada el " << e.cuando()
	             << std::endl;
    }
    std::cout << std::endl << "Número total de pedidos: " 
	      << Pedido::n_total_pedidos() << std::endl;
}

