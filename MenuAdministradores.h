#ifndef MENUADMINISTRADORES_H_INCLUDED
#define MENUADMINISTRADORES_H_INCLUDED

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

nodoListaUsers* menuDeAdministradores(nodoListaUsers*,nodoListaUsers*,char[],char[]);
nodoListaUsers* altaUsuarioAdmin(nodoListaUsers*,char[]);
void mostrarUsuario(stUsuario);
stUsuario altaUsuario(char[],stUsuario);
void listados(char archivoUsers[]);
void mostrarBajasEnArchivo(char archivoUsers[]);
nodoListaUsers* bajaUsuarioAdmin(nodoListaUsers* listaUsers, char archivoUsers[]);
nodoListaUsers* modificarPerfilAdmin(nodoListaUsers* listaUsers, char archivoUsers[]);
void consulta(nodoListaUsers* listaUsers,char archivoUsers[]);

#endif // MENUADMINISTRADORES_H_INCLUDED
