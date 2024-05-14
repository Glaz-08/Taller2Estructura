#pragma once
#include <iostream>
#include "Cliente.h"
using namespace std;

class ClientePreferencial: public Cliente{
    public:
        ClientePreferencial(string,string,string,string tipode,int);
        int getNumero();
        string getTipode();
   


};