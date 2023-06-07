#ifndef LISTAPELICULAS_H_INCLUDED
#define LISTAPELICULAS_H_INCLUDED
#include "pelis.h"
#include "arbolPeli.h"

/*typedef struct
{
 stPeliculas peli;
 struct nodoListaPelis * sig;
} nodoListaPelis;*/

nodoListaPelis* inicLista();
nodoListaPelis* crearNodoPeli(stPeliculas dato);
nodoListaPelis* agregarAlPrincipio(nodoListaPelis *lista, nodoListaPelis *nuevo);
void mostrarLista(nodoListaPelis *lista);
nodoListaPelis* buscarUltimoNodo(nodoListaPelis* lista);
nodoListaPelis* agregarAlFinal(nodoListaPelis* lista, nodoListaPelis* nuevoNodo);
nodoListaPelis* pasarDeArbolAlistaPorNombre(nodoArbolPelis* arbol, nodoListaPelis* lista);
nodoListaPelis* agregarEnOrdenPorAnio(nodoListaPelis* lista, nodoListaPelis* nodoAgregar);
nodoListaPelis* pasarDeArbolAlistaPorAnio(nodoArbolPelis* arbol, nodoListaPelis* lista);
nodoListaPelis* pasarDeArbolAlista(nodoArbolPelis* arbol, nodoListaPelis* lista, char genero[]);
void mostrarPeliRecomendadas(char arch[], nodoArbolPelis* arbol, int idUser);
int comparar(int dato, int dato2, int dato3, int dato4, int dato5, int dato6);


#endif // LISTAPELICULAS_H_INCLUDED
