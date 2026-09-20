#ifndef FUNCIONES_TABLA_H
#define FUNCIONES_TABLA_H

unsigned char ** crear_tablero(unsigned char ** ptr_contenido,unsigned short num_filas, unsigned short num_columnas, unsigned short * ptr_num_expo, unsigned short * bytes_rservados);

unsigned char ** expandir_memoria(unsigned char ** ptr_contenido, unsigned short * bytes_reservados, 
    unsigned short bytes_necesarios, unsigned short * ptr_num_expo);

void disminuir_memoria(unsigned char ** ptr_contenido, unsigned short * bytes_reservados,unsigned short bytes_necesarios);

unsigned char ** agregar_fila(unsigned char ** ptr_contenido, unsigned short fila_remplazar,unsigned short * ptr_num_filas, unsigned short * ptr_num_columnas,
     unsigned short * bytes_reservados, unsigned short * ptr_num_expo);

unsigned char ** agregar_columna(unsigned char ** ptr_contenido, unsigned short columna_remplazar,unsigned short * ptr_num_filas, unsigned short * ptr_num_columnas,
     unsigned short * bytes_reservados, unsigned short * ptr_num_expo);

void quitar_fila(unsigned char ** ptr_contenido, unsigned short fila_quitar,unsigned short * ptr_num_filas,
     unsigned short * ptr_num_columnas, unsigned short * bytes_reservados);

unsigned char ** quitar_columna(unsigned char ** ptr_contenido, unsigned short columna_quitar,unsigned short * ptr_num_filas,
     unsigned short * ptr_num_columnas, unsigned short * bytes_reservados, unsigned short * ptr_num_expo);

#endif