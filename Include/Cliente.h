#pragma once
#include <string>
using namespace std;

class Cliente {
protected:
    string nombre,edad,tipo;
    int numero;

public:
    Cliente(string nombre,string edad, string tipo) ;
        string getNombre();
        string getEdad();
        string getTipo();
        ~Cliente();
        int getNumero();
        void setNumero(int);
        virtual string getTipode();
};