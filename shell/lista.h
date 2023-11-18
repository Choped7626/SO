#ifndef SO_P0_LISTA_H
#define SO_P0_LISTA_H
#define MAX_NAME_LENGTH 256

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct tNode* tPos;

typedef struct tNode{
    long dfORCommNUm;
    void* data;
    struct tNode* next;
}tNode;

typedef struct list{
    int size;
    tNode* head;
}tList;

tList* create_list();

void add_to_list(tList* list , void* data , long id);

bool remove_from_list(tList* list , tPos P);

void free_list(tList* list);

bool isEmpty(tList list);

void* printList(tList list , void (*fptr)(void *));

void printStrings(void* s);//declarar en funciones

tPos first(tList list);

tPos next(tPos P , tList list);

tPos previous(tPos P , tList list);

tPos findCommORdf(tList list , void* data);

tNode getNode(tList list , tPos P);

tPos last(tList list);

void delete_list(tList* list);

#endif
