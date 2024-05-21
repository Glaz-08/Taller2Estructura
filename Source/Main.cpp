#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include "Cliente.h"
#include "Categoria.h"
#include "ClientePreferencial.h"
#include "ClienteNormal.h"
#include "SubCategoria.h"

using namespace std;
// Función para leer datos desde un archivo de texto y cargarlos en los vectores de clientes
void leerDatosClientesTxt(queue<Cliente*>& clientesNormales,queue<Cliente*>& clientesPreferenciales,queue<Cliente*>& auxiliarPreferenciales,queue<Cliente*>& auxiliarNormales){
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
                clientePref->setNumeroPreferencia(3);
                //los tercera edad tendran un numero 3 para hacer una mejor comparacion
            }
            else if(clientePref->getTipode()=="Embarazada"){
                clientePref->setNumeroPreferencia(1);
                //las embarazadas tendran un numero 1 para hacer una mejor comparacion
            }
             else if(clientePref->getTipode()=="Discapacidad"){
                clientePref->setNumeroPreferencia(2);
                //discapacidad tendran un numero 2 para hacer una mejor comparacion
            }
            clientesPreferenciales.push(clientePref);
            auxiliarPreferenciales.push(clientePref);
        }
        else{
            int numeroNorm = stoi(partes[4]);
            Cliente* clienteNorm = new ClienteNormal(nombre,edad,tipo,numeroNorm);
            clientesNormales.push(clienteNorm);
            auxiliarNormales.push(clienteNorm);
        }

    }archivo.close();


}
// Función para leer datos desde un archivo de texto y cargarlos en los vectores de categorias
void leerDatosClientesTxt(queue<Categoria*>& categorias){
    string linea;
    ifstream archivo("Productos.txt");  
    char delimitador = ',';
    while(getline(archivo,linea)) {
        vector<string> partes = split(linea, delimitador); 
        string nombreCategoria= partes[0];
        string nombreSubCategoria= partes[1];
        int precio=stoi(partes[2]);
        int cantidad=stoi(partes[3]);
        int id=stoi(partes[4]);
        categoria* categoria= new SubCategoria(nombreCategoria,nombreSubCategoria,precio,cantidad,id);
        categorias.push(categoria);

    }archivo.close();

}
//funcion para hacer el ordenamiento de la fila prioritaria y fila normanl
void ordenamientoPorPrioridad(queue<Cliente*>& clientesNormales,queue<Cliente*>& prioridades,queue<Cliente*>& ClientesPreferenciales,queue<Cliente*>& auxiliarPreferenciales,queue<Cliente*>& auxiliarNormales){
    int numeroMenorPreferenciales=0;
    int numeroMenorNormales=0;
    queue<Cliente*>& auxiliar2;
    auxiliarPreferenciales.pop();
    auxiliarNormales.pop();
    //hacer ciclo para buscar el numero menor de cada tipo embarazada,discapacitado,tercera edad.
    //para haci despues buscar al menor numero de cada tipo y meterlo a la cola de prioridades
    
    while (!ClientesPreferenciales.empty()) {
        while (!auxiliarPreferenciales.empty()){
            //con getNumeroPreferencial solo hago 3 comparaciones,con la manera de string hacia casi 8
            if(ClientesPreferenciales.front()->getNumeroPreferencia()==auxiliarPreferenciales.front()->getNumeroPreferencia()){
                // los dos tienen el mismo tipo de preferencialidad
                int numeroMenor=0;
                while (!ClientesPreferenciales.empty()){
                    if (ClientesPreferenciales.front()->getNumero() < numeroMenor) {
                         numeroMenor = ClientesPreferenciales.front()->getNumero();
                         clienteMenor = numeroMenorPreferenciales;
                     }
                }//fin del while que busca el numero menor de la misma preferencialidad
                
            }

        }
        

        
    }
}
void mostrar(queue<Cliente*>& prioridades;){
    while (!prioridades.empty()){
        cout << "Atendiendo al numero: " << cliente.front()->getNumero() << endl;

    }

}



int main(){
    queue<Cliente*> clientesNormales;
    queue<Cliente*> auxiliarNormales;
    queue<Cliente*> prioridades;
    queue<Cliente*> clientesPreferenciales;
    queue<Cliente*> auxiliarPreferenciales;
    queue<Categoria*> categorias;
    leerDatosClientesTxt(clientesNormales,clientesPreferenciales,auxiliarPreferenciales,auxiliarNormales);
    leerDatosClientesTxt(categorias);
    ordenamientoPorPrioridad(clientesNormales,prioridades,clientesPreferenciales,auxiliarPreferenciales,auxiliarNormales);
    mostrar(prioridades);


    


    return 0;
}