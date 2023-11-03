#include <iostream>
#include <vector>
#include <ctime>
#include <filesystem> 
#include <fstream>
#include "../../src/CargarArchivos.hpp"

//g++ ../../src/HashMapConcurrente.cpp ../../src/CargarArchivos.cpp experimento3.cpp -o exp3 -std=c++17 -pthread


using namespace std;

double ejecutarExperimento(int cantidadArchivo, int cantThreads) {
   
    vector<string> filePath = {};
    for (int i = 1; i <= cantidadArchivo ; i++)
    {
        string abrir = "./archivos/parte_"+ to_string(i)+"_"+ to_string(cantidadArchivo) + ".txt";
        //cout << abrir << endl;
        filePath.push_back(abrir);
    }
    
        int repes = 20;
        double contador = 0;
        for (int j = 0; j < repes ; j++)
        {
            HashMapConcurrente hashmap;
            clock_t start = clock();
            cargarMultiplesArchivos(hashmap, cantThreads, filePath);
            contador += (clock() - start) / (double)CLOCKS_PER_SEC;
        }

        double duracion = contador / repes;
        return duracion;
}

int main(int argc, char* argv[]) {

    for (int k = 1; k < 16; k++){

        const string OUTPUT_FILE = "resultados/divir_archivos_thread_" + to_string(k) + ".txt";

        ofstream outFile(OUTPUT_FILE);
        //outFile.open(OUTPUT_FILE, ios_base::app);

        for (int i = 1; i <= 8; i++){

            double duracion = ejecutarExperimento(i, k); //Cantidad de archivos que se quiere dividir
            string nombreExperimento = to_string(i) + " " + to_string(duracion);
            outFile << nombreExperimento << endl;
            cout << nombreExperimento << endl;
        }

        outFile.close();
    }

    return 0;
}
