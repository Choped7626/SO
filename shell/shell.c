/*
Nombre: Daniel Puñal Diaz       Login:  daniel.punal.diaz@udc.es    Grupo:3.2
Nombre: Mario Lamas Angeriz     Login: m.lamasa@udc.es              Grupo:3.2
*/
#include "cabeceras.h"

int main(int argc , char *argv[] , char *env[]){

    bool F = false;
    bool *fin = &F;

    tList *histComm = create_list();
    tList *listOpen = create_list();
    tList *listmalloc = create_list();
    tList *listaProcss = create_list();

    char commando[MAX_TOTAL_COMMAND];
///
    insertOpenFiles(0 , "stdin" , listOpen , 02);
    insertOpenFiles(1 , "stdout" , listOpen , 02);
    insertOpenFiles(2 , "stderr" , listOpen , 02);
///

    while (!*fin){
        errno = 0;          //inicializo esto para q cando de error non de o mismo q o anterior(en cadena vacia)
        for (int i = 0; i < MAX_TOTAL_COMMAND; ++i) {
            commando[i] = '\0';
        }
        printf("#");
        fgets(commando , MAX_TOTAL_COMMAND , stdin);
        procesarEntrada(commando , fin , histComm , listOpen , listmalloc , listaProcss , argc , argv , env);
    }

    bloque *b;
    for (tPos p = first(*listmalloc); p != NULL ; p = next(p , *listmalloc)) {
        b = p->data;
        if(strcmp("malloc" , b->typeOfAlloc) == 0){
            free(b->address);
        }else if(strcmp("shared" , b->typeOfAlloc) == 0){
            shmdt(b->address);
        }else if(strcmp("mmap" , b->typeOfAlloc) == 0){
            close(p->dfORCommNUm);
            munmap(b->address , b->size);
        }
        }

    free_list(listmalloc);
    free_list(histComm);
    free_list(listOpen);
    free_list(listaProcss);
}