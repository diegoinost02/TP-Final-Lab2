#ifndef PELIS_H_INCLUDED
#define PELIS_H_INCLUDED


/*typedef struct{
    int id;
    char nombre[50];
    int anio;
    char genero[30];
    char actores[3][50];
    int calificacion;
    int estado;
}stPeliculas;*/

/*typedef struct{
    int idUsuario;
    int idPelicula;
    int estadoPelicula;
}stPlaylist;*/

void cargarArchivo(char arch[]);
void cargarMatrizActores(char M[][50], int dimF);
void mostrarMatrizActores(char M[4][50]);
void mostrarPeliculaAUsuario(stPeliculas aux);
void mostrarArchiPeliculasAdmin(char archivo[]);
void modificarArchivoPorId(char archivo[], int dato);
void altaPeliPlaylist(char arch[], int idPeli, int idUser);
void bajaPeli(char arch[], int idPeli, int idUser);
int existePeli(char arch[], int idPeli, int idUser);
void mostrarPeliculaAadmin(stPeliculas aux);


#endif // PELIS_H_INCLUDED
