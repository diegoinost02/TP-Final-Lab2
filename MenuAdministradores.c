#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <windows.h>
#include "structs.h"
#include "pelis.h"
#include "arbolPeli.h"
#include "listapeliculas.h"
#include "animaciones.h"
#include "TdaLdl.h"
#include "TdaListasS.h"
#include "FuncionesArch.h"
#include "MenuUsuario.h"
#include "MenuPrincipal.h"
#include "MenuAdministradores.h"

nodoListaUsers* menuDeAdministradores(nodoListaUsers* encontrado,nodoListaUsers* listaUsers,char archivoUsers[],char archivo[])
{
    int opcion = 0;

    while(opcion!=7)
    {
        system("cls");
        printf("\n1. listados");
        printf("\n2. alta");
        printf("\n3. baja");
        printf("\n4. modificacion");
        printf("\n5. consulta");
        printf("\n6. listado peliculas");
        printf("\n7. salir\n");

        scanf("%i",&opcion);

        do
        {
            switch(opcion)
            {
            case 1:
                ;
                system("cls");
                printf("listados\n");
                Sleep(1000);
                listados(archivoUsers);
                break;
            case 2:
                ;
                system("cls");
                printf("alta\n");
                Sleep(1000);
                listaUsers = altaUsuarioAdmin(listaUsers,archivoUsers);
                break;
            case 3:
                ;
                system("cls");
                printf("baja\n");
                Sleep(1000);
                listaUsers = bajaUsuarioAdmin(listaUsers,archivoUsers);
                break;
            case 4:
                ;
                system("cls");
                printf("modificacion\n");
                Sleep(1000);
                listaUsers = modificarPerfilAdmin(listaUsers,archivoUsers);
                break;
            case 5:
                ;
                system("cls");
                printf("consulta\n");
                Sleep(1000);
                consulta(listaUsers,archivoUsers);
                break;
            case 6:
                ;
                system("cls");
                menuPelisAdmin(archivo);
                break;
            }
        }
        while(opcion <1 && opcion > 6);
    }
}
void menuPelisAdmin(char archivo[])
{
    int opcion = 0;
    system("cls");
    printf("1. para ver las peliculas\n");
    printf("2. para modificar una pelicula\n");
    printf("3. para salir\n");
    scanf("%i",&opcion);

    while(opcion!=3)
    {
        do
        {
            switch(opcion)
            {
            case 1:
                system("cls");
                mostrarArchiPeliculasAdmin(archivo);
                system("pause");
                opcion = 3;
                break;
            case 2:
                system("cls");
                int id;
                printf("ingrese el id de la pelicula que desea modificar\n");
                scanf("%i",&id);
                modificarArchivoPorId(archivo,id);
                system("pause");
                opcion = 3;
                break;
            default:
                system("cls");
                printf("opcion incorrecta, saliendo");
                Sleep(1000);
                opcion = 3;
                break;
            }
        }
        while(opcion <1 && opcion > 2);
    }
}
void listados(char archivoUsers[])
{
    nodoListaUsers* listaAux = NULL;
    listaAux = recorrerArch(archivoUsers,listaAux);

    while(listaAux != NULL)
    {
        mostrarUsuario(listaAux->user);
        listaAux = listaAux->sig;
    }
    system("pause");
}

nodoListaUsers* altaUsuarioAdmin(nodoListaUsers* listaUsers,char archivoUsers[])
{
    mostrarBajasEnArchivo(archivoUsers);

    //int i = 0;
    stUsuario user;

    printf("eliga el mail que desea dar de alta\n");
    fflush(stdin);
    gets(user.mail);

    user = altaUsuario(archivoUsers,user);

    listaUsers = agregarUsuarioALista(listaUsers,user);

    return listaUsers;

}

void mostrarUsuario(stUsuario usuario)
{
    printf("\nid: %i\n",usuario.id);
    printf("apellido y nombre: ");
    puts(usuario.apellidoYnombres);
    printf("mail: ");
    puts(usuario.mail);
    printf("celular: %i\n",usuario.celular);
    printf("contrasenia: ");
    puts(usuario.contrasenia);
    printf("estado: %i\n",usuario.estado);
    printf("tipo de usuario: %i\n",usuario.tipoDeUsuario);
}

stUsuario altaUsuario(char archivoUsers[],stUsuario usuario)
{
    int flag = 0;
    int pos = 0;
    stUsuario use;

    FILE* arch = fopen(archivoUsers,"r+b");

    if(arch)
    {
        while(fread(&use,sizeof(stUsuario),1,arch)>0 && flag==0)
        {
            mostrarUsuario(use);
            pos++;
            if(strcmpi(use.mail,usuario.mail)==0)
            {
                flag = 1;
            }
        }

        fseek(arch,sizeof(stUsuario)*(pos-1),0);
        use.estado = 1;
        fwrite(&use,sizeof(stUsuario),1,arch);

        fclose(arch);
    }
    return use;
}

void mostrarBajasEnArchivo(char archivoUsers[])
{
    stUsuario user;
    FILE* arch = fopen(archivoUsers,"rb");

    if(arch)
    {
        while(fread(&user,sizeof(stUsuario),1,arch)>0)
        {
            if(user.estado == 0)
            {
                printf("\n----------\nUSUARIO\n----------");
                mostrarUsuario(user);
            }
        }
        fclose(arch);
    }
}

nodoListaUsers* bajaUsuarioAdmin(nodoListaUsers* listaUsers, char archivoUsers[])
{
    int opcion;
    stUsuario user;

    while(opcion!=3)
    {
        system("cls");
        printf("ingrese 1 si desea ver los usuarios, ingrese 2 para dar de baja un usuario, ingrese 3 para volver\n");
        scanf("%i",&opcion);

        switch(opcion)
        {
        case 1:
            system("cls");
            printf("usuarios: \n");
            recorrerYMostrar(listaUsers);
            system("pause");
            animacionCargando();
            break;
        case 2:
            system("cls");
            printf("\ningrese el mail del usuario que desea dar de baja\n");
            fflush(stdin);
            gets(user.mail);
            listaUsers = bajaDeUsuario(listaUsers,user,archivoUsers);
            animacionCargando();
            printf("el usuario se dio de baja exitosamente\n");
            system("pause");
            break;
        case 3:
            opcion = 3;
            animacionCargando();
            break;
        default:
            system("cls");
            printf("opcion incorrecta");
            system("pause");
            animacionCargando();
            break;
        }
    }
    return listaUsers;
}

nodoListaUsers* modificarPerfilAdmin(nodoListaUsers* listaUsers, char archivoUsers[])
{
    int opcion;
    stUsuario user;
    nodoListaUsers* encontrado = NULL;

    while(opcion!=3)
    {
        system("cls");
        printf("ingrese 1 si desea ver los usuarios, ingrese 2 para modificar un usuario, ingrese 3 para volver\n");
        scanf("%i",&opcion);

        switch(opcion)
        {
        case 1:
            system("cls");
            printf("usuarios: \n");
            recorrerYMostrar(listaUsers);
            system("pause");
            animacionCargando();
            break;
        case 2:
            system("cls");
            printf("ingrese el mail del usuario que desea modificar\n");
            fflush(stdin);
            gets(user.mail);

            encontrado = buscarEnLista(listaUsers,user);

            if(encontrado == NULL)
            {
                printf("el mail no existe o esta dado de baja\n");
                system("pause");
            }
            else
            {
                modificarPerfil(archivoUsers,&encontrado);
            }
            system("pause");
            break;
        case 3:
            opcion = 3;
            animacionCargando();
            break;
        default:
            system("cls");
            printf("opcion incorrecta");
            system("pause");
            animacionCargando();
            break;
        }
    }
    return listaUsers;
}

void consulta(nodoListaUsers* listaUsers,char archivoUsers[])
{
    int opcion = 0;
    stUsuario user;
    nodoListaUsers* encontrado = NULL;

    while(opcion!=3)
    {
        system("cls");
        printf("ingrese 1 para ver todos los usuarios, ingrese 2 para ver un usuario en especifico, ingrese 3 para volver\n");
        scanf("%i",&opcion);

        switch(opcion)
        {
        case 1:
            system("cls");
            printf("usuarios: \n");
            recorrerYMostrar(listaUsers);
            system("pause");
            animacionCargando();
            break;
        case 2:
            printf("ingrese el mal del usuario que desea ver\n");
            fflush(stdin);
            gets(user.mail);
            encontrado = buscarEnLista(listaUsers,user);

            if(encontrado != NULL)
            {
                verPerfil(encontrado->user);
            }
            else
            {
                user = buscarEnArch(archivoUsers,user.mail);

                if(user.estado == 0 || user.estado == 1)
                {
                    encontrado = agregarUsuarioALista(encontrado,user);
                    verPerfil(encontrado->user);
                }
                else
                {
                    printf("la cuenta no existe\n");
                    system("pause");
                }
            }
            break;
        case 3:
            opcion = 3;
            animacionCargando();
            break;
        default:
            system("cls");
            printf("opcion incorrecta");
            system("pause");
            animacionCargando();
            break;
        }
    }
}
