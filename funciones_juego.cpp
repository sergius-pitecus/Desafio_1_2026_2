#include <iostream>
#include "funciones_juego.h"
#include "funciones_primarias.h"
using namespace std;



void print_tablero(unsigned char ** ptr_contenido, unsigned short num_columnas, unsigned short num_filas){
    for (short int fila = 0; fila<num_filas;fila++){
        for(unsigned short columna = 0; columna<num_columnas; columna++){
            unsigned char ficha_actual = obtener_ficha(ptr_contenido,num_columnas,fila,columna);

            switch (ficha_actual){
            
            case 1:
            cout<<"   ";
            break;
            
            case 2:
            cout<<"■  ";
            break;

            case 3:
            cout<<"◉  ";
            break;
            
            case 4:
            cout<<"♥  ";
            break;

            case 5:
            cout<<"♦  ";
            break;

            case 6:
            cout<<"⬡  ";
            break;

            case 7:
            cout<<"★  ";
            break;
            
            default:
            cout<<"!  ";
            break;
            }
        }
        cout<<fila<<"\n";
    }
    for(unsigned short i = 0; i < num_columnas; i++){
        if(i<10){cout<<i<<"  ";}
        if(i<100 && i>9){cout<<i<<" ";}
        if(i<1000 && i>99){cout<<i;}
    }
    cout<<"\n\n";
}

void print_tablero_binario(unsigned char ** ptr_contenido, unsigned short num_columnas, unsigned short num_filas){
    for (signed short fila = 0; fila<num_filas;fila++){
        for(signed short columna = 0; columna<num_columnas; columna++){
            unsigned char ficha_actual = obtener_ficha(ptr_contenido,num_columnas,fila,columna);

            switch (ficha_actual){
            
            case 1:
            cout<<"   ";
            break;
            
            case 2:
            cout<<"010 ";
            break;

            case 3:
            cout<<"011 ";
            break;
            
            case 4:
            cout<<"100 ";
            break;

            case 5:
            cout<<"101 ";
            break;

            case 6:
            cout<<"110 ";
            break;

            case 7:
            cout<<"111 ";
            break;
            
            default:
            cout<<"! ";
            break;
            }
        }
        cout<<"  "<<fila<<"\n";
    }
    for(unsigned short i = 0; i < num_columnas; i++){
        if(i<10){cout<<i<<"   ";}
        if(i<100 && i>9){cout<<i<<"  ";}
        if(i<1000 && i>99){cout<<i<<" ";}
    }
    cout<<"\n\n";
}

bool comparar_fichas(unsigned char ** ptr_contenido, unsigned short fila_1, unsigned short fila_2, unsigned short columna_1,
    unsigned short columna_2, unsigned short num_columnas){
    // retorna true si son iguales, false si no
    if(obtener_ficha(ptr_contenido,num_columnas,fila_1,columna_1) != 1){
    return (obtener_ficha(ptr_contenido,num_columnas,fila_1,columna_1) == obtener_ficha(ptr_contenido,num_columnas,fila_2,columna_2));
    }
    else{
        return false;
    }
}

unsigned short buscar_arriba(unsigned char ** ptr_contenido,unsigned short fila, unsigned short columna, unsigned short num_columnas){
    short cont = 0;
    while((short(fila)-cont-1 >= 0) && comparar_fichas(ptr_contenido,fila,short(fila)-cont-1,columna,columna,num_columnas)){
        cont += 1;
    }
    return cont;
}

unsigned short buscar_abajo(unsigned char ** ptr_contenido,unsigned short fila, unsigned short columna, unsigned short num_columnas, unsigned short num_filas){
    short cont = 0;
    while((fila+cont+1 < num_filas) && comparar_fichas(ptr_contenido,fila,fila + cont + 1,columna,columna,num_columnas)){
        cont += 1;
    }
    return cont;
}

unsigned short buscar_izquierda(unsigned char ** ptr_contenido,unsigned short fila, unsigned short columna, unsigned short num_columnas){
    short cont = 0;
    while((short(columna)-cont-1 >= 0 ) && comparar_fichas(ptr_contenido,fila,fila,columna,short(columna) - cont - 1,num_columnas)){
        cont += 1;
    }
    return cont;

}

unsigned short buscar_derecha(unsigned char ** ptr_contenido,unsigned short fila,unsigned short columna, unsigned short num_columnas){
    short cont = 0;
    while((columna+cont+1 < num_columnas ) && comparar_fichas(ptr_contenido,fila,fila,columna,columna + cont + 1,num_columnas)){
        cont += 1;
    }
    return cont;
}

unsigned short buscar_combinaciones(unsigned char ** ptr_contenido,unsigned short num_filas, unsigned short num_columnas, unsigned short *ptr_fichas_eliminadas){

    unsigned short contador_combinaciones = 0;

    for(unsigned short fila = 0; fila < num_filas; fila++){
        for(unsigned short columna = 0; columna < num_columnas; columna++){
            if(obtener_ficha(ptr_contenido,num_columnas,fila,columna) != 1){
                unsigned short arriba = buscar_arriba(ptr_contenido,fila,columna,num_columnas);
                unsigned short abajo = buscar_abajo(ptr_contenido,fila,columna,num_columnas,num_filas);

                if(arriba + abajo >= 2 ){
                    for(unsigned short fila_2 = fila-arriba; fila_2 <= fila+abajo ; fila_2++){
                        unsigned short derecha_2 = buscar_derecha(ptr_contenido,fila_2,columna,num_columnas);
                        unsigned short izquierda_2 = buscar_izquierda(ptr_contenido,fila_2,columna,num_columnas);
                        if (derecha_2 + izquierda_2 >= 2){
                            for(unsigned short columna_2 = columna - izquierda_2; columna_2 <= columna + derecha_2; columna_2++){
                                cambiar_ficha(ptr_contenido,num_columnas,fila_2,columna_2,1);
                                *ptr_fichas_eliminadas += 1;
                            }
                        contador_combinaciones += 1;
                        *ptr_fichas_eliminadas -= 1;
                        }
                        cambiar_ficha(ptr_contenido,num_columnas,fila_2,columna,1);
                        *ptr_fichas_eliminadas += 1 ;
                    }
                    contador_combinaciones += 1;
                }

                unsigned short izquierda = buscar_izquierda(ptr_contenido,fila,columna,num_columnas);
                unsigned short derecha= buscar_derecha(ptr_contenido,fila,columna,num_columnas);
                if(izquierda + derecha >= 2){
                    for(unsigned short columna_2 = columna-izquierda; columna_2 <= columna+derecha ; columna_2++){
                        unsigned short arriba_2 = buscar_arriba(ptr_contenido,fila,columna_2,num_columnas);
                        unsigned short abajo_2 = buscar_abajo(ptr_contenido,fila,columna_2,num_columnas,num_filas);
                        if(arriba_2 + abajo_2 >= 2){
                            for(unsigned short fila_2 = fila - arriba_2; fila_2 <= fila + abajo_2; fila_2++){
                                cambiar_ficha(ptr_contenido,num_columnas,fila_2,columna_2,1);
                                *ptr_fichas_eliminadas += 1;
                            }
                        contador_combinaciones += 1;
                        *ptr_fichas_eliminadas -= 1;
                        }
                        cambiar_ficha(ptr_contenido,num_columnas,fila,columna_2,1);
                        *ptr_fichas_eliminadas += 1 ;
                    }
                    contador_combinaciones += 1;
                }
            }
        } 
    } 
    return contador_combinaciones; 
}

void rellenar_huecos(unsigned char ** ptr_contenido,unsigned short num_filas, unsigned short num_columnas){
    unsigned short ficha_actual;
    for(short fila = num_filas-1; fila >= 0; fila--){
        for(short columna = num_columnas-1; columna >= 0; columna--){
            ficha_actual = obtener_ficha(ptr_contenido,num_columnas,fila,columna);
            if(ficha_actual == 1){
                unsigned char ficha_auxiliar = 1;
                unsigned short cont = 1;
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

void quitar_una_ficha(unsigned char ** ptr_contenido, unsigned short num_columnas,unsigned short fila,unsigned short columna){
    cambiar_ficha(ptr_contenido,num_columnas,fila,columna,1);
    unsigned short fila_2 = fila;
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

void mostrar_juego(unsigned char ** ptr_contenido, unsigned short *ptr_filas,unsigned short * ptr_columnas, unsigned short * ptr_fichas_eliminadas, unsigned short * num_combinaciones_total,unsigned short num_eliminaciones,unsigned short *puntos, unsigned short eliminaciones_puntuales){

    unsigned short num_combinaciones = 1;
    unsigned short acumulacion_combinaciones = 0;
    unsigned short cont_referencial = 0;
    unsigned short puntos_auxiliar = *ptr_fichas_eliminadas;
    print_tablero(ptr_contenido, *ptr_columnas, *ptr_filas);

    while(num_combinaciones != 0){

        num_combinaciones = buscar_combinaciones(ptr_contenido,*ptr_filas,*ptr_columnas, ptr_fichas_eliminadas);
        if(num_combinaciones == 0){break;}
        acumulacion_combinaciones += num_combinaciones;

        print_tablero(ptr_contenido, *ptr_columnas, *ptr_filas);

        rellenar_huecos(ptr_contenido,*ptr_filas,*ptr_columnas);

        print_tablero(ptr_contenido, *ptr_columnas, *ptr_filas);

        cont_referencial += 1;
    }
    *puntos += ((*ptr_fichas_eliminadas-puntos_auxiliar) * 5);
    *num_combinaciones_total += acumulacion_combinaciones;
    cout<<"dimenciones filaxcolumna: "<<*ptr_filas<<"x"<<*ptr_columnas<<"\n"
        <<"eliminaciones puntuales(una ficha): "<<eliminaciones_puntuales<<"\n"
        <<"combinaciones en cascada: "<<((acumulacion_combinaciones > 0) ? acumulacion_combinaciones-1 : 0)<<"\n"
        <<"veces que se refresco: "<<cont_referencial<<"\n"
        <<"total fichas eliminadas: "<<*ptr_fichas_eliminadas<<"\n"
        <<"total combinaciones detectadas: "<<*num_combinaciones_total<<"\n"
        <<"filas/columnas eliminadas: "<< num_eliminaciones<<"\n"
        <<"puntuacion: "<<*puntos<<"\n\n";
}