#include <iostream>
#include <vector>
#include <ctime>
#include <filesystem> 
#include <fstream>
#include "../src/CargarArchivos.hpp"

const std::string DATA_PATH = "archivos/";
const std::string OUTPUT_FILE = "resultados/resultados_experimentos.csv";

void ejecutarExperimento(int numeroExperimento) {
    HashMapConcurrente hashmap;
    
    std::vector<std::string> filePaths;
    std::string experimentPath = DATA_PATH + "experimento" + std::to_string(numeroExperimento) + "/";
    for (const auto & entry : std::filesystem::directory_iterator(experimentPath)) {
        filePaths.push_back(entry.path());
    }

    std::clock_t start = std::clock();
    
    // Código del experimento
    
    double duracion = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    
    std::ofstream outFile;
    outFile.open(OUTPUT_FILE, std::ios_base::app);
    std::string nombreExperimento = "experimento" + std::to_string(numeroExperimento);
    outFile << nombreExperimento << "," << duracion << std::endl;
    outFile.close();
}

int main(int argc, char* argv[]) {
    int numeroExperimento = std::stoi(argv[1]);
    ejecutarExperimento(numeroExperimento);
    return 0;
}
