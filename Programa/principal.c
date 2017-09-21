#include <stdio.h>
#include "funciones.c"
#include <string.h>

int main()
{    
    char nombre[25];
    int *arregloEntrada;
    int *arregloSalida;
    int *arregloIntermedio;
    arregloEntrada = (int*)malloc(sizeof(int)*3);
    arregloIntermedio = (int*)malloc(sizeof(int)*3);
    arregloSalida = (int*)malloc(sizeof(int)*3);
    Tablero *matriz;
    matriz = NULL;
    Position *estadosPendientes;
    Position *estadosCerrados;
    Position *estadosActuales;
    Position *estadosPendientesB;
    Position *estadosCerradosB;
    Position *estadosActualesB;
    int opcion;
    int paso = 0;

    do
    {
        printf( "\n   1. Cargar Tablero");
        printf( "\n   2. Mostrar tablero cargado");
        printf( "\n   3. Buscar Llave" );
        printf( "\n   4. Buscar Salida " );
        printf( "\n   5. Creditos" );
        printf( "\n   6. Salir" );
        printf( "\n\n   Introduzca opcion (1-6): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        switch ( opcion )
        {
            case 1: printf(" Ingrese el nombre del archivo del laberinto ");
                    scanf("%s",nombre);
                    matriz = cargar(nombre);
                    break;

            case 2: if (matriz != NULL)
                    {
                        print(matriz);
                        break;
                    }
                    printf("Primero debe cargar alguna matriz, elegir opcion 1 \n");
                    break;

            case 3: if (matriz != NULL)
                    {
                        arregloEntrada = buscarPos(matriz,'E');
                        arregloIntermedio = buscarPos(matriz,'K');
                        estadosActuales = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
                        estadosCerrados = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));    
                        estadosPendientes = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
                        buscarCamino(matriz,estadosActuales,estadosCerrados,estadosPendientes,arregloEntrada,'K',arregloIntermedio);
                        paso = 1;
                        break;
                    }
                    printf("Primero debe cargar alguna matriz, elegir opcion 1 \n");
                    break;

            case 4: if (matriz != NULL && paso != 0)
                    {
                        arregloEntrada = buscarPos(matriz,'E');
                        arregloSalida = buscarPos(matriz,'S');
                        estadosActualesB = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
                        estadosCerradosB = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));    
                        estadosPendientesB = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
                        buscarCamino(matriz,estadosActualesB,estadosCerradosB,estadosPendientesB,arregloIntermedio,'S',arregloSalida);
                        break;
                    }
                    if (paso == 0 && matriz != NULL)
                    {
                    	printf("Primero debe buscar el camino hacia la llave\n");
                    	break;
                    }
                    if (matriz == NULL)
                    {
                    	printf("Primero debe cargar alguna matriz, elegir opcion 1 \n");
                    	break;
                    }
                    break;

            case 5: printf(" * Autor: CRISTIAN EDUARDO ESPINOZA SILVA \n ");
                    printf(" * Universidad santiago de chile \n");
                    break;
        }

    }while(opcion!=6);

    return 0;
}
