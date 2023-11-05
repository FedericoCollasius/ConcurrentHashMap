#include <iostream>
#include <vector>
#include <ctime>
#include <filesystem> 
#include <fstream>
#include "../../src/CargarArchivos.hpp"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
using namespace std;

//g++ ../../src/HashMapConcurrente.cpp ../../src/CargarArchivos.cpp experimento4.cpp -o exp4 -std=c++17 -pthread

HashMapConcurrente hashmap;
vector<string> filePath ;

double ejecutarExperimento(int cantidadThreads) {
   
        int repes = 10;
        double contador = 0;
        
        for (int j = 0; j < repes ; j++)
        {
            auto t1 = Clock::now();
            hashMapPair actual = hashmap.maximoParalelo(cantidadThreads);
            string palabra = actual.first;
            int cantidad = actual.second;
            auto t2 = Clock::now();
            contador += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        }
        double duracion = contador / repes;
        return duracion;
    }   

int main(int argc, char* argv[]) {

     const string OUTPUT_FILE = "resultados/exp4_12threads_6720000palabras.txt";

    int cantidadArchivos = 12;
    for (int i = 1; i <= cantidadArchivos; i++)
    {   
        cout << "archivos/archivo" + to_string(i) + "_560000palabras.txt" <<  endl;
        filePath.push_back("archivos/archivo" + to_string(i) + "_560000palabras.txt");
    }
    cargarMultiplesArchivos(hashmap, 12, filePath);
    cout << "Termine de cargar" << endl;

     ofstream outFile(OUTPUT_FILE);

    for (int i = 1; i < 16; i++)
    {
        double duracion = ejecutarExperimento(i); //Cantidad de threads a utilizar
        string nombreExperimento = to_string(i) + " " + to_string(duracion);
        outFile << nombreExperimento << endl;
        cout << nombreExperimento << endl;
    }
    outFile.close();

    return 0;
}
