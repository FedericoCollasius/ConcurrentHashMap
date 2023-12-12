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

    for(auto &p:  *tabla[idx]) {
        if(p.first == clave){
            p.second++;
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
        for (auto &p: *tabla[i]) {
            resultado.push_back(p.first);
        }
        mutexes[i].unlock_shared();
    }

    return resultado;
}


unsigned int HashMapConcurrente::valor(std::string clave) {
    unsigned int valor = 0; 
    unsigned int idx = hashIndex(clave);
    mutexes[idx].lock_shared();
    for(auto &p: *tabla[idx]) {
        if(p.first == clave){
            valor = p.second;
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
        for (auto &p: *tabla[i]) {
            if (p.second > max->second) {
                max->first = p.first;
                max->second = p.second;
            }
        }
        mutexes[i].unlock_shared();
    }

    return *max;
}

hashMapPair workerMaximo(ListaAtomica<hashMapPair> **tabla, std::atomic<int> &listaActual, std::shared_mutex *mutexes) {
    hashMapPair *localMax = new hashMapPair();

    for (int idx = listaActual.fetch_add(1); idx < HashMapConcurrente::cantLetras; idx = listaActual.fetch_add(1)) {
        for (auto &p: *tabla[idx]) {
            if (p.second > localMax->second) {
                localMax->first = p.first;
                localMax->second = p.second;
            }
        }
        // Desbloquea el mutex correspondiente a esta letra después de procesarla.
        mutexes[idx].unlock_shared();
    }

    return *localMax;
}


hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {
    std::vector<std::thread> threads;
    std::vector<hashMapPair> resultados(cant_threads); 
    std::atomic<int> listaActual(0);

    // Bloqueo como en maximo()
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        mutexes[i].lock_shared();
    }

    for (unsigned int i = 0; i < cant_threads; i++) {
        threads.emplace_back([&](int idx) {
            resultados[idx] = workerMaximo(this->tabla, listaActual, this->mutexes); 
        }, i);
    }

    for (auto &t:threads) {
        t.join();
    }

    hashMapPair *max = new hashMapPair();

    for (auto &res:resultados) {
        if (res.second > max->second) {
            max->first = res.first;
            max->second = res.second;
        }
    }
    return *max;
}

#endif
