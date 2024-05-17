#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
// Función para leer datos desde un archivo de texto y cargarlos en los vectores de clientes
void leerDatosClientesTxt(vector<Cliente*>& clientes;){
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
            clientes.push_back(clientePref);
        }
        else{
            int numeroNorm = stoi(partes[4]);
            Cliente* clienteNorm = new ClienteNormal(nombre,edad,tipo,numeroNorm);
            clientes.push_back(clienteNorm);
        }

    }archivo.close();


}
// Función para leer datos desde un archivo de texto y cargarlos en los vectores de categorias
void leerDatosClientesTxt(vector<Categoria*>& categorias;){
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
        categorias.push_back(categoria);

    }archivo.close();

}




int main(){
    vector<Cliente*> clientes;
    vector<Categoria*> categorias;
    leerDatosClientesTxt(clientes);
    leerDatosClientesTxt(categorias)

    


    return 0;
}