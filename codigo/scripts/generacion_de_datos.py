import random
import string
import os
import nltk
from nltk.corpus import words, cess_esp

nltk.download('words')

def generar_archivo_datos(num_palabras=1000, longitud_palabra=None, idioma=None, repeticion_unica_palabra=False):
    if idioma == "ingles":
        lista_palabras = [palabra for palabra in words.words() if (not longitud_palabra or longitud_palabra[0] <= len(palabra) <= longitud_palabra[1])]
    elif idioma == "espanol":
        lista_palabras = [palabra for palabra in cess_esp.words() if (not longitud_palabra or longitud_palabra[0] <= len(palabra) <= longitud_palabra[1])]
    else:
        lista_palabras = None

    todas_las_palabras = []
    for _ in range(num_palabras):
        if lista_palabras:
            palabra = random.choice(lista_palabras)
        else:
            if longitud_palabra:
                longitud_actual = random.randint(longitud_palabra[0], longitud_palabra[1])
                palabra = ''.join(random.choices(string.ascii_lowercase, k=longitud_actual))
            else:
                palabra = ''.join(random.choices(string.ascii_lowercase, k=random.randint(1, 15)))
        todas_las_palabras.append(palabra)

    if repeticion_unica_palabra:
        todas_las_palabras = [todas_las_palabras[0]] * num_palabras

    nombre_archivo = f"datos_{idioma if idioma else 'aleatorio'}_"
    if repeticion_unica_palabra:
        nombre_archivo += "repeticion_unica_"
    nombre_archivo += f"{num_palabras}palabras.txt"

    directorio = "data/archivos"
    if not os.path.exists(directorio):
        os.makedirs(directorio)
    with open(f"data/archivos/{nombre_archivo}", "w") as f:
        for palabra in todas_las_palabras:
            f.write(palabra + '\n')

    print(f"Archivo {nombre_archivo} generado!")


