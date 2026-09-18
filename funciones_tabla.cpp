#include <iostream>
#include "funciones_tabla.h"
#include "funciones_primarias.h"
#include <random>
using namespace std;


unsigned char ** expandir_memoria(unsigned char ** ptr_contenido, short int * bytes_reservados, 
    short int bytes_necesarios, short int * ptr_num_expo){
    short int auxiliar_expo = 2;
    //analizar error de tipos en los punteros aqui
        if ((bytes_necesarios+5)/6 > *ptr_num_expo){ //miramos si cabe entre los bloques que ya tenemos
            while(((auxiliar_expo * (*ptr_num_expo))*6 ) < bytes_necesarios){
                auxiliar_expo += 1;
            }
            unsigned char ** contenido = new unsigned char*[*ptr_num_expo];
            for(short int i = 0; i < *ptr_num_expo; i++){
                contenido[i] = ptr_contenido[i];
            }
            delete[] ptr_contenido;
            ptr_contenido = new unsigned char*[(*ptr_num_expo)*auxiliar_expo];
            
            for(short int i = 0; i < *ptr_num_expo; i++ ){
                ptr_contenido[i] = contenido[i];
            }
            for(short int i = ((*bytes_reservados+5)/6); i < (((bytes_necesarios)+5)/6); i++){ //revisar esta parte
                ptr_contenido[i] = new unsigned char[6]{};
            }
            *ptr_num_expo *= auxiliar_expo;
            delete[] contenido;
        }
        else{
            for(short int i = ((*bytes_reservados+5)/6); i < (((bytes_necesarios)+5)/6); i++){//desde el ultimo bloque ya existente hasta todos los bloques necesarios 
                ptr_contenido[i] = new unsigned char[6]{};
            }
        }
    *bytes_reservados = ((bytes_necesarios+5)/6)*6; // esto es para que nos cuadre con el sistema de bloques
    return ptr_contenido;
}

void disminuir_memoria(unsigned char ** ptr_contenido, short int * bytes_reservados,short int bytes_necesarios){
    
    short int bloques_actuales = (*bytes_reservados + 5) / 6; //acordate que esto empieza en uno pues es la cantidad de bloques
    short int bloques_necesarios = (bytes_necesarios + 5) / 6;

    for(short int i = bloques_actuales -1 ; i >= bloques_necesarios; i-- ){
        delete[] ptr_contenido[i]; // por el momento dejesmolo asi pero tambien seria bueno pensar en recortar el arreglo principal
        ptr_contenido[i] = nullptr;
    }
    *bytes_reservados = ((bytes_necesarios+5)/6)*6;
}

unsigned char ** crear_tablero(unsigned char ** ptr_contenido,short int num_filas, short int num_columnas, short int * ptr_num_expo, short int *bytes_reservados){
    //aqui sacar calculo de la memoria necesaria para el primer trabalero y como organizarla en los bloques
    short int bytes_necesarios = ((((num_filas * num_columnas)*3)+7)/8);
    if (bytes_necesarios > *bytes_reservados){ 
    ptr_contenido =  expandir_memoria(ptr_contenido,bytes_reservados,bytes_necesarios, ptr_num_expo);
    }
    
    unsigned char valor_random;
    for(short int fila = 0; fila<num_filas; fila++){
        for(short int columna = 0;columna<num_columnas;columna++){
            valor_random = ficha_aleatoria();
            cambiar_ficha(ptr_contenido,num_columnas,fila,columna,valor_random);
        }
    }
    return ptr_contenido;
}

unsigned char ** agregar_fila(unsigned char ** ptr_contenido, short int fila_remplazar,short int * ptr_num_filas, short int * ptr_num_columnas,
     short int * bytes_reservados, short int * ptr_num_expo){
    // ptr_num_expo es el numero de arreglos dinamicos dentro del arreglo principal ptr_contenido
    // abajo en ese reguero de codigo se verifica la memoria ya reservada y la necesaria para agregar la fila
    
    *ptr_num_filas += 1;
    short int bytes_necesarios = ((((*ptr_num_filas * *ptr_num_columnas)*3)+7)/8); //divicion entera que redondea al techo

    if (bytes_necesarios > *bytes_reservados){
    ptr_contenido = expandir_memoria(ptr_contenido,bytes_reservados,bytes_necesarios,ptr_num_expo);
    }
    if(fila_remplazar != *ptr_num_filas-1){
        for(short int fila = ((*ptr_num_filas)-2); fila >= fila_remplazar; fila--){ //el -2 es por que ya le sumamos 1 a las filas y ademas aqui hay fila 0 lo que retrasa cada fila por 1
            for(short int columna = ((*ptr_num_columnas)-1);columna >= 0;columna--){
                unsigned char ficha = obtener_ficha(ptr_contenido,*ptr_num_columnas,fila,columna);
                cambiar_ficha(ptr_contenido,*ptr_num_columnas,fila + 1,columna,ficha);
            }
        }
    }
    for(short int columna = 0; columna < *ptr_num_columnas; columna++){
        cambiar_ficha(ptr_contenido,*ptr_num_columnas,fila_remplazar,columna,1);// el 1 es por que ese es el bit del espacio libre (001)
        //y de lo demas se encarga la funcion de llenado de huecos
    }
    return ptr_contenido;
    
}

unsigned char ** agregar_columna(unsigned char ** ptr_contenido, short int columna_remplazar,short int * ptr_num_filas, short int * ptr_num_columnas,
     short int * bytes_reservados, short int * ptr_num_expo){
    *ptr_num_columnas += 1;
    short int bytes_necesarios = ((((*ptr_num_filas * *ptr_num_columnas)*3)+7)/8); //divicion entera que redondea al techo

    if (bytes_necesarios > *bytes_reservados){
    ptr_contenido = expandir_memoria(ptr_contenido,bytes_reservados,bytes_necesarios,ptr_num_expo);
    }

    for(short int columna = ((*ptr_num_columnas)-2); columna >= columna_remplazar; columna--){ //el -2 es por que ya le sumamos 1 a las filas y ademas aqui hay fila 0 lo que retrasa cada fila por 1
        for(short int fila = ((*ptr_num_filas)-1);fila >= 0;fila--){
            unsigned char ficha = obtener_ficha(ptr_contenido,*ptr_num_columnas - 1,fila,columna);
            cambiar_ficha(ptr_contenido,*ptr_num_columnas,fila,columna + 1,ficha);
        }
    }
    for(short int fila = 0; fila < *ptr_num_filas; fila++){
        cambiar_ficha(ptr_contenido,*ptr_num_columnas,fila,columna_remplazar,1);// el 1 es por que ese es el bit del espacio libre (001)
    }
    return ptr_contenido;
}

void quitar_fila(unsigned char ** ptr_contenido, short int fila_quitar,short int * ptr_num_filas,
     short int * ptr_num_columnas, short int * bytes_reservados, short int * ptr_num_expo){
    *ptr_num_filas -= 1;
    if(fila_quitar < *ptr_num_filas){
        for(short int fila = fila_quitar + 1; fila <= *ptr_num_filas; fila++){
            for(short int columna = *ptr_num_columnas-1; columna >= 0; columna--){

                unsigned char ficha_cambio = obtener_ficha(ptr_contenido,*ptr_num_columnas,fila,columna);
                cambiar_ficha(ptr_contenido,*ptr_num_columnas,fila-1,columna,ficha_cambio);

            }
        }
    }
    //de aqui abajo es gestion de memoria
    short int bytes_necesarios = ((((*ptr_num_filas * *ptr_num_columnas)*3)+7)/8);
    if(bytes_necesarios < (*bytes_reservados * 65) / 100){
        disminuir_memoria(ptr_contenido,bytes_reservados,bytes_necesarios);

    }
}

void quitar_columna(unsigned char ** ptr_contenido, short int columna_quitar,short int * ptr_num_filas,
     short int * ptr_num_columnas, short int * bytes_reservados, short int * ptr_num_expo){
    
    *ptr_num_columnas -= 1;

    for(short int columna = columna_quitar + 1; columna <= *ptr_num_columnas;columna++){
        for(short int fila = *ptr_num_filas-1; fila >= 0; fila--){

            unsigned char ficha_cambio = obtener_ficha(ptr_contenido,*ptr_num_columnas+1,fila,columna);
            cambiar_ficha(ptr_contenido,*ptr_num_columnas,fila,columna-1,ficha_cambio);

        }
    }
    //de aqui abajo es gestion de memoria
    short int bytes_necesarios = ((((*ptr_num_filas * *ptr_num_columnas)*3)+7)/8);
    if(bytes_necesarios < (*bytes_reservados * 65) / 100){
        disminuir_memoria(ptr_contenido,bytes_reservados,bytes_necesarios);
    }
}