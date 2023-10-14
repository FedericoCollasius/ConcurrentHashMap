#include <iostream>
#include <vector>
#include <ctime>
#include <filesystem> 
#include <fstream>
#include "../src/CargarArchivos.hpp"
#include "../src/HashMapConcurrente.hpp"

const std::string DATA_PATH = "archivos/";
const std::string OUTPUT_FILE = "resultados/resultados_experimentos.csv";

void guardarResultadoCSV(const std::string &nombreExperimento, double duracion, const std::pair<std::string, int> &maximo) {
    std::ofstream outFile;
    outFile.open(OUTPUT_FILE, std::ios_base::app); // Abrir archivo en modo append
    outFile << nombreExperimento << "," << duracion << "," << maximo.first << "," << maximo.second << std::endl;
    outFile.close();
}

void ejecutarExperimento(int numeroExperimento) {
    // 1. Inicialización
    printf("Inicializacion\\n");
    HashMapConcurrente hashmap;

    // Hardcodeamos las rutas de los archivos de experimento1
    std::vector<std::string> filePaths = {
        "archivos/experimento1/datos_idioma_parte1_de_3_100palabras.txt",
        "archivos/experimento1/datos_idioma_parte2_de_3_100palabras.txt",
        "archivos/experimento1/datos_idioma_parte3_de_3_100palabras"
        // Añade más rutas según el número de archivos en experimento1
    };
    
    // 2. Configuración del experimento
    int cantThreads = 4; // Ejemplo

    // 3. Ejecución y medición del tiempo
    std::clock_t start = std::clock();
    
    // Código del experimento
    cargarMultiplesArchivos(hashmap, cantThreads, filePaths);

    // Detener el tiempo justo después de la ejecución del experimento
    double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    
    // 4. Resultados y guardado en CSV
    auto maximo = hashmap.maximo();
    //guardarResultadoCSV("experimento" + std::to_string(numeroExperimento), duration, maximo);

    // 5. Limpieza (si es necesario)
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: " << argv[0] << " [numero de experimento]" << std::endl;
        return 1;
    }
    printf("Convertir caracter");
    int numeroExperimento = std::stoi(argv[1]);
    ejecutarExperimento(numeroExperimento);
    return 0;
}
