#include <iostream>
#include "funciones_primarias.h"
#include "funciones_tabla.h"
#include "funciones_juego.h"
using namespace std;

//short int * num_combinaciones,short int *acumulacion_combinaciones,short int *combinaciones_en_cascada,short int * cont_referencial


main(){
    short int * ptr_num_expo = new short int(4);
    short int * ptr_filas = new short int;
    short int * ptr_columnas = new short int;
    unsigned char ** ptr_contenido = new unsigned char *[4];

    for(int i = 0; i<4; i++ ){
        ptr_contenido[i] = new unsigned char[6];
    }
    short int * bytes_reservados = new short int(24);

    cout<<"ingrese numero de filas del tablero inicial: ";
    cin>>*ptr_filas;
    cout<<"ingrese numero de columnas del tablero incial: ";
    cin>>*ptr_columnas;


    ptr_contenido = crear_tablero(ptr_contenido,*ptr_filas,*ptr_columnas,ptr_num_expo,bytes_reservados);

    mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas);

    short int valor_ingresado = 0;

    while (valor_ingresado != 6){
        cout<<"ingrese un numero por el proseso que desea realizar:\n1. quitar ficha \n2. añadir fila \n3. quitar fila \n4.añadir columna \n5.quitar columna\n6.terminar ejecucion\n";
        cin>>valor_ingresado;

        switch (valor_ingresado){
        case 1:
            short int fila;
            short int columna;
            cout<<"ingrese la fila: ";
            cin>>fila;
            cout<<"ingese la columna: ";
            cin>>columna;
            quitar_una_ficha(ptr_contenido,*ptr_columnas,fila,columna);//funciona_bien
            mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas);
            break;
            
        case 2:
            short int fila_agregar;
            cout<<"ingrese el lugar de la fila a añadir: ";
            cin>>fila_agregar; //hay problemas con la funcion de agregar fila
            ptr_contenido = agregar_fila(ptr_contenido,fila_agregar,ptr_filas,ptr_columnas,bytes_reservados,ptr_num_expo);
            //print_tablero(ptr_contenido,*ptr_columnas,*ptr_filas);
            rellenar_huecos(ptr_contenido,*ptr_filas,*ptr_columnas);
            mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas);
            break;

        case 3:
            short int fila_sacar;
            cout<<"ingrese la fila a eliminar: ";
            cin>>fila_sacar;
            quitar_fila(ptr_contenido,fila_sacar,ptr_filas,ptr_columnas,bytes_reservados,ptr_num_expo);
            //print_tablero(ptr_contenido,*ptr_columnas,*ptr_filas);
            mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas);
            break;
        
        case 4:
            short int columna_agregar;
            cout<<"ingrese el lugar de la columna a añadir: ";
            cin>>columna_agregar;
            ptr_contenido = agregar_columna(ptr_contenido,columna_agregar,ptr_filas,ptr_columnas,bytes_reservados,ptr_num_expo);
            print_tablero(ptr_contenido,*ptr_columnas,*ptr_filas);
            rellenar_huecos(ptr_contenido,*ptr_filas,*ptr_columnas);
            mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas);
            break;
        case 5:
            short int columna_sacar;
            cout<<"ingrese la columna a eliminar: ";
            cin>>columna_sacar;
            ptr_contenido = quitar_columna(ptr_contenido,columna_sacar,ptr_filas,ptr_columnas,bytes_reservados,ptr_num_expo);
            mostrar_juego(ptr_contenido,ptr_filas,ptr_columnas);
            break;
        case 6:
            cout<<"--gracias por jugar--";
            for(short int i = 0; i < *ptr_num_expo; i++){
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
}


