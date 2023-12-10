import matplotlib.pyplot as plt

cantPalabras = []
tiempoSinConcurrencia = []
tiempoConConcurrencia = []

with open("exp5_12threads_6720000palabras.txt", "r") as archivo:
#with open("resultados/.txt", "r") as archivo:
    # for linea in archivo:
    #     partes = linea.split()  
    #     if len(partes) == 2:  
    #         cantidadArchivos.append(int(partes[0]))
    #         tiempo.append(float(partes[1]))
    for linea in archivo:
        valores = [float(valor) for valor in linea.split()]
        
        # Asegurarse de que hay al menos tres valores en la línea
        if len(valores) >= 3:
            # Asignar los valores a los vectores respectivos
            cantPalabras.append(int(valores[0]))
            tiempoSinConcurrencia.append(valores[1])
            tiempoConConcurrencia.append(valores[2])

print("cantPalabras:", cantPalabras)
print("tiempoSinConcurrencia:", tiempoSinConcurrencia)
print("tiempoConConcurrencia:", tiempoConConcurrencia)

# plt.plot(cantidadArchivos, tiempo, label="12 Thread", color="b" , marker='x')

plt.plot(cantPalabras, tiempoSinConcurrencia, label='Sin Concurrencia')
plt.plot(cantPalabras, tiempoConConcurrencia, label='Con hashMap')
# # Personalizar el gráfico
plt.xlabel('Cantidad de palabras')
# plt.xticks(range(1,len(cantidadArchivos)+1), range(1,len(cantidadArchivos)+1))
plt.ylabel('Tiempo (ms)')
plt.title('Tiempo en buscar la cantidad de repeticiones\n')
plt.legend(loc='best')
plt.show()