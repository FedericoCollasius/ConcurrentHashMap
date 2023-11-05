#include <iostream>
#include <vector>
#include <ctime>
#include <filesystem> 
#include <fstream>
#include "../../src/CargarArchivos.hpp"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
using namespace std;


// g++ ../../src/HashMapConcurrente.cpp ../../src/CargarArchivos.cpp experimento1.cpp -o exp1 -std=c++17 -pthread

double ejecutarExperimentoConThreads(int cantidadArchivo, int threads) {
   
    vector<string> filePath = {};
    for (int i = 1; i <= cantidadArchivo ; i++)
    {
        string abrir = "./archivos/archivo_"+ to_string(i)+".txt";
        filePath.push_back(abrir);
    }
        int repes = 10;
        double contador = 0;
        for (int j = 0; j < repes ; j++)
        {
            HashMapConcurrente hashmap;
            auto t1 = Clock::now();
            cargarMultiplesArchivos(hashmap, threads, filePath);
            auto t2 = Clock::now();
            contador += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        }
        double duracion = contador / repes;
        return duracion;
}

int main(int argc, char* argv[]) {

    const string OUTPUT_FILE = "resultados/resultados_cargaArchivosConYSinThreads6threads.txt";
    ofstream outFile(OUTPUT_FILE);

    int cantidadArchivos = 16;

    for (int i = 1; i < 13; i++)
    {
        double duracion = ejecutarExperimentoConThreads(cantidadArchivos , i); 
        string nombreExperimento = to_string(i) + " " + to_string(duracion);
        outFile << nombreExperimento << endl;
        cout << nombreExperimento << endl;
    }

   outFile.close();
   return 0;
}
