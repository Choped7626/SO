
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

tList* create_list(){
    tList* new_list = (tList*)malloc(sizeof(tList));
    new_list->size = 0;
    new_list->head = NULL;
    return new_list;
}

void add_to_list(tList* list , void* data){
    tNode *copia;
    tNode* new_node = (tNode*) malloc(sizeof(tNode));
    new_node->data = data;
    new_node->next = NULL;
    if(isEmpty(*list)){
        list->head = new_node;
        list->size++;
        return;
    }else {
        for (copia = list->head; copia->next != NULL; copia = copia->next);
        copia->next = new_node;
        list->size++;
        return;
    }
}

void* printList(tList list, void (*fptr)(void *)){
    while (list.head != NULL){
        (*fptr)(list.head->data);
        list.head = list.head->next;
    }
}
void printStrings(void *n){
    printf(" %s", (char*) n);
}

void free_list(tList* list){
    tNode* current_node = list->head;
    while (current_node != NULL){
        tNode* next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    free(list);
}

bool isEmpty(tList list){
    if(list.head == NULL)
        return true;
    else
        return false;
}

tPos first(tList list){
    return list.head;
}

tPos next(tPos P , tList list){
    if(!isEmpty(list)) {
        tNode *copia;
        for (copia = list.head; copia != P && copia != NULL; copia = copia->next);
        return copia->next;
    }
    return NULL;
}

tPos previous(tPos P , tList list){
    tNode *copia;
    for (copia = list.head; copia->next != P && copia != NULL ; copia = copia->next);
    return copia;
}

tPos last(tList list){
    for ( list; list.head->next != NULL ; list.head = list.head->next);
    return list.head;
}


tPos findCommORdf(tList list , void* data){
    tNode* aux;
    tPos prim = first(list);
    for(list ; list.head != NULL ; list.head = prim){
        prim = next(prim , list);
        aux = list.head;
        struct files* lol[10];
        for (int i = 0; i < 10; ++i) {
            lol[i] = (struct files*)aux->data;
            if(lol[i]->dfORnumComm == (int)data){
                return list.head;
            }
            aux = aux->next;
        }
    }
}

void* getNode(tList list , tPos P){
    tNode* sol;
    tPos prim = first(list);
    for ( list ; list.head != P ; list.head = prim ) {
        prim = next(prim , list);
        if(list.head == NULL)
            return NULL;
    }
    sol = list.head;
    return sol;
}

bool remove_from_list(tList* list , tPos P){
    if (list->size == 0) {
        return false;
    }
    if(P == first(*list)){
        P = P->next;
    }else{
        P->data = P->next->data;
        tPos tmp = P->next;
        P->next = tmp->next;
        P = tmp;
    }
    free(P);
    list->size--;
    return true;
}
