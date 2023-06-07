#ifndef MENUUSUARIO_H_INCLUDED
#define MENUUSUARIO_H_INCLUDED

/*typedef struct
{
    int id;
    char nombre [50];
    int anio;
    char genero [30];
    char actores [3][50];
    int calificacion;
    int estado;

} stPelicula;

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

typedef struct
{
    stPelicula peli;
    struct nodoListaPelis * sig;
} nodoListaPelis;

typedef struct nodoListaUsers
{
    stUsuario user;
    nodoListaPelis * playlist;
    struct nodoListaUsers* sig;
} nodoListaUsers;*/

nodoListaUsers* menuDeUsuario(nodoListaUsers**,nodoListaUsers*,char[]);
nodoListaUsers* bajaDeUsuario(nodoListaUsers*,stUsuario,char[]);
void verPerfil(stUsuario);
void modificarPerfil(char[],nodoListaUsers**);
nodoListaUsers* cargarStUsuario(nodoListaUsers*,char[]);
nodoListaUsers* mostrarPeliculas(nodoListaUsers*,stUsuario);

#endif // MENUUSUARIO_H_INCLUDED
