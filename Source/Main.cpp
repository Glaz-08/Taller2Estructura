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
            ClientePreferencial* clientePref = new ClientePreferencial(nombre,edad,tipo,tipoPrioridad,numero);
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
            int numeroNorm = stoi(partes[3]);
            ClienteNormal* clienteNorm = new ClienteNormal(nombre,edad,tipo,numeroNorm);
            clientesNormales.push(clienteNorm);
            auxiliarNormales.push(clienteNorm);
        }
    }archivo.close();
}
// Función para leer datos desde un archivo de texto y cargarlos en los vectores de categorias

//funcion para hacer el ordenamiento de la fila prioritaria y fila normanl
queue<Cliente*> ordenamientoPorPrioridad(queue<Cliente*>& clientesNormales,queue<Cliente*>& ClientesPreferenciales,queue<Cliente*>& auxiliarPreferenciales,queue<Cliente*>& auxiliarNormales){
    queue<Cliente*> prioridades;
    int numeroMenorPreferenciales=0;
    int numeroMenorNormales=0;
    queue<Cliente*> auxiliarTerceraEdad;
    queue<Cliente*> auxiliarTerceraEdadDos;
    queue<Cliente*> auxiliarEmbarazada;
    queue<Cliente*> auxiliarEmbarazadaDos;
    queue<Cliente*> auxiliarDiscapacitado;
    queue<Cliente*> auxiliarDiscapacitadoDos;
    queue<Cliente*> auxiliarNormalesDos;
    auxiliarPreferenciales.pop();
    auxiliarNormales.pop();
    //hacer ciclo para buscar el numero menor de cada tipo embarazada,discapacitado,tercera edad.
    while (!ClientesPreferenciales.empty()) {
        if(ClientesPreferenciales.front()->getTipo()=="Tercera edad"){
            auxiliarTerceraEdad.push(ClientesPreferenciales.front());
            ClientesPreferenciales.pop();
        }
       else if(ClientesPreferenciales.front()->getTipo()=="Embarazada"){
            auxiliarEmbarazada.push(ClientesPreferenciales.front());
            ClientesPreferenciales.pop();
        }
        else if(ClientesPreferenciales.front()->getTipo()=="Discapacidad"){
            auxiliarDiscapacitado.push(ClientesPreferenciales.front());
            ClientesPreferenciales.pop();
        }
        else if(ClientesPreferenciales.front()->getTipo()=="Normal"){
            clientesNormales.push(ClientesPreferenciales.front());
            ClientesPreferenciales.pop();
        }
    }
    //para asi despues buscar al menor numero de cada tipo y meterlo a la cola de prioridades
    std::vector<int> menoresTerceraEdad;
    while (!auxiliarTerceraEdad.empty()){
        menoresTerceraEdad.push_back(auxiliarTerceraEdad.front()->getNumero());
        auxiliarTerceraEdadDos.push(auxiliarTerceraEdad.front());
        auxiliarTerceraEdad.pop();
    }
    //rellene la lista con los valores de numeros ordenados, donde posteriormente la lleno denuevo para buscar los numeros
    std::sort(menoresTerceraEdad.begin(), menoresTerceraEdad.end());//ordena los numeros de menor a mayor
    for(int i=0;i<menoresTerceraEdad.size();i++){
        while(!auxiliarTerceraEdadDos.empty()){
            if(auxiliarTerceraEdadDos.front()->getNumero()==menoresTerceraEdad[i]){
                prioridades.push(auxiliarTerceraEdadDos.front());
                auxiliarTerceraEdadDos.pop();
                break;
            }

        }
    }
    //se repite lo mismo pero con Discapacitados
    std::vector<int> menoresDiscapacitados;
    while (!auxiliarDiscapacitado.empty()){
        menoresDiscapacitados.push_back(auxiliarDiscapacitado.front()->getNumero());
        auxiliarDiscapacitadoDos.push(auxiliarDiscapacitado.front());
        auxiliarDiscapacitado.pop();
    }//rellene la lista con los valores de numeros ordenados, donde posteriormente la lleno denuevo para buscar los numeros
    std::sort(menoresDiscapacitados.begin(), menoresDiscapacitados.end());//ordena los numeros de menor a mayor
    for(int i=0;i<menoresDiscapacitados.size();i++){
        while(!auxiliarDiscapacitadoDos.empty()){
            if(auxiliarDiscapacitadoDos.front()->getNumero()==menoresDiscapacitados[i]){
                prioridades.push(auxiliarDiscapacitadoDos.front());
                auxiliarDiscapacitadoDos.pop();
                break;
            }

        }
    }
    //se repite con embarazadas
    std::vector<int> menoresEmbarazadas;
    while (!auxiliarEmbarazada.empty()){
        menoresEmbarazadas.push_back(auxiliarEmbarazada.front()->getNumero());
        auxiliarEmbarazadaDos.push(auxiliarEmbarazada.front());
        auxiliarEmbarazada.pop();
    }//rellene la lista con los valores de numeros ordenados, donde posteriormente la lleno denuevo para buscar los numeros
    std::sort(menoresEmbarazadas.begin(), menoresEmbarazadas.end());//ordena los numeros de menor a mayor
    for(int i=0;i<menoresEmbarazadas.size();i++){
        while(!auxiliarEmbarazadaDos.empty()){
            if(auxiliarEmbarazadaDos.front()->getNumero()==menoresEmbarazadas[i]){
                prioridades.push(auxiliarEmbarazadaDos.front());
                auxiliarEmbarazadaDos.pop();
                break;
            }

        }
    }
    //ahora con personasNormales
    std::vector<int> menoresNormales;
    while (!clientesNormales.empty()){
        menoresNormales.push_back(clientesNormales.front()->getNumero());
        auxiliarNormalesDos.push(clientesNormales.front());
        clientesNormales.pop();
    }//rellene la lista con los valores de numeros ordenados, donde posteriormente la lleno denuevo para buscar los numeros
    std::sort(menoresNormales.begin(), menoresNormales.end());//ordena los numeros de menor a mayor
    for(int i=0;i<menoresNormales.size();i++){
        while(!auxiliarNormalesDos.empty()){
            if(auxiliarNormalesDos.front()->getNumero()==menoresNormales[i]){
                prioridades.push(auxiliarNormalesDos.front());
                auxiliarNormalesDos.pop();
                break;
            }

        }
        //ahora todo esta en orden en la cola llamada "prioridades"
    }

    return prioridades;
}

void mostrar(queue<Cliente*>& prioridades){
    cout<<"asdads"<<endl;
    while (!prioridades.empty()){
        cout << "Atendiendo al numero: " << prioridades.front()->getNumero() << endl;
        prioridades.pop();
    }

}



int main(){
    queue<Cliente*> clientesNormales;
    queue<Cliente*> auxiliarNormales;
    queue<Cliente*> clientesPreferenciales;
    queue<Cliente*> auxiliarPreferenciales;
    queue<Categoria*> categorias;
    leerDatosClientesTxt(clientesNormales,clientesPreferenciales,auxiliarPreferenciales,auxiliarNormales);
    queue<Cliente*> prioridades = ordenamientoPorPrioridad(clientesNormales,clientesPreferenciales,auxiliarPreferenciales,auxiliarNormales);
    mostrar(prioridades);
    
    return 0;
}