import random
import string
import os
import nltk
#nltk.download('words')

import nltk
from nltk.corpus import words

def experimento1(cantidadPalabras , cantidadRepetidas , cantidadArchivos):
    for i in range(1, cantidadArchivos + 1 ):
        palabras = words.words()  
        random.shuffle(palabras)

        palabrasSeleccionadas = palabras[:cantidadPalabras]

        cantidadPalabrasFaltantes = cantidadRepetidas
        while cantidadPalabrasFaltantes > 0:
            palabraQueVoyARepetir = palabrasSeleccionadas[random.randint(0, len(palabrasSeleccionadas) - 1)]
            repetir = random.randint(1, cantidadPalabrasFaltantes)
            for _ in range (1, repetir + 1):
                palabrasSeleccionadas.append(palabraQueVoyARepetir)
            cantidadPalabrasFaltantes = cantidadPalabrasFaltantes - repetir

        random.shuffle(palabrasSeleccionadas)    

        with open(f"experimento1/archivos/archivo_"+str(i)+".txt"    , "w") as f:
            for palabra in palabrasSeleccionadas:
                f.write(palabra.lower() + '\n')  # LAS PALABRAS TIENEN QUE ESTAR EN MINUSCULA


def experimento2(cantidadPalabras, cantidadRepetidas):
    palabras = words.words()  
    random.shuffle(palabras)

    palabrasSeleccionadas = palabras[:cantidadPalabras]

    cantidadPalabrasFaltantes = cantidadRepetidas
    while cantidadPalabrasFaltantes > 0:
         palabraQueVoyARepetir = palabrasSeleccionadas[random.randint(0, len(palabrasSeleccionadas) - 1)]
         repetir = random.randint(1, cantidadPalabrasFaltantes)
         for _ in range (1, repetir + 1):
             palabrasSeleccionadas.append(palabraQueVoyARepetir)
         cantidadPalabrasFaltantes = cantidadPalabrasFaltantes - repetir

    random.shuffle(palabrasSeleccionadas)
    #print(palabrasSeleccionadas)

    with open(f"experimento2/archivos/real_{len(palabrasSeleccionadas)}palabras.txt", "w") as f:
        for palabra in palabrasSeleccionadas:
            f.write(palabra.lower() + '\n')  # LAS PALABRAS TIENEN QUE ESTAR EN MINUSCULA


def experimento3(cantidadPalabras, cantidadRepetidas):
    palabras = words.words()  
    random.shuffle(palabras)

    palabrasSeleccionadas = palabras[:cantidadPalabras]

    cantidadPalabrasFaltantes = cantidadRepetidas
    while cantidadPalabrasFaltantes > 0:
         palabraQueVoyARepetir = palabrasSeleccionadas[random.randint(0, len(palabrasSeleccionadas) - 1)]
         repetir = random.randint(1, cantidadPalabrasFaltantes)
         for _ in range (1, repetir + 1):
             palabrasSeleccionadas.append(palabraQueVoyARepetir)
         cantidadPalabrasFaltantes = cantidadPalabrasFaltantes - repetir

    random.shuffle(palabrasSeleccionadas)
    #print(palabrasSeleccionadas)
    

    with open(f"experimento3/archivos/{len(palabrasSeleccionadas)}palabras.txt", "w") as f:
        for palabra in palabrasSeleccionadas:
            f.write(palabra.lower() + '\n')  # LAS PALABRAS TIENEN QUE ESTAR EN MINUSCULA


def dividir_archivo(archivo_entrada, cantidadArchivos):
    
    totalPalabras =  36000
    cantidadPalabrasPorArchvio =  totalPalabras / cantidadArchivos

    with open(archivo_entrada, 'r') as entrada:
         
         parte_actual = []
         numero_de_archivo = 1

         for linea in entrada:
            parte_actual.append(linea)
            if len(parte_actual) > cantidadPalabrasPorArchvio:
                with open(f'experimento3/archivos/parte_{numero_de_archivo}_{cantidadArchivos}.txt', 'w') as salida:
                    for elemento in parte_actual:
                        salida.write(elemento)
                numero_de_archivo += 1
                parte_actual = []

         with open(f'experimento3/archivos/parte_{numero_de_archivo}_{cantidadArchivos}.txt', 'w') as salida:
            for elemento in parte_actual:
                salida.write(elemento)


def experimento4(cantidadPalabras, cantidadRepetidas , cantidadArchivos): #distribucion aleatoria xq sino estamos acotados 
    for i in range(1, cantidadArchivos + 1):
        aleatorio_words = [''.join(random.choices(string.ascii_lowercase, k=random.randint(1, 15))) for _ in range(cantidadPalabras)]

        palabras = aleatorio_words

        random.shuffle(palabras)

        palabrasSeleccionadas = palabras[:cantidadPalabras]

        cantidadPalabrasFaltantes = cantidadRepetidas
        while cantidadPalabrasFaltantes > 0:
            palabraQueVoyARepetir = palabrasSeleccionadas[random.randint(0, len(palabrasSeleccionadas) - 1)]
            repetir = random.randint(1, cantidadPalabrasFaltantes)
            for _ in range (1, repetir + 1):
                palabrasSeleccionadas.append(palabraQueVoyARepetir)
            cantidadPalabrasFaltantes = cantidadPalabrasFaltantes - repetir

        random.shuffle(palabrasSeleccionadas)
        

        with open(f"experimento4/archivos/archivo{i}_{len(palabrasSeleccionadas)}palabras.txt", "w") as f:
            for palabra in palabrasSeleccionadas:
                f.write(palabra.lower() + '\n')  # LAS PALABRAS TIENEN QUE ESTAR EN MINUSCULA


#experimento1(100000, 5000, 15)
#experimento2(260000, 100000)
#experimento3(26000, 10000)

# Uso de la función para dividir el archivo
#for numero in range(1, 16):
    #dividir_archivo('experimento3/archivos/36000palabras.txt', numero)

experimento4(26000, 30000, 12)
  

