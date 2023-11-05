import matplotlib.pyplot as plt

colores = ['#FF5733', '#33FF57', '#5733FF', '#FF3399', '#99FF33', '#33B5E5', '#FF33CC', '#33CCFF', '#FF9933', '#9933FF', '#FF33A6', '#A633FF']

for i in range(1, 13):
    with open("resultados/divir_archivos_thread_" + str(i)+"_3raVuelta.txt", "r") as archivo:
        thread = []
        tiempo = []
        for linea in archivo:
            partes = linea.split()  
            if len(partes) == 2:  
                thread.append(int(partes[0]))
                tiempo.append(float(partes[1]))
    plt.plot(thread, tiempo, label = str(i) + " threads" ,  color=colores[i-1] , marker='x')


# Personalizar el gráfico
plt.xlabel('Cantidad de archivos')
plt.xticks(range(1,16))
plt.ylabel('Tiempo (ms)')
plt.title('Tiempo de carga para distintas cantidades de archivos y threads\n')
plt.legend(loc='best')
plt.show()