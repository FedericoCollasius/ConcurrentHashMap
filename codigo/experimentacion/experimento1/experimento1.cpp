#include <iostream>
#include <vector>
#include <ctime>
#include <filesystem> 
#include <fstream>
#include "../../src/CargarArchivos.hpp"

// g++ ../../src/HashMapConcurrente.cpp ../../src/CargarArchivos.cpp experimento1.cpp -o exp1 -std=c++17 -pthread

using namespace std;

double ejecutarExperimentoConThreads(int cantidadArchivo, int threads) {
       
    vector<string> filePath = {};
    for (int i = 1; i <= cantidadArchivo ; i++)
    {
        string abrir = "./archivos/archivo_"+ to_string(i)+".txt";
        //cout << abrir << endl;
        filePath.push_back(abrir);
    }
        int repes = 3;
        double contador = 0;
        for (int j = 0; j < repes ; j++)
        {
            HashMapConcurrente hashmap;
            clock_t start = clock();
            cargarMultiplesArchivos(hashmap, threads, filePath);
            contador += (clock() - start) / (double)CLOCKS_PER_SEC;
        }
        double duracion = contador / repes;
        return duracion;
}

double ejecutarExperimentoSinThreads(int cantidadArchivo) {
    vector<string> filePath = {};
    for (int i = 1; i <= cantidadArchivo ; i++)
    {
        string abrir = "./archivos/archivo_"+ to_string(i)+".txt";
        //cout << abrir << endl;
        filePath.push_back(abrir);
    }
        int repes = 3;
        double contador = 0;
        for (int j = 0; j < repes ; j++)
        {
            HashMapConcurrente hashmap;
            atomic<int> atomicInteger(0);
            clock_t start = clock();
            workerCargarMultiplesArchivos(hashmap, atomicInteger , filePath);
            contador += (clock() - start) / (double)CLOCKS_PER_SEC;
        }
        double duracion = contador / repes;
        return duracion;
}


int main(int argc, char* argv[]) {

    const string OUTPUT_FILE = "resultados/resultados_cargaArchivosConYSinThreads.txt";
    ofstream outFile(OUTPUT_FILE);

    int cantidadArchivos = 15;
    double duracion = ejecutarExperimentoSinThreads(cantidadArchivos); 
    outFile << "0 " << duracion << endl;
    cout << "0 " << duracion << endl;

    for (int i = 1; i < 16; i++)
    {
        double duracion = ejecutarExperimentoConThreads(cantidadArchivos , i); 
        string nombreExperimento = to_string(i) + " " + to_string(duracion);
        outFile << nombreExperimento << endl;
        cout << nombreExperimento << endl;
    }

   outFile.close();

    return 0;
}
