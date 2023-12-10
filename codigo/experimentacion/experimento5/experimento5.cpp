#include <iostream>
#include <vector>
#include <ctime>
#include <filesystem> 
#include <fstream>
#include "../../src/CargarArchivos.hpp"
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
using namespace std;

//g++ ../../src/HashMapConcurrente.cpp ../../src/CargarArchivos.cpp experimento5.cpp -o exp5 -std=c++17 -pthread

vector<int> resultado1;
vector<int> resultado2;
int repes = 1;

bool sonVectoresIguales(const std::vector<int>& v1, const std::vector<int>& v2) {
    // Verificar si los tamaños son iguales
    if (v1.size() != v2.size()) {
        return false;
    }

    // Comparar elemento por elemento
    for (size_t i = 0; i < v1.size(); ++i) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }

    // Si todos los elementos son iguales, los vectores son iguales
    return true;
} 



double concurrencia (vector<string> palabras , int cantidadPalabras){
    const string nombre_archivo = "ejemplo.txt";

    ifstream archivo_entrada(nombre_archivo);

    if (!archivo_entrada.is_open()) {
        cerr << "Error al abrir el archivo: " << nombre_archivo << std::endl;
        return {}; // Salir con código de error
    }

    double tiempo = 0;
        
    for (int j = 0; j < repes ; j++)
    {
        auto t1 = Clock::now();

        HashMapConcurrente hashmap;
        vector<string> libro = {"ejemplo.txt"};
        cargarMultiplesArchivos(hashmap, 1, libro); //Solo un thread carga el archivo? 
        vector<int> contador(cantidadPalabras , 0);
        for (int i = 0; i < cantidadPalabras; i++)
        {
            contador[i] = hashmap.valor(palabras[i]);
        }

        auto t2 = Clock::now();
        tiempo += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        resultado1 = contador;
    }
    cout << "Con concurrencia ";
    for (int i = 0; i < resultado1.size(); ++i) {
        cout << resultado1[i] << " ";
    }
    cout << endl;
    double duracion = tiempo / repes;
    return duracion;
}



void abrirArchivo(){
    const string nombre_archivo = "ejemplo.txt";
    ifstream archivo_entrada(nombre_archivo);

        if (!archivo_entrada.is_open()) {
        cerr << "Error al abrir el archivo: " << nombre_archivo << endl;
        return;
    }

}

double contadorApariciones (vector<string> palabras , int cantidadPalabras){
    const string nombre_archivo = "ejemplo.txt";
    double tiempo = 0;

    for (int j = 0; j < repes ; j++){
        auto t1 = Clock::now();

        vector<int> contador(cantidadPalabras , 0);

        for (int i = 0; i < cantidadPalabras ; i++)
        {
            ifstream archivo_entrada(nombre_archivo);

            if (!archivo_entrada.is_open()) {
                cerr << "Error al abrir el archivo: " << nombre_archivo << endl;
                return {}; // Salir con código de error
            }

            string palabra;
            while (archivo_entrada >> palabra) {
                if (palabra == palabras[i])
                    {
                        contador[i]++;
                    }
                }
            // Cerrar el archivo
            archivo_entrada.close();
        }
        auto t2 = Clock::now();
        tiempo += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        resultado2 = contador;
    }
    cout << "Sin concurrencia ";
    for (size_t i = 0; i < resultado2.size(); ++i) {
        cout << resultado2[i] << " ";
    }
    cout << endl;
    double duracion = tiempo / repes;
    return duracion;
}

vector<std::string> readWordsIntoVector(const std::string& filename) {
    vector<std::string> words;
    string word;
    ifstream file(filename);

    if (file.is_open()) {
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
    } else {
        cerr << "Unable to open file" << endl;
    }

    return words;
}



int main(int argc, char* argv[]) {

    //Eliminar del libro , : mayuscula numeros

    const string OUTPUT_FILE = "resultado.txt";

    vector<string> palabras = readWordsIntoVector("randomWordsDracula.txt");

    
    ofstream outFile(OUTPUT_FILE);

    for (int i = 1; i < palabras.size() ; ++i) {
        double resultadoSinConcurrencia = contadorApariciones(palabras , i);
        double resultadoConConcurrencia = concurrencia(palabras , i);
        string resultado = to_string(i) + " " + to_string(resultadoSinConcurrencia) + " " + to_string(resultadoConConcurrencia);
        outFile << resultado  << endl;
        cout << sonVectoresIguales(resultado1 , resultado2) << endl;
    }
    outFile.close();

    return 0;
}
