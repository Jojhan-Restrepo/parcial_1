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

void reiniciarRouters(map<char, Router*>& routers) {
    for (auto& routerPair : routers) {
        routerPair.second->reinicio();
    }
}

void dijkstra(Router* fuente, map<char, Router*>& routers) {
    reiniciarRouters(routers); // Asegúrate de reiniciar los routers antes de ejecutar Dijkstra
    fuente->confDistancia(0);

    priority_queue<pair<int, Router*>> pq;
    pq.push({0, fuente});

    while (!pq.empty()) {
        Router* actual = pq.top().second;
        pq.pop();

        if (actual->visitado) continue;

        actual->visitado = true;

        for (auto& vec : actual->vecinos) {
            Router* sigRouter = vec.first;
            int costoBorde = vec.second;

            int nuevaDistancia = actual->distancia + costoBorde;
            if (nuevaDistancia < sigRouter->distancia) {
                sigRouter->confDistancia(nuevaDistancia);
                pq.push({-nuevaDistancia, sigRouter});
            }
        }
    }
}
void eliminarVecino(Router* router, Router* vecino, int costo) {
    router->eliminarVecino(vecino, costo);
}

void eliminarEnrutador(map<char, Router*>& routers, char routerID, char vecinoID, int costo) {
    Router* router = routers[routerID];
    Router* vecino = routers[vecinoID];
    eliminarVecino(router, vecino, costo);
}

void eliminarenrutador(map<char, Router*>& routers) {
    int opcion;
    cout << "Ingrese si quiere eliminar" << endl << "1. Router " << endl << "2. Enrutador" << endl;
    cout << "Ingrese 3 para salir: ";
    cin >> opcion;

    switch (opcion) {
    case 1: {
        int routerID;
        cout << "Ingrese el ID del router que desea eliminar: ";
        cin >> routerID;
        if (routerID < 4) {
            routers.erase(routerID);
            cout << "Se ha eliminado con éxito" << endl;
        }
        break;
    }
    case 2: {
        char lugarperteneciente, haciadondeva;
        int costoida;
        cout << "Ingrese el router del que pertenece su enrutador: ";
        cin >> lugarperteneciente;
        cout << "Ingrese hacia qué vecino iba su enrutador: ";
        cin >> haciadondeva;
        cout << "Ingrese el costo de ida de su respectivo enrutador: ";
        cin >> costoida;
        eliminarEnrutador(routers, lugarperteneciente, haciadondeva, costoida);
        break;
    }
    case 3:
        cout << "Ha salido" << endl;
        break;
    default:
        cout << "Opción no válida" << endl;
        break;
    }
}
void crearnuevoenrutador(const string& nomArchivo) {
    int distanciacorta;
    bool bandera = true;
    Router A(0), B(1), C(2), D(3);
    A.nuevoVecino(&B, 2);
    A.nuevoVecino(&B, 3);
    B.nuevoVecino(&C, 1);
    B.nuevoVecino(&D, 7);
    C.nuevoVecino(&D, 3);
    D.nuevoVecino(&A, 2);
    D.nuevoVecino(&B, 0);
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
    while (bandera == true) {
        int elegido;
        cout << "Escoge una opción: " << endl << endl;
        cout << "1. ¿Quieres saber alguna distancia específica?" << endl;
        cout << "2. Eliminar algún enrutador o router" << endl;
        cout << "3. Cambiar tabla de algún router" << endl;
        cout << "4. Agregar enrutadores" << endl;
        cout << "5. Salir del menú" << endl;
        cout << "---------------------------------------" << endl << endl << endl << endl;
        cin >> elegido;
        switch (elegido) {
        case 1: {
            cout << "Ingrese el lugar de origen de su paquete: " << endl;
            cin >> desde;
            cout << "Ingrese el lugar hacia donde quiere ir: ";
            cin >> hacia;
            dijkstra(routers[desde], routers);
            switch (hacia) {
            case 'A': {
                distanciacorta = A.distancia;
                cout << "Distancia de " << desde << " a " << hacia << " ES: " << distanciacorta << endl;
                break;
            }
            case 'B': {
                distanciacorta = B.distancia;
                cout << "Distancia corta de " << desde << " a " << hacia << " ES: " << distanciacorta << endl;
                break;
            }
            case 'C': {
                distanciacorta = C.distancia;
                cout << "Distancia corta de " << desde << " a " << hacia << " ES: " << distanciacorta << endl;
                break;
            }
            case 'D': {
                distanciacorta = D.distancia;
                cout << "Distancia corta de " << desde << " a " << hacia << " ES: " << distanciacorta << endl;
                break;
            }
            default:
                cout << "Opción no válida" << endl;
                break;
            }
            break;
        }
        case 2: {
            eliminarenrutador(routers);
            break;
        }
        case 3:{
            break;
        }
        case 4: {
            cout << "Seleccionaste la opción 4" << endl << endl;
            cout << "Ingrese el lugar de origen si desea agregar un enrutador: " << endl;
            cout << "De lo contrario marque X para salir." << endl;
            cin >> desde;
            if (desde == 'X') {
                cout << "Ha salido --";
                bandera = false;
                break;
            }
            cout << "Ingrese el lugar hacia donde quiere ir: ";
            cin >> hacia;
            cout << "Ingrese el valor del costo de ida hacia el lugar: ";
            cin >> valor;
            switch (desde) {
            case 'A': {
                cout << "Seleccionaste la opción A" << endl;
                A.nuevoVecino(routers[hacia], valor);
                file << endl << desde << ".nuevoVecino" << "(&" << hacia << "," << valor << ")" << std::endl;
                cout << "El nuevo enrutador se ha escrito en el archivo correctamente." << endl;
                break;
            }
            case 'B': {
                cout << "Seleccionaste la opción B" << endl;
                B.nuevoVecino(routers[hacia], valor);
                file << endl << desde << ".nuevoVecino" << "(&" << hacia << "," << valor << ")" << std::endl;
                cout << "El nuevo enrutador se ha escrito en el archivo correctamente." << endl;
                break;
            }
            case 'C': {
                cout << "Seleccionaste la opción C" << endl;
                C.nuevoVecino(routers[hacia], valor);
                file << endl << desde << ".nuevoVecino" << "(&" << hacia << "," << valor << ")" << std::endl;
                cout << "El nuevo enrutador se ha escrito en el archivo correctamente." << endl;
                break;
            }
            case 'D': {
                cout << "Seleccionaste la opción D" << endl;
                D.nuevoVecino(routers[hacia], valor);
                file << endl << desde << ".nuevoVecino" << "(&" << hacia << "," << valor << ")" << std::endl;
                cout << "El nuevo enrutador se ha escrito en el archivo correctamente." << endl;
                break;
            }
            default:
                cout << "Opción no válida" << endl;
                break;
            }
            break;
        }
        case 5: {
            cout << "Ha salido del menú" << endl;
            bandera = false;
            break;
        }
        default:
            cout << "Opción no válida" << endl;
            break;


        file.close(); // Cierra el archivo al finalizar
        }}}
/*void eliminarenrutador(){
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
}*/
void menu(){
    cout<<"Escoja entre las siguientes opciones"<<endl<<endl;
    cout<<"1: Agregar enrutadores "<<endl;
    cout<<"-- Eliminar enrutadores "<<endl;
    cout<<"-- Modificar tabla de algun enrutador "<<endl;
    cout<<"-- Saber cuanto cuesta envier un paquete a cierta ubicacion"<<endl;
    cout<<"2: Saber el camino correcto para que un paquete llegue bien"<<endl;
    cout<<"3: Salir del menu :"<<endl<<endl;
}

