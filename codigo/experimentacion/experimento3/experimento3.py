import matplotlib.pyplot as plt

cantidadArchivosThread1 = []
tiempoThread1 = []

with open("resultados/divir_archivos_thread_1.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    for linea in archivo:
        partes = linea.split()  
        if len(partes) == 2:  
            cantidadArchivosThread1.append(int(partes[0]))
            tiempoThread1.append(float(partes[1]))


plt.plot(cantidadArchivosThread1, tiempoThread1, label = "1 threads" ,  color= '#fc0303' , marker='x')

cantidadArchivosThread2 = []
tiempoThread2 = []

with open("resultados/divir_archivos_thread_2.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    for linea in archivo:
        partes = linea.split()  
        if len(partes) == 2:  
            cantidadArchivosThread2.append(int(partes[0]))
            tiempoThread2.append(float(partes[1]))


plt.plot(cantidadArchivosThread2, tiempoThread2, label = "2 threads" ,  color='#fc4e03' , marker='x')

cantidadArchivosThread3 = []
tiempoThread3 = []

with open("resultados/divir_archivos_thread_3.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    for linea in archivo:
        partes = linea.split()  
        if len(partes) == 2:  
            cantidadArchivosThread3.append(int(partes[0]))
            tiempoThread3.append(float(partes[1]))


plt.plot(cantidadArchivosThread3, tiempoThread3, label = "3 threads" ,  color='#fcc203' , marker='x')

cantidadArchivosThread4 = []
tiempoThread4 = []

with open("resultados/divir_archivos_thread_4.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    for linea in archivo:
        partes = linea.split()  
        if len(partes) == 2:  
            cantidadArchivosThread4.append(int(partes[0]))
            tiempoThread4.append(float(partes[1]))


plt.plot(cantidadArchivosThread4, tiempoThread4, label = "4 threads" ,  color='#b1fc03' , marker='x')

cantidadArchivosThread5 = []
tiempoThread5 = []

with open("resultados/divir_archivos_thread_5.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    for linea in archivo:
        partes = linea.split()  
        if len(partes) == 2:  
            cantidadArchivosThread5.append(int(partes[0]))
            tiempoThread5.append(float(partes[1]))


plt.plot(cantidadArchivosThread5, tiempoThread5, label = "5 threads" ,  color='#005903' , marker='x')

cantidadArchivosThread6 = []
tiempoThread6 = []

with open("resultados/divir_archivos_thread_6.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    for linea in archivo:
        partes = linea.split()  
        if len(partes) == 2:  
            cantidadArchivosThread6.append(int(partes[0]))
            tiempoThread6.append(float(partes[1]))


plt.plot(cantidadArchivosThread6, tiempoThread6, label = "6 threads" ,  color='#00ffb7' , marker='x')

cantidadArchivosThread7 = []
tiempoThread7 = []

with open("resultados/divir_archivos_thread_7.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    for linea in archivo:
        partes = linea.split()  
        if len(partes) == 2:  
            cantidadArchivosThread7.append(int(partes[0]))
            tiempoThread7.append(float(partes[1]))


plt.plot(cantidadArchivosThread7, tiempoThread7, label = "7 threads" ,  color='#00c3ff' , marker='x')

cantidadArchivosThread8 = []
tiempoThread8 = []

with open("resultados/divir_archivos_thread_8.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    for linea in archivo:
        partes = linea.split()  
        if len(partes) == 2:  
            cantidadArchivosThread8.append(int(partes[0]))
            tiempoThread8.append(float(partes[1]))


plt.plot(cantidadArchivosThread8, tiempoThread8, label = "8 threads" ,  color='#0037ff' , marker='x')


# Personalizar el gráfico
plt.xlabel('Cantidad de archivos')
plt.ylabel('Tiempo (s)')
plt.title('Cantidad de archivos vs tiempo')
plt.legend(loc='best')
plt.show()