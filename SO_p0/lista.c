
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

tList* create_list(){
    tList* new_list = (tList*)malloc(sizeof(tList));
    new_list->size = 0;
    new_list->head = NULL;
    return new_list;
}

void add_to_list(tList* list , void* data , int id){
    tNode *copia;
    tNode* new_node = (tNode*) malloc(sizeof(tNode));
    new_node->data = data;
    new_node->next = NULL;
    new_node->dfORCommNUm = id;
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
}
void printStrings(void *n){
    printf(" %s\n", (char*)n);
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

void delete_list(tList* list){
    tNode* current_node = list->head;
    while (current_node != NULL){
        tNode* next_node = current_node->next;
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
    for ( list; list.head->next != NULL ; list.head = list.head->next);
    return list.head;
}


tPos findCommORdf(tList list , void* data){
    tPos aux;
    tPos prim = first(list);
    for( ; list.head != NULL ; list.head = prim){
        prim = next(prim , list);
        if(list.head->dfORCommNUm == (int)data){
            aux = list.head;
            return aux;
            }
        }
    }

tNode getNode(tList list , tPos P){//preCD no vacia
    tPos prim = first(list);
    for ( list ; list.head != P ; list.head = prim ) {
        prim = next(prim , list);
    }
    tNode sol = *list.head;
    return sol;
}

bool remove_from_list(tList* list , tPos P){
    if (list->size == 0) {
        return false;
    }
    tNode *tmp;
    if(P == first(*list)){
        tmp = list->head;
        list->head = list->head->next;
        free(tmp);
    }else if (P == last(*list)){
        tPos ult = last(*list);
        tPos prev = previous(P , *list);
        prev->next = NULL;
        free(ult);
    }else{
        tPos prev = previous(P , *list);
        tmp = prev->next;
        prev->next = tmp->next;
        free(tmp);
    }
    list->size--;
    return true;
}
