# Ejercicio 1

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

# Ejercicio 2

Nos basamos principalmente en la idea que necesitamos garantizar que solo haya contención en caso de colisión de hash. Es decir, si dos o más threads intentan incrementar claves que caen en el mismo bucket, deben ser sincronizados. Pero si las claves caen en diferentes buckets, las operaciones deben ser concurrentes sin bloqueo.
Pensamos en un array de mutex, donde cada mutex protege un bucket específico de la tabla de hash. De esta manera, cuando queremos incrementar una clave, solo bloqueamos el mutex del bucket correspondiente, permitiendo que otros threads modifiquen otros buckets simultáneamente. Esto ultimo es especifico para la funcion incrementar.
La funcion claves tambien esta protegida por esa dinamica. Es decir, solo voy a poder acceder a la lista enlazada de claves de una letra en particular en caso que ningun otro thread este actualmente agregando algo en esa lista. Igualmente puede suceder que un thread agregue una clave a una letra previa cuando otro thread siga recopilando las claves. Lo que pensaba que se podia hacer es liberar los mutex una vez que ya recorri todas las claves de todas las letras. Igualmente podria suceder esto ultimo pero reduciria las posibilidades.
La funcion valor(clave) funciona de manera similar. Solamente vamos a poder ver cuantas veces se guardo una clave si el mutex correspondiente a esa letra se libero.
