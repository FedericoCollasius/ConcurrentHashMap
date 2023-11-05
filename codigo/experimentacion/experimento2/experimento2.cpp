#include <iostream>
#include <vector>
#include <ctime>
#include <filesystem> 
#include <fstream>
#include "../../src/CargarArchivos.hpp"
using namespace std;
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

//g++ ../../src/HashMapConcurrente.cpp ../../src/CargarArchivos.cpp experimento2.cpp -o exp2 -std=c++17 -pthread

const string ARCHIVO = "archivos/real_336736palabras.txt";


double ejecutarExperimento(int cantidadArchivo, int cantidadThreads) {
   
        vector<string> vectorArchivo(cantidadArchivo, ARCHIVO);
        vector<string> filePath = vectorArchivo;
        
        int repes = 3;
        double contador = 0;
        for (int j = 0; j < repes ; j++)
        {
            HashMapConcurrente hashmap;
            auto t1 = Clock::now();
            cargarMultiplesArchivos(hashmap, cantidadThreads, filePath);
            auto t2 = Clock::now();
            contador += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        }
        double duracion = contador / repes;
        return duracion;
    }   


int main(int argc, char* argv[]) {

     const string OUTPUT_FILE = "resultados/real_threads_12_16archivos.txt";
     const int cantidadThreads = 12;
     ofstream outFile(OUTPUT_FILE);

    for (int i = 1; i < 17; i++)
    {
        double duracion = ejecutarExperimento(i, cantidadThreads); 
        string nombreExperimento = to_string(i) + " " + to_string(duracion);
        outFile << nombreExperimento << endl;
        cout << nombreExperimento << endl;
    }
  outFile.close();

    return 0;
}
