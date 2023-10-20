
#ifndef SO_P0_LISTA_H
#define SO_P0_LISTA_H
#define MAX_OPTIONS 100
#define MAX_COMMAND_LENGTH 20
#define MAX_NAME_LENGTH 256


#define PNULL NULL
#include <stdbool.h>

typedef int tcommandNum;
typedef char tcommand[MAX_COMMAND_LENGTH];
typedef char toptions[MAX_OPTIONS];


typedef struct tItem {
    tcommandNum CommNum;
    tcommand comm;
    toptions options1;
    toptions options2;

}tItem;

typedef struct tNodo* tPos;

struct tNodo{
    tItem command;
    tPos next;
    tPos last;
};

typedef tPos tList;


void createEmptyList(tList* L);

void deleteList(tList* L);

tPos previous(tPos P , tList L);

bool isEmptyList(tList L);

tPos first(tList L);

tPos last(tList L);

tPos next(tPos P, tList L);

bool insertItem(tItem I, tList* L);

tList updateLast(tList* L , tPos p);

tItem getItem(tPos P, tList L);//cd lista no vacia

tPos findItem(tcommandNum N , tList L);

bool CreateNode(tPos *pos);

void deleteAtPosition(tPos pos , tList *L);

#endif //SO_P0_LISTA_H
