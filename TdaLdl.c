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
#include "FuncionesArch.h"
#include "MenuUsuario.h"
#include "MenuAdministradores.h"
#include "MenuPrincipal.h"
#include "TdaLdl.h"

nodoListaUsers* cargarListaDeListas(nodoListaUsers* lista,char archivo[])
{
    stUsuario user;

    FILE* arch = fopen(archivo,"rb");

    if(arch)
    {
        while(fread(&user,sizeof(stUsuario),1,arch) > 0)
        {
            lista = pasarArchEnLdl(lista,user);
        }
        fclose(arch);
    }
    return lista;
}

nodoListaUsers* buscar(nodoListaUsers* lista,int id)
{
    nodoListaUsers* rta = NULL;

    while(lista != NULL)
    {
        if(lista->user.id == id)
        {
            rta = lista;
        }
        lista = lista->sig;
    }
    return rta;
}

nodoListaUsers* pasarArchEnLdl(nodoListaUsers* lista,stUsuario user)
{
    //nodoNota* nota = crearNodoNota(a);
    nodoListaUsers* pos = buscar(lista,user.id);

    if(pos == NULL)
    {
        nodoListaUsers* usuario = crearNodoUsuario(user);
        lista = agregarAlPpio(lista,usuario);
        pos = lista;
    }
  //  pos->playlist = agregarAlFinal(pos->playlist,nota);

    return lista;
}

void recorrerListaDeUsers(nodoListaUsers* lista)
{
    while(lista != NULL)
    {
        mostrarUsuario(lista->user);
        recorrerListaDePelis(lista->playlist);
        lista = lista->sig;
    }
}

void recorrerListaDePelis(nodoListaPelis* lista)
{
    while(lista != NULL)
    {
        mostrarPeliculaAUsuario(lista->peli);
        lista = lista->sig;
    }
}
