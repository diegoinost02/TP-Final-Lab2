#ifndef USUARIOS_H_INCLUDED
#define USUARIOS_H_INCLUDED

/*typedef struct{
    int id;
    char apellidoYnombre[30];
    char mail[50];
    int celular;
    char contrasenia[8];
    int estado;

}stUsuarios;

typedef struct{
    stPeliculas dato;
    struct nodoPlaylist* sig;
}nodoPlaylist;

typedef struct{
    stUsuarios dato;
    struct nodoListaUsers* siguiente;
    nodoPlaylist* playlist;
}nodoListaUsers;*/




void cargarArchivoUsuarios(char arch[]);
nodoListaUsers* inicListaUsers();
nodoListaUsers* crearNodoUser(stUsuario dato);
nodoListaUsers* agregarAlPpioUsers(nodoListaUsers* lista, nodoListaUsers* nuevoNodo);
void mostrarUsuarioEnLDL(stUsuario dato);
nodoPlaylist* inicListaPlaylist();
nodoPlaylist* crearNodoPlaylist(stPeliculas dato);
nodoPlaylist* buscarUltimito(nodoPlaylist* lista);
nodoPlaylist* agregarAlFinalPlaylist(nodoPlaylist* lista, nodoPlaylist* nuevoNodo);
void mostrarLDL(nodoListaUsers* LDL);
nodoListaUsers* altaSoloUsuariosEnLDL(nodoListaUsers* lista, stUsuario dato);
nodoListaUsers* buscarUser(nodoListaUsers* lista, int id);
nodoListaUsers* pasarDeArchsALDL(char arch1[], char arch2[], nodoListaUsers* LDL, nodoArbolPelis* arbol);
void mostrarArchiUsuarios(char arch[]);
void mostrarUser(stUsuario dato);
nodoListaUsers* hacerElalta(nodoListaUsers* LDL, stUsuario dato, stPlaylist datin, nodoArbolPelis* arbol);
void mostrarLDL(nodoListaUsers* LDL);

#endif // USUARIOS_H_INCLUDED
