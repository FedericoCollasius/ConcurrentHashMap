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

    for(auto &c : *tabla[idx]) {
        if(c.first == clave){
            c.second++;
            encontreClave = true; 
            break;
        }
    }

    if(!encontreClave) {
        tabla[idx]->insertar(std::make_pair(clave, 1));
    }

    mutexes[idx].unlock();
}

std::vector<std::string> HashMapConcurrente::claves() {
    std::vector<std::string> claves; 
    
    for(unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++){
        mutexes[i].lock();
        for (auto &c : *tabla[i]) {
            claves.push_back(c.first);
        }
    }

    for(unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++){
        mutexes[i].unlock();
    }

    return claves; 
}

unsigned int HashMapConcurrente::valor(std::string clave) {
    unsigned int valor = 0; 
    unsigned int idx = hashIndex(clave); 
    
    mutexes[idx].lock();
    for(auto &c : *tabla[idx]) {
        if(c.first == clave){
            valor = c.second;
            break;
        }
    }
    mutexes[idx].unlock();

    return valor; 
}

hashMapPair HashMapConcurrente::maximo() {
    hashMapPair *max = new hashMapPair();
    max->second = 0;

    for (unsigned int index = 0; index < HashMapConcurrente::cantLetras; index++) {
        for (auto &p : *tabla[index]) {
            if (p.second > max->second) {
                max->first = p.first;
                max->second = p.second;
            }
        }
    }

    return *max;
}



hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {
    // Completar (Ejercicio 3)
}

#endif
