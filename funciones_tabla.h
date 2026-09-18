#ifndef FUNCIONES_TABLA_H
#define FUNCIONES_TABLA_H

unsigned char ** crear_tablero(unsigned char ** ptr_contenido,short int num_filas, short int num_columnas, short int * ptr_num_expo, short int * bytes_rservados);

unsigned char ** expandir_memoria(unsigned char ** ptr_contenido, short int * bytes_reservados, 
    short int bytes_necesarios, short int * ptr_num_expo);

void disminuir_memoria(unsigned char ** ptr_contenido, short int * bytes_reservados,short int bytes_necesarios);

unsigned char ** agregar_fila(unsigned char ** ptr_contenido, short int fila_remplazar,short int * ptr_num_filas, short int * ptr_num_columnas,
     short int * bytes_reservados, short int * ptr_num_expo);

unsigned char ** agregar_columna(unsigned char ** ptr_contenido, short int columna_remplazar,short int * ptr_num_filas, short int * ptr_num_columnas,
     short int * bytes_reservados, short int * ptr_num_expo);

void quitar_fila(unsigned char ** ptr_contenido, short int fila_quitar,short int * ptr_num_filas,
     short int * ptr_num_columnas, short int * bytes_reservados, short int * ptr_num_expo);

void quitar_columna(unsigned char ** ptr_contenido, short int columna_quitar,short int * ptr_num_filas,
     short int * ptr_num_columnas, short int * bytes_reservados, short int * ptr_num_expo);

#endif