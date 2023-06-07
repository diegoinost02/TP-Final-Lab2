#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <windows.h>
#define RESET_COLOR    "\x1b[0m"
#define CYAN_F     "\x1b[46m"
#define NEGRO_T        "\x1b[30m"
#define ROJO_F     "\x1b[41m"
#include "animaciones.h"

void animacionCargando()
{
    printf("\n\n\n                                                 cargando");
    Sleep(300);
    system("cls");
    printf("\n\n\n                                                 cargando.");
    Sleep(300);
    system("cls");
    printf("\n\n\n                                                 cargando..");
    Sleep(300);
    system("cls");
    printf("\n\n\n                                                 cargando...");
    Sleep(300);
    system("cls");
}

/*void logoCyan()
{
    printf("\n                                                  "CYAN_F NEGRO_T"LABTWO PRIME\n\n"RESET_COLOR);
}
void logoRojo()
{
    printf("\n                                                  "ROJO_F"LABTWO PRIME\n\n"RESET_COLOR);
}*/
