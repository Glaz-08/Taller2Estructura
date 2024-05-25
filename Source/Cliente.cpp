#include "Cliente.h"

Cliente::Cliente(string nombre,string edad, string tipo){
    this-> edad = edad;
    this-> nombre = nombre;
    this-> tipo = tipo;
}
Cliente::~Cliente(){}//destructoor

string Cliente::getTipo() {
    return this-> tipo;
}
string Cliente::getEdad() {
    return this-> edad;
}
string Cliente::getNombre() {
    return this-> nombre;
}
int Cliente::getNumero() {
    return this->numero;
}
void Cliente::setNumero(int numero) {
    this-> numero = numero;
}
string Cliente::getTipode(){//ver la prioridad si es 3ra edad, embarazada o discapacitado
    return "";
}


