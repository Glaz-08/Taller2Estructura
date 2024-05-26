#include <vector>
#include "Nodo.h"
#include "Producto.h"

class HashMap {
public:
    HashMap(double maxLoadFactor = 0.90);

    void insertar(int clave, Producto* valor);
    void MostrarProductos();
    int AsignarID();
    Producto* obtener(int clave);
    void borrar(int clave);
    int getNumeroElementos();

private:
    int tamanoTabla;
    double factorCargaMaxima;
    std::vector<Nodo*> tabla;

    int funcionHash(int clave);
    void rehash();
};