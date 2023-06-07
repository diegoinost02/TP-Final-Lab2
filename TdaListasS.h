#ifndef TDALISTASS_H_INCLUDED
#define TDALISTASS_H_INCLUDED

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

nodoListaUsers* agregarAlPpio(nodoListaUsers*,nodoListaUsers*);
nodoListaUsers* borrarNodo(nodoListaUsers*,int);
nodoListaUsers* crearNodoUsuario(stUsuario );
nodoListaUsers* inicListaS();
nodoListaUsers* agregarEnOrden(nodoListaUsers*,nodoListaUsers*);
nodoListaUsers* buscarEnLista(nodoListaUsers*, stUsuario);
nodoListaUsers* agregarUsuarioALista(nodoListaUsers*, stUsuario);
void recorrerYMostrar(nodoListaUsers* lista);
void mostrar(nodoListaUsers* nodoAux);

#endif // TDALISTASS_H_INCLUDED
