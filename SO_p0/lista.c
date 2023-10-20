
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

void createEmptyList(tList* L){
    *L = PNULL;
}

void deleteList(tList* L) {
    if (!isEmptyList(*L)) {
        tPos j;
        for (tPos i = last(*L); i != PNULL; i = j) {
            j = previous(i, *L);
            free(i);
        }
        *L = PNULL;
    }
}

tPos previous(tPos P ,tPos L){ //PreCD: La posición indicada es una posición válida en la lista.
    tPos prev = PNULL;
    tPos aux;
    for(aux = first(L); aux != PNULL; aux = aux->next){
        if(P == aux->next)
            prev = aux;
    }
    return prev;
}

bool isEmptyList(tList L){
    if(L == PNULL){
        return true;
    }else
        return false;
}

tPos first(tList L){
    return L;
}

tPos last(tList L){
    return L->last;
}

tPos next(tPos P, tList L){
    return P->next;
}

bool insertItem(tItem I, tList* L){
    tPos p , q;
    if(!CreateNode(&p)){
        return false;
    }else{
        p->command = I;
        p->next = PNULL;
        if(*L == PNULL){
            p->last = PNULL;
            *L = p;
            return true;
        }else{
            for (q = *L; q->next != PNULL; q = q->next);
            q->next = p;
            p->last = PNULL;
            updateLast(L , p);
            return true;
        }
    }
}

void deleteAtPosition(tPos pos , tList *L){
    if(pos == first(*L)){
        pos = pos->next;
    }
    else if(pos == last(*L)){
        previous(pos, *L)->next = PNULL;
        pos = previous(pos, *L);
        updateLast(L, pos);
    }
    else{
        pos->command = pos->next->command;

        tPos tmp = pos->next;
        pos->next = tmp->next;
        pos = tmp;
    }
    free(pos);
}


tList updateLast(tList* L , tPos p){
    for (tPos i = first(*L) ; i->next != PNULL  ; i = next(i , *L) ) {
        i->last = p;
    }
    return *L;
}

tItem getItem(tPos P, tList L){ // poden pasar cousas se pos una unha posicion non valida (ainda q non de error)
    return P->command;          //PRECONDICION IMPORTANTE: P DEBE SER UNHA POSICION VÁLIDA NA LISTA ANTES DE CHAMAR GETITEM
}


tPos findItem(tcommandNum N , tList L){
    if(isEmptyList(L)){
        return PNULL;
    }
    tPos p;
    for (p = L ; p != PNULL ; p = next(p , L)) {
        if(p->command.CommNum == N){
            return p;
        }
    }
    return p;
}

bool CreateNode(tPos *pos){
    *pos= malloc(sizeof (struct tNodo));
    return (*pos!=PNULL);
}