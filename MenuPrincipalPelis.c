#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pelis.h"
#include "arbolPeli.h"
#include "listapeliculas.h"
#include "usuarios.h"

const char archivo[]= "pelis";
const char archMiLista[]= "playlist";
const char archUsers[]= "usuarios";

    //cargarArchivoUsuarios(archUsers);
    //mostrarArchiUsuarios(archUsers);
    mostrarArchivoPlaylist(archMiLista);
    mostrarArchiPeliculasAdmin(archivo);

    int opcion;
    nodoArbolPelis* arbolPeli = inicArbol();
    arbolPeli = cargarArbolDesdeArchivo(archivo, arbolPeli);
    do{
        printf("1- Mostrar peliculas en orden alfabetico \n");
        printf("2- Mostrar peliculas ordenadas por anio \n");
        printf("3- Mostrar peliculas por genero \n");
        printf("4- Peliculas recomendadas \n");
        printf("5- Ver mi playlist \n");
        printf("0- salir \n");
        scanf("%i", &opcion);
        switch(opcion)
        {
        case 1: ;
            int opcion1;
            char nombrepeli[30];
            char seguir= 's';

            nodoListaPelis* listaNombre= inicLista();
            listaNombre= pasarDeArbolAlistaPorNombre(arbolPeli, listaNombre);
            mostrarLista(listaNombre);
            printf("__________________________________\n");

                printf("Quiere agregar una pelicula a su lista de favoritos \n");
                printf("1- SI \n");
                printf("0- NO \n");
                scanf("%i", &opcion1);
                if(opcion1 == 1)
                {
                    while(seguir == 's')
                    {
                        printf("Ingrese el nombre de la pelicula que desea agregar: \n");
                        fflush(stdin);
                        gets(nombrepeli);
                        nodoArbolPelis* peliBuscada= buscarPeliPorNombre(arbolPeli, nombrepeli);
                        if(peliBuscada != NULL)
                        {
                            altaPeliPlaylist(archMiLista, peliBuscada->peli.id, 2001);
                        }else{
                            printf("La pelicula ingresada no se encontro, pruebe de nuevo\n");
                        }
                        printf("Desea seguir agregando peliculas? 's' continuar, 'n' salir \n");
                        scanf("%c", &seguir);
                    }
                }else{
                    break;
                }


            system("pause");
            system("cls");
            break;
        case 2: ;
            int opcion2;
            char seguir2= 's';
            char nombrepeli2[30];
            nodoListaPelis* listaAnio= inicLista();
            listaAnio= pasarDeArbolAlistaPorAnio(arbolPeli, listaAnio);
            mostrarLista(listaAnio);
            printf("Quiere agregar una pelicula a su lista de favoritos \n");
                printf("1- SI \n");
                printf("0- NO \n");
                scanf("%i", &opcion2);
                if(opcion2 == 1)
                {
                    while(seguir2 == 's')
                    {
                        printf("Ingrese el nombre de la pelicula que desea agregar: \n");
                        fflush(stdin);
                        gets(nombrepeli2);
                        nodoArbolPelis* peliBuscada2= buscarPeliPorNombre(arbolPeli, nombrepeli2);
                        if(peliBuscada2 != NULL)
                        {
                            altaPeliPlaylist(archMiLista, peliBuscada2->peli.id, 2001);
                        }else{
                            printf("La pelicula ingresada no se encontro, pruebe de nuevo\n");
                        }
                        printf("Desea seguir agregando peliculas? 's' continuar, 'n' salir \n");
                        scanf("%c", &seguir2);
                    }
                }else{
                    break;
                }

            system("pause");
            system("cls");
            break;
        case 3: ;
            int opcion3;
            char seguir3= 's';
            char nombrepeli3[30];
            nodoListaPelis* listaGenero= inicLista();
            char genero[20];
            printf("Ingrese el genero que desea buscar: \n");
            fflush(stdin);
            gets(genero);
            listaGenero= pasarDeArbolAlista(arbolPeli, listaGenero, genero);
            mostrarLista(listaGenero);
            printf("Quiere agregar una pelicula a su lista de favoritos \n");
                printf("1- SI \n");
                printf("0- NO \n");
                scanf("%i", &opcion3);
                if(opcion3 == 1)
                {
                    while(seguir3 == 's')
                    {
                        printf("Ingrese el nombre de la pelicula que desea agregar: \n");
                        fflush(stdin);
                        gets(nombrepeli3);
                        nodoArbolPelis* peliBuscada3= buscarPeliPorNombre(arbolPeli, nombrepeli3);
                        if(peliBuscada3 != NULL)
                        {
                            altaPeliPlaylist(archMiLista, peliBuscada3->peli.id, 2002);
                        }else{
                            printf("La pelicula ingresada no se encontro, pruebe de nuevo\n");
                        }
                        printf("Desea seguir agregando peliculas? 's' continuar, 'n' salir \n");
                        scanf("%c", &seguir3);
                    }
                }else{
                    break;
                }

            system("pause");
            system("cls");
            break;
        case 4: ;
            mostrarPeliRecomendadas(archMiLista, arbolPeli, 2002);
            system("pause");
            system("cls");
            break;
        case 5: ;
            nodoListaUsers* LDL= inicListaUsers();

            //bajaPeli(archMiLista, 1001, 2001);

            LDL= pasarDeArchsALDL(archUsers, archMiLista, LDL, arbolPeli);
            mostrarLDL(LDL);

            system("pause");
            system("cls");
        case 0:
            break;
        default:
            printf("opcion invalida\n");
        }
    }while(opcion != 0);

