#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "listapeliculas.h"
#include "pelis.h"
#include "arbolPeli.h"
#include "usuarios.h"
#include "animaciones.h"
#include "TdaLdl.h"
#include "TdaListasS.h"
#include "FuncionesArch.h"
#include "MenuUsuario.h"
#include "MenuAdministradores.h"
#include "MenuPrincipal.h"


void cargarArchivoUsuarios(char arch[])
{
    stUsuario aux;
    char seguir= 's';
    FILE* archi= fopen(arch, "ab");
    if(archi)
    {
        while(seguir == 's')
        {
            printf("Nombre: \n");
            fflush(stdin);
            gets(aux.apellidoYnombres);
            printf("Mail: \n");
            fflush(stdin);
            gets(aux.mail);
            printf("Contrasenia: \n");
            fflush(stdin);
            gets(aux.contrasenia);
            printf("Celular: \n");
            scanf("%i", &aux.celular);
            printf("Estado: \n");
            scanf("%i", &aux.estado);
            fseek(archi, 0, SEEK_END);
            int cant= ftell(archi)/sizeof(stUsuario);
            aux.id= 2000 + cant;
            fseek(archi, 0, SEEK_SET);
            fwrite(&aux, sizeof(stUsuario), 1, archi);
            printf("Desea seguir? 's' continuar 'n' salir \n");
            fflush(stdin);
            scanf("%c", &seguir);
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir elarchivo \n");
    }
}
void mostrarArchiUsuarios(char arch[])
{
    stUsuario aux;
    FILE* archi= fopen(arch, "rb");
    if(archi)
    {
        while(fread(&aux, sizeof(stUsuario), 1, archi) > 0)
        {
            mostrarUsuario(aux);
        }
        fclose(archi);
    }
}
void mostrarUser(stUsuario dato)
{
    printf("Nombre y apellido: %s \n", dato.apellidoYnombres);
    printf("mail: %s \n", dato.mail);
    printf("Celular: %i \n", dato.celular);
    printf("Estado: %i \n", dato.estado);
    printf("ID: %i \n", dato.id);
    puts("------------------------------- \n");
}
void mostrarPlaylist(stPlaylist dato)
{
    printf("ID usuario: %i \n", dato.idUsuario);
    printf("ID pelicula: %i \n", dato.idPelicula);
    printf("Estado pelicula: %i \n ", dato.estadoPelicula);
    puts("------------------------------\n");
}
void mostrarArchivoPlaylist(char arch[])
{
    stPlaylist aux;
    FILE* archi= fopen(arch, "rb");
    if(archi)
    {
        while(fread(&aux, sizeof(stPlaylist), 1, archi) > 0)
        {
            mostrarPlaylist(aux);
        }
        fclose(archi);
    }
}
///funciones para pasar usuarios a la ldl
nodoListaUsers* inicListaUsers()
{
    return NULL;
}
nodoListaUsers* crearNodoUser(stUsuario dato)
{
    nodoListaUsers* aux= (nodoListaUsers*)malloc(sizeof(nodoListaUsers));
    aux->user= dato;
    aux->sig= NULL;

    return aux;
}
nodoListaUsers* agregarAlPpioUsers(nodoListaUsers* lista, nodoListaUsers* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->sig = lista;
        lista= nuevoNodo;
    }
    return lista;
}
void mostrarUsuarioEnLDL(stUsuario dato)
{
    printf("Nombre: %s \n", dato.apellidoYnombres);
    printf("Mail: %s \n", dato.mail);
    if(dato.estado == 1)
    {
        printf("Estado Activo \n");
    }
    printf("ID: %i \n", dato.id);
}
/////////////
nodoPlaylist* inicListaPlaylist()
{
    return NULL;
}
nodoPlaylist* crearNodoPlaylist(stPeliculas dato)
{
    nodoPlaylist* aux= (nodoPlaylist*)malloc(sizeof(nodoPlaylist));
    aux->dato= dato;
    aux->sig= NULL;

    return aux;
}
nodoPlaylist* buscarUltimito(nodoPlaylist* lista)
{
    nodoPlaylist* seg = lista;
    if(seg)
        while(seg->sig != NULL)
        {
            seg= seg->sig;
        }
    return seg;
}
nodoPlaylist* agregarAlFinalPlaylist(nodoPlaylist* lista, nodoPlaylist* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nodoPlaylist* ultimo = buscarUltimito(lista);
        ultimo->sig= nuevoNodo;
    }
    return lista;
}

void mostrarLDL(nodoListaUsers* LDL)
{
    nodoListaUsers* seguidora= LDL;
    nodoPlaylist* segui;

    while(seguidora != NULL)
    {
        mostrarUser(seguidora->user);
        segui->dato = seguidora->playlist->peli;
        while(segui != NULL)
        {
            if(segui->dato.estado == 1)
            {
                mostrarPeliculaAUsuario(segui->dato);
            }
            segui= segui->sig;
        }
        seguidora= seguidora->sig;
    }
}
nodoListaUsers* altaSoloUsuariosEnLDL(nodoListaUsers* lista, stUsuario dato)
{
    nodoListaUsers* usuarioEncontrado = buscarUser(lista, dato.id);
    if(usuarioEncontrado == NULL)
    {
        nodoListaUsers* nuevoNodo= crearNodoUsuario(dato);
        lista= agregarAlPpioUsers(lista, nuevoNodo);

    }
    return lista;
}
/*nodoListaUsers* altaUsersEnLDL(nodoListaUsers* lista, nodoPlaylist* nuevo, stUsuario dato)
{
    nodoListaUsers* usuarioEncontrado = buscarUser(lista, dato.id);

    if(usuarioEncontrado == NULL)
    {
        nodoListaUsers* nuevoNodo= crearNodoUser(dato);
        lista= agregarAlPpioUsers(lista, nuevoNodo);
        lista->playlist = agregarAlFinalPlaylist(lista->playlist, nuevo);

    }
    else
    {
        usuarioEncontrado->playlist = agregarAlFinalPlaylist(usuarioEncontrado->playlist, nuevo);
    }
    return lista;
}*/
nodoListaUsers* buscarUser(nodoListaUsers* lista, int id)
{
    nodoListaUsers* seg = lista;
    nodoListaUsers* usuarioEncontrado = NULL;
    int flag = 0;
    while(seg!= NULL && flag == 0)
    {
        if(seg->user.id == id)
        {
            usuarioEncontrado= seg;
            flag=1;
        }
        seg= seg->sig;
    }
    return usuarioEncontrado;
}

/*nodoListaUsers* pasarDeArchsALDL(char arch1[], char arch2[], nodoListaUsers* LDL, nodoArbolPelis* arbol)
{
    stUsuario aux1, users;
    //int i= 0;
    int existe= 0;
    stPeliculas pelis;
    stPlaylist aux;
    FILE* archi= fopen(arch1, "rb");
    FILE* archivin= fopen(arch2, "rb");
    if(archi != NULL && archivin != NULL)
    {
        while(fread(&aux1, sizeof(stUsuario), 1, archi) > 0)
        {
            while(fread(&aux, sizeof(stPlaylist), 1, archivin) > 0)
            {

                if(aux1.id == aux.idUsuario && aux.estadoPelicula == 1)
                {

                    users= aux1;
                    nodoArbolPelis* peliBuscada= buscarPeliPorID(arbol, aux.idPelicula);
                    pelis= peliBuscada->peli;
                    nodoPlaylist* nuevo= crearNodoPlaylist(pelis);
                    LDL= altaUsersEnLDL(LDL, nuevo, users);

                    existe= 1;

                }
                else
                {
                    existe= 0;
                }
            }
            fseek(archivin, 0, SEEK_SET);
            if(existe == 0)
            {
                nodoPlaylist* nuevo= NULL;
                users= aux1;

                LDL= altaUsersEnLDL(LDL, nuevo, users);
            }
        }
        fclose(archi);
        fclose(archivin);
    }
    else
    {
        printf("Alguno o ningun archivo pudo abrirse \n");
    }
    return LDL;
}*/

