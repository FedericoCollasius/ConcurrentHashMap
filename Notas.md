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

Es una idea muy similar a claves. maximo() te asegura que te va a devolver el maximo en el momento que vos llamaste a la funcion. Quizas despues entro un thread que incremento una clave previa a la que estamos viendo actualmente y supero al maximo que habia pero
