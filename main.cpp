#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "ArbolAVL.h"
using namespace std;

int main(int argc, char **argv){
    string archivo= argv[argc-1];
    cout<<"Archivo: "<<archivo<<endl;

    for(int i=1; i<argc-1; i++) {
        string arg = argv[i];
        cout << arg << endl;

        if (arg == "-hola") {
            cout << "adios";
        }

        if (arg == "") {
            cout << "nadis";
        }
    }
}

/*
//argc cant de argumentos, argv los argumentos en si, separados por palabras
//el ultimo argumento es el archivo, y el 0 es el nombre del ejecutable ej. main.exe
//edit config puedo poner los argumentos que voy a ir probando
//poner en el working directory la carpeta donde tenemos el archivo para q busque ahi

Estructura para representar un artículo y su stock en un depósito
struct Articulo {
    std::string nombre;
    int stock;

    Articulo(const std::string& n, int s) : nombre(n), stock(s) {}
};

int main(int argc, char* argv[]) {
    // Verifica si se proporcionó un archivo CSV como argumento
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " archivo.csv" << std::endl;
        return 1;
    }

    Crea un objeto ArbolAVL para almacenar los artículos
    ArbolAVL<Articulo> arbol;

    Lee el archivo CSV y carga los datos en el árbol
    std::ifstream archivoCSV(argv[1]);
    if (archivoCSV.is_open()) {
        std::string linea;
        while (std::getline(archivoCSV, linea)) {
            std::istringstream ss(linea);
            std::string nombreArticulo;
            int stockDeposito;

            Analiza cada línea del archivo CSV y extrae el nombre del artículo y el stock del depósito
            if (std::getline(ss, nombreArticulo, ',')) {
                if (ss >> stockDeposito) {
                    Crea un objeto Articulo y lo inserta en el árbol AVL
                    Articulo nuevoArticulo(nombreArticulo, stockDeposito);
                    arbol.put(nuevoArticulo);
                }
            }
        }
        archivoCSV.close();
    } else {
        std::cerr << "No se pudo abrir el archivo CSV." << std::endl;
        return 1;
    }

    // Ahora puedes utilizar los métodos de ArbolAVL para acceder a los datos del inventario
    // Implementa las funciones requeridas según el enunciado para acceder a la información de inventario.

    return 0;
}
*/