import matplotlib.pyplot as plt

cantidadArchivos = []
tiempo = []

with open("resultados/real_threads_12_16archivos.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    for linea in archivo:
        partes = linea.split()  
        if len(partes) == 2:  
            cantidadArchivos.append(int(partes[0]))
            tiempo.append(float(partes[1]))


plt.plot(cantidadArchivos, tiempo, label="12 Thread", color="b" , marker='x')


# Personalizar el gráfico
plt.xlabel('Cantidad de archivos')
plt.xticks(range(1,len(cantidadArchivos)+1), range(1,len(cantidadArchivos)+1))
plt.ylabel('Tiempo (ms)')
plt.title('Tiempo de carga de archivos para cantidad fija de threads\n')
plt.legend(loc='best')
plt.show()