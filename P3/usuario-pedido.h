
// Práctica 3 Programación orientada a objetos
// Rafael Valle Cabrera
// Clase de asociación Usuario_Pedido

#ifndef _USUARIO_PEDIDO_H_
#define _USUARIO_PEDIDO_H_

#include <map>
#include <set>

#include "usuario.h"
#include "pedido.h"

using namespace std;
 
class Usuario_Pedido{
public:
  // tipo miembro clase Usuario_Pedido
  typedef set<Pedido*> Pedidos;

  typedef map<Usuario*,Pedidos> UsuarioPedidos;
  typedef map<Pedido*,Usuario*> PedidosUsuarios;
  
  // Métodos observadores
  //template <typename Usuario, typename Pedido>
  Pedidos& pedidos(Usuario& user){ return userpeds[&user];}
  
  //template <typename Usuario, typename Pedido>
  const Usuario* cliente(Pedido& ped){ return pedsuser[&ped];}
  
  // Métodos modificadores
  void asocia(Usuario& user, Pedido& ped){ userpeds[&user].insert(&ped); pedsuser[&ped] = &user;}
  void asocia(Pedido& ped, Usuario& user){ asocia(user,ped);}
  
private:
  UsuarioPedidos userpeds;
  PedidosUsuarios pedsuser;
};

#endif