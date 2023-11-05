# 1.

1. Creamos un nuevo nodo con el valor dado.
2. Guardamos el valor actual de la cabeza de la lista en cabeza_antigua.
3. Hacemos que el siguiente nodo después del nuevo nodo sea la antigua cabeza (esto es lo que nos permite insertar al principio de la lista).
4. Usamos compare_exchange_weak para intentar establecer la cabeza de la lista al nuevo nodo. Si \_cabeza todavía apunta a cabeza_antigua, devuelve true y \_cabeza se actualiza para apuntar al nuevo nodo. Si \_cabeza ya no apunta a cabeza_antigua (otro thread modifico la lista mientras estabamos entrando), entonces compare_exchange_weak actualiza automáticamente cabeza_antigua al valor actual de \_cabeza y regresamos al comienzo del ciclo do-while para probar de nuevo.

## ¿Qué significa que la lista sea atómica?

Significa que la insercion en la lista se hace sin que se interrumpa, o un proceso espera a tener premiso para hacerla.

## ¿Si un programa utiliza esta lista atómica, queda protegido de incurrir en condiciones de carrera?

A la hora de insertar un nuevo elemento a la lista se asegura que el programa no incurra en condiciones de carrea.

## ¿Cómo hace su implementación de insertar para cumplir la propiedad de atomicidad?

Utilizamos la función compare_exchange_weak para intentar actualizar el puntero \_cabeza de manera atómica. En caso de no lograrlo se vuelve a repetir.

# 2.

Nos basamos principalmente en la idea que necesitamos garantizar que solo haya contención en caso de colisión de hash. Es decir, si dos o más threads intentan incrementar claves que caen en el mismo bucket, deben ser sincronizados. Pero si las claves caen en diferentes buckets, las operaciones deben ser concurrentes sin bloqueo.

Pensamos en un array de mutex compartidos (shared_mutex), donde cada mutex protege un bucket específico de la tabla de hash. La particularidad del shared_mutex es que protege datos compartidos de ser accedidos simultanemante por multiples procesos. Son especialmente útiles cuando los datos compartidos pueden ser leídos de manera segura por cualquier número de proceso simultáneamente, pero un proceso solo puede escribir los mismos datos cuando ningún otro proceso está leyendo o escribiendo al mismo tiempo. A diferencia de otros tipos de mutex que facilitan el acceso exclusivo, un shared_mutex tiene dos niveles de acceso: - compartido (shared): varios threads pueden tener el mismo mutex. Si un proceso lo ha adquirido (lock_shared()), ningún otro proceso puede adquirir el bloqueo exclusivo, pero puede adquirir el bloqueo compartido. - exclusivo: solo un thread puede poseer el mutex. Si un proceso lo adquirio (lock()), ningún otro proceso puede adquirir el bloqueo (incluido el compartido).
Solo cuando el exclusivo no ha sido adquirido por ningún proceso, el compartido puede ser adquirido por múltiples hilos. Dentro de un mismo hilo, solo se puede adquirir un bloqueo (compartido o exclusivo) al mismo tiempo.
La razon principal para usar shared_mutex en vez de un mutex es para que los procesos que solamente quieran leer no tengan que esperar de mas.
Referencia: https://en.cppreference.com/w/cpp/thread/shared_mutex

## Incrementar

De esta manera, cuando queremos incrementar una clave, bloqueamos el mutex del bucket correspondiente usando lock(), permitiendo que otros threads modifiquen otros buckets simultáneamente.

## Claves

La funcion claves te asegura que te va a devolver las claves que habia en el instante que las pediste. Ademas, al estar protegida por lock_shared() varios threads pueden acceder a la vez y leer las claves que hay. A medida que vamos recopilando las claves de una lista vamos liberando el mutex compartido asocidado a esa lista de manera que un proceso ya podria entrar y escribir una nueva clave en posiciones previas de las que estamos actualmente.

## Valor

La funcion valor(clave) funciona de manera similar. Solamente vamos a poder ver cuantas veces se guardo una clave si el mutex correspondiente a esa letra no lo tiene un proceso que quiere escribir en la lista donde se encuentra esa clave. Ademas mas de un proceso a la vez puede leer esa lista ya que funciona con la dinamica del lock_shared().

# 3.

# Maximo

Si las funciones maximo e incrementar se ejecutan concurrentemente sin mecanismos de sincronización pueden surgir problemas con condiciones de carrera.

- El thread A comienza a ejecutar maximo.
- El thread A identifica que "arbol" tiene la cuenta más alta (10) hasta ahora y comienza a comparar con otros valores en el HashMap.
- Antes de que el thread A termine, el thread B ejecuta incrementar varias veces para la palabra "anana", que estaba previo a "arbol" en el bucket llevandolo a 11.
- El hilo A continúa y termina su ejecución de maximo, identificando incorrectamente que "arbol" con una cuenta de 10 es la palabra más frecuente.

Sin embargo, la palabra más frecuente es en realidad "banana" con una cuenta de 11.

# MaximoParalelo

**Descripcion:**
MaximoParalelo busca el par clave-valor con el máximo valor en HashMapConcurrente de manera concurrente, utilizando múltiples threads.

**Estrategia para repartir el trabajo:**
Cada thread se le asigna una fila de la tabla a la vez. El trabajo se distribuye de que cuando un thread termina de procesar una fila, toma la siguiente fila disponible. Esta estrategia garantiza que todos los threads estén constantemente trabajando y que se maximice la concurrencia, ya que no hay threads inactivos hasta que todas las filas hayan sido procesadas.

**Recursos compartidos:**

- El HashMapConcurrente, ya que todos los threads leen de él.
- Un índice atómico (o contador) que rastrea qué fila está siendo procesado en tiempo real.
- Un vector de resultados donde cada thread guarda el valor máximo encontrado en los buckets que procesa.

**Protección contra condiciones de carrera:**

- La función incrementar en HashMapConcurrente debe ser thread-safe para manejar múltiples accesos concurrentes.
- El índice atómico se utiliza para garantizar que los threads accedan a las filas de manera exclusiva.
- El vector de resultados se accede de forma que cada thread escribe en una posición única, por lo que no hay condiciones de carrera.

# 4.

# CargarArchivo

No fue necesario tomar recaudos ya que de eso se ocupa la funcion incrementar que es la que le pasamos para cargar la clave.

# CargarMultiplesArchivos

Se introdujo una variable atómica, archivoActual, para tener el índice del archivo que se está procesando en tiempo real. Esto permite que cada thread sepa cuál es el siguiente archivo que debe procesar sin tener condiciones de carrera.
Cada thread obtiene el siguiente archivo a procesar basado en el valor de archivoActual, lo procesa, y luego avanza al siguiente, hasta que todos los archivos hayan sido procesados.
Se optó por el uso de variables y operaciones atómicas como fetch_add para garantizar que los threads no procesen el mismo archivo más de una vez y que no se salten archivos. Esta elección elimina la necesidad de bloqueos o mutexes adicionales para coordinar el acceso a la lista de archivos.

# 5.

**Objetivo:**
Evaluar que ventajas ofrece la ejecucion concurrente, en terminos de performance, a la hora de encontrar la palabra con mayor cantidad de apariciones en un conjunto de archivos.

**Hipótesis General:**
La ejecución concurrente, al utilizar múltiples threads para procesar los archivos en paralelo, ofrece una mejora significativa en el rendimiento en comparación con una ejecución secuencial, especialmente cuando tenemos muchos datos.
Sin embargo habra un limite ya que aumentar el número de threads más allá del número de núcleos físicos disponibles podría no ofrecer ganancias adicionales e incluso podría reducir el rendimiento debido al overhead de la gestión de threads y la contención.

## Posibles experimentos

**Escala de la concurrencia en maximoParalelo:**

- Hipótesis: Hay un punto donde agregar más threads no mejorará el rendimiento debido a la contención y el overhead de la gestión de threads.
- Experimento: Ejecutar la función maximoParalelo con un número creciente de threads mucho más allá del número de núcleos disponibles.
- Dudas para experimento:
  Cantidad de archivos? Longitud de las palabras? Cantidad de palabras? Cantidad de palabras que empiecen con la misma letra?

**Impacto de las operaciones de lectura vs. escritura:**

- Hipótesis: Las operaciones de escritura son más costosas en términos de sincronización que las de lectura.
- Experimento: Comparar el rendimiento cuando la mayoría de las operaciones son de lectura (por ejemplo, obtener el valor de una clave) versus cuando la mayoría son de escritura.
- Comentarios : Para el de lectura, que recorra todas las claves y nos devuelva la cantidad de repeticiones y para el de escritura, incrementar cada clave, esto por cada thread.

**Escala de la concurrencia en cargarMultiplesArchivos:**

- Hipótesis: Hay un punto donde agregar más threads no mejorará el rendimiento debido a la contención y el overhead de la gestión de threads.
- Experimento: Ejecutar la función cargarMultiplesArchivos con un número creciente de threads mucho más allá del número de núcleos disponibles.
- Dudas para experimento:
  Cantidad de archivos? Longitud de las palabras? Cantidad de palabras? Cantidad de palabras que empiecen con la misma letra? Cargar mismos archivos?

**Mismo conjunto de palabras en pocos o varios archivos:**

- Hipótesis: Va a convenir que el conjunto de palabras esten distribuidas equitativamentes en varios archivos para un mayor rendimiento, cercano a la cantidad de threads que tenga el procesador.
- Experimento: Ejecutar cargaMultiplesArchivos siempre con el mismo conjunto de palabras incrementando la cantidad de archivos. Ej: 1 archivo con 1000 palabras, luego 2 archivos con 500 palabras c/u ..... Esto por cada thread (4threads).
- Dudas para experimento:
  Longitud de las palabras? Cantidad de palabras? Cantidad de palabras que empiecen con la misma letra?
