#pragma once
#include <iostream>
using namespace std;

class Producto{
    private:
        string nombre,subcategoria;
        int precio,cantidad,id;

    public:
        Producto(string nombre,string subcategoria,int precio,int cantidad,int id);
        string getSubCategoria();
        string getNombre();
        int getPrecio();
        int getCantidad();
        int getId();
        void setCantidad(int num);
};