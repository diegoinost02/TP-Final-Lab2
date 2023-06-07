#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <windows.h>
#define RESET_COLOR    "\x1b[0m"
#define CYAN_F     "\x1b[46m"
#define NEGRO_T        "\x1b[30m"
#define ROJO_F     "\x1b[41m"
#include "structs.h"
#include "pelis.h"
#include "arbolPeli.h"
#include "listapeliculas.h"
#include "animaciones.h"
#include "TdaLdl.h"
#include "TdaListasS.h"
#include "FuncionesArch.h"
#include "MenuUsuario.h"
#include "MenuAdministradores.h"
#include "MenuPrincipal.h"

void menuPrincipal(char archivoUsers[],nodoListaUsers* listaUsers,char archivo[])
{
    stUsuario usuario;

    int control=1;
    nodoListaUsers* encontrado = NULL;
    int flagCerrar=1;
    int opcion;
    int volver;

    char reactivar = 'n';

    while(flagCerrar==1)
    {
        encontrado = NULL;

        if(control==1)
        {
            system("cls");
            printf("\n                                                  "CYAN_F NEGRO_T"LABTWO PRIME\n\n"RESET_COLOR);
            printf("                                               1. INICIAR SESION");
            printf("\n\n\n");
            printf("                                               2. CREAR CUENTA");
            printf("\n\n\n");
            printf("                                               3. SALIR");
            printf("\n\n\n                                                    ");
            scanf("%i",&opcion);
        }
        else if(control==2)
        {
            opcion=1;
        }
        else if(control==3)
        {
            opcion=2;
        }

        switch(opcion)
        {
        case 1:

            while(control==1 || control==2)
            {
                system("cls");
                printf("\nIngrese su mail: \n");
                fflush(stdin);
                gets(usuario.mail);

                encontrado = buscarEnLista(listaUsers,usuario);

                if(encontrado == NULL)
                {
                    usuario = buscarEnArch(archivoUsers,usuario.mail);

                    if(usuario.estado == 1 || usuario.estado == 0)
                    {
                    encontrado = agregarUsuarioALista(encontrado,usuario);
                    }


                    if(encontrado != NULL && encontrado->user.estado  == 0)
                    {
                        printf("su cuenta esta dada de baja\ndesea reactivarla? s/n\n");
                        fflush(stdin);
                        scanf("%c",&reactivar);

                        if(reactivar == 's' || reactivar == 'S')
                        {
                            usuario = altaUsuario(archivoUsers,usuario);
                            encontrado->user.estado = usuario.estado;
                            listaUsers = agregarUsuarioALista(listaUsers,usuario);
                        }
                        else
                        {
                            animacionCargando();
                        }
                    }
                    else
                    {
                        animacionCargando();
                    }

                }
                if(encontrado == NULL)//if(encontrado == NULL)
                {
                    system("cls");
                    printf("La cuenta no existe\n1 para volver al menu principal\n2 para volver a ingresar\n3 para crear una cuenta nueva\n");
                    scanf("%i",&control);
                }


                if(encontrado != NULL)
                {
                    for(int i=0; i<3; i++)
                    {
                        printf("\nIngrese su contrase%ca\n%i intento de 3\n",164,i+1);
                        fflush(stdin);
                        gets(usuario.contrasenia);

                        if(strcmpi(encontrado->user.contrasenia,usuario.contrasenia) == 0)
                        {
                            if(encontrado->user.tipoDeUsuario==1)
                            {
                                system("cls");
                                printf("\nbienvendio a amazon prime...\n");
                                Sleep(1000);
                                animacionCargando();
                                listaUsers = menuDeUsuario(&encontrado,listaUsers,archivoUsers);
                            }
                            else if(encontrado->user.tipoDeUsuario==2)
                            {
                                system("cls");
                                printf("\nbienvenido al menu de administrador...\n");
                                Sleep(1000);
                                listaUsers = menuDeAdministradores(encontrado,listaUsers,archivoUsers,archivo);
                            }
                            i = 3;
                        }
                        else
                        {
                            if(i != 2)
                            {
                                system("cls");
                                printf("Constrase%ca incorrecta, ingrese 1 para ingresar la constrase%ca nuevamente, 2 para volver\n",164,164);
                                scanf("%i",&volver);
                            }
                            else if(i == 2)
                            {
                                system("cls");
                                printf("ya superaste el limites de intentos, seras redireccionado al menu principal...\n");
                                animacionCargando();
                            }
                            if(volver==1)
                            {
                                system("cls");
                            }

                            else if(volver==2)break;
                            {
                                control=1;
                            }
                        }

                    }
                }
                if(control==1 || control==2)break;
            }

            continue;

        case 2:
            system("cls");
            printf("crea tu cuenta de amazon\n");
            listaUsers = cargarStUsuario(listaUsers,archivoUsers);
            control = 1;
            break;

        case 3:
            system("cls");
            printf("\n  "ROJO_F"LABTWO PRIME\n\n"RESET_COLOR);
            flagCerrar=0;
            break;
        }
    }
}
