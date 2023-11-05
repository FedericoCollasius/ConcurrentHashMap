#ifndef CHM_CPP
#define CHM_CPP

#include <thread>
#include <iostream>
#include <fstream>

#include "HashMapConcurrente.hpp"

// Por cada bucket crea una ListaAtomica de tipo hashMapPair
HashMapConcurrente::HashMapConcurrente() {
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        tabla[i] = new ListaAtomica<hashMapPair>();
    }
}

// Dado una clave, me devuelve el index de la tabla
unsigned int HashMapConcurrente::hashIndex(std::string clave) {
    return (unsigned int)(clave[0] - 'a');
}

// Dado una clave, si dicha clave no se encuentra en el hash lo agrega, caso contrario incrementa la cantidad
void HashMapConcurrente::incrementar(std::string clave) {
    unsigned int idx = hashIndex(clave); // Obtenemos el index
    mutexes[idx].lock();                 
    bool encontreClave = false; 

    // Recorremos toda la ListaAtomica
    for(auto &p:  *tabla[idx]) {
        // Si la encuentro, incremento la cantidad
        if(p.first == clave){
            p.second++;
            encontreClave = true; 
            break;
        }
    }

    // Si no la encontre, la inserto
    if(!encontreClave) {
        tabla[idx]->insertar(hashMapPair(clave, 1));
    }

    mutexes[idx].unlock();
}

std::vector<std::string> HashMapConcurrente::claves() {
    std::vector<std::string> resultado;

    // Bloqueo todos los mutexes antes de arrancar a recorrer el Hash Map. 
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        mutexes[i].lock_shared();
    }

    // Por cada bucket recorro la lista y guardo las claves en resultado
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) { 
        for (auto &p: *tabla[i]) {
            resultado.push_back(p.first);
        }
        // Desbloqueo el bucket actual. 
        mutexes[i].unlock_shared();
    }

    return resultado;
}


unsigned int HashMapConcurrente::valor(std::string clave) {
    unsigned int valor = 0; 
    unsigned int idx = hashIndex(clave); // Index de la clave
    
    mutexes[idx].lock_shared();
    for(auto &p: *tabla[idx]) {
        // Si encuentro la clave que estoy buscando, me guardo la cantidad
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

    // Bloqueo todos los mutexes antes de arrancar a recorrer el Hash Map 
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        mutexes[i].lock_shared();
    }

    // Por cada bucket recorro la lista y comparo a ver si es mayor al maximo actual 
    for (unsigned int i = 0; i < HashMapConcurrente::cantLetras; i++) {
        for (auto &p: *tabla[i]) {
            if (p.second > max->second) {
                max->first = p.first;
                max->second = p.second;
            }
        }
        // Desbloqueo el bucket actual 
        mutexes[i].unlock_shared();
    }

    return *max;
}

hashMapPair workerMaximo(ListaAtomica<hashMapPair> **tabla, std::atomic<int> &listaActual, std::shared_mutex *mutexes) {

    hashMapPair *localMax = new hashMapPair();


    while (true) {
        int idx = listaActual.fetch_add(1); // Incrementa atomicamente el valor de listaActual y idx es el valor antes de incrementarse

        if (idx >= HashMapConcurrente::cantLetras) break; // Termino si alcance todas las letras

        mutexes[idx].lock_shared();
        // Recorro la lista y me quedo con el maximo de todas los buckets que vi
        for (auto &p: *tabla[idx]) {
            if (p.second > localMax->second) {
                localMax->first = p.first;
                localMax->second = p.second;
            }
        }
        mutexes[idx].unlock_shared();
    } // Repito hasta que idx >= cantLetras
    return *localMax;
}

hashMapPair HashMapConcurrente::maximoParalelo(unsigned int cant_threads) {
    std::vector<std::thread> threads;
    std::vector<hashMapPair> resultados(cant_threads); // Vector donde voy a guardar los resultados de cada hilo
    std::atomic<int> listaActual(0); // Entero atomico que me va a indicar cual es la proxima lista a recorrer 

    for (unsigned int i = 0; i < cant_threads; i++) {
        threads.emplace_back([&](int idx) {
            resultados[idx] = workerMaximo(this->tabla, listaActual, this->mutexes); //Me guardo el resultado de todas las lineas que vio el thread
        }, i);
    }

    for (auto &t:threads) {
        t.join();
    }

    hashMapPair *max = new hashMapPair();

    // Recorro todos los resultados obtenidos y me quedo con el maximo
    for (auto &res:resultados) {
        if (res.second > max->second) {
            max->first = res.first;
            max->second = res.second;
        }
    }
    return *max;
}

#endif
