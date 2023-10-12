import random
import string
import os
import nltk
from nltk.corpus import words

nltk.download('words')

def generar_archivo_datos(num_palabras=1000, longitud_palabra=None, idioma=True, repeticion_unica_palabra=False):
    if idioma:
        todas_las_palabras = words.words()
        if longitud_palabra:
            todas_las_palabras = filtrar_por_longitud(todas_las_palabras, longitud_palabra)
    else:
        todas_las_palabras = generar_palabras_aleatorias(num_palabras, longitud_palabra)
    
    if repeticion_unica_palabra:
        todas_las_palabras = [todas_las_palabras[0]] * num_palabras

    nombre_archivo = construir_nombre_archivo(idioma, repeticion_unica_palabra, num_palabras)

    guardar_archivo(todas_las_palabras, nombre_archivo)
    print(f"Archivo {nombre_archivo} generado")

def filtrar_por_longitud(lista, longitud):
    return [palabra for palabra in lista if longitud[0] <= len(palabra) <= longitud[1]]

def generar_palabras_aleatorias(num_palabras, longitud_palabra):
    if longitud_palabra:
        return [''.join(random.choices(string.ascii_lowercase, k=random.randint(longitud_palabra[0], longitud_palabra[1]))) for _ in range(num_palabras)]
    else:
        return [''.join(random.choices(string.ascii_lowercase, k=random.randint(1, 15))) for _ in range(num_palabras)]

def construir_nombre_archivo(idioma, repeticion_unica_palabra, num_palabras):
    nombre = f"datos_{'idioma' if idioma else 'aleatorio'}_"
    if repeticion_unica_palabra:
        nombre += "repeticion_unica_"
    nombre += f"{num_palabras}palabras.txt"
    return nombre

def guardar_archivo(palabras, nombre_archivo):
    directorio = "data/archivos"
    if not os.path.exists(directorio):
        os.makedirs(directorio)
    with open(f"data/archivos/{nombre_archivo}", "w") as f:
        for palabra in palabras:
            f.write(palabra + '\n')



# Ejemplo 
generar_archivo_datos(num_palabras=100, longitud_palabra=(3, 7), palabras_reales=True)

