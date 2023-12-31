#ifndef HMC_ARCHIVOS_HPP
#define HMC_ARCHIVOS_HPP

#include <ctype.h>
#include <vector>
#include <string>

#include "HashMapConcurrente.hpp"

int cargarArchivo(
    HashMapConcurrente &hashMap,
    std::string filePath
);

void cargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
    unsigned int cantThreads,
    std::vector<std::string> filePaths
);

void workerCargarMultiplesArchivos(
    HashMapConcurrente &hashMap,
     std::atomic<int> &archivoActual,
      std::vector<std::string> &filePaths
);

#endif /* HMC_ARCHIVOS_HPP */
