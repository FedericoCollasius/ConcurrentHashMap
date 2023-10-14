#ifndef CHM_CPP
#define CHM_CPP

#include <vector>
#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>

#include "CargarArchivos.hpp"

int cargarArchivo(HashMapConcurrente &hashMap, std::string filePath) {
    std::fstream file;
    int cant = 0;
    std::string palabraActual;

    // Abro el archivo.
    file.open(filePath, file.in);
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo '" << filePath << "'" << std::endl;
        return -1;
    }
    while (file >> palabraActual) {
        hashMap.incrementar(palabraActual);//Agregamos la palabra al hash
        cant++;
    }
    // Cierro el archivo.
    if (!file.eof()) {
        std::cerr << "Error al leer el archivo" << std::endl;
        file.close();
        return -1;
    }
    file.close();
    return cant;
}

void workerCargarMultiplesArchivos(HashMapConcurrente &hashMap, std::atomic<int> &archivoActual, std::vector<std::string> &filePaths) {
    int n = filePaths.size(); //Cantidad de archivos
    while(true){
        int idx = archivoActual.fetch_add(1); 
        if (idx >= n) break; //Si es igual o supere la cantidad de archivos, termino
        cargarArchivo(hashMap, filePaths[idx]); //Leo archivo
    } //Repito hasta que todos los archivos sean cargados
} 

void cargarMultiplesArchivos(HashMapConcurrente &hashMap, unsigned int cantThreads, std::vector<std::string> filePaths) {
    std::vector<std::thread> threads;
    std::atomic<int> archivoActual(0);
    for (unsigned int i = 0; i < cantThreads; i++) {
        threads.emplace_back([&] {
            workerCargarMultiplesArchivos(hashMap, archivoActual, filePaths);
        });
    }

    for (auto &t:threads) {
        t.join();
    }
}

#endif
