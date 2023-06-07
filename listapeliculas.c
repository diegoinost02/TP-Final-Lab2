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

nodoListaPelis* inicLista()
{
    return NULL;
}
nodoListaPelis* crearNodoPeli(stPeliculas dato)
{
    nodoListaPelis* aux= (nodoListaPelis*)malloc(sizeof(nodoListaPelis));

    aux->peli= dato;
    aux->sig= NULL;

    return aux;
}
nodoListaPelis* agregarAlPrincipio(nodoListaPelis *lista, nodoListaPelis *nuevo)
{
    if(lista == NULL)
    {
        lista= nuevo;
    } else{
        nuevo->sig= lista;
        lista= nuevo;
    }
    return lista;
}
void mostrarLista(nodoListaPelis *lista)
{
    nodoListaPelis * seguidora= lista;
    if(seguidora == NULL)
    {
        printf("La lista esta vacia \n");
    } else{
        while(seguidora != NULL)
        {
            mostrarPeliculaAUsuario(seguidora->peli);
            seguidora= seguidora->sig;
        }
    }
}
nodoListaPelis* buscarUltimoNodo(nodoListaPelis* lista)
{
    nodoListaPelis* ultimo= lista;
    while(ultimo->sig != NULL)
    {
        ultimo= ultimo->sig;
    }
    return ultimo;
}
nodoListaPelis* agregarAlFinal(nodoListaPelis* lista, nodoListaPelis* nuevoNodo)
{
    if(lista == NULL)
    {
        lista= nuevoNodo;
    } else{
        nodoListaPelis* ultimo= buscarUltimoNodo(lista);
        ultimo->sig= nuevoNodo;
    }
    return lista;
}

nodoListaPelis* borarNodo(nodoListaPelis* lista, int ID)
{
    if(lista != NULL)
    {
        if(ID == lista->peli.id)
        {
            nodoListaPelis* aBorrar= lista;
            lista= lista->sig;
            free(aBorrar);
        } else{
            nodoListaPelis* ante= lista;
            nodoListaPelis* seguidora= lista->sig;
            while(seguidora != NULL && ID != seguidora->peli.id)
            {
                ante= seguidora;
                seguidora= seguidora->sig;
            }
            if(seguidora != NULL)
            {
                ante->sig= seguidora->sig;
                free(seguidora);
            }
        }
    }
    return lista;
}
//mostrar pelis por orden alfabetico
nodoListaPelis* agregarEnOrdenPorNombre(nodoListaPelis* lista, nodoListaPelis* nodoAgregar)
{
    if(lista == NULL)
    {
        lista= nodoAgregar;
    } else {
        if(strcmpi(nodoAgregar->peli.nombre, lista->peli.nombre) < 0)
        {
            lista= agregarAlPrincipio(lista, nodoAgregar);
        } else{
            nodoListaPelis* ante= lista;
            nodoListaPelis* seguidora= lista->sig;
            while(seguidora != NULL && (strcmpi(nodoAgregar->peli.nombre, seguidora->peli.nombre) > 0 || strcmpi(nodoAgregar->peli.nombre, seguidora->peli.nombre) == 0))
            {
                ante= seguidora;
                seguidora= seguidora->sig;
            }
            nodoAgregar->sig= seguidora;
            ante->sig= nodoAgregar;
        }
    }
    return lista;
}
nodoListaPelis* pasarDeArbolAlistaPorNombre(nodoArbolPelis* arbol, nodoListaPelis* lista)
{
    if(arbol)
    {
        nodoListaPelis* nuevo= crearNodoPeli(arbol->peli);
        lista= agregarEnOrdenPorNombre(lista, nuevo);
        lista= pasarDeArbolAlistaPorNombre(arbol->izq, lista);
        lista= pasarDeArbolAlistaPorNombre(arbol->der, lista);
    }

    return lista;
}
// mostrar por año
nodoListaPelis* agregarEnOrdenPorAnio(nodoListaPelis* lista, nodoListaPelis* nodoAgregar)
{
    if(lista == NULL)
    {
        lista= nodoAgregar;
    } else {
        if(nodoAgregar->peli.anio > lista->peli.anio)
        {
            lista= agregarAlPrincipio(lista, nodoAgregar);
        } else{
            nodoListaPelis* ante= lista;
            nodoListaPelis* seguidora= lista->sig;
            while(seguidora != NULL && nodoAgregar->peli.anio <= seguidora->peli.anio)
            {
                ante= seguidora;
                seguidora= seguidora->sig;
            }
            nodoAgregar->sig= seguidora;
            ante->sig= nodoAgregar;
        }
    }
    return lista;
}
nodoListaPelis* pasarDeArbolAlistaPorAnio(nodoArbolPelis* arbol, nodoListaPelis* lista)
{
    if(arbol)
    {
        nodoListaPelis* nuevo= crearNodoPeli(arbol->peli);
        lista= agregarEnOrdenPorAnio(lista, nuevo);
        lista= pasarDeArbolAlistaPorAnio(arbol->izq, lista);
        lista= pasarDeArbolAlistaPorAnio(arbol->der, lista);
    }

    return lista;
}
//mostrar por genero
nodoListaPelis* pasarDeArbolAlista(nodoArbolPelis* arbol, nodoListaPelis* lista, char genero[])
{
    if(arbol)
    {
        if(strcmpi(genero, arbol->peli.genero) == 0)
        {
            nodoListaPelis* nuevo= crearNodoPeli(arbol->peli);
            lista= agregarAlPrincipio(lista, nuevo);
            lista= pasarDeArbolAlista(arbol->izq, lista, genero);
            lista= pasarDeArbolAlista(arbol->der, lista, genero);
        } else{
            lista= pasarDeArbolAlista(arbol->izq, lista, genero);
            lista= pasarDeArbolAlista(arbol->der, lista, genero);
        }
    }

    return lista;
}

void mostrarPeliRecomendadas(char arch[], nodoArbolPelis* arbol, int idUser)
{
    //int i= 0;
    int cComedia= 0;
    int cSuspenso= 0;
    int cTerror= 0;
    int cRoman= 0;
    int cDrama= 0;
    int cAccion= 0;
    int drama, accion, susp, terror, romant, com;

    stPlaylist aux;
    FILE* archi= fopen(arch, "rb");
    if(archi)
    {
        while(fread(&aux, sizeof(stPlaylist), 1, archi) > 0)
        {
            nodoArbolPelis* peli= buscarPeliPorID(arbol, aux.idPelicula);
            if(aux.idUsuario == idUser)
            {

                if(strcmpi(peli->peli.genero, "drama") == 0)
                {
                    cDrama++;
                } else
                if(strcmpi(peli->peli.genero, "terror") == 0)
                {
                    cTerror++;
                } else
                if(strcmpi(peli->peli.genero, "accion") == 0)
                {
                    cAccion++;
                } else
                if(strcmpi(peli->peli.genero, "comedia") == 0)
                {
                    cComedia++;
                } else
                if(strcmpi(peli->peli.genero, "suspenso") == 0)
                {
                    cSuspenso++;
                } else
                if(strcmpi(peli->peli.genero, "romantica") == 0)
                {
                    cRoman++;
                }
            }
        }
        fclose(archi);
    }else{
        printf("No se pudo abrir el archivo \n");
    }
    drama= comparar(cDrama, cSuspenso, cComedia, cTerror, cRoman, cAccion);
    susp= comparar(cSuspenso, cDrama, cComedia, cTerror, cRoman, cAccion);
    accion= comparar(cAccion, cSuspenso, cComedia, cTerror, cRoman, cDrama);
    com= comparar(cComedia, cSuspenso, cDrama, cTerror, cRoman, cAccion);
    terror= comparar(cTerror, cSuspenso, cComedia, cDrama, cRoman, cAccion);
    romant= comparar(cRoman, cSuspenso, cComedia, cDrama, cTerror, cAccion);

    nodoListaPelis* listaRecomend= inicLista();
    if(drama == 1)
    {
        listaRecomend= pasarDeArbolAlista(arbol, listaRecomend, "drama");
        mostrarLista(listaRecomend);
    }else
    if(susp == 1)
    {
        listaRecomend= pasarDeArbolAlista(arbol, listaRecomend, "suspenso");
        mostrarLista(listaRecomend);
    }else
    if(accion == 1)
    {
        listaRecomend= pasarDeArbolAlista(arbol, listaRecomend, "accion");
        mostrarLista(listaRecomend);
    }else
    if(romant == 1)
    {
        listaRecomend= pasarDeArbolAlista(arbol, listaRecomend, "romantica");
        mostrarLista(listaRecomend);
    }else
    if(terror == 1)
    {
        listaRecomend= pasarDeArbolAlista(arbol, listaRecomend, "terror");
        mostrarLista(listaRecomend);
    }else
    if(com == 1)
    {
        listaRecomend= pasarDeArbolAlista(arbol, listaRecomend, "comedia");
        mostrarLista(listaRecomend);
    }

}
int comparar(int dato, int dato2, int dato3, int dato4, int dato5, int dato6)
{
    if(dato > dato2 && dato > dato3 && dato > dato4 && dato > dato5 && dato > dato6)
    {
        return 1;
    }
    return 0;
}


