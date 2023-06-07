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
#include "TdaListasS.h"
#include "structs.h"
#include "TdaLdl.h"
#include "TdaListasS.h"
#include "MenuUsuario.h"
#include "MenuAdministradores.h"
#include "MenuPrincipal.h"
#include "FuncionesArch.h"


void MostrarArchivoStUsuario(char nombre[])
{
    stUsuario usuario;

    FILE*FP;
    FP=fopen(nombre,"rb");

    if(FP!=NULL)
    {
        while(fread(&usuario,sizeof(stUsuario),1,FP)>0)
        {
            if(usuario.tipoDeUsuario==2)
            {
                printf("\n----------\nADMINISTRADOR\n----------");
                mostrarUsuario(usuario);
            }
            else
            {
                printf("\n----------\nUSUARIO\n----------");
                mostrarUsuario(usuario);
            }
        }
        fclose(FP);
    }
}

nodoListaUsers* pasarArchEnListaUsers(char archivo[],nodoListaUsers* lista)
{
    FILE* arch = fopen(archivo,"rb");
    stUsuario usuario;

    if(arch)
    {
        while(fread(&usuario,sizeof(stUsuario),1,arch) > 0)
        {
            if(usuario.tipoDeUsuario == 1 && usuario.estado == 1)
            {
                nodoListaUsers* nuevoNodo = crearNodoUsuario(usuario);
                lista = agregarAlPpio(lista,nuevoNodo);
            }
        }
        fclose(arch);
    }
    return lista;
}

stUsuario buscarEnArch(char archivoUsers[],char mail[])
{
    stUsuario user;
    int flag = 0;
    FILE* arch = fopen(archivoUsers,"rb");

    if(arch)
    {
        while(flag == 0 && fread(&user,sizeof(stUsuario),1,arch) > 0)
        {
            if(strcmpi(user.mail,mail)==0)
            {
                flag = 1;
            }
        }
        if(flag==0)
        {
            user.estado = 2;
        }
        fclose(arch);
    }
    return user;
}

void bajaEnArchivo(stUsuario usuario, char archivoUsers[])
{
    stUsuario user;
    int pos = 0;
    int flag = 0;

    FILE* arch = fopen(archivoUsers,"r+b");

    if(arch)
    {
        while(fread(&user,sizeof(stUsuario),1,arch)>0 && flag==0)
        {
            pos++;

            if(strcmpi(user.mail,usuario.mail)==0)
            {
                flag = 1;
            }
        }

        fseek(arch,sizeof(stUsuario)*(pos-1),0);

        user.estado = 0;

        fwrite(&user,sizeof(stUsuario),1,arch);

        fclose(arch);
    }
}

nodoListaUsers* recorrerArch(char archivo[],nodoListaUsers* lista)
{
    FILE* arch = fopen(archivo,"rb");
    stUsuario usuario;

    if(arch)
    {
        while(fread(&usuario,sizeof(stUsuario),1,arch) > 0)
        {
            nodoListaUsers* nuevoNodo = crearNodoUsuario(usuario);
            lista = agregarEnOrden(lista,nuevoNodo);


        }
        fclose(arch);
    }
    return lista;
}

/*nodoListaUsers* pasarArchPersistirEnListaUsers(char archivoPersistir[],nodoListaUsers* listaUsers)
{
    nodoListaUsers* seg = listaUsers;
    persistirPelis peliculas;
    int i = 0;

    FILE* arch = fopen(archivoPersistir,"ab");

    if(arch)
    {
        while(fread(&peliculas,sizeof(persistirPelis),1,arch)>0)
        {
            while(seg->user.id != peliculas.idUsuario)
            {
                seg = seg->sig;
            }
            while(i < peliculas.validos)
            {
                seg->playlist->peli.id = peliculas.idPeli[i];
                seg->playlist = seg->playlist->sig;
                i = i+1;
            }
            seg = listaUsers;
        }
        fclose(arch);
    }

    return listaUsers;
}*/

/*nodoListaUsers* cargarPelisCompletas(char archivo[],nodoListaUsers* listaUsers)
{
    nodoListaUsers* seg = listaUsers;
    stPeliculas aux;
    //int validos;
    FILE* arch = fopen(archivo,"rb");

    if(arch)
    {
        while(fread(&aux,sizeof(stPeliculas),1,arch)>0)
        {
            while(seg->playlist !=NULL && aux.id != seg->playlist->peli.id)
            {
                seg->playlist = seg->playlist->sig;
            }
            if(aux.id != seg->playlist->peli.id)
            {
                seg = seg->sig;
            }
            else if(aux.id == seg->playlist->peli.id)
            {
                seg->playlist->peli.anio = aux.anio;
                seg->playlist->peli.calificacion = aux.calificacion;
                seg->playlist->peli.id = aux.id;
                for(int i = 0; i < 3; i++)
                {
                    strcpy(seg->playlist->peli.actores[i],aux.actores[i]);
                }
                strcpy(seg->playlist->peli.genero,aux.genero);
                strcpy(seg->playlist->peli.nombre,aux.nombre);
            }
            seg = listaUsers;
        }
        fclose(arch);
    }

    return listaUsers;
}*/

nodoListaUsers* agregarPeliAPlaylista(nodoListaUsers* lista,stUsuario user,stPeliculas pelicula)
{

    nodoListaPelis* peli = crearNodoPeli(pelicula);
    nodoListaUsers* pos = buscar(lista,user.id);


    if(pos == NULL)
    {
        nodoListaUsers* usuario = crearNodoUsuario(user);
        lista = agregarAlPpio(lista,usuario);
        pos = lista;
    }

    pos->playlist = agregarAlPpioPeli(pos->playlist,peli);


    return lista;
}
void guardarEnArchivoPeli(char archivoPersistir[],stPeliculas peli,stUsuario user,nodoListaUsers* lista)
{
    FILE* arch;
    arch = fopen(archivoPersistir,"ab");
    persistirPelis fav;
    int flag = 0;
    int pos = 0;
    // int i = 0;

    if(arch)
    {

        while(flag == 0 && fread(&fav,sizeof(persistirPelis),1,arch)>0)
        {

            pos++;

            if(fav.idUsuario == user.id)
            {
                flag = 1;
            }
        }

        if(flag == 1)
        {
            fseek(arch,sizeof(persistirPelis) * (pos-1),0);

            fav.idUsuario = user.id;
            fav.peli= peli;

            fwrite(&fav,sizeof(persistirPelis),1,arch);
        }

        if(fav.idUsuario != user.id)
        {
            fav.idUsuario= user.id;
            fav.peli/*[0]*/= peli;
            //fav.validos=1;
            fwrite(&fav,sizeof(persistirPelis),1,arch);
        }
        fclose(arch);
    }
}

nodoListaUsers* pasarArchPelisAlista(nodoListaUsers* lista,stUsuario user,char archivoPersistir[])
{
    FILE* arch = fopen(archivoPersistir,"rb");
    persistirPelis fav;
    // int flag = 0;

    if(arch)
    {
        while(fread(&fav,sizeof(persistirPelis),1,arch) > 0)
        {
            if(user.id == fav.idUsuario)
            {

                //flag = 1;
                lista = agregarPeliAPlaylista(lista,user,fav.peli);


            }
        }
        fclose(arch);
    }
    return lista;
}

nodoListaPelis* agregarAlPpioPeli(nodoListaPelis* lista, nodoListaPelis* nuevoNodo)
{
    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->sig = lista;
        lista = nuevoNodo;
    }
    return lista;
}
