#include "Categoria.h"

Categoria::Categoria(string nombre){
    this-> nombre = nombre;
}
Categoria::~Categoria(){}//destructoor

string Cliente::getNombre() {
    return this-> nombre;
}