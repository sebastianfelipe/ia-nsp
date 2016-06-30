# ia-nsp

Este programa está habilitado como código libre en Git-Hub

Básicamente se compila con make y se limpian los archivos extras con make clean
La ejecución es bastante sencilla. Luego de compilar, se generará un archivo llamado nsp,
el cual se ejecuta de la siguiente manera:

./nsp instancia

Las instancias están dentro de la carpeta instances. Por ejemplo, si la instancia
a ejecutar es la 25_7_4_1.nsp, entonces esta instancia se ejecutaría con la
siguiente sentencia:

./nsp instances/25_7_4_1.nsp

Si se quieren modificar parámetros del flujo principal del algoritmo,
se debe hacer dentro del archivo main.cxx

Si se desea modificar parámetros del problema y de la
ejecución del algoritmo evolutivo, entonces
se debe hacer dentro de la definición del constructor de Hospital,
ubicado en hospital.cxx

Si se desea debuguear el programa, es decir, hacer un seguimiento de
todas las mejores soluciones posibles, a medida que vayan apareciendo
habilitar DEBUG en true, dentro del archivo main.cxx

En carpeta results se pueden encontrar los siguientes experimentos:
* general:
- using seed 10 and population 4 restarts 20 
- varying general probability .2 (2), .5 (5), .8 (8)

* seed:
- using .5 general probability and population 4
- varying seed 4,10,20,50 and 100

* population
- using seed 10 and general probability .8
- varying population 4 8 12