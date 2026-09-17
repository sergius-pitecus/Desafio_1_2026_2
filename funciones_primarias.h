#ifndef FUNCIONES_PRIMARIAS_H
#define FUNCIONES_PRIMARIAS_H

short int pos_byte(short int num_columnas_tabla, short int fila, short int columna);

short int pos_bit_in_byte(short int num_columnas_tabla, short int fila, short int columna);

unsigned char obtener_ficha(unsigned char ** ptr_contenido, short int num_columnas, short int fila, short int columna);

void cambiar_ficha(unsigned char ** ptr_contenido, short int num_columnas,short int fila, short int columna, unsigned char ficha_cambio);

void reubicar_ficha(unsigned char ** ptr_contenido, short int num_columnas, short int fila_anterior, short int columna_anterior, short int columna_actual, short int fila_actual);

#endif