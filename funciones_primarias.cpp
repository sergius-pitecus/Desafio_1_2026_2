#include <iostream>
#include "funciones_primarias.h"
#include <random>
#include <chrono>

std::mt19937 gen(
    static_cast<unsigned int>(
        std::chrono::steady_clock::now()
        .time_since_epoch()
        .count()
    )
);
std::uniform_int_distribution<int> dist(2, 7);
using namespace std;


unsigned char ficha_aleatoria(){
    return static_cast<unsigned char>(dist(gen));
}

unsigned short pos_byte(unsigned short num_columnas_tabla, unsigned short fila, unsigned short columna){
    //retorna el byte en el que se encuentra la ficha
    return ((((fila * num_columnas_tabla) + columna)*3)/8);// fila y columna aqui empiezan en 0
}

unsigned short pos_bit_in_byte(unsigned short num_columnas_tabla, unsigned short fila,unsigned short columna){
    //retorna un numero que nos indica el tipo de ficha segun su ubicacion en el byte
    return ((((fila * num_columnas_tabla) + columna)*3) % 8);
}

unsigned char obtener_ficha(unsigned char ** ptr_contenido, unsigned short num_columnas,
    unsigned short fila, unsigned short columna){
    
    unsigned short bit_en_byte = pos_bit_in_byte(num_columnas,fila,columna);
    unsigned short indice_byte = pos_byte(num_columnas, fila, columna);
    unsigned char mask = 1;
    /*
    esto era lo que teniamos antes:
    unsigned char mask1 = 1;   //00000001  se puede usar una sola mascara y desplazarla para usarla
    unsigned char mask2 = 2;   //00000010 <<1
    unsigned char mask3 = 4;   //00000100 <<2
    unsigned char mask4 = 8;   //00001000 <<3
    unsigned char mask5 = 16;  //00010000 <<4
    unsigned char mask6 = 32;  //00100000 <<5
    unsigned char mask7 = 64;  //01000000 <<6
    unsigned char mask8 = 128; //10000000 <<7
    */
    unsigned char bit_1, bit_2, bit_3;

    unsigned short bloque = indice_byte / 6;
    unsigned short posicion = indice_byte % 6;

    unsigned char byte_trajando = ptr_contenido[bloque][posicion];
    unsigned char siguiente_byte_trajando;

if (bit_en_byte >= 6) {
    if (posicion == 5) {
        siguiente_byte_trajando = ptr_contenido[bloque + 1][0];
    } else {
        siguiente_byte_trajando = ptr_contenido[bloque][posicion + 1];
    }
}
    switch (bit_en_byte) {
    case 0:
        // código si bit_en_byte == 0 (xxx0000 donde x es un bit de la ficha necesitada)
        bit_1 = (mask<<7) & byte_trajando;
        bit_2 = (mask<<6) & byte_trajando;
        bit_3 = (mask<<5) & byte_trajando;
        return (bit_1 | bit_2 | bit_3)>>5;
        break;
    case 1:
        bit_1 = (mask<<6) & byte_trajando;
        bit_2 = (mask<<5) & byte_trajando;
        bit_3 = (mask<<4) & byte_trajando;
        return (bit_1 | bit_2 | bit_3)>>4;
        break;
    case 2:
        bit_1 = (mask<<5) & byte_trajando;
        bit_2 = (mask<<4) & byte_trajando;
        bit_3 = (mask<<3) & byte_trajando;
        return (bit_1 | bit_2 | bit_3)>>3;
        break;
    case 3:
        bit_1 = (mask<<4) & byte_trajando;
        bit_2 = (mask<<3) & byte_trajando;
        bit_3 = (mask<<2) & byte_trajando;
        return (bit_1 | bit_2 | bit_3)>>2;
        break;
    case 4:
        bit_1 = (mask<<3) & byte_trajando;
        bit_2 = (mask<<2) & byte_trajando;
        bit_3 = (mask<<1) & byte_trajando;
        return (bit_1 | bit_2 | bit_3)>>1;
        break;
    case 5:
        bit_1 = (mask<<2) & byte_trajando;
        bit_2 = (mask<<1) & byte_trajando;
        bit_3 = (mask) & byte_trajando;
        return (bit_1 | bit_2 | bit_3);
        break;
    case 6:
        bit_1 = (mask<<1) & byte_trajando;
        bit_2 = (mask) & byte_trajando;
        bit_3 = (mask<<7) & siguiente_byte_trajando;
        return ((bit_1<<1) | (bit_2<<1) | (bit_3>>7));
        break;
    case 7:
        bit_1 = mask & byte_trajando;
        bit_2 = (mask<<7) & siguiente_byte_trajando;
        bit_3 = (mask<<6) & siguiente_byte_trajando;
        return ((bit_1<<2) | (bit_2>>6) | (bit_3>>6));
        break;
    default:
        cerr<<"error en la obtencion de fichas";
        break;
    }
    return 0;
}

void cambiar_ficha(unsigned char ** ptr_contenido,unsigned short num_columnas,unsigned short fila, unsigned short columna, unsigned char ficha_cambio){
    // ficha_cambio es literalmente los bits de la ficha en forma 00000xxx donde x son los bits usados
    unsigned short bit_en_bite = pos_bit_in_byte(num_columnas,fila,columna);
    unsigned short indice_byte = pos_byte(num_columnas, fila, columna);
    unsigned char mask = 31;
    /*
    lo que teniamos antes: 
    unsigned char mask1 = 31;   //00011111 
    unsigned char mask2 = 143;  //10001111  (mask>>1)|(mask<<7)
    unsigned char mask3 = 199;  //11000111  (mask>>2)|(mask<<6)
    unsigned char mask4 = 227;  //11100011  (mask>>3)|(mask<<5)
    unsigned char mask5 = 241;  //11110001  (mask>>4)|(mask<<4)
    unsigned char mask6 = 248;  //11111000  (mask>>5)|(mask<<3)
    unsigned char mask7 = 252;  //11111100  
    unsigned char mask8 = 254;  //11111110  
    unsigned char mask9 = 127;  //01111111  
    unsigned char mask10 = 63;  //00111111
    */
    unsigned char mask2 = 252;  //11111100  
    unsigned char mask3 = 254;  //11111110  
    unsigned char mask4 = 127;  //01111111  
    unsigned char mask5 = 63;  //00111111

    unsigned short bloque = indice_byte / 6;
    unsigned short posicion = indice_byte % 6;

    unsigned char byte_trabajando = ptr_contenido[bloque][posicion];
    unsigned char siguiente_byte_trajando;

    if (bit_en_bite >= 6) {
        if (posicion == 5) {
            siguiente_byte_trajando = ptr_contenido[bloque + 1][0];
        }
        else {
            siguiente_byte_trajando = ptr_contenido[bloque][posicion + 1];
        }
    }
    unsigned char auxiliar;

    switch (bit_en_bite) {
    case 0:
        auxiliar = byte_trabajando & mask;
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio<<5;
        break;
    case 1:
        auxiliar = byte_trabajando & ((mask>>1)|(mask<<7));
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio<<4;
        break;
    case 2:
        auxiliar = byte_trabajando & ((mask>>2)|(mask<<6));
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio<<3;
        break;
    case 3:
        auxiliar = byte_trabajando & ((mask>>3)|(mask<<5));
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio<<2;
        break;
    case 4:
       auxiliar = byte_trabajando & ((mask>>4)|(mask<<4));
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio<<1;
        break;
    case 5:
        auxiliar = byte_trabajando & ((mask>>5)|(mask<<3));
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | ficha_cambio;
        break;
    case 6:
        auxiliar = byte_trabajando & mask2;
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | (ficha_cambio>>1);
        auxiliar = siguiente_byte_trajando & mask4;
        if (bit_en_bite >= 6) {
            if(posicion == 5){
                ptr_contenido[indice_byte/6+1][0] = auxiliar | (ficha_cambio << 7);
            }
            else{
                ptr_contenido[indice_byte/6][(indice_byte % 6 )+1] = auxiliar | (ficha_cambio << 7); // mirar si el siguiente byte al sumar uno este o no en el arreglo actual (cosa que no creo por que se supone en ese byte (el final) todos los elementos estan completos)
            }
            break;
        }
    case 7:
        auxiliar = byte_trabajando & mask3;
        ptr_contenido[indice_byte/6][indice_byte % 6] = auxiliar | (ficha_cambio >> 2);
        auxiliar = siguiente_byte_trajando & mask5;
        if (bit_en_bite >= 6) {
            if(posicion == 5){
                ptr_contenido[(indice_byte/6)+1][0] = auxiliar | (ficha_cambio << 6);
            }
            else{
                ptr_contenido[indice_byte/6][(indice_byte % 6 )+1] = auxiliar | (ficha_cambio << 6);
            }
        }
        break;
    default:
        cerr<<"si sale este mensaje hay error en identificacion del orden de la ficha en bits";
        break;
    }
}

