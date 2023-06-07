#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "animaciones.h"
#include "TdaLdl.h"
#include "TdaListasS.h"
#include "FuncionesArch.h"
#include "MenuUsuario.h"
#include "MenuAdministradores.h"
#include "MenuPrincipal.h"
#include "listapeliculas.h"
#include "pelis.h"
#include "arbolPeli.h"
#include "usuarios.h"

//funciones admin
void cargarArchivo(char arch[])
{
    stPeliculas aux;
    char control= 's';
    FILE* archi= fopen(arch, "ab");
    if(archi)
    {
        while(control == 's')
        {
            fseek(archi, 0, SEEK_END);
            int cant= ftell(archi)/sizeof(stPeliculas);
            aux.id= 1000 + cant;
            printf("Nombre: \n");
            fflush(stdin);
            gets(aux.nombre);
            printf("Genero: \n");
            fflush(stdin);
            gets(aux.genero);
            printf("Anio: \n");
            scanf("%i", &aux.anio);
            printf("Actores: \n");
            cargarMatrizActores(aux.actores, 3);
            printf("Calificacion: \n");
            scanf("%i", &aux.calificacion);
            printf("Estado: \n");
            scanf("%i", &aux.estado);
            fseek(archi, 0, SEEK_SET);
            fwrite(&aux, sizeof(stPeliculas), 1, archi);
            printf("¿Desea seguir cargando peliculas? 's' seguir, 'n' terminar \n");
            fflush(stdin);
            scanf("%c", &control);
        }
        fclose(archi);
    } else{
        printf("No se pudo abrir el archivo \n");
    }
}
void cargarMatrizActores(char M[][50], int dimF)
{
    int f= 0;

    while(f < dimF)
    {
        printf("Nombre del actor/a: \n");
        fflush(stdin);
        gets(M[f]);
        f++;
    }
}
void mostrarMatrizActores(char M[3][50])
{
    int f= 0;
    int dimF= 3;
    while(f < dimF)
    {
        printf("%s \n", M[f]);
        f++;
    }

}
void mostrarArchiPeliculasAdmin(char archivo[])
{
    stPeliculas aux;

    FILE *archi= fopen(archivo, "rb");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stPeliculas), 1, archi) > 0)
        {
            if(aux.estado == 1)
            {
                mostrarPeliculaAadmin(aux);
            }

        }
        fclose(archi);
    } else {
        printf("No se pudo abrir el archivo \n");
    }
}
void mostrarPeliculaAadmin(stPeliculas aux)
{

    printf("\nNombre: %s\n", aux.nombre);
    printf("Genero: %s\n", aux.genero);
    printf("Anio: %i\n", aux.anio);
    printf("Actores: \n");
    mostrarMatrizActores(aux.actores);
    printf("Calificacion: %i \n", aux.calificacion);
    printf("ID:  %i \n", aux.id);
    printf("Estado: %i\n", aux.estado);
    puts("---------------------------");

}
void modificarArchivoPorId(char archivo[], int dato)
{
    stPeliculas aux;
    int flag = 0;
    int pos = 0;
    int continuar;
    FILE* archi= fopen(archivo, "r+b");
    if(archi != NULL)
    {
        while(flag == 0 && fread(&aux, sizeof(stPeliculas), 1, archi) > 0)
        {
            pos++;
            if(aux.id == dato)
            {

                do{
                    printf("Elija la opcion que desea modificar: \n");
                    printf("1- Nombre. \n ");
                    printf("2- Genero. \n");
                    printf("3- Anio. \n");
                    printf("4- Actores. \n");
                    printf("5- Calificacion. \n");
                    printf("6- ID. \n");
                    printf("7- Estado. \n");
                    printf("0- Salir \n");
                    scanf("%i", &continuar);

                    switch(continuar)
                    {
                    case 1:
                        printf("Nombre modificado: \n");
                        fflush(stdin);
                        gets(aux.nombre);
                        fseek(archi, sizeof(stPeliculas)* (pos-1), 0);
                        fwrite(&aux, sizeof(stPeliculas), 1, archi);
                        system("pause");
                        system("cls");
                        break;
                    case 2:
                        printf("Genero modificado: \n");
                        fflush(stdin);
                        gets(aux.genero);
                        fseek(archi, sizeof(stPeliculas)* (pos-1), 0);
                        fwrite(&aux, sizeof(stPeliculas), 1, archi);
                        system("pause");
                        system("cls");
                        break;
                    case 3:
                        printf("Anio modificado: \n");
                        scanf("%i", &aux.anio);
                        fseek(archi, sizeof(stPeliculas)* (pos-1), 0);
                        fwrite(&aux, sizeof(stPeliculas), 1, archi);
                        system("pause");
                        system("cls");
                        break;
                    case 4:
                        printf("Modificar actores \n");
                        break;
                    case 5:
                        printf("Calificacion modificada: \n");
                        scanf("%i", &aux.calificacion);
                        fseek(archi, sizeof(stPeliculas)* (pos-1), 0);
                        fwrite(&aux, sizeof(stPeliculas), 1, archi);
                        system("pause");
                        system("cls");
                        break;
                    case 6:
                        printf("Modificar ID: \n");
                        scanf("%i", &aux.id);
                        fseek(archi, sizeof(stPeliculas)* (pos-1), 0);
                        fwrite(&aux, sizeof(stPeliculas), 1, archi);
                        system("pause");
                        system("cls");
                        break;
                    case 7:
                        printf("Modificar estado: \n");
                        scanf("%i", &aux.estado);
                        fseek(archi, sizeof(stPeliculas)* (pos-1), 0);
                        fwrite(&aux, sizeof(stPeliculas), 1, archi);
                        system("pause");
                        system("cls");
                        break;
                    case 0:
                        system("cls");
                        break;
                    default:
                        printf("Opcion invalida \n");

                    }

                    flag= 1;
                }while(continuar != 0);
            }
        }

        fclose(archi);
    } else {
        printf("No se pudo abrir el archivo\n");
    }
}
//usuario
void mostrarPeliculaAUsuario(stPeliculas aux)
{

    printf("\nNombre: %s\n", aux.nombre);
    printf("Genero: %s\n", aux.genero);
    printf("Anio: %i\n", aux.anio);
    printf("Actores: \n");
    mostrarMatrizActores(aux.actores);
    printf("Calificacion: %i \n", aux.calificacion);
    puts("---------------------------");

}


//funciones de alta o baja
int existePeli(char arch[], int idPeli, int idUser)
{
    stPlaylist aux;
    int existe= 0;
    int pos = -1;
    FILE* archi= fopen(arch, "r+b");
    if(archi)
    {

         while(fread(&aux, sizeof(stPlaylist), 1, archi) > 0 && existe == 0)
         {
            if(aux.idPelicula == idPeli && aux.idUsuario == idUser)
            {
                if(aux.estadoPelicula == 0)
                {
                    aux.estadoPelicula= 1;
                    fseek(archi, sizeof(stPlaylist) * (pos), SEEK_CUR);
                    fwrite(&aux, sizeof(stPlaylist), 1, archi);
                }
                existe= 1;
            }

        }

        fclose(archi);
    }else{
        printf("No se pudo abrir el archivo \n");
    }
    return existe;
}
void altaPeliPlaylist(char arch[], int idPeli, int idUser)
{
    stPlaylist aux;

    int existe= existePeli(arch, idPeli, idUser);
    if(existe != 1)
    {
        FILE* archi= fopen(arch, "ab");
        if(archi)
        {

            aux.idPelicula= idPeli;
            aux.idUsuario= idUser;
            aux.estadoPelicula= 1;
            fwrite(&aux, sizeof(stPlaylist), 1, archi);

            fclose(archi);
        }else{
            printf("no se pudo abrir el archivo \n");
        }

   }
}
void bajaPeli(char arch[], int idPeli, int idUser)
{
    stPlaylist aux;
    int flag= 0;
    int pos = -1;
    FILE *archi= fopen(arch, "r+b");
    if(archi != NULL)
    {
        while(fread(&aux, sizeof(stPlaylist), 1, archi) > 0 && flag == 0)
        {
            if(aux.idPelicula == idPeli && aux.idUsuario == idUser)
            {
                aux.estadoPelicula= 0;
                fseek(archi, sizeof(stPlaylist) * (pos), SEEK_CUR);
                fwrite(&aux, sizeof(stPlaylist), 1, archi);
                flag= 1;
            }

        }
        fclose(archi);
    }else{
        printf("No se pudo abrir el archivo \n");
    }

}




