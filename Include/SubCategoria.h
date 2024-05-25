#pragma once
#include <iostream>
#include "Categoria.h"
using namespace std;

class SubCategoria:public Categoria{
    public:
        SubCategoria(string categoria,string subcategora,int precio,int cantidad,int id);
        string getSubCategoria();
        int getPrecio();
        int getCantidad();
        int getId();
};