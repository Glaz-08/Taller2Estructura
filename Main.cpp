#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>

using namespace std;
// Función para leer datos desde un archivo de texto y cargarlos en los vectores de clientes
void leerDatosClientesTxt(queue<Cliente*>& clientes,queue<Cliente*>& auxiliar){
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
            clientes.push(clientePref);
            auxiliar.push(clientePref);
        }
        else{
            int numeroNorm = stoi(partes[4]);
            Cliente* clienteNorm = new ClienteNormal(nombre,edad,tipo,numeroNorm);
            clientes.push(clienteNorm);
            auxiliar.push(clienteNorm);
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
void ordenamientoPorPrioridad(queue<Cliente*>& clientes,queue<Cliente*>& prioridades,queue<Cliente*>& auxiliar){
    int numeroMenor=0;
    queue<Cliente*>& auxiliar2;
    while (!clientes.empty()) {
        while (!auxiliar.empty()){

            if(clientes.top()->getTipo()=="Preferencial"){

                if(auxiliar.top()->getTipo()=="Preferencial"){
                    if(clientes.top().getNumero()>=auxiliar.top()){
                        numeroMenor=auxiliar.top()->getNumero();
                        auxiliar2.push(auxiliar.top());
                        auxiliar.pop();

                    }
                    else{
                        auxiliar2.push(auxiliar.top());
                        auxiliar.pop();
                    }

                }
            }

        }
        while (!clientes.empty()){
            if(clientes.top()->getNumero()==numeroMenor){
                 prioridades.push(clientes.top());
            }
        }
        while (!auxiliar2.empty()){
            auxiliar.push(auxiliar2.top());
            auxiliar2.pop();
        }
    }
}
void mostrar(queue<Cliente*>& prioridades;){
    while (!prioridades.empty()){
        cout << "Atendiendo a: " << cliente->getNumero() << endl;

    }

}



int main(){
    queue<Cliente*> clientes;
    queue<Categoria*> categorias;
    queue<Cliente*> prioridades;
    queue<Cliente*> auxiliar;
    leerDatosClientesTxt(clientes,auxiliar);
    leerDatosClientesTxt(categorias);
    ordenamientoPorPrioridad(clientes,prioridades,auxiliar);
    mostrar(prioridades);


    


    return 0;
}