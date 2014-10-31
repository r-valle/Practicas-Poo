
// Implementación del algoritmo de Luhn en C++
// para asegurarnos de la validez de un nº de tarjeta de crédito

#include "cadena.h"

bool luhn(const Cadena& num, unsigned n){
  unsigned suma = 0;
  bool alt = false;
  
  for(int i = n-1; i > -1; --i){
    n = num[unsigned(i)]-'0';
    if(alt){
      n *= 2;
      if(n > 9){
	n = (n%10)+1;
      }
    }
    alt = !alt;
    suma += n;
  }
  return !(suma%10);
}
