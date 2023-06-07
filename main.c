#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "usuarios.h"
#include "pelis.h"
#include "arbolPeli.h"
#include "listapeliculas.h"
#include "animaciones.h"
#include "TdaLdl.h"
#include "TdaListasS.h"
#include "FuncionesArch.h"
#include "MenuUsuario.h"
#include "MenuAdministradores.h"
#include "MenuPrincipal.h"


void crearArchivoDeStAdministrador(char nombre[]);
stUsuario cargarStAdministrador(stUsuario administrador,int);

const char archivo[]= "pelis";
const char archMiLista[]= "playlist";
const char archUsers[]= "usuarios";
const char archivoPersistir[] = "pelisFav";

int main()
{
    nodoListaUsers* listaUsers = inicListaS();
    char archivoUsers [] = "archivoUsuarios.bin";
    char archivoPersistir[] = "pelisFav.bin";
    MostrarArchivoStUsuario(archivoUsers);
    // system("pause");
    //crearArchivoDeStAdministrador(archivoUsers);
    listaUsers = pasarArchEnListaUsers(archivoUsers,listaUsers);
    //listaUsers = pasarArchPersistirEnListaUsers(archivoPersistir,listaUsers);
    //listaUsers = cargarPelisCompletas(archivo,listaUsers);*/
    animacionCargando();
    menuPrincipal(archivoUsers,listaUsers,archivo);
    return 0;
}

void crearArchivoDeStAdministrador(char nombre[])
{
    FILE* fp;
    fp=fopen(nombre,"w+b");

    stUsuario administrador;

    char seguir = 's';

    if(fp!=NULL)
    {
        while(seguir=='s' || seguir == 'S')
        {
            int cant= ftell(fp)/sizeof(stUsuario);
            administrador = cargarStAdministrador(administrador,cant);

            fwrite(&administrador,sizeof(stUsuario),1,fp);

            printf("desea seguir ?s/n\n");
            fflush(stdin);
            scanf("%c",&seguir);
        }
        fclose(fp);
    }
}

stUsuario cargarStAdministrador(stUsuario administrador,int cant)
{
    administrador.id=cant;
    printf("ingrese apellido y nombre/s\n");
    fflush(stdin);
    gets(administrador.apellidoYnombres);
    printf("ingrese el mail\n");
    fflush(stdin);
    gets(administrador.mail);
    printf("ingrese el celular\n");
    scanf("%i",&administrador.celular);
    printf("ingrese la contrasenia\n");
    fflush(stdin);
    gets(administrador.contrasenia);

    administrador.estado = 1;
    administrador.tipoDeUsuario = 2;

    return administrador;
}
