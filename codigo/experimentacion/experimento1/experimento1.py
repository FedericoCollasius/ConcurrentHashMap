import matplotlib.pyplot as plt

cantidadThreads = []
tiempo = []

with open("resultados/resultados_cargaArchivosConYSinThreads6threads.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    for linea in archivo:
        partes = linea.split()  
        if len(partes) == 2:  
            cantidadThreads.append(int(partes[0]))
            tiempo.append(float(partes[1]))


plt.plot(cantidadThreads, tiempo,  color="b" , marker='x')

# Personalizar el gráfico
plt.xlabel('Cantidad de threads')
plt.xticks(range(1,len(cantidadThreads)+1),range(1,len(cantidadThreads) + 1))

plt.ylabel('Tiempo (ms)')
plt.title('Tiempo de inserción para diferentes threads\n')
plt.legend(loc='best')
plt.show()