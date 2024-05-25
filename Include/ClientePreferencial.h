#pragma once
#include <iostream>
#include "Cliente.h"
using namespace std;

class ClientePreferencial: public Cliente{
    private:
        string prioridad;
        int numeroPreferencia;
    public:
        ClientePreferencial(string nombre,string edad,string tipo,string prioridad,int numero);
        int getNumeroPreferencia();
        void setNumeroPreferencia(int);
        string getTipode();
   


};