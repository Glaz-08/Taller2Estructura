#pragma once
#include <iostream>
#include "Producto.h"
using namespace std;

class Nodo 
{
    public: 
        int clave;
        Producto* valor;
        Nodo* siguiente;
        Nodo(int clave, Producto* valor);
};
