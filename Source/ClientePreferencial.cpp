#include "ClientePreferencial.h"

ClientePreferencial::ClientePreferencial(string nombre,string edad,string tipo,string prioridad,int numero):Cliente(nombre,edad,tipo){
    this-> numero=numero;
    this-> nombre=nombre;
    this-> edad=edad;
    this-> tipo=tipo;
    this-> numero=numero;
    int NumeroPreferencia;

};
int Cliente::getNumero() {
    return this-> numero;
}
string ClientePreferencial::getTipode(){//ver la prioridad si es 3ra edad,embarasada o discapacitado
    return this->prioridad;
}
int getNumeroPreferencia(){
    return NumeroPreferencia;

}
void setNumeroPreferencia(int valor) {
        NumeroPreferencia = valor;
    }
