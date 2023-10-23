#ifndef SO_P0_CABECERAS_H
#define SO_P0_CABECERAS_H
#include "lista.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#define MAX_TOTAL_COMMAND 100

void authors(char opciones[]);
void pid (char opciones[]);
void chdirSO (char opciones[]);
void date ();
void timeSO ();
void hist (char opciones[] , tList* histCom , int* commNum);
void command (char *tr[] , tList *histComm , int* commNum , bool* fin , int* recursividad , tList *listOpen);
void openSO (char *tr[], tList *listOpen);
void closeSO (char *tr[], tList *listOpen);
void dupSO (char *tr[] , tList *listOpen);
void listOpenFiles (tList *listOpen);
void infosys ();
void help (char opciones[]);
void meterDatos(const int* num , char *tr[], tList *hist);
void closeShell (bool *fin);
void whichCommand(char *tr[], tList *histComm , int* commNum , bool* fin , int* recursividad , tList *listOpen);
void procesarEntrada(char c[] , bool *fin , tList *histComm , tList *listOpen);
int TrozearCadena(char* cadena , char* tr[]);
void insertOpenFiles(int df , const char *nombre , tList *listOpen , int mode);
void deleteOpenFiles(int df, tList *listOpen);
char* ConvierteModo(mode_t modo);
char LetraTF(mode_t modo);
void create(char* tr[]);
void statSO(char *tr[]);
void list();
void delete(char* tr[]);
void deltree(char* tr[]);
#endif //SO_P0_CABECERAS_H
