#ifndef CHM_CPP
#define CHM_CPP

#include <thread>
#include <iostream>
#include <fstream>

#include "HashMapConcurrente.hpp"

HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

void HashMapConcurrente::incrementar(std::string clave) {
    unsigned int idx = hashIndex(clave);
    mutexes[idx].lock();
    bool encontreClave = false; 

    for(auto &c:*tabla[idx]) {
        if(c.first == clave){
            c.second++;
            encontreClave = true; 
            break;
        }
    }

    if(!encontreClave) {
        tabla[idx]->insertar(hashMapPair(clave, 1));
    }

    mutexes[idx].unlock();
}

std::vector<std::string> HashMapConcurrente::claves() {
    std::vector<std::string> resultado;

    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        mutexes[i].lock_shared();
    }

    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) { 
        for (auto &c:*tabla[i]) {
            resultado.push_back(c.first);
        }
        mutexes[i].unlock_shared();
    }

    return resultado;
}


unsigned int HashMapConcurrente::valor(std::string clave) {
    unsigned int valor = 0; 
    unsigned int idx = hashIndex(clave); 
    
    mutexes[idx].lock_shared();
    for(auto &c : *tabla[idx]) {
        if(c.first == clave){
            valor = c.second;
            break;
        }
    }
    mutexes[idx].unlock_shared();

    return valor; 
}

hashMapPair HashMapConcurrente::maximo() {
    hashMapPair *max = new hashMapPair();
    max->second = 0;

    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        mutexes[i].lock_shared();
    }

    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        for (auto &p : *tabla[i]) {
            if (p.second > max->second) {
                max->first = p.first;
                max->second = p.second;
            }
        }
        mutexes[i].unlock_shared();
    }

    return *max;
}



hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {
    
}

#endif
