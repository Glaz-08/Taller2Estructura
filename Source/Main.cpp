#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include "Cliente.h"
#include "Categoria.h"
#include "ClientePreferencial.h"
#include "ClienteNormal.h"
#include "SubCategoria.h"

using namespace std;

vector<string> split(const string& str, char delim) {
    vector<string> tokens;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }

    return tokens;
}

// Función para leer datos desde un archivo de texto y cargarlos en los vectores de clientes
void leerDatosClientesTxt(queue<Cliente*>& clientesNormales,queue<Cliente*>& clientesPreferenciales){
    string linea;
    ifstream archivo("Clientes.txt");  
    char delimitador = ',';
    while(getline(archivo,linea)) {
        vector<string> partes = split(linea, delimitador); 
        string nombre= partes[0];
        string edad= partes[1];
        string tipo = partes[2];
        if(tipo=="Preferencial"){
            string tipoPrioridad=partes[3];
            int numero = stoi(partes[4]);
            Cliente* clientePref = new ClientePreferencial(nombre,edad,tipo,tipoPrioridad,numero);
            if(clientePref->getTipode()=="Tercera edad"){
                //clientePref->setNumeroPreferencia(3);
                //los tercera edad tendran un numero 3 para hacer una mejor comparacion
            }
            else if(clientePref->getTipode()=="Embarazada"){
                //clientePref->setNumeroPreferencia(1);
                //las embarazadas tendran un numero 1 para hacer una mejor comparacion
            }
             else if(clientePref->getTipode()=="Discapacidad"){
                //clientePref->setNumeroPreferencia(2);
                //discapacidad tendran un numero 2 para hacer una mejor comparacion
            }
            clientesPreferenciales.push(clientePref);
            clientePref = nullptr;
            delete(clientePref);
        }
        else{
            int numeroNorm = stoi(partes[3]);
            Cliente* clienteNorm = new ClienteNormal(nombre,edad,tipo,numeroNorm);
            clientesNormales.push(clienteNorm);
            clienteNorm = nullptr;
            delete(clienteNorm);
        }
    }archivo.close();
}

//funcion para hacer el ordenamiento de la fila prioritaria y fila normanl
void ordenamientoPorPrioridad(queue<Cliente*>& clientesNormales, queue<Cliente*>& ClientesPreferenciales, queue<Cliente*>& clientesPreferencialesOrdenados){
    queue<Cliente*> auxiliarTerceraEdad, auxiliarEmbarazada, auxiliarDiscapacitado;
    
    //hacer ciclo para buscar el numero menor de cada tipo embarazada,discapacitado,tercera edad.
    while (!ClientesPreferenciales.empty()) {
        if(ClientesPreferenciales.front()->getTipode()=="Tercera edad"){
            auxiliarTerceraEdad.push(ClientesPreferenciales.front());
            ClientesPreferenciales.pop();
        }
       else if(ClientesPreferenciales.front()->getTipode()=="Embarazada"){
            auxiliarEmbarazada.push(ClientesPreferenciales.front());
            ClientesPreferenciales.pop();
        }
        else if(ClientesPreferenciales.front()->getTipode()=="Discapacidad"){
            auxiliarDiscapacitado.push(ClientesPreferenciales.front());
            ClientesPreferenciales.pop();
        }
    }

    //ordenar cola general de prioridades por tipo de prioridad de los clientes
    int contador = 1;
    Cliente* aux;
    while(!auxiliarTerceraEdad.empty()) {
        aux = auxiliarTerceraEdad.front();
        aux->setNumero(contador);
        clientesPreferencialesOrdenados.push(aux);
        auxiliarTerceraEdad.pop();
        contador++;
    }
    while(!auxiliarDiscapacitado.empty()) {
        aux = auxiliarDiscapacitado.front();
        aux->setNumero(contador);
        clientesPreferencialesOrdenados.push(aux);
        auxiliarDiscapacitado.pop();
        contador++;
    }
    while(!auxiliarEmbarazada.empty()) {
        aux = auxiliarEmbarazada.front();
        aux->setNumero(contador);
        clientesPreferencialesOrdenados.push(aux);
        auxiliarEmbarazada.pop();
        contador++;
    }
    while(!clientesNormales.empty()) {
        aux = clientesNormales.front();
        aux->setNumero(contador);
        clientesPreferencialesOrdenados.push(aux);
        clientesNormales.pop();
        contador++;
    }
    aux = nullptr;
    delete(aux);
}

void mostrar(queue<Cliente*>& clientesPreferencialesOrdenados){
    while (!clientesPreferencialesOrdenados.empty()){
        cout << "Atendiendo al numero: " << clientesPreferencialesOrdenados.front()->getTipode()<<" "<< clientesPreferencialesOrdenados.front()->getNumero() << endl;
        clientesPreferencialesOrdenados.pop();
    }

}

void menu(queue<Cliente*> clientesNormales, queue<Cliente*> clientesPreferenciales, queue<Cliente*> clientesPreferencialesOrdenados) {
    cout<<"--- Bienvenido/a al Menú ---"<<endl;
    int opcion = 0;
    do {
        cout<<"1. Cargar clientes (y organizar números)"<<endl;
        cout<<"2. Atender a siguiente cliente"<<endl;
        cout<<"3. Ingresar cliente a cola"<<endl;
        cout<<"4. Agregar producto a bodega"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"Seleccione una opción: "<<endl;
        cin>>opcion;
        switch(opcion) {
            case 1:
                leerDatosClientesTxt(clientesNormales,clientesPreferenciales);
                ordenamientoPorPrioridad(clientesNormales,clientesPreferenciales,clientesPreferencialesOrdenados);
                mostrar(clientesPreferencialesOrdenados);     
                break;
            case 2:
                
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
                cout<<"Saliendo..."<<endl;
                break;
            default:
                cout<<"Opción incorrecta, por favor ingrese una opción válida"<<"\n"<<endl;
                cin.clear();
                cin.ignore();
        }
    } while(opcion != 5);    
}

int main(){
    queue<Cliente*> clientesNormales, clientesPreferenciales, clientesPreferencialesOrdenados;
    queue<Categoria*> categorias;
    menu(clientesNormales,clientesPreferenciales,clientesPreferencialesOrdenados);
    
    return 0;
}