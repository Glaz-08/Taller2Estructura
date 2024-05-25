#include "ClientePreferencial.h"

ClientePreferencial::ClientePreferencial(string nombre,string edad,string tipo,string prioridad,int numero):Cliente(nombre,edad,tipo),numeroPreferencia(0){
    this-> nombre=nombre;
    this-> edad=edad;
    this-> tipo=tipo;
    this-> prioridad=prioridad;
    this-> numero=numero;

};
string ClientePreferencial::getTipode(){//ver la prioridad si es 3ra edad, embarazada o discapacitado
    return this->prioridad;
}
int ClientePreferencial::getNumeroPreferencia(){
    return this->numeroPreferencia;
}
void ClientePreferencial::setNumeroPreferencia(int valor) {
        this->numeroPreferencia = valor;
}
