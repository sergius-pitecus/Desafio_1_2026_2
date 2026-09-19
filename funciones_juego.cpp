#include <iostream>
#include "funciones_juego.h"
#include "funciones_primarias.h"
#include <random>
using namespace std;

void print_tablero(unsigned char ** ptr_contenido, short int num_columnas, short int num_filas){
    cout<<"0  ";
    for (short int fila = 0; fila<num_filas;fila++){
        for(short int columna = 0; columna<num_columnas; columna++){
            unsigned char ficha_actual = obtener_ficha(ptr_contenido,num_columnas,fila,columna);

            switch (ficha_actual){
            
            case 1:
            cout<<"  ";
            break;
            
            case 2:
            cout<<"H ";
            break;

            case 3:
            cout<<"O ";
            break;
            
            case 4:
            cout<<"% ";
            break;

            case 5:
            cout<<"W ";
            break;

            case 6:
            cout<<"@ ";
            break;

            case 7:
            cout<<"$ ";
            break;
            
            default:
            cout<<"! ";
            break;
            }
        }
        cout<<"\n"<<fila+1<<"  ";
    }
    for(short int i = 0; i < num_columnas; i++){
        cout<<i<<" ";
    }
    cout<<"\n\n";
}

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

short int buscar_combinaciones(unsigned char ** ptr_contenido,short int num_filas, short int num_columnas){
    //hay que terminar esta funcion, mañana volverla a analizar, mañana si o si hay quie terminar codigo

    short int contador_combinaciones = 0;

    for(short int fila = 0; fila < num_filas; fila++){
        for(short int columna = 0; columna < num_columnas; columna++){
            if(obtener_ficha(ptr_contenido,num_columnas,fila,columna) != 1){
                short int arriba = buscar_arriba(ptr_contenido,fila,columna,num_columnas);
                short int abajo = buscar_abajo(ptr_contenido,fila,columna,num_columnas,num_filas);

                if(arriba + abajo >= 2 ){
                    for(short int fila_2 = fila-arriba; fila_2 <= fila+abajo ; fila_2++){
                        short int derecha_2 = buscar_derecha(ptr_contenido,fila_2,columna,num_columnas);
                        short int izquierda_2 = buscar_izquierda(ptr_contenido,fila_2,columna,num_columnas);
                        if (derecha_2 + izquierda_2 >= 1){
                            for(short int columna_2 = columna - izquierda_2; columna_2 <= columna + derecha_2; columna_2++){
                                cambiar_ficha(ptr_contenido,num_columnas,fila_2,columna_2,1);
                            }
                        }
                        cambiar_ficha(ptr_contenido,num_columnas,fila_2,columna,1);
                    }
                    contador_combinaciones += 1;
                }

                short int izquierda = buscar_izquierda(ptr_contenido,fila,columna,num_columnas);
                short int derecha= buscar_derecha(ptr_contenido,fila,columna,num_columnas);
                if(izquierda + derecha >= 2){
                    for(short int columna_2 = columna-izquierda; columna_2 <= columna+derecha ; columna_2++){
                        short int arriba_2 = buscar_arriba(ptr_contenido,fila,columna_2,num_columnas);
                        short int abajo_2 = buscar_abajo(ptr_contenido,fila,columna_2,num_columnas,num_filas);
                        if(arriba_2 + abajo_2 >= 1){
                            for(short int fila_2 = fila - arriba_2; fila_2 <= fila + abajo_2; fila_2++){
                                cambiar_ficha(ptr_contenido,num_columnas,fila_2,columna_2,1);
                            }
                        }
                        cambiar_ficha(ptr_contenido,num_columnas,fila,columna_2,1);
                    }
                    contador_combinaciones += 1;
                }
            }
        } 
    } 
    return contador_combinaciones; 
}

void rellenar_huecos(unsigned char ** ptr_contenido,short int num_filas, short int num_columnas){
    unsigned char ficha_actual;
    for(short int fila = num_filas-1; fila >= 0; fila--){
        for(short int columna = num_columnas-1; columna >= 0; columna--){
            ficha_actual = obtener_ficha(ptr_contenido,num_columnas,fila,columna);
            if(ficha_actual == 1){
                unsigned char ficha_auxiliar = 1;
                short int cont = 1;
                if(fila == 0){
                    cambiar_ficha(ptr_contenido,num_columnas,fila,columna,ficha_aleatoria());
                }
                while((fila - cont >= 0) && (ficha_auxiliar == 1)){
                    ficha_auxiliar = obtener_ficha(ptr_contenido,num_columnas,fila-cont,columna);
                    if(ficha_auxiliar != 1){
                        cambiar_ficha(ptr_contenido,num_columnas,fila,columna,ficha_auxiliar);
                        cambiar_ficha(ptr_contenido,num_columnas,fila - cont,columna,1);
                        break;
                    }
                    cont += 1;
                    if((fila - cont) < 0){
                        cambiar_ficha(ptr_contenido,num_columnas,fila,columna,ficha_aleatoria());
                    }
                    
                }
            }
        }
    }
}

void quitar_una_ficha(unsigned char ** ptr_contenido, short int num_columnas,short int fila,short int columna){
    cambiar_ficha(ptr_contenido,num_columnas,fila,columna,1);
    short int fila_2 = fila;
    unsigned char ficha_actual;
    while(fila_2 >= 1){
        ficha_actual = obtener_ficha(ptr_contenido,num_columnas,fila_2 - 1,columna);
        cambiar_ficha(ptr_contenido,num_columnas,fila_2,columna,ficha_actual);
        fila_2-=1;
    }
    ficha_actual = ficha_aleatoria();
    //cuando fila_2 es 0;
    cambiar_ficha(ptr_contenido,num_columnas,fila_2,columna,ficha_actual); 
}

void mostrar_juego(unsigned char ** ptr_contenido, short int *ptr_filas,short int * ptr_columnas){

    short int num_combinaciones = 1;
    short int acumulacion_combinaciones = 0;
    short int combinaciones_en_cascada = 0;
    short int cont_referencial = 0;

    print_tablero(ptr_contenido, *ptr_columnas, *ptr_filas);

    while(num_combinaciones != 0){

        num_combinaciones = buscar_combinaciones(ptr_contenido,*ptr_filas,*ptr_columnas);
        if(num_combinaciones == 0){break;}
        acumulacion_combinaciones += num_combinaciones;
        if(cont_referencial != 0){
            combinaciones_en_cascada += num_combinaciones;
        }

        print_tablero(ptr_contenido, *ptr_columnas, *ptr_filas);

        rellenar_huecos(ptr_contenido,*ptr_filas,*ptr_columnas);

        print_tablero(ptr_contenido, *ptr_columnas, *ptr_filas);

        cont_referencial += 1;
    }
    cout<<"numero total de combinaciones: "<<acumulacion_combinaciones<<"\n"
        <<"combinaciones en cascada: "<<combinaciones_en_cascada<<"\n"
        <<"numero de cascadas(veces que se refresco): "<<cont_referencial<<"\n";
}