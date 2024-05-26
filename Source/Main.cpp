#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include "Cliente.h"
#include "Producto.h"
#include "HashMap.h"
#include "ClientePreferencial.h"
#include "ClienteNormal.h"

using namespace std;

HashMap* bodega = new HashMap();
vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Encuentra el número mayor en la cola
int encontrarMayor(queue<Cliente*> clientesPreferenciales) {
    int mayor = 0;
    while (!clientesPreferenciales.empty()) {
        if (clientesPreferenciales.front()->getNumero() > mayor) {
            mayor = clientesPreferenciales.front()->getNumero();
        }
        clientesPreferenciales.pop();
    }
    return mayor;
}

// Da el siguiente número preferencial basado en el mayor número actual
int darNumeroPreferencial(queue<Cliente*> clientesPreferenciales) {
    return encontrarMayor(clientesPreferenciales) + 1;
}


// Lee datos de clientes desde un archivo de texto
void leerDatosClientesTxt(queue<Cliente*>& clientesNormales, queue<Cliente*>& clientesPreferenciales) {
    string linea;
    ifstream archivo("Clientes.txt");  
    char delimitador = ',';
    while (getline(archivo, linea)) {
        vector<string> partes = split(linea, delimitador); 
        string nombre = partes[0];
        string edad = partes[1];
        string tipo = partes[2];
        if (tipo == "Preferencial") {
            string tipoPrioridad = partes[3];
            int numero = stoi(partes[4]);
            Cliente* clientePref = new ClientePreferencial(nombre, edad, tipo, tipoPrioridad, numero);
            clientesPreferenciales.push(clientePref);
        } else {
            int numeroNorm = stoi(partes[3]);
            Cliente* clienteNorm = new ClienteNormal(nombre, edad, tipo, numeroNorm);
            clientesNormales.push(clienteNorm);
        }
    }
    archivo.close();
}


// Ordena la cola de clientes por prioridad
void ordenamientoPorPrioridad(queue<Cliente*>& clientesNormales, queue<Cliente*>& ClientesPreferenciales, queue<Cliente*>& clientesPreferencialesOrdenados) {
    if (!ClientesPreferenciales.empty() && !clientesNormales.empty()) {
        queue<Cliente*> auxiliarTerceraEdad, auxiliarEmbarazada, auxiliarDiscapacitado;

        while (!ClientesPreferenciales.empty()) {
            if (ClientesPreferenciales.front()->getTipode() == "Tercera edad") {
                auxiliarTerceraEdad.push(ClientesPreferenciales.front());
            } else if (ClientesPreferenciales.front()->getTipode() == "Embarazada") {
                auxiliarEmbarazada.push(ClientesPreferenciales.front());
            } else if (ClientesPreferenciales.front()->getTipode() == "Discapacidad") {
                auxiliarDiscapacitado.push(ClientesPreferenciales.front());
            }
            ClientesPreferenciales.pop();
        }

        int contador = 1;
        Cliente* aux = nullptr;
        while (!auxiliarTerceraEdad.empty()) {
            aux = auxiliarTerceraEdad.front();
            aux->setNumero(contador);
            clientesPreferencialesOrdenados.push(aux);
            auxiliarTerceraEdad.pop();
            contador++;
        }
        while (!auxiliarDiscapacitado.empty()) {
            aux = auxiliarDiscapacitado.front();
            aux->setNumero(contador);
            clientesPreferencialesOrdenados.push(aux);
            auxiliarDiscapacitado.pop();
            contador++;
        }
        while (!auxiliarEmbarazada.empty()) {
            aux = auxiliarEmbarazada.front();
            aux->setNumero(contador);
            clientesPreferencialesOrdenados.push(aux);
            auxiliarEmbarazada.pop();
            contador++;
        }
        while (!clientesNormales.empty()) {
            aux = clientesNormales.front();
            aux->setNumero(contador);
            clientesPreferencialesOrdenados.push(aux);
            clientesNormales.pop();
            contador++;
        }
    } else {
        cout << "No se pueden ordenar clientes. Las colas de clientes están vacías." << endl;
    }
}

// Muestra los clientes ordenados por prioridad
void mostrar(queue<Cliente*>& clientesPreferencialesOrdenados) {
    while (!clientesPreferencialesOrdenados.empty()) {
        cout << "Atendiendo al numero: " << clientesPreferencialesOrdenados.front()->getTipode() << " " << clientesPreferencialesOrdenados.front()->getNumero() << endl;
        clientesPreferencialesOrdenados.pop();
    }
}

// Control de error para la creación de clientes
void controlDeError(string nombreCliente, string edad, queue<Cliente*>& clientesNormales, queue<Cliente*>& clientesPreferencialesOrdenados) {
    int opcion = 0;
    int numero = 0;
    string tipoDeDiscapacidad;
    Cliente* clientePref = nullptr;
    Cliente* clienteNorm = nullptr;

    do {
        cout << "Ingrese alguno de los valores a continuación:" << endl;
        cout << "1) si es Preferencial " << endl;
        cout << "2) si es Normal " << endl;

        while (!(cin >> opcion)) {
            cout << "Entrada no válida. Por favor, ingrese un número." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (opcion) {
            case 1:
                cout << "Ingrese el tipo de Preferencialidad: Embarazada, Discapacidad, Tercera edad" << endl;
                cout << "Escríbalo tal cual como sale: Embarazada / Discapacidad / Tercera edad" << endl;
                cin >> tipoDeDiscapacidad;
                numero = darNumeroPreferencial(clientesPreferencialesOrdenados);
                clientePref = new ClientePreferencial(nombreCliente, edad, "Preferencial", tipoDeDiscapacidad, numero);
                clientesPreferencialesOrdenados.push(clientePref);
                opcion = 3;
                break;
            case 2:
                numero = darNumeroPreferencial(clientesPreferencialesOrdenados);
                clienteNorm = new ClienteNormal(nombreCliente, edad, "Normal", numero);
                clientesNormales.push(clienteNorm);
                opcion = 3;
                break;
            default:
                cout << "Opción incorrecta, por favor ingrese una opción válida" << "\n" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (opcion != 3);
}




// Lee datos de productos desde un archivo de texto
void leerDatosProductosTxt() {
    string linea;
    ifstream archivo("Productos.txt");
    char delimitador = ',';
    while (getline(archivo, linea)) {
        vector<string> partes = split(linea, delimitador); 
        if (partes.size() >= 5) {
            string nombreCategoria = partes[0];
            string nombreSubCategoria = partes[1];
            int precio = stoi(partes[2]);
            int cantidad = stoi(partes[3]);
            int id = stoi(partes[4]);
            Producto* produc = new Producto(nombreCategoria, nombreSubCategoria, precio, cantidad, id);
            bodega->insertar(id, produc);
        } else {
            cout << "Error: Datos incompletos en la línea del archivo de productos." << endl;
        }
    }
    archivo.close();
}



// Función que despliega el menú y da opciones para otros métodos
void menu(queue<Cliente*> clientesNormales, queue<Cliente*> clientesPreferenciales, queue<Cliente*> clientesPreferencialesOrdenados) {
    cout << "--- Bienvenido/a al Menú ---" << endl;
    int opcion = 0;
    string nombre;
    string nombreSub;
    int precio;
    int cantidad;
    int id = 0; 
    Producto* pro = nullptr; 
    int cantidadDeCompra;
    string nombreCliente;
    string edad;
    string preferencialidad;

    do {
        cout << "1. Cargar clientes (y organizar números)" << endl;
        cout << "2. Atender a siguiente cliente" << endl;
        cout << "3. Ingresar cliente a cola" << endl;
        cout << "4. Agregar producto a bodega" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: " << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                leerDatosClientesTxt(clientesNormales, clientesPreferenciales);
                ordenamientoPorPrioridad(clientesNormales, clientesPreferenciales, clientesPreferencialesOrdenados);
                mostrar(clientesPreferencialesOrdenados);
                break;
            case 2: // LEER LA COLA PARA QUE LA ATENCIÓN DE CLIENTES NO SEA INFINITA
                bodega->MostrarProductos();
                cout << "Ingrese la id del producto que desea comprar" << endl;
                cin >> id;
                cout << "El producto es: " << bodega->obtener(id)->getNombre() << " su precio es: " << bodega->obtener(id)->getPrecio() << endl;
                cout << "Ingrese la cantidad que desea comprar" << endl;
                cin >> cantidadDeCompra;
                if (bodega->obtener(id)->getCantidad() == 0) {
                    cout << "No hay más unidades" << endl;
                    break;
                } else if (bodega->obtener(id)->getCantidad() < cantidadDeCompra) {
                    cout << "¡Compraste todas las unidades que quedaban!" << endl;
                    int boleta = bodega->obtener(id)->getCantidad() * bodega->obtener(id)->getPrecio();
                    cout << "Total a pagar: " << boleta << endl;
                    bodega->obtener(id)->setCantidad(0);
                } else {
                    cout << "¡Compra realizada!" << endl;
                    int boleta = cantidadDeCompra * bodega->obtener(id)->getPrecio();
                    cout << "Total a pagar: " << boleta << endl;
                    bodega->obtener(id)->setCantidad(bodega->obtener(id)->getCantidad() - cantidadDeCompra);
                }
                break;
            case 3:
                cout << "Ingrese su nombre" << endl;
                cin >> nombreCliente;
                cout << "Ingrese su edad" << endl;
                cin >> edad;
                controlDeError(nombreCliente, edad, clientesNormales, clientesPreferencialesOrdenados);
                break;
            case 4:
                cout << "Ingrese el nombre del producto" << endl;
                cin >> nombre;
                cout << "Ingrese el nombre de la subcategoria" << endl;
                cin >> nombreSub;
                cout << "Ingrese el precio del producto" << endl;
                cin >> precio;
                cout << "Ingrese la cantidad que hay en la bodega" << endl;
                cin >> cantidad;
                id = bodega->AsignarID(); // ARREGLAR EL ID DEL PRODUCTO
                pro = new Producto(nombre, nombreSub, precio, cantidad, id);
                bodega->insertar(id, pro);
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción inválida, por favor intente nuevamente." << endl;
        }
    } while (opcion != 5);
}

// Función principal
int main() {
    queue<Cliente*> clientesNormales;
    queue<Cliente*> clientesPreferenciales;
    queue<Cliente*> clientesPreferencialesOrdenados;
    leerDatosProductosTxt();
    menu(clientesNormales, clientesPreferenciales, clientesPreferencialesOrdenados);

    return 0;
}
