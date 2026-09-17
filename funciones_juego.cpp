#include <iostream>
#include "funciones_juego.h"
#include "funciones_primarias.h"

using namespace std;

bool comparar_fichas(unsigned char ** ptr_contenido, short int fila_1, short int fila_2, short int columna_1,
    short int columna_2, short int num_columnas){
    // retorna true si son iguales, false si no
    if(obtener_ficha(ptr_contenido,num_columnas,fila_1,columna_1) != 1){
    return (obtener_ficha(ptr_contenido,num_columnas,fila_1,columna_1) == obtener_ficha(ptr_contenido,num_columnas,fila_2,columna_2));
    }
    else{
        return false;
    }
}

short int buscar_arriba(unsigned char ** ptr_contenido,short int fila, short int columna, short int num_columnas){
    short int cont = 0;
    while((fila-cont-1 >= 0) && comparar_fichas(ptr_contenido,fila,fila-cont-1,columna,columna,num_columnas)){
        cont += 1;
    }
    return cont;
}

short int buscar_abajo(unsigned char ** ptr_contenido,short int fila, short int columna, short int num_columnas, short int num_filas){
    short int cont = 0;
    while((fila+cont+1 < num_filas) && comparar_fichas(ptr_contenido,fila,fila + cont + 1,columna,columna,num_columnas)){
        cont += 1;
    }
    return cont;
}

short int buscar_izquierda(unsigned char ** ptr_contenido,short int fila, short int columna, short int num_columnas){
    short int cont = 0;
    while((columna-cont-1 >= 0 ) && comparar_fichas(ptr_contenido,fila,fila,columna,columna - cont - 1,num_columnas)){
        cont += 1;
    }
    return cont;

}

short int buscar_derecha(unsigned char ** ptr_contenido,short int fila, short int columna, short int num_columnas){
    short int cont = 0;
    while((columna+cont+1 < num_columnas ) && comparar_fichas(ptr_contenido,fila,fila,columna,columna + cont + 1,num_columnas)){
        cont += 1;
    }
    return cont;
}
/*
void buscar_combinaciones(unsigned char ** ptr_contenido,short int num_filas, short int num_columnas){
    //hay que terminar esta funcion, mañana volverla a analizar, mañana si o si hay quie terminar codigo
    for(short int fila = 0; fila < num_filas; fila++){
        for(short int columna = 0; columna < num_columnas; columna++){

            short int arriba = buscar_arriba(ptr_contenido,fila,columna,num_columnas);
            short int abajo = buscar_abajo(ptr_contenido,fila,columna,num_columnas,num_filas);
            if(arriba + abajo >= 2){
                for(short int fila_2 = fila-arriba; fila_2 <= fila+abajo ; fila++){
                    short int derecha_2 = buscar_derecha(ptr_contenido,fila_2,columna,num_columnas);
                    short int izquierda_2 = buscar_izquierda;
                    if (derecha_2 + izquierda_2 > 2){
                        for(short int columna_2 = columna - izquierda_2; columna_2 < columna + derecha_2; columna++){
                            cambiar_ficha(ptr_contenido,num_columnas,fila_2,columna_2,1);
                        }
                    }
                }
            }
            short int izquierda = buscar_izquierda(ptr_contenido,fila,columna,num_columnas);
            short int derecha= buscar_derecha(ptr_contenido,fila,columna,num_columnas);


        } 
    }  
}

*/