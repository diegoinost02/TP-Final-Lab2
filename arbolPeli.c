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
#include "pelis.h"
#include "arbolPeli.h"
#include "listapeliculas.h"
#include "usuarios.h"

nodoArbolPelis* inicArbol()
{
    return NULL;
}
nodoArbolPelis* crearNodo(stPeliculas dato)
{
    nodoArbolPelis* aux= (nodoArbolPelis*)malloc(sizeof(nodoArbolPelis));
    aux->peli= dato;
    aux->izq= NULL;
    aux->der= NULL;

    return aux;
}
nodoArbolPelis* insertarNodoPorID(nodoArbolPelis* arbol, stPeliculas dato)
{
    if(arbol==NULL)
    {
        arbol= crearNodo(dato);
    }
    else
    {
        if(dato.id > arbol->peli.id)
        {
            arbol->der= insertarNodoPorID(arbol->der, dato);
        }
        else
        {
            arbol->izq= insertarNodoPorID(arbol->izq, dato);
        }
    }
    return arbol;
}
void preOrder(nodoArbolPelis* arbol)
{
    if(arbol != NULL)
    {
        mostrarPeliculaAUsuario(arbol->peli);
        preOrder(arbol->izq);
        preOrder(arbol->der);
    }
}
void inOrder(nodoArbolPelis* arbol)
{
    if(arbol != NULL)
    {
        inOrder(arbol->izq);
        mostrarPeliculaAUsuario(arbol->peli);
        inOrder(arbol->der);
    }
}
void postOrder(nodoArbolPelis* arbol)
{
    if(arbol != NULL)
    {
        postOrder(arbol->izq);
        postOrder(arbol->der);
        mostrarPeliculaAUsuario(arbol->peli);
    }
}
nodoArbolPelis* nodoMasDerecha(nodoArbolPelis* arbol)
{
    if(arbol)
    {
        if(arbol->der != NULL)
        {
            arbol = nodoMasDerecha(arbol->der);
        }
    }
    return arbol;
}
nodoArbolPelis* nodoMasIzquierda(nodoArbolPelis* arbol)
{
    if(arbol)
    {
        if(arbol->izq != NULL)
        {
            arbol = nodoMasIzquierda(arbol->izq);
        }
    }
    return arbol;
}
nodoArbolPelis* borrarNodoPorId(nodoArbolPelis* arbol, int ID)
{
    if(arbol!=NULL)
    {
        if(ID > arbol->peli.id)
        {
            arbol->der = borrarNodoPorId(arbol->der, ID);
        }
        else if (ID < arbol->peli.id)
        {
            arbol->izq = borrarNodoPorId(arbol->izq, ID);
        }
        else if (ID == arbol->peli.id)
        {
            if(arbol->izq != NULL)
            {
                nodoArbolPelis* masDer = nodoMasDerecha(arbol->izq);
                arbol->peli = masDer->peli;
                arbol->izq = borrarNodoPorId(arbol->izq, arbol->peli.id);
            }
            else if(arbol->der != NULL)
            {
                nodoArbolPelis* masIzq = nodoMasIzquierda(arbol->der);
                arbol->peli = masIzq->peli;
                arbol->der = borrarNodoPorId(arbol->der, arbol->peli.id);
            }
            else
            {
                free(arbol);
                arbol = NULL;
            }
        }
    }
    return arbol;
}
nodoArbolPelis* buscarPeliPorID(nodoArbolPelis* arbol, int ID)
{
    nodoArbolPelis* rta=NULL;
    if(arbol!=NULL)
    {
        if(ID == arbol->peli.id)
        {
            rta = arbol;
        }
        else
        {
            if(ID > arbol->peli.id)
            {
                rta = buscarPeliPorID(arbol->der, ID);
            }
            else
            {
                rta = buscarPeliPorID(arbol->izq, ID);
            }
        }
    }
    return rta;
}
nodoArbolPelis* buscarPeliPorNombre(nodoArbolPelis* arbol, char nombre[])
{
    nodoArbolPelis* rta=NULL;
    if(arbol)
    {
        if(strcmpi(nombre, arbol->peli.nombre) == 0)
        {
            rta= arbol;
        }
        else
        {
            rta= buscarPeliPorNombre(arbol->izq, nombre);
            if(rta == NULL)
            {
                rta= buscarPeliPorNombre(arbol->der, nombre);
            }
        }
    }
    return rta;
}
nodoArbolPelis* cargarArbolDesdeArchivo(char arch[], nodoArbolPelis* arbol)
{
    stPeliculas aux;
    FILE* archi= fopen(arch, "rb");
    if(archi)
    {
        int cant, mitad;
        fseek(archi, 0, SEEK_END);
        cant= ftell(archi)/sizeof(stPeliculas);
        mitad= cant / 2 ;
        fseek(archi, sizeof(stPeliculas)*(-mitad - 1), SEEK_CUR);
        fread(&aux, sizeof(stPeliculas), 1, archi);
        arbol= insertarNodoPorID(arbol, aux);
        while(fread(&aux, sizeof(stPeliculas), 1, archi) > 0)
        {
            arbol= insertarNodoPorID(arbol, aux);
        }
        fseek(archi, 0, SEEK_SET);
        for(int i= 0; i < mitad - 1; i++)
        {
            fread(&aux, sizeof(stPeliculas), 1, archi);
            arbol= insertarNodoPorID(arbol, aux);
        }
        fclose(archi);
    }
    else
    {
        printf("No se pudo abrir el archivo \n");
    }
    return arbol;
}
//funciones para las recomendadas
int contarPorGenero(nodoArbolPelis* arbol, char genero[])
{
    int rta= 0;
    if(arbol)
    {
        if(strcmpi(arbol->peli.genero, genero) == 0)
        {
            rta= 1 + contarPorGenero(arbol->der, genero) + contarPorGenero(arbol->izq, genero);
        }
        else
        {
            rta= contarPorGenero(arbol->der, genero) + contarPorGenero(arbol->izq, genero);
        }
    }
    return rta;
}






