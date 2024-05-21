#include "SubCategoria.h"

SubCategoria::SubCategoria(string nombre,string categoria,string SubCategoria,int precio,int cantidad,int id):Categoria(nombre){
    this-> nombre=nombre;
    this-> categoria=categoria;
    this-> SubCategoria=SubCategoria;
    this-> precio=precio;
    this-> cantidad=cantidad;
    this-> id=id;
}
string getSubCategoria(){
    return this-> SubCategoria;
}
int getPrecio(){
    return this-> precio;
}
int getCantidad(){
    return this-> cantidad;
}
int getId(){
    return this-> id;
}