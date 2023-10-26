/*
Nombre: Daniel Puñal Diaz       Login:  daniel.punal.diaz@udc.es    Grupo:3.2
Nombre: Mario Lamas Angeriz     Login: m.lamasa@udc.es              Grupo:3.2
*/
#include "cabeceras.h"

int main(){

    bool F = false;
    bool *fin = &F;

    tList *histComm = create_list();
    tList *listOpen = create_list();


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
        procesarEntrada(commando , fin , histComm , listOpen);
    }
    free_list(histComm);
    free_list(listOpen);
}