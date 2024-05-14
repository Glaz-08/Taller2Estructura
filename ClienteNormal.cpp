#include "ClienteNormal.h"

ClienteNormal::ClienteNormal(string nombre,string edad,string tipo,int numero):Cliente(nombre,edad,tipo){
    this-> numero=numero;
    this-> nombre=nombre;
    this-> edad=edad;
    this-> tipo=tipo;
    this-> numero=numero;

};

int Cliente::getNumero() {
    return this-> numero;
}