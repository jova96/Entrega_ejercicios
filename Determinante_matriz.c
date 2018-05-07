/*funcion que calcula el determinante de una matriz , los parametros que recibe*/
/*son la matriz , un puntero donde guardar el determinante y el rango */
/*la funcion devuelve un status_t , verifica que el rango sea el permitido (1,2,3)*/
/*por que esta funcion solo calcula el determinante para esos rangos*/
/*para el rango se utilizo una variable tipo size_t por lo tanto se tiene que*/
/*validar antes de ingresar a la funcion*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_FILAS 2

typedef enum{ST_OK ,
			 ST_RANGO_MATRIZ_INCALCULABLE ,
			 ST_PUNTERO_NULL } status_t ;

status_t determinante_matriz( int pptr_matriz[][MAX_FILAS] ,
							  int * determinante ,
							  size_t rango_matriz );

int main(void){
	/*int pptr_matriz[][MAX_FILAS] = {{5,2,1},{0,4,1},{0,0,2}};*/
	int pptr_matriz[][MAX_FILAS] = {{2,1},{0,2}};
	int  determinante ;
	if(determinante_matriz(pptr_matriz,&determinante,MAX_FILAS ) != ST_OK){
		fprintf(stderr,"ERROR\n");
	}
	printf("el determinante es: %i\n", determinante);
	return EXIT_SUCCESS;
}

status_t determinante_matriz( int pptr_matriz[][MAX_FILAS] ,
							  int * determinante ,
							  size_t rango_matriz )
{
	int pos_fila;
	int pos_fila_inferior;
	int pos_fila_superior;

	if( pptr_matriz == NULL || determinante == NULL ){
		return ST_PUNTERO_NULL;
	}
	if(rango_matriz > 3 || !rango_matriz){
		return ST_RANGO_MATRIZ_INCALCULABLE;
	}
/*ya se valido que el rango sea el permitido para esta funcion (1,2,3)*/
	if(rango_matriz == 3){
		for(determinante[0]=0 , pos_fila = rango_matriz - 1 , pos_fila_superior = 0;
			pos_fila >= 0 ;
			pos_fila_superior++){
			for(pos_fila_inferior = pos_fila_superior + 1 ;
				pos_fila_inferior < rango_matriz  ;
				pos_fila-- , pos_fila_inferior
/*el determinante se calcula con los coeficientes de la primer columna (0)y */
/*tomando los subdeterminantes de las columnas 2 y 3*/
/*(o 1 y 2 , en C las columnas son 0, 1 y 2 )*/
					determinante[0] +=
									  pptr_matriz[pos_fila][0]*
									  (pptr_matriz[pos_fila_superior][1]
									  *(pptr_matriz[pos_fila_inferior][2])
									  - (pptr_matriz[pos_fila_superior][2])
									  *(pptr_matriz[pos_fila_inferior][1]));
					if( pos_fila%2){
						determinante[0] = (-1) * (determinante[0]);
					}
			}
		}
	return ST_OK;
	}
	else if(rango_matriz == 2){
		determinante[0] = pptr_matriz[0][0]*(pptr_matriz[1][1])
						  - pptr_matriz[1][0]*(pptr_matriz[0][1]);
		return ST_OK;
	}
	else{
		determinante[0] = pptr_matriz[0][0];
		return ST_OK;
	}
}
