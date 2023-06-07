#ifndef ARBOLPELI_H_INCLUDED
#define ARBOLPELI_H_INCLUDED
#include "pelis.h"


/*typedef struct
{
    stPeliculas peli;
    struct nodoArbolPelis * izq;
    struct nodoArbolPelis * der;
} nodoArbolPelis;*/

nodoArbolPelis* inicArbol();
nodoArbolPelis* crearNodo(stPeliculas dato);
nodoArbolPelis* insertarNodoPorID(nodoArbolPelis* arbol, stPeliculas dato);
void preOrder(nodoArbolPelis* arbol);
void inOrder(nodoArbolPelis* arbol);
void postOrder(nodoArbolPelis* arbol);
nodoArbolPelis* nodoMasDerecha(nodoArbolPelis* arbol);
nodoArbolPelis* nodoMasIzquierda(nodoArbolPelis* arbol);
nodoArbolPelis* borrarNodoPorId(nodoArbolPelis* arbol, int ID);
nodoArbolPelis* buscarPeliPorID(nodoArbolPelis* arbol, int ID);
nodoArbolPelis* buscarPeliPorNombre(nodoArbolPelis* arbol, char nombre[]);
nodoArbolPelis* cargarArbolDesdeArchivo(char arch[], nodoArbolPelis* arbol);
int contarPorGenero(nodoArbolPelis* arbol, char genero[]);



#endif // ARBOLPELI_H_INCLUDED
