#ifndef TDALDL_H_INCLUDED
#define TDALDL_H_INCLUDED

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

typedef struct
{
    stUsuario user;
    nodoListaPelis * playlist;
    struct nodoListaUsers* sig;
} nodoListaUsers;*/

nodoListaUsers* cargarListaDeListas(nodoListaUsers*,char[]);
nodoListaUsers* buscar(nodoListaUsers*,int);
nodoListaUsers* pasarArchEnLdl(nodoListaUsers*,stUsuario);
void recorrerListaDeUsers(nodoListaUsers* lista);
void recorrerListaDePelis(nodoListaPelis* lista);

#endif // TDALDL_H_INCLUDED
