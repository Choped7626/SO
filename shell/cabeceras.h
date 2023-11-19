#ifndef SO_P0_CABECERAS_H
#define SO_P0_CABECERAS_H
#include "lista.h"

void authors(char opciones[]);
void pid (char opciones[]);
void chdirSO (char opciones[]);
void date ();
void timeSO ();
void hist (char opciones[] , tList* histCom , int* commNum);
void command (char *tr[] , tList *histComm , int* commNum , bool* fin , int* recursividad , tList *listOpen , tList *listmalloc);
void openSO (char *tr[], tList *listOpen);
void closeSO (char *tr[], tList *listOpen);
void dupSO (char *tr[] , tList *listOpen);
void listOpenFiles (tList *listOpen);
void infosys ();
void help (char opciones[]);
void meterDatos(const int* num , char *tr[], tList *hist);
void closeShell (bool *fin);
void whichCommand(char *tr[], tList *histComm , int* commNum , bool* fin , int* recursividad , tList *listOpen , tList *listmalloc);
void procesarEntrada(char c[] , bool *fin , tList *histComm , tList *listOpen , tList *listmalloc);
int TrozearCadena(char* cadena , char* tr[]);
void insertOpenFiles(int df , const char *nombre , tList *listOpen , int mode);
void deleteOpenFiles(int df, tList *listOpen);
char* ConvierteModo(mode_t modo);
char LetraTF(mode_t modo);
void create(char* tr[]);
void statSO(char *tr[]);
void list(char* tr[]);
void delete(char* tr[]);
void deltree(char* tr[]);
void mallocSO(char* tr[] , tList *listmalloc);
void shared(char* tr[] , tList *listBlocks);
#endif //SO_P0_CABECERAS_H
