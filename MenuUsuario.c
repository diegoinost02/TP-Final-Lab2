#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <windows.h>
#include "structs.h"
#include "usuarios.h"
#include "pelis.h"
#include "arbolPeli.h"
#include "listapeliculas.h"
#include "animaciones.h"
#include "TdaLdl.h"
#include "TdaListasS.h"
#include "FuncionesArch.h"
#include "MenuAdministradores.h"
#include "MenuPrincipal.h"
#include "MenuUsuario.h"

nodoListaUsers* cargarStUsuario(nodoListaUsers* listaUsers,char archivoUsers[])
{
    stUsuario usuario;
    FILE* fp = fopen(archivoUsers,"ab");

    int cant= ftell(fp)/sizeof(stUsuario);

    if(fp)
    {
        usuario.id=cant+1;
        printf("ingrese apellido y nombre/s\n");
        fflush(stdin);
        gets(usuario.apellidoYnombres);
        system("cls");
        printf("ingrese el mail\n");
        fflush(stdin);
        gets(usuario.mail);
        system("cls");
        printf("ingrese el celular\n");
        scanf("%i",&usuario.celular);
        system("cls");
        printf("ingrese la contrasenia\n");
        fflush(stdin);
        gets(usuario.contrasenia);
        system("cls");
        usuario.tipoDeUsuario = 1;
        usuario.estado=1;

        fwrite(&usuario,sizeof(stUsuario),1,fp);
        listaUsers = agregarUsuarioALista(listaUsers,usuario);

        system("cls");
        printf("                      registro exitoso, a la brevedad sera redireccionado al menu principal\n");
        Sleep(1500);
        animacionCargando();

        fclose(fp);
    }
    return listaUsers;
}

nodoListaUsers* menuDeUsuario(nodoListaUsers** encontrado,nodoListaUsers* lista,char archivoUsers[])
{
    int opcion;

    while(opcion != 5)
    {
        system("cls");
        printf("\n1. baja de usuario");
        printf("\n2. ver mi perfil");
        printf("\n3. modificar mi perfil");
        printf("\n4. mostrar peliculas");
        printf("\n5. salir\n");

        scanf("%i",&opcion);

        do
        {
            switch(opcion)
            {
            case 1:
                system("cls");
                printf("baja de usuario\n");
                Sleep(1000);
                lista = bajaDeUsuario(lista,(*encontrado)->user,archivoUsers);
                (*encontrado)->user.estado = 0;
                break;
            case 2:
                system("cls");
                printf("ver perfil\n");
                Sleep(1000);
                verPerfil((*encontrado)->user);
                break;
            case 3:
                system("cls");
                printf("modificar mi perfil\n");
                Sleep(1000);
                modificarPerfil(archivoUsers,encontrado);
                break;
            case 4:
                system("cls");
                printf("mostrar peliculas\n");
                Sleep(1000);
                lista = mostrarPeliculas(lista,(*encontrado)->user);
                break;
            default:
                system("cls");
                if(opcion == 5)
                {
                    printf("cerrando...\n");
                    Sleep(2000);
                }
                else
                {
                    printf("opcion incorrecta vuelva a intentarlo\n");
                    Sleep(1000);
                }
                break;
            }
        }
        while(opcion < 1 && opcion > 4);
    }
    return lista;

}

void verPerfil(stUsuario usuario)
{


    if(usuario.estado == 1)
    {
        system("cls");
        printf("\nid: %i\n",usuario.id);
        printf("apellido y nombre: ");
        puts(usuario.apellidoYnombres);
        printf("mail: ");
        puts(usuario.mail);
        printf("celular: %i\n",usuario.celular);

        int cantLetrasContrasenia = strlen(usuario.contrasenia);
        //  char contrasenia[cantLetrasContrasenia];

        printf("contrase%ca: ",164);
        for(int i=0; i<cantLetrasContrasenia; i++)
        {
            printf("*");
            //contrasenia[i]='*';
        }
        printf("\n");

        //printf("contrase%ca: ",165);
        // puts(contrasenia);

    }
    else
    {
        printf("los datos no existen\n");
    }
    system("pause");
}

void modificarPerfil(char archivoUsers[],nodoListaUsers** encontrado)
{

    int opcion = 0;
    stUsuario aux;
    int flag = 0;
    int pos = 0;
    FILE* arch = fopen(archivoUsers,"r+b");

    if((*encontrado)->user.estado == 1 && arch != NULL)
    {
        while(fread(&aux,sizeof(stUsuario),1,arch) > 0 && flag == 0)
        {

            if(strcmpi((*encontrado)->user.mail,aux.mail) == 0)
            {
                flag = 1;
            }
            pos++;
        }

        fseek(arch,sizeof(stUsuario)*(pos-1),0);

        while(opcion != 5)
        {

            do
            {

                printf("elija la opcion de elemento del registro que desea modificar\n");
                printf("1)celular\n");
                printf("2)nombre y apellido\n");
                printf("3)contrase%ca\n",164);
                printf("4)mail\n");
                printf("5)salir\n");
                scanf("%i",&opcion);

                switch(opcion)
                {
                case 1:

                    printf("celular\n");
                    scanf("%i",&aux.celular);
                    (*encontrado)->user.celular = aux.celular;
                    fwrite(&(*encontrado)->user,sizeof(stUsuario),1,arch);
                    break;
                case 2:
                    printf("nombre y apellido\n");
                    fflush(stdin);
                    gets(aux.apellidoYnombres);
                    strcpy((*encontrado)->user.apellidoYnombres,aux.apellidoYnombres);
                    fwrite(&(*encontrado)->user,sizeof(stUsuario),1,arch);
                    break;
                case 3:
                    printf("contrase%ca\n",164);
                    fflush(stdin);
                    gets(aux.contrasenia);
                    strcpy((*encontrado)->user.contrasenia,aux.contrasenia);
                    fwrite(&(*encontrado)->user,sizeof(stUsuario),1,arch);
                    break;
                case 4:
                    printf("mail\n");
                    fflush(stdin);
                    gets(aux.mail);
                    strcpy((*encontrado)->user.mail,aux.mail);
                    fwrite(&(*encontrado)->user,sizeof(stUsuario),1,arch);
                    break;
                default:
                    if(opcion == 5)
                    {
                        animacionCargando();
                    }
                    else
                    {
                        printf("opcion incorrecta\n");
                    }
                    break;

                }
                system("cls");
            }
            while(opcion < 1 && opcion > 4);


        }
        fclose(arch);
    }
    else if((*encontrado)->user.estado == 0)
    {
        printf("la cuenta ya no existe\n");
        system("pause");
    }
}

nodoListaUsers* bajaDeUsuario(nodoListaUsers* listaUsers,stUsuario usuario,char archivoUsers[])
{
    bajaEnArchivo(usuario,archivoUsers);
    listaUsers = borrarNodo(listaUsers, usuario.id);

    return listaUsers;
}

nodoListaUsers* mostrarPeliculas(nodoListaUsers* lista,stUsuario user)
{

    const char archivo[]= "pelis";
    const char archMiLista[]= "playlist";
    const char archUsers[]= "usuarios";
    char archivoPersistir[] = "pelisFav";

    //cargarArchivoUsuarios(archUsers);
    //mostrarArchiUsuarios(archUsers);
    mostrarArchivoPlaylist(archMiLista);
    mostrarArchiPeliculasAdmin(archivo);
    lista = pasarArchPelisAlista(lista,user,archivoPersistir);

    int opcion;
    nodoArbolPelis* arbolPeli = inicArbol();
    arbolPeli = cargarArbolDesdeArchivo(archivo, arbolPeli);
    do
    {
        printf("1- Mostrar peliculas en orden alfabetico \n");
        printf("2- Mostrar peliculas ordenadas por anio \n");
        printf("3- Mostrar peliculas por genero \n");
        printf("4- Peliculas recomendadas \n");
        printf("5- Ver mi playlist \n");
        printf("0- salir \n");
        scanf("%i", &opcion);
        switch(opcion)
        {
        case 1:
            ;
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
                        lista = agregarPeliAPlaylista(lista,user,peliBuscada->peli);
                        guardarEnArchivoPeli(archivoPersistir,peliBuscada->peli,user,lista);
                    }
                    else
                    {
                        printf("La pelicula ingresada no se encontro, pruebe de nuevo\n");
                    }
                    printf("Desea seguir agregando peliculas? 's' continuar, 'n' salir \n");
                    scanf("%c", &seguir);
                }
            }
            else
            {
                break;
            }


            system("pause");
            system("cls");
            break;
        case 2:
            ;
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
                        lista = agregarPeliAPlaylista(lista,user,peliBuscada2->peli);
                        guardarEnArchivoPeli(archivoPersistir,peliBuscada2->peli,user,lista);
                    }
                    else
                    {
                        printf("La pelicula ingresada no se encontro, pruebe de nuevo\n");
                    }
                    printf("Desea seguir agregando peliculas? 's' continuar, 'n' salir \n");
                    scanf("%c", &seguir2);
                }
            }
            else
            {
                break;
            }

            system("pause");
            system("cls");
            break;
        case 3:
            ;
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
                        lista = agregarPeliAPlaylista(lista,user,peliBuscada3->peli);
                        guardarEnArchivoPeli(archivoPersistir,peliBuscada3->peli,user,lista);
                    }
                    else
                    {
                        printf("La pelicula ingresada no se encontro, pruebe de nuevo\n");
                    }
                    printf("Desea seguir agregando peliculas? 's' continuar, 'n' salir \n");
                    scanf("%c", &seguir3);
                }
            }
            else
            {
                break;
            }

            system("pause");
            system("cls");
            break;
        case 4:
            ;
            mostrarPeliRecomendadas(archMiLista, arbolPeli, 2002);
            system("pause");
            system("cls");
            break;
        case 5:
            ;
            recorrerListaDeUsers(lista);
            system("pause");
            system("cls");
            break;
        case 0:
            break;
        default:
            printf("opcion invalida\n");
        }
    }
    while(opcion != 0);

    return lista;
}
