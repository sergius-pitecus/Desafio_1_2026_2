#ifndef FUNCIONES_PRIMARIAS_H
#define FUNCIONES_PRIMARIAS_H

unsigned char ficha_aleatoria();

unsigned short pos_byte(unsigned short num_columnas_tabla, unsigned short fila, unsigned short columna);

unsigned short pos_bit_in_byte(unsigned short num_columnas_tabla, unsigned short fila, unsigned short columna);

unsigned char obtener_ficha(unsigned char ** ptr_contenido, unsigned short num_columnas, unsigned short fila, unsigned short columna);

void cambiar_ficha(unsigned char ** ptr_contenido, unsigned short num_columnas,unsigned short fila, unsigned short columna, unsigned char ficha_cambio);

void reubicar_ficha(unsigned char ** ptr_contenido, unsigned short num_columnas, unsigned short fila_anterior, unsigned short columna_anterior, unsigned short columna_actual, unsigned short fila_actual);

#endif