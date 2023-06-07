#ifndef FUNCIONESARCH_H_INCLUDED
#define FUNCIONESARCH_H_INCLUDED

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

void MostrarArchivoStUsuario(char[]);
nodoListaUsers* pasarArchEnListaUsers(char[],nodoListaUsers*);
stUsuario buscarEnArch(char[],char[]);
nodoListaUsers* recorrerArch(char[],nodoListaUsers*);
void bajaEnArchivo(stUsuario, char[]);
nodoListaUsers* pasarArchPersistirEnListaUsers(char archivoPersistir[],nodoListaUsers* listaUsers);
nodoListaUsers* cargarPelisCompletas(char archivo[],nodoListaUsers* listaUsers);
void guardarEnArchivoPeli(char archivoPersistir[],stPeliculas peli,stUsuario User,nodoListaUsers* lista);
nodoListaPelis* agregarAlPpioPeli(nodoListaPelis* lista, nodoListaPelis* nuevoNodo);
nodoListaUsers* agregarPeliAPlaylista(nodoListaUsers* lista,stUsuario user,stPeliculas pelicula);
nodoListaUsers* pasarArchPelisAlista(nodoListaUsers* lista,stUsuario user,char archivoPersistir[]);

#endif // FUNCIONESARCH_H_INCLUDED
