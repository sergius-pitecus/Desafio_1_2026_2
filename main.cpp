#include <iostream>
#include "funciones_primarias.h"
#include "funciones_tabla.h"
#include "funciones_juego.h"
#include <windows.h>
using namespace std;

int main(){

    SetConsoleOutputCP(CP_UTF8);//para poder imprimir en unicode mejores fichas
    SetConsoleCP(CP_UTF8);

    unsigned short * ptr_num_expo = new unsigned short(4);
    unsigned short * ptr_filas = new unsigned short;
    unsigned short * ptr_columnas = new unsigned short;
    unsigned char ** ptr_contenido = new unsigned char *[4];

    unsigned short * num_fichas_eliminadas = new unsigned short(0);//tambien cuentan las eliminaciiones de fila y columna? 
    unsigned short * num_combinaciones_total = new unsigned short(0);
    unsigned short num_eliminaciones = 0;
    unsigned short * puntos = new unsigned short(0);
    unsigned short eliminaciones_puntuales = 0;


    for(unsigned short i = 0; i<4; i++ ){
        ptr_contenido[i] = new unsigned char[6];
    }
    unsigned short * bytes_reservados = new unsigned short(24);

    cout<<"ingrese numero de filas del tablero inicial: ";
    cin>>*ptr_filas;
    cout<<"ingrese numero de columnas del tablero incial: ";
    cin>>*ptr_columnas;


    ptr_contenido = crear_tablero(ptr_contenido,*ptr_filas,*ptr_columnas,ptr_num_expo,bytes_reservados);

    mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas,num_fichas_eliminadas,num_combinaciones_total,num_eliminaciones,puntos,eliminaciones_puntuales);;

    unsigned short valor_ingresado = 0;

    while (valor_ingresado != 7){
        cout<<"ingrese un numero por el proseso que desea realizar:\n1. quitar ficha \n2. añadir fila \n3. quitar fila \n4. añadir columna \n5. quitar columna\n6. mostrar tablero en binario\n7. terminar ejecucion\n";
        cin>>valor_ingresado;

        switch (valor_ingresado){
        case 1:
            unsigned short fila;
            unsigned short columna;
            cout<<"ingrese la fila: ";
            cin>>fila;
            cout<<"ingrese la columna: ";
            cin>>columna;
            *num_fichas_eliminadas += 1;
            eliminaciones_puntuales += 1;
            quitar_una_ficha(ptr_contenido,*ptr_columnas,fila,columna);//funciona_bien
            mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas,num_fichas_eliminadas,num_combinaciones_total,num_eliminaciones,puntos, eliminaciones_puntuales);
            break;
            
        case 2:
            unsigned short fila_agregar;
            cout<<"ingrese el lugar de la fila a agregar: ";
            cin>>fila_agregar;
            ptr_contenido = agregar_fila(ptr_contenido,fila_agregar,ptr_filas,ptr_columnas,bytes_reservados,ptr_num_expo);
            rellenar_huecos(ptr_contenido,*ptr_filas,*ptr_columnas);
            mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas,num_fichas_eliminadas,num_combinaciones_total,num_eliminaciones,puntos, eliminaciones_puntuales);
            break;

        case 3:
            unsigned short fila_sacar;
            cout<<"ingrese la fila a eliminar: ";
            cin>>fila_sacar;
            quitar_fila(ptr_contenido,fila_sacar,ptr_filas,ptr_columnas,bytes_reservados);
            num_eliminaciones += 1;
            *num_fichas_eliminadas += *ptr_columnas;
            mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas,num_fichas_eliminadas,num_combinaciones_total,num_eliminaciones,puntos, eliminaciones_puntuales);
            break;
        
        case 4:
            unsigned short columna_agregar;
            cout<<"ingrese el lugar de la columna a agregar: ";
            cin>>columna_agregar;
            ptr_contenido = agregar_columna(ptr_contenido,columna_agregar,ptr_filas,ptr_columnas,bytes_reservados,ptr_num_expo);
            rellenar_huecos(ptr_contenido,*ptr_filas,*ptr_columnas);
            mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas,num_fichas_eliminadas,num_combinaciones_total,num_eliminaciones,puntos, eliminaciones_puntuales);
            break;
        case 5:
            unsigned short columna_sacar;
            cout<<"ingrese la columna a eliminar: ";
            cin>>columna_sacar;
            ptr_contenido = quitar_columna(ptr_contenido,columna_sacar,ptr_filas,ptr_columnas,bytes_reservados,ptr_num_expo);
            num_eliminaciones += 1;
            *num_fichas_eliminadas += *ptr_filas;
            mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas,num_fichas_eliminadas,num_combinaciones_total,num_eliminaciones,puntos, eliminaciones_puntuales);
            break;
        case 6:
            print_tablero_binario(ptr_contenido,*ptr_columnas,*ptr_filas);
            cout<<"\n";
            break;
        case 7:
            cout<<"--gracias por jugar--";
            for(unsigned short i = 0; i < *ptr_num_expo; i++){
                delete[] ptr_contenido[i];
            }
            delete ptr_num_expo;
            delete ptr_filas;
            delete ptr_columnas;
            delete bytes_reservados;
            break;
        default:
            cout<<"ingrese un numero valido\n";
            break;
        }
    }
    return 0;
}


