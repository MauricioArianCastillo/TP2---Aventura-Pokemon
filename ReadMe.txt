

                                        Read Me
                                -------------------------------


Lineas de compilacion:
---------------------

Para compilarlo la linea es: gcc lista.c heap.c cargas.c batallas.c menu.c -o pruebas 

Para correrlo: ./pruebas

Para correrlo con valgrind: valgrind ./pruebas

Para correr mis pruebas de carga: gcc lista.c heap.c cargas.c pruebas_cargas.c -o pruebas

Para correrlo: ./pruebas

Para correrlo con valgrind: valgrind ./pruebas

Introduccion:
------------

El trabajo consta de la implementacion de un juego de pokemones la cual hago en diferentes archivos. Los archivos son cargas.c, batallas.c y menu.c. A lo largo de la implementacion estuve usando 2 TDA, los cuales son la lista, y el heap.
El heap lo utilizo para almacenar los gimnasios, y la lista la utilizo en diferentes ocaciones las cuales voy a detallar mas abajo.

Implementacion:
--------------
cargas.c:
--------

En este archivo utilizo la libreria cargas.h la cual contiene las estructuras que voy a utilizar. Algunas aclaraciones:

-pokemon_t: decidi ponerle nombre, velocidad, defensa, ataque y un contador para el bonificador.
-entrenador_t: decidi usar una lista para almacenar los pokemones ya que me resultaba mas comodo por sus funciones. La alternativa podria haber sido crear un vector dinamico de pokemones pero no me gustaba la idea de hacer realloc.
-gimnasio_t: decidi usar una lista para entrenadores ya que de esa manera es mas sencillo almacenar estructuras dinamicas. Ademas el id_puntero_funcion seria para saber con que funcion de batalla se va a jugar las batallas del gimnasio.
-personaje_t: nuevamente decidi usar una lista para pokemones obtenidos y pokemones para combatir, porque es mas sencillo a la hora de hacer las cargas y desenvolverme en la implementacion del juego.

Luego en cargas.c implemento las 3 funciones de cargas.h que son cargar_gimnasios, cargar_personaje, y destruir personaje:

-cargar gimnasios: Es una funcion que retorna un heap cargado con los gimnasios. Antes de empezar a cargar los gimnasios, creo un heap y les paso mis funciones para comparar gimnasios y destruirlos. Luego abro el archivo con la ruta del archivo pasada por parametro, y con mis formatos de lectura para cada estructura y para la letra que identifica a cada estructura, busco hacer un corte de control utilizando 3 ciclos while anidados para que, a medida que lee la primer letra sepa si es un gimnasio entrenador o pokemon y luego de eso lea con el formato de lectura para cada estructura dentro de cada ciclo, para asi ir insertando hasta el final del archivo los pokemones en la lista del entrenador, los entrenadores en la lista de entrenadores del gimnasio y los gimnasios en el heap. Cosas que tuve en cuenta: Cree modulos que reservan la memoria para un gimnasio, un entrenador y un pokemon, para luego en la carga de gimnasios, ir insertando diferentes bloques de memoria en cada lista o heap, y de esa manera no tener que hacer un vector dinamico y hacerle realloc cada vez que quiera insertar un nuevo pokemon, entrenador o gimnasio. Por otra parte fui elegi usar el TDA pila para apilar los entrenadores, para poder enfrentarme del peor al mejor.

-cargar_personaje: Esta funcion carga el personaje y lo retorna. Abro el archivo con la ruta del mismo pasada por parametro y luego empiezo a leer, la primera letra y luego leo el personaje. Despues de eso creo el personaje y leo los pokemones, y mientras los creo y cargo la informacion los voy insertando en las listas de mi personaje, para asi al final asignar todo a mi personaje y finalmente retornarlo. 

-destruir_personaje: Esta funcion recibe como parametro el personaje, y recorre sus dos listas liberando todos sus pokemones, sus listas y finalmente el personaje.

menu.c:
------

Menu de inicio:

-Carga de gimnasios: llama a la funcion case_A que con la funcion de cargar_gimnasios del archivo cargas.c devuelvo el heap cargado.
-Carga de personaje: llama a la funcion case_E que con la funcion de cargar_personaje del archivo cargas.c devuelvo el personaje cargado.
-Iniciar partida: Con validar cargas verifica que los archivos esten cargados antes de iniciar la partida. Luego llama a case_I, la cual me lleva a menu gimnasio y pasa por parametro un bool terminar, que devuelve true si eligio terminar o si termino.
-Simulacion: Con validar cargas verifica que los archivos esten cargados antes de iniciar la partida. Luego llama a case_S, la cual llama a la funcion simulacion, enviandole por parametro el gimnasio, entrenador, la cantidad de entrenadores, siguiente, terminar y el tope del heap. Luego devuelve terminar=true si desea terminar, siguiente=true si desea avanzar al siguiente gimnasio. Elegi usar la variable tope en vez de usar heap->tope (tienen el mismo valor) para evitar y solucionar errores de memoria. Si el tope es mayor o distinto de cero extraer raiz del heap y reasignar el gimnasio al siguiente gimnasio. Porque esa condicion? Porque si extraigo el ultimo gimnasio con extraer raiz se pierde un bloque de memoria, en cambio si se lo dejo a la funcion de heap_destruir se destruye todo correctamente.

Menu de gimnasio:

-Mostrar personaje con sus pokemones: llama a case_E_gym, la cual llama a mostrar_personaje el cual imprime el personaje con todos sus pokemones.
-Mostrar la informacion del gimnasio actual: llama a case_G, la cual llama a mostrar_gimnasio el cual imprime el gimnasio con sus enrtenadores y sus pokemones.
-Cambiar los pokemones de batalla: Llama a la funcion cambiar_pokemones la cual muestra todos los pokemones y luego segun lo que haya ingresado el usuario, realiza el swap.
-Jugar la siguiente batalla: llama a case_B, la cual llama a la funcion menu_batalla, enviandole por parametro el gimnasio, entrenador, la cantidad de entrenadores, reintentar, terminar y el tope del heap. Luego si terminar es true termina, sino elimino el gimnasio y avanzo al siguiente.

Menu de batalla:

-Hago un switch que dependiendo del id del gimnasio, llama a la funcion batalla para realizar las batallas contra los pokemones de un entrenador y devuelve su resultado. Si gano contra el lider llama a menu victoria. Si perdio llama a menu_derrota pudiendo elegir cambiar pokemones, reintentar la batalla o finalizar la partida. Y si gano contra un entrenador avanzar al siguiente. En este ultimo caso voy recorriendo la pila de entrenadores hasta llegar al lider.
-batalla: creo dos iteradores para recorrer la lista de pokemones de mi personaje y la del entrenador del gimnasio. Informo las caractersticas de cada uno y llamo a la funcion batalla. Luego dentro de un ciclo while uso un contador para, en el caso de que gane mi pokemon, cambiar hasta 5 veces el pokemon del rival, luego sumo el bonificador con sumar_estadisticas. En el caso que mi pokemon pierda con el rival sumo las estadisticas del pokemon rival y mientras el elemento del iterador tenga un siguiente avanzar a mi siguiente pokemon (hasta 5 veces). Luego destruyo los iteradores y devuelvo el resultado final.
-sumar estadisticas: suma los atributos del pokemon en 1, hasta un maximo de bonificador de 63. Para lograr esto, utilizo cantidad bonificador de mi pokemon para incrementarlo y utilizarlo como caso borde.

Simulacion:

La funcion simulacion es practicamente igual que el menu de batalla nada mas que solo informa si gano o perdio el gimnasio.

Menu derrota:

-Cambiar pokemones: cambia los pokemones llamando a la funcion cambiar_pokemones.
-Reintenta la batalla: le digo al puntero booleano que sea verdadero, asi cuando vuelve al menu batalla sepa que quiero reintentar la batalla y vuelva a jugar la batalla.

Menu victoria: 

-opcion_victoria: Imprime el menu de victoria y devuelve la opcion.
-Obtener un pokemon del lider: Muestro los pokemones del lider y le digo al usuario que elija el que quiera con un numero. Luego obtengo ese pokemon y lo elimino de la lista del lider, para insertarlo en la lista de pokemones obtenidos del personaje. Ademas le digo al bool t que sea verdadero, asi cuando vuelve a leer la opcion
-Cambiar pokemones: Cambia los pokemones con cambiar_pokemones.
-Proximo Gimnasio: le digo al bool* que sea verdadero, asi cuando vuelve al menu batalla y luego al menu gimnasio, sepa que quiero avanzar al siguiente gimnasio.
-Victoria: Si el personaje derroto a todos los gimnasios se le informa que se convirtio en maestro pokemon



