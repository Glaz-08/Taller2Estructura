#pragma once
#include <iostream>
#include "Cliente.h"
using namespace std;

class ClienteNormal: public Cliente{
    public:
        ClienteNormal(string,string,string,int);
        int getNumero();
   


};