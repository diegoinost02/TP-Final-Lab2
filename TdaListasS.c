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
#include "FuncionesArch.h"
#include "MenuUsuario.h"
#include "MenuAdministradores.h"
#include "MenuPrincipal.h"
#include "TdaListasS.h"

nodoListaUsers* inicListaS()
{
    return NULL;
}

nodoListaUsers* buscarEnLista(nodoListaUsers* lista, stUsuario user)
{
    nodoListaUsers* seg;
    seg = lista;

    while(seg !=NULL && strcmpi(seg->user.mail,user.mail) != 0)
    {
        seg = seg->sig;

    }

    return seg;
}

nodoListaUsers* crearNodoUsuario(stUsuario u)
{
    nodoListaUsers* aux = (nodoListaUsers*) malloc(sizeof(nodoListaUsers));

    strcpy(aux->user.mail,u.mail);
    strcpy(aux->user.apellidoYnombres,u.apellidoYnombres);
    aux->user.celular = u.celular;
    strcpy(aux->user.contrasenia,u.contrasenia);
    aux->user.estado = u.estado;
    aux->user.id = u.id;
    aux->user.tipoDeUsuario = u.tipoDeUsuario;
    aux->sig = NULL;

    return aux;
}
nodoListaUsers* agregarAlPpio(nodoListaUsers* lista,nodoListaUsers* nuevoNodo)
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

nodoListaUsers* borrarNodo(nodoListaUsers* listaUsers,int id)
{
    nodoListaUsers* seg;
    nodoListaUsers* ante;

    if(listaUsers!=NULL && listaUsers->user.id == id)
    {
        nodoListaUsers* aux = listaUsers;
        listaUsers = listaUsers->sig;
        free(aux);
    }
    else
    {
        seg = listaUsers;
        while(seg!=NULL && listaUsers->user.id != id)
        {
            ante = seg;
            seg = seg->sig;
        }
        if(seg != NULL)
        {
            ante->sig = seg->sig;
            free(seg);
        }
    }

    return listaUsers;
}

nodoListaUsers* agregarEnOrden(nodoListaUsers* lista,nodoListaUsers* nuevoNodo)
{

    if(lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        if(lista != NULL && strcmpi(lista->user.apellidoYnombres,nuevoNodo->user.apellidoYnombres) < 0)
        {
            lista = agregarAlPpio(lista,nuevoNodo);
        }
        else
        {
            nodoListaUsers* ante;
            nodoListaUsers* seguidora = lista;

            while(seguidora != NULL && strcmpi(seguidora->user.apellidoYnombres,nuevoNodo->user.apellidoYnombres) > 0)
            {
                ante = seguidora;
                seguidora = seguidora->sig;
            }
            if(seguidora != NULL)
            {
                nuevoNodo->sig = seguidora;
                ante->sig = nuevoNodo;
            }
            else
            {
                nuevoNodo->sig = seguidora;
                ante->sig = nuevoNodo;
            }
        }
    }
    return lista;
}

nodoListaUsers* agregarUsuarioALista(nodoListaUsers* listaUsers, stUsuario usuario)
{
    nodoListaUsers* nuevoNodo = crearNodoUsuario(usuario);
    listaUsers = agregarAlPpio(listaUsers,nuevoNodo);

    return listaUsers;
}

void recorrerYMostrar(nodoListaUsers* lista)
{
    nodoListaUsers* nodoAux = lista;

    while(nodoAux!=NULL)
    {
        mostrar(nodoAux);
        nodoAux=nodoAux->sig;
    }
}

void mostrar(nodoListaUsers* nodoAux)
{
    printf("----------usuario----------\n");
    mostrarUsuario(nodoAux->user);
}
