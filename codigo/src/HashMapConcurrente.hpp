#ifndef HMC_HPP
#define HMC_HPP

#include <shared_mutex>
#include <array>
#include <atomic>
#include <string>
#include <vector>

#include "ListaAtomica.hpp"

typedef std::pair<std::string, unsigned int> hashMapPair;

class HashMapConcurrente {
 public:
    static constexpr int cantLetras = 26;

    HashMapConcurrente();

    void incrementar(std::string clave);
    std::vector<std::string> claves();
    unsigned int valor(std::string clave);

    hashMapPair maximo();
    hashMapPair maximoParalelo(unsigned int cantThreads);

 private:
    ListaAtomica<hashMapPair> *tabla[HashMapConcurrente::cantLetras];

    static unsigned int hashIndex(std::string clave);
    
    //Creamos un arreglo de tamaño cantLetras, donde cada elemento es un mutex
    std::shared_mutex mutexes[HashMapConcurrente::cantLetras];
   
};

#endif  /* HMC_HPP */
