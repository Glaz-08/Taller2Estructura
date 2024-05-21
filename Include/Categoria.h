#pragma once
#include <string>
using namespace std;

class Categoria{
    protected:
     string nombre;
    public:
    Categoria(string nombre);
    string getNombre();
    ~Categoria();


}