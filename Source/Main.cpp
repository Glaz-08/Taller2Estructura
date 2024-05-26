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
HashMap* bodega = new HashMap();
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
//encuentra el numero mayor del stack
int encontrarMayor(queue<Cliente*> clientesPreferenciales) {
    int mayor = clientesPreferenciales.front()->getNumero();
    clientesPreferenciales.pop();
    
    // Recorremos la cola para encontrar el número mayor
    while (!clientesPreferenciales.empty()) {
        if (clientesPreferenciales.front()->getNumero()> mayor) {
            mayor = clientesPreferenciales.front()->getNumero();
        }
        clientesPreferenciales.pop();
    }
    
    return mayor;
}
//funcion para buscar el numero mayor del stack de clientes y sumarle 1 para que asi sea el numero mas reciente en llegar
//por lo que seria el ultimo en atenderse, pero eso depende de su preferencialidad
int darNumeroPreferencial(queue<Cliente*> clientesPreferenciales){

    return encontrarMayor(clientesPreferenciales)+1;

}
//funcion que convierte los textos a minusculas
void toLowerCase(std::string& texto) {
    std::transform(texto.begin(), texto.end(), texto.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
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
//control de error para cuando vayan a crear a una persona por su tipo de preferencialidad
void controlDeError(string nombreCliente,string edad,queue<Cliente*> clientesNormales, queue<Cliente*> clientesPreferencialesOrdenados){
    int opcion=0;
    int numero=0;
    string preferencialidad;
    std::string texto;
    string tipoDeDiscapacidad;
    do{
        cout<<"Ingrese alguno de los valores a continuacion:"<<endl;
        cout<<"1) si es Preferencial "<<endl;
        cout<<"2) si es Normal "<<endl;
        cin>>preferencialidad;
        texto=preferencialidad;
        toLowerCase(texto);//lo convierto a minusculas para comparar mejor
        cin>>opcion;
        switch(opcion) {
            case 1:
                cout<<"ingrese el tipo de Preferencialidad: Embarazada,Discapacidad,Tercera edad "<<endl;
                cout<<"escribalo tal cual como sale: Embarazada / Discapacidad / Tercera edad "<<endl;
                cin>>tipoDeDiscapacidad;
                numero = darNumeroPreferencial(clientesPreferencialesOrdenados);
                Cliente* clientePref = new ClientePreferencial(nombreCliente,edad,preferencialidad,tipoDeDiscapacidad,numero);
                opcion=3;
                break;
            case 2:
                numero = darNumeroPreferencial(clientesPreferencialesOrdenados);
                Cliente* clienteNorm = new ClienteNormal(nombreCliente,edad,preferencialidad,numero);
                opcion=3;
                break;
            default:
                cout<<"Opción incorrecta, por favor ingrese una opción válida"<<"\n"<<endl;
                cin.clear();
                cin.ignore();
        }
    }while(opcion != 3); 

}
//metodo para leer el archivo txt de productos y crear el objeto productos y almacenarlo en el hashmap
void leerDatosProductosTxt(){
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
        Producto* produc= new Producto(nombreCategoria,nombreSubCategoria,precio,cantidad,id);
        bodega->insertar(id,produc);


    }archivo.close();

}
//funcion que despliega el menu y da opciones para otros metodos
void menu(queue<Cliente*> clientesNormales, queue<Cliente*> clientesPreferenciales, queue<Cliente*> clientesPreferencialesOrdenados) {
    cout<<"--- Bienvenido/a al Menú ---"<<endl;
    int opcion = 0;
    string nombre;
    string nombreSub;
    int precio;
    int cantidad;
    int id;
    int cantidadDeCompra;
    string nombreCliente;
    string edad;
    string preferencialidad;
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
                bodega->MostrarProductos();
                cout<<" Ingrese la id del producto que desea comprar"<<endl;
                cin>>id;
                cout<<"El producto es:"<<bodega->obtener(id)->getNombre()<<"su precio es:"<<bodega->obtener(id)->getPrecio()<<endl;
                cout<<"ingese la cantidad que desea comprar"<<endl;
                cin>>cantidadDeCompra;
                if(bodega->obtener(id)->getCantidad()==0){
                    cout<<"No hay mas unidades"<<endl;
                    break;
                }
                else if(bodega->obtener(id)->getCantidad()<cantidadDeCompra){
                    cout<<"Compraste todas las unidades que quedaban!!"<<endl;
                    int boleta=bodega->obtener(id)->getCantidad()*bodega->obtener(id)->getPrecio();
                    cout<<"Total a pagar:"<<boleta<<endl;
                    bodega->obtener(id)->setCantidad(0);
                    break;
                }
                else{
                    int cantidadDespuesDeComprar= bodega->obtener(id)->getCantidad()-cantidadDeCompra;
                    int boleta=cantidadDeCompra*bodega->obtener(id)->getPrecio();
                    bodega->obtener(id)->setCantidad(cantidadDespuesDeComprar);
                    cout<<"Total a pagar:"<<boleta<<endl;
                }
                break;
            case 3:
                cout<<"Ingrese el nombre del cliente nuevo"<<endl;
                cin>>nombreCliente;
                cout<<"Ingrese la edad del cliente nuevo"<<endl;
                cin>>edad;
                controlDeError(nombreCliente,edad,clientesNormales,clientesPreferencialesOrdenados);
                ordenamientoPorPrioridad(clientesNormales,clientesPreferenciales,clientesPreferencialesOrdenados);
                //para ordenar denuevo con el cliente nuevo ya añadido
                break;
            case 4:
                cout<<"Bienvenido, para crear su producto necesitamos los siguientes datos: "<<endl;
                cout<<"ingrese el nombre de la categoria de su producto"<<endl;
                cin>>nombre;
                cout<<"ingrese el nombre de su sub categoria: "<<endl;
                cin>>nombreSub;
                cout<<"ingrese el precio del producto: "<<endl;
                cin>>precio;
                cout<<"ingrese la cantidad de producto "<<endl;
                cin>>cantidad;
                //la id se debderia asignar automaticamente
                int id= bodega->AsignarID();
                cout<<"La id que se le asigno a su producto, es la id: "<<id<<endl;
                Producto* pro = new Producto(nombre,nombreSub,precio,cantidad,id);
                bodega->insertar(id,pro);
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
    leerDatosProductosTxt();
    menu(clientesNormales,clientesPreferenciales,clientesPreferencialesOrdenados);
    
    return 0;
}