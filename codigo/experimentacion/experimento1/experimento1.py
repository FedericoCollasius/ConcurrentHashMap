import matplotlib.pyplot as plt

cantidadThreads = []
tiempo = []

with open("resultados/resultados_cargaArchivosConYSinThreads.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    for linea in archivo:
        partes = linea.split()  
        if len(partes) == 2:  
            cantidadThreads.append(int(partes[0]))
            tiempo.append(float(partes[1]))


plt.plot(cantidadThreads, tiempo,  color="b" , marker='x')


# Personalizar el gráfico
plt.xlabel('Cantidad de threads')
plt.ylabel('Tiempo (s)')
plt.title('Tiempo en busqueda maximo vs threads')
plt.legend(loc='best')
plt.show()