import random
import string
import os
import nltk
from nltk.corpus import words

def filtrar_por_longitud(lista, longitud):
    return [palabra for palabra in lista if longitud[0] <= len(palabra) <= longitud[1]]

def obtener_palabras_aleatorias_del_corpus(num_palabras, longitud_palabra=None):
    todas_las_palabras = words.words()
    if longitud_palabra:
        todas_las_palabras = filtrar_por_longitud(todas_las_palabras, longitud_palabra)
    return random.sample(todas_las_palabras, num_palabras)

def generar_palabras_aleatorias(num_palabras, longitud_palabra):
    if longitud_palabra:
        return [''.join(random.choices(string.ascii_lowercase, k=random.randint(longitud_palabra[0], longitud_palabra[1]))) for _ in range(num_palabras)]
    else:
        return [''.join(random.choices(string.ascii_lowercase, k=random.randint(1, 15))) for _ in range(num_palabras)]

def construir_nombre_archivo(idioma, num_palabras, num_archivos, archivo_actual):
    nombre = f"datos_{'idioma' if idioma else 'aleatorio'}_"
    if num_archivos > 1:
        nombre += f"parte{archivo_actual}_de_{num_archivos}_"
    nombre += f"{num_palabras}palabras.txt"
    return nombre

def construir_directorio_experimento(experimento_numero):
    return f"archivos/experimento{experimento_numero}"

def guardar_archivo(palabras, nombre_archivo, directorio_experimento):
    if not os.path.exists(directorio_experimento):
        os.makedirs(directorio_experimento)
    with open(f"{directorio_experimento}/{nombre_archivo}", "w") as f:
        for palabra in palabras:
            f.write(palabra + '\n')

def generar_archivo_datos(experimento_numero, num_palabras=1000, longitud_palabra=None, idioma=True, num_archivos=1):
    if idioma:
        todas_las_palabras = obtener_palabras_aleatorias_del_corpus(num_palabras * num_archivos, longitud_palabra)
    else:
        todas_las_palabras = generar_palabras_aleatorias(num_palabras * num_archivos, longitud_palabra)

    directorio_experimento = construir_directorio_experimento(experimento_numero)
    
    for i in range(num_archivos):
        palabras_actuales = todas_las_palabras[i*num_palabras:(i+1)*num_palabras]
        nombre_archivo = construir_nombre_archivo(idioma, num_palabras, num_archivos, i+1)
        guardar_archivo(palabras_actuales, nombre_archivo, directorio_experimento)
        print(f"Archivo {nombre_archivo} generado en {directorio_experimento}")

# Ejemplo 
generar_archivo_datos(1, num_palabras=100, longitud_palabra=(3, 7), num_archivos=3)

