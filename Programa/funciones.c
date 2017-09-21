#include <stdio.h>
#include "struct.h"
#include <string.h>
#include <stdlib.h>

int contuni = 0;
int contcerrados = 0;
int origen = 0 ;
int entrada = 0;
int conactual = 0;
int bandera = 0;
int recorrido = 0;
int vuelta = 0;

Tablero *cargar(char nombre[])
{
    FILE *archivo; // Declaramos un puntero File para poder leer el archivo de entrada.

    archivo = fopen (nombre, "r"); // Estamos abriendo el archivo en modo lectura

    Tablero *matriz; // Declaramos un variable de tipo de la structura tablero.
    int caracter;

    //Verificamos si el archivo se encuentra nulo
    if( archivo == NULL)
    {
        printf("Error al abrir archivo \n");
        return 0;
    }
    
    int fila,columna;
    fscanf(archivo, "%d %d", &fila, &columna); //Primero leemos las dimensiones del tablero.

    matriz = createBoard(fila,columna); //Creamos un tablero con las dimensiones que tendra el tablero

    while(getc(archivo) != '\n'); // Que lea el archivo siempre y cuando no sea un salto de linea

    int i,j;

    for(i = 0; i < matriz->fila; i++)
    {
        for(j = 0; j <= matriz->columna; j++)
        {
            matriz->mapa[i][j] = getc(archivo); // Cada caracter que lea sera almacenado en la variable de tipo (struct Tablero)
        }

        char c;
        while((c = getc(archivo)) == '\n' || c == '\r');
        fseek(archivo, -1, SEEK_CUR);
    }

    fclose(archivo); // Cerramos el archivo
 
    return matriz; //Retornamo la variable matriz, con el tablero contenido, el cual se leyó desde el archivo ingresado
}

void print(Tablero *matriz)
{
    for (int i = 0; i < matriz->fila; i++)
    {
        for (int j = 0; j < matriz->columna; j++)
        {
            printf("%c", matriz->mapa[i][j]); //Imprimos por pantalla cada una de las caracteristicas que guarda dentro de si el tablero
        }
        printf("\n");
    }
}

Tablero* createBoard(int n,int m)
{
    int i,j;
    // Procedemos a crear una variable de tipo Tablero y a solicitar memoria para dicha variable
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));

    matriz->mapa = (char**)malloc(n*sizeof(char*)); // Inicializamos una de variables que contiene nuestra estructura con tantas filas diga el archivo
    matriz->fila = n;
    matriz->columna = m;

    for (i=0; i<n ;i++)
    {
        matriz->mapa[i] = (char*)malloc(m*sizeof(char)); // Aca inicializamos las columnas que rescatamos desde el archivo

        for (j=0; j<m ;j++)
        {
            matriz->mapa[i][j] = 'X'; // Asignamos un elemento neutro que demostrara que el tablero esta creado pero no utilizado 
        }
    }

    return matriz; // retornamos el tablero inicilizado (con elemento que representa estar vacio)
}

int *buscarPos(Tablero *mapa, char busca)
{
    // Inicializamos la variable de tipo Tablero y solicitamos memoria para dicha variable
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));

    matriz = mapa; //Hacemos un asignacion respecto a la variable que estan pasando como parametro 
    // Declaramos un arreglo de interos para almacenar la posicion donde se encontrara la posicion que andamos buscando
    int *arreglo; 
    arreglo = (int*)malloc(sizeof(int)*3);
    int i,j;
    // Almacenamos el caracter que andamos buscando dentro de la matriz
    char e;
    e = busca;

    for (i=0; i<matriz->fila ;i++)
    {
        for (j=0; j<matriz->columna ;j++)
        {
            if(matriz->mapa[i][j] == e)
            {
                // Si cumple todas las condiciones anteriores, almacenados las posiciones de donde se encuentra el caracter que andamos buscando
                arreglo[0] = i;
                arreglo[1] = j;
            }
        }
    }

    return arreglo; //Retornamos el arreglo que contiene las posiciones donde se encuentra el caracter que andamos buscando.
}

int noEstarCerrado(int fila, int columna,Tablero *campo,Position *cerrados)
{
    // Inicializamos una variable de tipo Tablero y a la misma ves pedimos memoria para dicha variable y le asignamos el parametro que recibe
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));
    matriz = campo;
    // Inicialamos una variable de tipo Position, luego pedimos memoria y la asignamos a la variable que se esta pasando como parametro.
    Position *estadosCerrados;
    estadosCerrados = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna)); 
    estadosCerrados = cerrados;

    for (int i = 0; i < contcerrados; i++)
    {
        if (estadosCerrados[i].columna == columna && estadosCerrados[i].fila == fila) //En caso qe estas sean iguales
        {
            return 0; // Retornamos un 0, verificando que si se encuentra dentro del arreglos de estados cerrados
        }
    }

    return 1; // Si no se encuentra devolvemos un 1, que significa que dicha posicion no se encuentra en estados cerrados
}

int buscarCamino (Tablero *campo, Position *Actuales, Position *Cerrados, Position *Pendientes, int* posicion , char obj , int* posobj ) 
{
    // Inicializamos una variable de tipo Tablero y a la misma ves pedimos memoria para dicha variable y le asignamos el parametro que recibe
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));
    matriz = campo;

    int j,i;

    char objetivo;
    objetivo = obj;
    // Inicialamos una variable de tipo Position, luego pedimos memoria y la asignamos a la variable que se esta pasando como parametro.
    Position *estadosPendientes;
    Position *estadosCerrados;
    Position *estadosActuales;
    Position *ruta;
    Position *caminoC;
    Position *caminoaux;

    int* posicionActual = posicion;
    int* posobjetivo = posobj;

    estadosActuales = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    estadosCerrados = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));    
    estadosPendientes = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    caminoC = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    caminoaux = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));

    // Pedimos memroia para la rura que existe dentro de laberinto
    ruta = (Position*)malloc(sizeof(Position)*4);
    // Asiganmos cad una de las rutas posibles dentro del laberinto
    ruta[0].fila = 0; // 1
    ruta[0].columna = -1; // 0
    ruta[1].fila = 0; // -1
    ruta[1].columna = 1; //0
    ruta[2].fila = 1; // 0
    ruta[2].columna = 0; //1
    ruta[3].fila = -1; //0 
    ruta[3].columna = 0; //-1
    // Asignamos a cada una de las variables declaras, la variable que se esta recibiendo como parametro

    for (int z = 0 ; z < matriz->fila*matriz->columna; z++)
    {
        estadosPendientes[z] = Pendientes[z];
        estadosCerrados[z] = Cerrados[z];
        estadosActuales[z] = Actuales[z];
    }

    //estadosPendientes = Pendientes;
    //estadosCerrados = Cerrados;
    //estadosActuales = Actuales;
    // Agregamos el primer estado actual que seria la entrada del laberinto o la llave.
    if (entrada == 0)
    {
        estadosActuales[origen].fila = posicionActual[0];        
        estadosActuales[origen].columna = posicionActual[1];
        estadosActuales[origen].origen = origen;
        entrada = 1 ;
    } 
    // Caso base de la recursion, con el fin de llamar a la funcion que busca el camino correcto
    if (matriz->mapa[estadosActuales[origen].fila][estadosActuales[origen].columna] == objetivo)
    {
        // Hacemos el llamado a la funcion que se encarga de buscar el camino correcto hacia el objetivo que andamos buscando.
        caminoCorrec(estadosPendientes, estadosActuales,matriz,posicionActual,caminoC);
        return 0;
    }

    for (i = 0; i < 4; i++)
    {
        if ( (estadosActuales[origen].fila + ruta[i].fila) >= 0 && (estadosActuales[origen].columna + ruta[i].columna) >= 0 )
        {    
            if ( (estadosActuales[origen].fila + ruta[i].fila) < matriz->fila && (estadosActuales[origen].columna + ruta[i].columna) < matriz->columna )  
            {   
                if(matriz->mapa[(estadosActuales[origen].fila + ruta[i].fila)][(estadosActuales[origen].columna + ruta[i].columna)] != '*')
                {
                    if (noEstarCerrado( (estadosActuales[origen].fila + ruta[i].fila) ,(estadosActuales[origen].columna + ruta[i].columna) , matriz , estadosCerrados ) == 1 )
                    {
                        // Gregamos el nuevo estado abierto a los estados pendientes para que sean abiertos en su momento, ademas de agregar quine lo abrio
                        estadosPendientes[contuni].fila = (estadosActuales[origen].fila + ruta[i].fila);
                        estadosPendientes[contuni].columna = (estadosActuales[origen].columna + ruta[i].columna); 
                        estadosPendientes[contuni].origen = origen;
                        // Aumentamos el contador para no sobreescribir ningun estado pendiente
                        contuni++;
                    }
                }
            }
        }

        // Las siguientes 4 condiciones es para que el laberinto pueda ser de una manera circular.

        if ((estadosActuales[origen].fila + ruta[i].fila) == matriz->fila)
        {
            if ( matriz->mapa[0][(estadosActuales[origen].columna + ruta[i].columna)] != '*')
            {
                estadosPendientes[contuni].fila = 0;
                estadosPendientes[contuni].columna = (estadosActuales[origen].columna + ruta[i].columna); 
                estadosPendientes[contuni].origen = origen;
                contuni++;            
            }
        }

        if ((estadosActuales[origen].columna + ruta[i].columna) == matriz->columna)
        {
            if ( matriz->mapa[estadosActuales[origen].fila + ruta[i].fila][0] != '*')
            {
                estadosPendientes[contuni].fila = estadosActuales[origen].fila + ruta[i].fila;
                estadosPendientes[contuni].columna = 0; 
                estadosPendientes[contuni].origen = origen;
                contuni++;
            }   
        }

        if ((estadosActuales[origen].fila + ruta[i].fila) == -1)
        {
            if ( matriz->mapa[(matriz->fila) - 1][estadosActuales[origen].columna + ruta[i].columna] != '*')
            {
                estadosPendientes[contuni].fila = (matriz->fila) - 1;
                estadosPendientes[contuni].columna = estadosActuales[origen].columna + ruta[i].columna; 
                estadosPendientes[contuni].origen = origen;
                contuni++;
            }
        }

        if ((estadosActuales[origen].columna + ruta[i].columna) == -1)
        {
            if ( matriz->mapa[estadosActuales[origen].fila + ruta[i].fila][(matriz->columna) - 1] != '*')
            {
                estadosPendientes[contuni].fila = estadosActuales[origen].fila + ruta[i].fila;
                estadosPendientes[contuni].columna = (matriz->columna) - 1; 
                estadosPendientes[contuni].origen = origen;
                contuni++;
            }
        } 
    }

    // Aca declaramos el nuevo estado cerrado
    estadosCerrados[contcerrados].fila = estadosActuales[origen].fila;
    estadosCerrados[contcerrados].columna = estadosActuales[origen].columna;
    origen++;
    // Cambiamo el estado estado actual y colocamos el origen desde donde proviene, ademas de aumentar el origen para que cada estado actual tena un origen distinto.
    estadosActuales[origen].fila = estadosPendientes[contcerrados].fila;
    estadosActuales[origen].columna = estadosPendientes[contcerrados].columna;
    estadosActuales[origen].origen = origen;
    estadosPendientes[contcerrados].estado = 1; 
    // Aumentamos el contador de estados cerrados para asi no sobreescribir ninguno
    contcerrados++;
    // Hacemos el llamado recursivo dentro de la funcion
    buscarCamino(matriz,estadosActuales,estadosCerrados,estadosPendientes,posicionActual,obj,posobjetivo);

    return 1;
}

void caminoCorrec (Position *pendiente, Position *actuales, Tablero *campo, int* posicion, Position *caminoC) 
{
    // Inicializamos una variable de tipo Tablero y a la misma ves pedimos memoria para dicha variable y le asignamos el parametro que recibe
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));
    matriz = campo;
    // Inicializamos y soliciamos memoria para una variable de tipo Position, ademas le asiganmos la variable que se recibe como parametro.
    Position *estadosPendientes;
    Position *estadosActuales;
    Position *caminoFinal;
    int* posicionActual = posicion;

    estadosActuales = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    estadosPendientes = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    caminoFinal = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    // asiganmos cada uno de los estados a las variables que se estan recibiendo como parametros
    estadosPendientes = pendiente;
    estadosActuales = actuales;
    caminoFinal = caminoC;   
    // Agregamos el primero estado al recorrido final, ya que desde ahi parte el camino correcto hacia el objetivo que se desea
    if (bandera == 0 )
    {
        caminoFinal[recorrido].fila = estadosActuales[origen].fila;
        caminoFinal[recorrido].columna = estadosActuales[origen].columna;
        bandera = 1;
    }

    if (caminoFinal[recorrido].fila == posicionActual[0] && caminoFinal[recorrido].columna == posicionActual[1])
    {
        // Reiniciamos todas las variables globales que se ocuparon para asi volver a buscar en otra oprtunidad.
        contuni = 0;
        contcerrados = 0;
        origen = 0 ;
        entrada = 0;
        conactual = 0;
        bandera = 0;      
        // Hacemos el llamado a la funcion que se encarga de escribir el camino correcto dentro del archivo
        saveTablero (matriz,caminoFinal,"Salida.out");
        // Agregamos este contador para saber de que manera abrir el archivo, para no perder informacino dentro del archivo
        vuelta++;
        recorrido = 0;
    }

    else 
    {
        for (int i = 0; i <= contuni; i++)
        {
            if (estadosActuales[i].fila == caminoFinal[recorrido].fila && estadosActuales[i].columna == caminoFinal[recorrido].columna)
            {
                for (int j = 0; j <= contuni; j++)
                {
                    if (estadosActuales[i].fila == estadosPendientes[j].fila && estadosActuales[i].columna == estadosPendientes[j].columna) 
                    {
                        for (int z = 0; z < contuni; z++)
                        {
                            if (estadosPendientes[j].origen == estadosActuales[z].origen) 
                            {
                                // Aumentamos para asi no sobreescribir ninguna posiciones que lleva al camino hacia el objetivo 
                                recorrido++;
                                // Si cumple las condiciones finales agregamos a la lista de camino correcto las posiciones que sirven para llegar al objetivo
                                caminoFinal[recorrido].fila = estadosActuales[z].fila;
                                caminoFinal[recorrido].columna = estadosActuales[z].columna;
                                // Hacemos el llamado recursivo hasta encontrar el camino final para el objetivo
                                caminoCorrec (estadosPendientes,estadosActuales,matriz,posicionActual,caminoFinal);
                            }
                        }
                    }
                }
            }
        }
    }
}

void saveTablero (Tablero *campo, Position* camino1, char nombre[])
{    
    // Incializamos y solicitamos memoria para una variable de tipo Tablero, ademas le asiganamos la variable que recibimos como parametro
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));
    matriz = campo;
    // Inicializamos y soliciamos memoria para una variable de tipo Position, ademas le asiganmos la variable que se recibe como parametro.
    Position *camino;
    camino = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    camino = camino1;

    FILE *txt;  // Incialzamos una variable de tipo FILE para poder trabajar con los archivos

    // Hacemos una comparacion para verificar si es el primero o segundo camino que se esta recibiendo 
    if (vuelta == 0) 
    {
        txt = fopen(nombre, "wt"); // Abrimos le archivo en modo escritura y que se cree si no exite el archivo nombrado
    }

    else
    {
        txt = fopen(nombre, "a"); // Abrimos el archivo en modo sobreescritura, para no perder el camino anterior que esta en el archivo
        fprintf(txt,"\n");
        fprintf(txt,"\n");
    }

    for (int i = 0; i< matriz->fila ; i++)
    {
        for(int j = 0; j< matriz->columna ; j++)
        {
            if (verificar(matriz,camino,i,j) == 1)
            {
                fprintf(txt,"X"); // Escribimos con una X, si es camino se encuentra dentro del arreglo camino
            }
            else
            {
                fprintf(txt,"%c",matriz->mapa[i][j]); // En caso contratio escribimos lo que se enceuntre en esa posicion
            }
        }

        fprintf(txt,"\n"); // Para poder dar la forma de un tablero
    }

    fclose(txt); // Cerramos el archivo
}

int verificar (Tablero *campo, Position *camin,int fila , int columna)
{   
    //Inicializamos la variable de tipo Tablero y pedimos memoria para dicha variable, ademas asignamos la variable que esta recibiendo como parametro
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));
    matriz = campo;

    // Inicializamos una variable de tipo Position y solicitamos memoria para dicha variable, ademas le asignamos la varable que recibe como parametro la funcion.
    Position *camino;
    camino = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    camino = camin;

    for (int i = 0; i <= recorrido; i++)
    {
        if (fila == camino[i].fila && columna == camino[i].columna) // Verificamos si las posiciones pasadas como parametros pertenecen alguna del arreglo camino
        {
            return 1; // En caso verdadero se devuelve un 1, representado que se encuentra dentro del arreglo
        }              
    }

    return 0; // En caso que no se encuentre devolvemos un 0, demostrando que no se encuentre dentro del arreglo camino
}
