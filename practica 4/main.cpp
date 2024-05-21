#include "Router.h"
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <QCoreApplication>
#include <QTextStream>
#include <QLocale>
using namespace std;

int main(int argc, char *argv[]) {

    const string nomArchivo = "archivo1.txt";
    vector<Router> routers(4); // Supongamos que tienes 4 routers, puedes ajustar esto según tus necesidades

    configurarRoutersDesdeArchivo(nomArchivo, routers);

    int opcion;
    menu();
    opcion= 2;
    while(opcion <= 3){
        menu();
        cout<<"ingrese su opcion: ";
        cin>>opcion;
        switch (opcion) {
        case 1:{
            cout << "Seleccionaste la opción 1" << endl;
            crearnuevoenrutador(nomArchivo);
            //distanciacorta();
            break;
            }
        case 2:{
            cout << "Seleccionaste la opción 2" << endl;
            break;}
        case 3:{
            cout<<"Hasta luego querido usuario ";
            opcion=4;
            break;
        }
        default:
            cout << "Opción no válida" << endl;
        }}
    string router= "Router A";
    return 0;
    }
