
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

tList* create_list(){
    tList* new_list = (tList*)malloc(sizeof(tList));
    new_list->size = 0;
    new_list->head = NULL;
    return new_list;
}

void free_node_data(void* data){
    free(data);
}

void add_String_to_list(tList* list , void* data , long id){
    tNode *new_node = malloc(sizeof(struct tNode));
    new_node->data = malloc(sizeof (char*[15]));
    memcpy(new_node->data , data , sizeof (char*[15]));
    new_node->next = NULL;
    new_node->dfORCommNUm = id;
    tNode* copia;
    if(isEmpty(*list)){
        list->head = new_node;
        list->size++;
        list->head->dfORCommNUm = id;
        return;
    }else {
        for (copia = list->head; copia->next != NULL; copia = copia->next);
        copia->next = new_node;
        list->size++;
        return;
    }
}

void add_Struct_to_list(tList* list , void* data , long id){
    tNode *new_node = malloc(sizeof(struct tNode));
    new_node->data = malloc(sizeof (bloque));
    memcpy(new_node->data , data , sizeof (bloque));
    new_node->next = NULL;
    new_node->dfORCommNUm = id;
    tNode* copia;
    if(isEmpty(*list)){
        list->head = new_node;
        list->size++;
        list->head->dfORCommNUm = id;
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
    return NULL;
}

void* printListBlocks(tList list, char* type, void (*fptr)(void *)){
    while (list.head != NULL){
        bloque *bloque1 = list.head->data;
        if(strcmp(bloque1->typeOfAlloc , type) == 0)
            (*fptr)(list.head->data);
        list.head = list.head->next;
    }
    return NULL;
}

void printStrings(void *n){
    printf(" %s\n", (char*)n);
}

void printStructs(void *n){
    bloque *bloque1 = n;
    printf("%10p %15ld %15s %7s %5s \n" , bloque1->address , bloque1->size , bloque1->timeAlloc , bloque1->typeOfAlloc , bloque1->other);
}

void free_list(tList* list){
    if (list->head != NULL) {
        tNode *node = list->head;
        while (node != NULL){
            list->head = node->next;
            free_node_data(node->data);
            free(node);
            list->size--;
            node = list->head;
        }
    }
    free(list);
}

void delete_list(tList* list){
    tNode* current_node = list->head;
    while (current_node != NULL){
        tNode* next_node = current_node->next;
        free(current_node->data);
        free(current_node);
        current_node = next_node;
    }
    list->head = NULL;
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
    for (; list.head->next != NULL ; list.head = list.head->next);
    return list.head;
}


tPos findCommORdf(tList list , void* data){
    tPos aux;
    tPos prim = first(list);
    for(; list.head != NULL ; list.head = prim){
        prim = next(prim , list);
        if(list.head->dfORCommNUm == (long)data){
            aux = list.head;
            return aux;
            }
        }
    return NULL;
    }

tNode getNode(tList list , tPos P){//preCD no vacia
    tPos prim = first(list);
    for (; list.head != P ; list.head = prim ) {
        prim = next(prim , list);
    }
    tNode sol = *list.head;
    return sol;
}

bool remove_from_list(tList* list , tPos P){
    if (list->size == 0) {
        return false;
    }
    if(P == first(*list)){
        list->head = list->head->next;
        free(P->data);
        free(P);
        list->size--;
        return true;
    }else if (P == last(*list)){
        tPos prev = previous(P , *list);
        prev->next = NULL;
        free(P->data);
        free(P);
        list->size--;
        return true;
    }else{
        tPos prev = previous(P , *list);
        prev->next = P->next;
        free(P->data);
        free(P);
        list->size--;
        return true;
    }
}
