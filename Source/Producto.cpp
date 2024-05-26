#include "Producto.h"

Producto::Producto(string nombre,string subcategoria,int precio,int cantidad,int id){
    this-> nombre=nombre;
    this-> subcategoria=subcategoria;
    this-> precio=precio;
    this-> cantidad=cantidad;
    this-> id=id;
}
string Producto:: getSubCategoria(){
    return this-> subcategoria;
}
string Producto:: getNombre(){
    return this-> nombre;
}
int Producto:: getPrecio(){
    return this-> precio;
}
int Producto::getCantidad(){
    return this-> cantidad;
}
int Producto::getId(){
    return this-> id;
}
void Producto::setCantidad(int numero){
    this-> cantidad=numero;
}