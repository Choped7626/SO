#ifndef SO_P0_LISTA_H
#define SO_P0_LISTA_H
#define MAX_NAME_LENGTH 256

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <errno.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/resource.h>
#define MAX_TOTAL_COMMAND 100
#define TAMANO 2048

extern char ** environ;

typedef struct bloquesMem{
    void* address;
    unsigned long size;
    char timeAlloc[MAX_NAME_LENGTH];///
    char* typeOfAlloc;
    char other[MAX_NAME_LENGTH];
    char fileName[MAX_NAME_LENGTH];
}bloque;

struct SEN{
    char *nombre;
    int senal;
};

typedef enum {
    ACTIVE,
    STOPPED,
    FINISHED,
    SIGNALED
}StatusProcess;

static char *StatusName[] = {
        "Active",
        "Stopped",
        "Finished",
        "Signaled"
};
typedef struct job {
    pid_t pid;
    struct tm *create;
    StatusProcess status;
    char *program;
    int senial;
}job;

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

void add_String_to_list(tList* list , void* data , long id);

void add_Struct_to_list(tList* list , void* data , long id);

void add_address_to_list(tList* list , void* data);

void add_process_to_list(tList* list , void* data , long id);

bool remove_from_list(tList* list , tPos P);

void free_list(tList* list);

bool isEmpty(tList list);

void* printList(tList list , void (*fptr)(void *));

void* printListBlocks(tList list , char* type , void (*fptr)(void *));

void* printALLListBlocks(tList list, void (*fptr)(void *));

void printStrings(void* s);//declarar en funciones

void printStructs(void* s);

tPos first(tList list);

tPos next(tPos P , tList list);

tPos previous(tPos P , tList list);

tPos findCommORdf(tList list , void* data);

tNode getNode(tList list , tPos P);

tPos last(tList list);

void delete_list(tList* list);

#endif
