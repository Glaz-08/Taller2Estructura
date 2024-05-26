#include <iostream>
#include <vector>
#include "HashMap.h"
#include "Nodo.h"
#include "Producto.h"

using namespace std;

void HashMap::rehash() {
    int nuevoTamanoTabla = tamanoTabla * 2;
    vector<Nodo*> nuevaTabla(nuevoTamanoTabla, nullptr);

    for (int i = 0; i < tamanoTabla; i++) {
        Nodo* actual = tabla[i];
        while (actual != nullptr) {
            int indice = funcionHash(actual->clave) % nuevoTamanoTabla;
            Nodo* nuevoNodo = new Nodo(actual->clave, actual->valor);

            Nodo* anterior = nullptr;
            Nodo* siguiente = nuevaTabla[indice];
            while (siguiente != nullptr && siguiente->clave > actual->clave) { 
                anterior = siguiente;
                siguiente = siguiente->siguiente;
            }

            if (anterior == nullptr) { 
                nuevaTabla[indice] = nuevoNodo;
            } else {
                anterior->siguiente = nuevoNodo;
            }
            nuevoNodo->siguiente = siguiente; 

            actual = actual->siguiente;
        }
    }

    tabla.swap(nuevaTabla);
    tamanoTabla = nuevoTamanoTabla;
}

HashMap::HashMap(double factorCargaMaxima) {
    this->tamanoTabla = 1000;
    this->factorCargaMaxima = factorCargaMaxima;
    tabla.resize(tamanoTabla, nullptr);
}

void HashMap::insertar(int clave, Producto* valor) {
    int indice = funcionHash(clave);
    Nodo* nuevoNodo = new Nodo(clave, valor);

    if (tabla[indice] == nullptr) {
        tabla[indice] = nuevoNodo;
    } else {
        Nodo* previo = nullptr;
        Nodo* actual = tabla[indice];
        while (actual != nullptr) {
            previo = actual;
            actual = actual->siguiente;
        }
        previo->siguiente = nuevoNodo;
    }

    double factorCarga = (double) getNumeroElementos() / tamanoTabla;

    if (factorCarga > factorCargaMaxima) {
        rehash();
    }
}

Producto* HashMap::obtener(int clave) {
    int indice = funcionHash(clave);
    Nodo* actual = tabla[indice];

    while (actual != nullptr) {
        if (actual->clave == clave) {
            return actual->valor;
        }
        actual = actual->siguiente;
    }

    return nullptr;
}

void HashMap::borrar(int clave) {
    int indice = funcionHash(clave);
    Nodo* previo = nullptr;
    Nodo* actual = tabla[indice];

    while (actual != nullptr) {
        if (actual->clave == clave) {
            if (previo == nullptr) {
                tabla[indice] = actual->siguiente;
            } else {
                previo->siguiente = actual->siguiente;
            }
            delete actual;
            return;
        }
        previo = actual;
        actual = actual->siguiente;
    }
}

int HashMap::getNumeroElementos() {
    int contador = 0;
    for (int i = 0; i < tamanoTabla; i++) {
        Nodo* actual = tabla[i];
        while (actual != nullptr) {
            contador++;
            actual = actual->siguiente;
        }
    }
    return contador;
}
//recorre el hashmap y retorna una id que no exista
int HashMap::AsignarID(){
    for (int i = 0; i < tamanoTabla; ++i) {
        Nodo* actual = tabla[i];
        while (actual != nullptr) {
            if(actual->siguiente==nullptr){
                return actual->valor->getId()+1;
            }
        }
    }
    return 0;
}
//recorre el hashmap y muestra los productos
void HashMap::MostrarProductos(){

    for (int i = 0; i < tamanoTabla; ++i) {

        Nodo* actual = tabla[i];
        while (actual != nullptr) {
            Producto* producto = actual->valor;

            cout << "ID: " << producto->getId() << ". Nombre/Categoria: " << producto->getNombre() << ", Precio: " << producto->getPrecio()
            << ", Stock: " << producto->getCantidad() << ", Subcategoría: " << producto->getSubCategoria()
            << endl;

            actual = actual -> siguiente;
            }
        }

}
