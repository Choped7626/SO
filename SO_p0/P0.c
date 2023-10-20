/*
Nombre: Daniel Puñal Diaz       Login:  daniel.punal.diaz@udc.es    Grupo:3.2
Nombre: Mario Lamas Angeriz     Login: m.lamasa@udc.es              Grupo:3.2
*/
#include "cabeceras.h"

int main(){

    bool F = false;
    bool *fin = &F;

    tList histComm;
    tList listOpen;

    createEmptyList(&histComm);
    createEmptyList(&listOpen);

    char commando[MAX_TOTAL_COMMAND];

    insertOpenFiles(0 , "stdin" , &listOpen , 02);
    insertOpenFiles(1 , "stdout" , &listOpen , 02);
    insertOpenFiles(2 , "stderr" , &listOpen , 02);

    while (!*fin){
        printf("#");
        fgets(commando , MAX_TOTAL_COMMAND , stdin);
        procesarEntrada(commando , fin , &histComm , &listOpen);
    }

}
