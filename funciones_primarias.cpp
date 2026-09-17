#include <iostream>
#include "funciones_primarias.h"
using namespace std;

short int pos_byte(short int num_columnas_tabla, short int fila, short int columna){
    //retorna el byte en el que se encuentra la ficha
    return ((((fila * num_columnas_tabla) + columna)*3)/8);// fila y columna aqui empiezan en 0
}

short int pos_bit_in_byte(short int num_columnas_tabla, short int fila, short int columna){
    //retorna un numero que nos indica el tipo de ficha segun su ubicacion en el byte
    return ((((fila * num_columnas_tabla) + columna)*3) % 8);
}

unsigned char obtener_ficha(unsigned char ** ptr_contenido, short int num_columnas,
    short int fila, short int columna){
    
    short int BitInByte = pos_bit_in_byte(num_columnas,fila,columna);
    short int indice_byte = pos_byte(num_columnas, fila, columna);
    unsigned char mask1 = 1;   //00000001  se puede usar una sola mascara y desplazarla para usarla
    unsigned char mask2 = 2;   //00000010
    unsigned char mask3 = 4;   //00000100
    unsigned char mask4 = 8;   //00001000
    unsigned char mask5 = 16;  //00010000
    unsigned char mask6 = 32;  //00100000
    unsigned char mask7 = 64;  //01000000
    unsigned char mask8 = 128; //10000000

    unsigned char bit_1, bit_2, bit_3;

    unsigned char byte_trajando = ptr_contenido[indice_byte/6][indice_byte % 6];
    unsigned char siguiente_byte_trajando = ptr_contenido[indice_byte/6][(indice_byte % 6)+1];

    switch (BitInByte) {
    case 0:
        // código si BitInByte == 0 (xxx0000 donde x es un bit de la ficha necesitada)
        bit_1 = mask8 & byte_trajando;
        bit_2 = mask7 & byte_trajando;
        bit_3 = mask6 & byte_trajando;
        return (bit_1 | bit_2 | bit_3)>>5;
        break;
    case 1:
        // código si BitInByte == 1 (0xxx000 donde x es un bit de la ficha necesitada)
        bit_1 = mask7 & byte_trajando;
        bit_2 = mask6 & byte_trajando;
        bit_3 = mask5 & byte_trajando;
        return (bit_1 | bit_2 | bit_3)>>4;
        break;
    case 2:
        // código si BitInByte == 2 (00xxx00 donde x es un bit de la ficha necesitada)
        bit_1 = mask6 & byte_trajando;
        bit_2 = mask5 & byte_trajando;
        bit_3 = mask4 & byte_trajando;
        return (bit_1 | bit_2 | bit_3)>>3;
        break;
    case 3:
        bit_1 = mask5 & byte_trajando;
        bit_2 = mask4 & byte_trajando;
        bit_3 = mask3 & byte_trajando;
        return (bit_1 | bit_2 | bit_3)>>2;
        break;
    case 4:
        bit_1 = mask4 & byte_trajando;
        bit_2 = mask3 & byte_trajando;
        bit_3 = mask2 & byte_trajando;
        return (bit_1 | bit_2 | bit_3)>>1;
        break;
    case 5:
        bit_1 = mask3 & byte_trajando;
        bit_2 = mask2 & byte_trajando;
        bit_3 = mask1 & byte_trajando;
        return (bit_1 | bit_2 | bit_3);
        break;
    case 6:
        bit_1 = mask2 & byte_trajando;
        bit_2 = mask1 & byte_trajando;
        bit_3 = mask8 & siguiente_byte_trajando;
        return ((bit_1<<1) | (bit_2<<1) | (bit_3>>7));
        break;
    case 7:
        bit_1 = mask1 & byte_trajando;
        bit_2 = mask8 & siguiente_byte_trajando;
        bit_3 = mask7 & siguiente_byte_trajando;
        return ((bit_1<<2) | (bit_2>>6) | (bit_3>>6));
        break;
    default:
        cout<<"si sale este mensaje hay que rezar";
        break;
    }
    return 0;
}

void cambiar_ficha(unsigned char ** ptr_contenido,
     short int num_columnas,short int fila, short int columna, unsigned char ficha_cambio){
    // ficha_cambio es literalmente los bits de la ficha en forma 00000xxx donde x son los bits usados
    short int BitInByte = pos_bit_in_byte(num_columnas,fila,columna);
    short int indice_byte = pos_byte(num_columnas, fila, columna);
    unsigned char mask1 = 31;   //00011111
    unsigned char mask2 = 143;  //10001111
    unsigned char mask3 = 199;  //11000111
    unsigned char mask4 = 227;  //11100011
    unsigned char mask5 = 241;  //11110001
    unsigned char mask6 = 248;  //11111000
    unsigned char mask7 = 252;  //11111100
    unsigned char mask8 = 254;  //11111110
    unsigned char mask9 = 127;  //01111111
    unsigned char mask10 = 63;  //00111111


    unsigned char bit_1, bit_2, bit_3;

    unsigned char byte_trabajando = ptr_contenido[indice_byte/6][indice_byte % 6];
    unsigned char siguiente_byte_trajando = ptr_contenido[indice_byte/6][(indice_byte % 6)+1];

    unsigned char auxiliar;

    switch (BitInByte) {
    case 0:
        // código si BitInByte == 0 (xxx0000 donde x es un bit de la ficha a cambiar)
        auxiliar = byte_trabajando & mask1;
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio<<5;
        break;
    case 1:
        auxiliar = byte_trabajando & mask2;
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio<<4;
        break;
    case 2:
        auxiliar = byte_trabajando & mask3;
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio<<3;
        break;
    case 3:
        auxiliar = byte_trabajando & mask4;
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio<<2;
        break;
    case 4:
       auxiliar = byte_trabajando & mask5;
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio<<1;
        break;
    case 5:
        auxiliar = byte_trabajando & mask6;
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio;
        break;
    case 6:
        auxiliar = byte_trabajando & mask7;
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | (ficha_cambio>>1);
        auxiliar = siguiente_byte_trajando & mask9;
        ptr_contenido[indice_byte/6][(indice_byte % 6 )+1] = auxiliar | (ficha_cambio << 7); // mirar si el siguiente byte al sumar uno este o no en el arreglo actual (cosa que no creo por que se supone en ese byte (el final) todos los elementos estan completos)

        break;
    case 7:
        auxiliar = byte_trabajando & mask8;
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | (ficha_cambio >> 2);
        auxiliar = siguiente_byte_trajando & mask10;
        ptr_contenido[indice_byte/6][(indice_byte % 6 )+1] = auxiliar | (ficha_cambio << 6);
    default:
        cerr<<"si sale este mensaje hay error en identificacion del orden de la ficha en bits";
        break;
    }
}

void reubicar_ficha(unsigned char ** ptr_contenido, short int num_columnas 
    ,short int fila_anterior, short int columna_anterior, short int columna_actual, short int fila_actual){
    // la verdad trabajar una ficha por individual no tiene ningun sentido, es reubicar y despues borrar los exedentes de memoria 

    short int ficha_cambio = obtener_ficha(ptr_contenido,num_columnas,fila_anterior,columna_anterior);

    cambiar_ficha(ptr_contenido,num_columnas,fila_actual,columna_actual,ficha_cambio);
    // xd, lit eso es todo (pese esta funcion iba a ser re dificil)

}
