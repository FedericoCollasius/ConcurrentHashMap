#include <iostream>
#include <vector>
#include <ctime>
#include <filesystem> 
#include <fstream>
#include "../../src/CargarArchivos.hpp"
using namespace std;


//g++ ../../src/HashMapConcurrente.cpp ../../src/CargarArchivos.cpp experimento2.cpp -o exp2 -std=c++17 -pthread

/*
Experimento 2: Fijamos los threads y se varía la cantidad de archivos siendo estos iguales.
Esto para ver cómo varía el tiempo de la inserción con una cantidad fija de threads pero diferente cantidad de archivos.
*/

const string ARCHIVO = "archivos/real_336736palabras.txt";

void printFilePath(vector<string> filePath){
        for (const string& path : filePath) {
        cout << path << endl;
    }
}


double ejecutarExperimento(int cantidadArchivo, int cantidadThreads) {
   

        vector<string> vectorArchivo(cantidadArchivo, ARCHIVO);
        vector<string> filePath = vectorArchivo;
        
        int repes = 3;
        double contador = 0;
        for (int j = 0; j < repes ; j++)
        {
            HashMapConcurrente hashmap;
            clock_t start = clock();
            cargarMultiplesArchivos(hashmap, cantidadThreads, filePath);
            clock_t close = clock();
            cout << (close - start) / (double)CLOCKS_PER_SEC << endl;
            contador += (close - start) / (double)CLOCKS_PER_SEC;
        }
        double duracion = contador / repes;
        return duracion;
    }   


int main(int argc, char* argv[]) {

     const string OUTPUT_FILE = "resultados/real_threads_12_50archivos.txt";
     const int cantidadThreads = 12;
     ofstream outFile(OUTPUT_FILE);

    for (int i = 1; i < 16; i++)
    {
        double duracion = ejecutarExperimento(i, cantidadThreads); 
        string nombreExperimento = to_string(i) + " " + to_string(duracion);
        outFile << nombreExperimento << endl;
        cout << nombreExperimento << endl;
    }
  outFile.close();

    return 0;
}
