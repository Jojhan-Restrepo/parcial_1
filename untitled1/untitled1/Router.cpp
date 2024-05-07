#include <iostream>
#include "Router.h"
#include <queue>
#include <climits>
#include <fstream>
#include <string>
#include <map>
using namespace std;
Router::Router(int id) : idRouter(id), distancia(INT_MAX), visitado(false) {}

//Constructor de la clase. El router se debe crear con su ID, y por defecto pone los miembros de la clase en esos valores
Router::~Router() {
    // Código para liberar recursos si es necesario
}
void Router::nuevoVecino(Router* vecino, int costo) {
    vecinos.emplace_back(vecino, costo); // en vez de push_back, porque construyo el elemento que es un par
}
void Router::eliminarVecino(Router* vecino, int costo) {
    for (auto it = vecinos.begin(); it != vecinos.end(); ++it) {
        if (it->first == vecino && it->second == costo) {
            vecinos.erase(it);
            return; // Terminar después de eliminar el primer vecino encontrado con el mismo vecino y costo
        }
    }
    // Si el vecino no se encontró, puedes imprimir un mensaje de error o tomar alguna acción adicional
    cout << "Vecino no encontrado" << endl;
}

void Router::confDistancia(int dist) {
    distancia = dist;
}

void Router::reinicio() {
    distancia = INT_MAX;
    visitado = false;
}

void escribirCharPorChar(const string& nomArchivo) { //Se pasa el nombre del archivo por referencia y se define como constante
    //todo esto para evitar que se cambie el valor y no se cree una copia de un string
    ofstream file(nomArchivo, ios::out | ios::app); // Se crea el archivo o se pone al final si ya existe
    if (!file.is_open()) {
        cerr << "Error abriendo archivo: " << nomArchivo << endl;
        return;
    }

    string text = "Esto es un texto de muestra y es escrito letra a letra. \n";
    for (char c : text) { //un for basado en rango, también se puede hacer con arreglos
        file.put(c); // Escritura
    }

    file.close();
    cout << "ok char" << endl;
}
void obtenerRouter(const string& nomArchivo, string router){

    ifstream file(nomArchivo); // Abre el archivo en modo lectura
    string linea_buscar = router; // La línea que quieres buscar

    if (file.is_open()) { // Verifica si el archivo se abrió correctamente
        string linea;
        bool encontrada = false;

        while (getline(file, linea)) { // Lee cada línea del archivo
            if (linea.find(linea_buscar) != string::npos) { // Comprueba si la línea contiene el texto buscado
                cout << "Router encontrado: " << linea << endl;
                encontrada = true;
                break; // Termina el bucle una vez que se encuentra la línea
            }
        }

        if (!encontrada) {
            cout << "El router no se encontró en el mapa" << endl;
        }

        file.close(); // Cierra el archivo después de usarlo
    } else {
        cerr << "No se pudo abrir el archivo." << endl; // Muestra un mensaje de error si no se puede abrir el archivo
    }

    return;
}
void escribirLineaporLinea(const string& nomArchivo) {
    ofstream file(nomArchivo, ios::out | ios::app); // Open file in append mode
    if (!file.is_open()) {
        cerr << "Error abriendo archivo: " << nomArchivo << endl;
        return;
    }

    // Texto específico a escribir en el archivo
    string textoEspecifico = "";

    file << textoEspecifico << endl; // Escribir el texto en el archivo

    file.close();
    cout << "El texto se ha escrito en el archivo correctamente." << endl;
}

void leerCharPorChar(const string& nomArchivo) {
    ifstream file(nomArchivo);
    if (!file.is_open()) {
        cerr << "Error abriendo archivo: " << nomArchivo << endl;
        return;
    }

    cout << "Leyendo char por char:" << endl;
    char c;
    while (file.get(c)) { // Read character by character
        cout << c;
    }

    file.close();
}

void leerLineaPorLinea(const string& nomArchivo) {
    ifstream file(nomArchivo);
    if (!file.is_open()) {
        cerr << "Error abriendo archivo: " << nomArchivo << endl;
        return;
    }

    cout << "Lectura linea por linea:" << endl;
    string linea;
    while (getline(file, linea)) { // Read line by line
        cout << linea << endl;
    }

    file.close();
}

void dijkstra(Router* fuente) {
    fuente->confDistancia(0); //(*fuente).confDistancia(0); es equivalente con dereferenciación

    std::priority_queue<std::pair<int, Router*>> pq; //es una cola que tiene un valor adicional(prioridad), el elemento con mayor prio se guarda al inicio
    pq.push({0, fuente});

    while (!pq.empty()) {
        Router* actual = pq.top().second; //Tomo el valor del router del primer elemento de la cola
        pq.pop();

        if (actual->visitado) continue;

        actual->visitado = true;

        for (auto& vec : actual->vecinos) { //leo los vecinos del router actual
            Router* sigRouter = vec.first; //vecinos es un vector de pares, el primero es un router
            int costoBorde = vec.second; //lo que cuesta el borde a ese primer vecino

            int nuevaDistancia = actual->distancia + costoBorde; //La distancia es un valor de la fuente al router
            if (nuevaDistancia < sigRouter->distancia) {
                sigRouter->confDistancia(nuevaDistancia);
                pq.push({-nuevaDistancia, sigRouter}); // lo guardo con una prioridad que garantice su lugar en la cola
            }
        }
    }
}
/*int damedistancia(){
    char lugardestino;
    int distanciacorta;
    cout<<"ingrese el lugar al que desea ir: "<<endl;
    cin>>lugardestino;
    cout<<"ingrese el lugar donde se encuentra: "<<endl;
    switch(lugardestino)
    case 'A':
    cout << "Seleccionaste la opción A" << endl;
    dijkstra(routers[desde]);
    distanciacorta = A.distancia;
    cout << "Distancia corta de A a B: " << distanciacorta << endl;
    break;
case 'B':
    cout << "Seleccionaste la opción B" << endl;
    dijkstra(routers[desde]);
    distanciacorta = B.distancia;
    cout << "Distancia corta de A a B: " << distanciacorta << endl;
    break;
case 'C':
    cout << "Seleccionaste la opción C" << endl;
    dijkstra(routers[desde]);
    distanciacorta = C.distancia;
    cout << "Distancia corta de A a B: " << distanciacorta << endl;
    break;
case 'D':
    cout << "Seleccionaste la opción D" << endl;
    dijkstra(routers[desde]);
    distanciacorta = D.distancia;
    cout << "Distancia corta de A a B: " << distanciacorta << endl;
    break;
default:
    cout << "Opción no válida" << endl;
    return distanciacorta;
}*/
void crearnuevoenrutador(const string& nomArchivo){
    int distanciacorta;
    bool bandera = true;
    Router A(0), B(1), C(2), D(3);
    A.nuevoVecino(&B, 2);
    A.nuevoVecino(&B, 3);
    //A.nuevoVecino(&C, 4);
    B.nuevoVecino(&C, 1);
    B.nuevoVecino(&D, 7);
    C.nuevoVecino(&D, 3);
    char desde, hacia;
    map<char, Router*> routers = {
        {'A', &A},
        {'B', &B},
        {'C', &C},
        {'D', &D}
    };
    int valor;
    ofstream file(nomArchivo, std::ios::out | std::ios::app); // Abre el archivo en modo de escritura (append)
    if (!file.is_open()) {
        cerr << "Error abriendo archivo: " << nomArchivo << endl;
        return;
    }
    while(bandera==true){
        int elegido;
        cout<<"escoge una opcion : "<<endl<<endl;
        cout<<"1. ¿quieres saber alguna distancia especifica?"<<endl;
        cout<<"2. eliminar algun enrutador o router "<<endl;
        cout<<"3. cambiar tabla de algun router "<<endl;
        cout<<"4. agregar enrutadores "<<endl;
        cout<<"5. Salir del menu: ";
        cout<<"---------------------------------------"<<endl<<endl<<endl<<endl;
        cin>>elegido;
        switch (elegido) {
        case 1:{
            cout << "Ingrese el lugar de origen de su paquete "<<endl;
            cin >> desde;
            cout << "Ingrese el lugar hacia donde quiere ir: ";
            cin >> hacia;
            dijkstra(routers[desde]);
            switch (hacia) {
            case 'A':{
                dijkstra(routers[desde]);
                distanciacorta = A.distancia;
                cout << "Distancia de "<<desde <<" a " <<hacia<<" ES : "<< distanciacorta << endl;
                break;
            }
            case 'B':{               
                dijkstra(routers[desde]);
                distanciacorta = B.distancia;
                cout << "Distancia corta de "<<desde <<" a " <<hacia<<" ES : "<< distanciacorta << endl;
                B.reinicio();
                B.confDistancia(distanciacorta);
                break;
            }
            case 'C':{
                dijkstra(routers[desde]);
                distanciacorta = C.distancia;
                cout << "Distancia corta de "<<desde <<" a " <<hacia<<" ES : "<< distanciacorta << endl;
                break;
            }
            case 'D':{
                dijkstra(routers[desde]);
                distanciacorta = D.distancia;
                cout << "Distancia corta de "<<desde <<" a " <<hacia<<" ES : "<< distanciacorta << endl;
                break;
            }
            }}
        case 2:{
            int router;
            char lugarperteneciente,haciadondeva;
            int costoida;
            int opcion;
            cout<<"ingrese si quiere eliminar"<<endl<<"1.Router "<<endl<<"2.Enrutador"<<endl;
            cout<<"ingrese 3 para salir : ";
            cin>>opcion;
            switch(opcion){
            case 1:{
                cout<<"ingrese el id del router que desea eliminar"<<endl;
                cin>>router;
                if(router<4){
                    A.~Router();
                    cout<<"se ha eliminado con exito";
                    break;
                }
            }
            case 2:{
                cout << "Ingrese el router del que pertenece su enrutador : ";
                cin>>lugarperteneciente;
                cout<< "ingrese hacia aque vecino iba su enrutador :";
                cin>>haciadondeva;
                cout<<" ingrese el costo de ida de su respectivo enrutador: ";
                cin>>costoida;
                switch(lugarperteneciente){
                case 'A':{
                    A.eliminarVecino(routers[haciadondeva],costoida);
                    break;
                }
                case 'B':{
                    B.eliminarVecino(routers[haciadondeva],costoida);
                    break;
                }
                case 'C':{
                    C.eliminarVecino(routers[haciadondeva],costoida);
                    break;
                }
                case 'D':{
                    D.eliminarVecino(routers[haciadondeva],costoida);
                    break;
                }
                }
            }
            case 3:{
                cout<<"ha salido"<<endl;
                break;
            }
            }
        }

        case 3:{
            break;
        }
        case 4:{
            cout << "Seleccionaste la opción 4" << endl<<endl;
            cout << "Ingrese el lugar de origen si desea agregar un enrutador: "<<endl;
            cout<<"de lo contrario marque X para salir."<<endl;
            cin >> desde;
            if(desde== 'X' ){
                cout<<"ha salido --";
                bandera=false;
                break;
            }
            cout << "Ingrese el lugar hacia donde quiere ir: ";
            cin >> hacia;
            cout << "Ingrese el valor del costo de ida hacia el lugar: ";
            cin >> valor;
            //dijkstra(routers[desde]);
            switch (desde) {
            case 'A':{
                cout << "Seleccionaste la opción A" << endl;
                A.nuevoVecino(routers[hacia], valor);
                dijkstra(routers[desde]);
                //Escribir el nuevo enrutador en el archivo
                file <<endl<< desde << ".nuevoVecino" <<"(&" << hacia << "," << valor <<")" << std::endl;
                file.close();
                std::cout << "El nuevo enrutador se ha escrito en el archivo correctamente." << std::endl;
                distanciacorta = B.distancia;
                cout << "Distancia corta de "<<desde <<" a " <<hacia<<" ES : "<< distanciacorta << endl;
                break;
            }
            case 'B':{
                cout << "Seleccionaste la opción B" << endl;
                B.nuevoVecino(routers[hacia], valor);
                //Escribir el nuevo enrutador en el archivo
                file <<endl<< desde << ".nuevoVecino" <<"(&" << hacia << "," << valor <<")" << std::endl;
                file.close();
                std::cout << "El nuevo enrutador se ha escrito en el archivo correctamente." << std::endl;
            }
            case 'C':{
                cout << "Seleccionaste la opción C" << endl;
                C.nuevoVecino(routers[hacia], valor);
                //Escribir el nuevo enrutador en el archivo
                file <<endl<< desde << ".nuevoVecino" <<"(&" << hacia << "," << valor <<")" << std::endl;
                file.close();
                std::cout << "El nuevo enrutador se ha escrito en el archivo correctamente." << std::endl;
            }
            case 'D':{
                cout << "Seleccionaste la opción D" << endl;
                D.nuevoVecino(routers[hacia], valor);
                //Escribir el nuevo enrutador en el archivo
                file <<endl<< desde << ".nuevoVecino" <<"(&" << hacia << "," << valor <<")" << std::endl;
                file.close();
                std::cout << "El nuevo enrutador se ha escrito en el archivo correctamente." << std::endl;
            }
            }
        }
        while(elegido==5){
            cout<<"ha salido ...";
            bandera=false;
            break;
            }
        }}}
void eliminarenrutador(){
    int router;
    int identificacion;
    char lugarperteneciente,haciadondeva;
    int costoida;
    Router A(0), B(1), C(2), D(3);
    A.nuevoVecino(&B, 2);
    A.nuevoVecino(&B, 3);
    A.nuevoVecino(&C, 4);
    B.nuevoVecino(&C, 1);
    B.nuevoVecino(&D, 7);
    C.nuevoVecino(&D, 3);
    map<char, Router*> routers = {
        {'A', &A},
        {'B', &B},
        {'C', &C},
        {'D', &D}
    };
    int opcion;
    cout<<"ingrese si quiere eliminar"<<endl<<"1.Router "<<endl<<"2.Enrutador"<<endl;
    cout<<"ingrese 3 para salir : ";
    cin>>opcion;
    switch(opcion){
    case 1:{
        cout<<"ingrese el id del router que desea eliminar"<<endl;
        cin>>router;
        if(router<4){
            A.~Router();
            cout<<"se ha eliminado con exito";
            break;
        }
        }
    case 2:{
        cout << "Ingrese el router del que pertenece su enrutador : ";
        cin>>lugarperteneciente;
        cout<< "ingrese hacia aque vecino iba su enrutador :";
        cin>>haciadondeva;
        cout<<" ingrese el costo de ida de su respectivo enrutador: ";
        cin>>costoida;
        switch(lugarperteneciente){
        case 'A':{
            A.eliminarVecino(routers[haciadondeva],costoida);
            break;
        }
        case 'B':{
            B.eliminarVecino(routers[haciadondeva],costoida);
            break;
        }
        case 'C':{
            C.eliminarVecino(routers[haciadondeva],costoida);
            break;
        }
        case 'D':{
            D.eliminarVecino(routers[haciadondeva],costoida);
            break;
        }
        }
    }
    case 3:{
        cout<<"ha salido"<<endl;
        break;
    }
    }
}
void menu(){
    cout<<"Escoja entre las siguientes opciones"<<endl<<endl;
    cout<<"1: Agregar enrutadores "<<endl;
    cout<<"-- Eliminar enrutadores "<<endl;
    cout<<"-- Modificar tabla de algun enrutador "<<endl;
    cout<<"-- Saber cuanto cuesta envier un paquete a cierta ubicacion"<<endl;
    cout<<"2: Saber el camino correcto para que un paquete llegue bien"<<endl;
    cout<<"3: Salir del menu :"<<endl<<endl;
}

