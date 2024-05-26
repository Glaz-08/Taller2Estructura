#include <iostream>
#include "Nodo.h"
#include "Producto.h"

Nodo::Nodo(int clave, Producto* valor)
{
    this->clave = clave;
    this->valor = valor;
    this->siguiente = nullptr;
}