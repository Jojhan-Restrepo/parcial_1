#ifndef ROUTER_H
#define ROUTER_H

#include <vector>
#include <utility>
#include <fstream>
#include <string>
using namespace std;
class Router {
public:
    Router(int id);
    int idRouter;
    std::vector<std::pair<Router*, int>> vecinos; // Un vector de pares, guarda los vecinos y los costos al vecino
    int distancia;
    bool visitado;
    void nuevoVecino(Router* vecino, int costo);
    void confDistancia(int distancia);
    void reinicio();
    void eliminarVecino(Router* vecino, int costo);
    ~Router();
};
void obtenerRouter(const string& nomArchivo, string router);
void dijkstra(Router* fuente);
void escribirCharPorChar(const string& nomArchivo);
void escribirLineaporLinea(const string& nomArchivo);
void leerCharPorChar(const string& nomArchivo);
void leerLineaPorLinea(const string& nomArchivo);
void crearnuevoenrutador(const string& nomArchivo);
void distanciacorta();
void menu();
void eliminarenrutador();
#endif // ROUTER_H
