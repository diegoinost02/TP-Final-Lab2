#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct
{
    int id;
    char nombre [50];
    int anio;
    char genero [30];
    char actores [3][50];
    int calificacion;
    int estado;

} stPeliculas;

typedef struct
{
    int idUsuario;
    int idPelicula;
    int estadoPelicula;
} stPlaylist;

typedef struct
{
    int id;
    char apellidoYnombres [50];
    char mail [50];
    int celular;
    char contrasenia[15];
    int estado;
    int tipoDeUsuario; ///1 usuario, 2 administrador

} stUsuario;

typedef struct nodoListaPelis
{
    stPeliculas peli;
    struct nodoListaPelis * sig;
} nodoListaPelis;

typedef struct nodoListaUsers
{
    stUsuario user;
    nodoListaPelis * playlist;
    struct nodoListaUsers* sig;
} nodoListaUsers;

typedef struct nodoArbolPelis
{
    stPeliculas peli;
    struct nodoArbolPelis * izq;
    struct nodoArbolPelis * der;
} nodoArbolPelis;

typedef struct nodoPlaylist
{
    stPeliculas dato;
    struct nodoPlaylist* sig;
} nodoPlaylist;

typedef struct
{
    int idUsuario;
    //int validos;
    stPeliculas peli;
} persistirPelis;

#endif // STRUCTS_H_INCLUDED
