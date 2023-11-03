#include <iostream>
#include <vector>
#include <ctime>
#include <filesystem> 
#include <fstream>
#include "../../src/CargarArchivos.hpp"

//g++ ../../src/HashMapConcurrente.cpp ../../src/CargarArchivos.cpp experimento4.cpp -o exp4 -std=c++17 -pthread


using namespace std;


HashMapConcurrente hashmap;
vector<string> filePath ;


void printFilePath(vector<string> filePath){
        for (const string& path : filePath) {
        cout << path << endl;
    }
}


double ejecutarExperimento(int cantidadThreads) {
   
        int repes = 10;
        double contador = 0;
        
        for (int j = 0; j < repes ; j++)
        {
            clock_t start = clock();
            hashMapPair actual = hashmap.maximoParalelo(cantidadThreads);
            string palabra = actual.first;
            int cantidad = actual.second;
            //cout << cantidad << endl;
            contador += (clock() - start) / (double)CLOCKS_PER_SEC;
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
          filePath.push_back("archivos/archivo" + to_string(i) + "_56000palabras.txt");
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
