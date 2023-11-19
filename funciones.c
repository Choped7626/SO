/*
Nombre: Daniel Puñal Diaz       Login:  daniel.punal.diaz@udc.es    Grupo:3.2
Nombre: Mario Lamas Angeriz     Login: m.lamasa@udc.es              Grupo:3.2
*/
/*
 * cambios q estarian chingones:
 *
 * hacer dup de un archivo q se use pero no este en listopen(dup 3 usando valgrind)
 * ser mais preciso a hora de elegir as flags dos 3 archvios abertos , detectalas de algunha forma porq stderr a veces e solo W
*/
#include "cabeceras.h"

void authors(char opciones[]){
    if(opciones == NULL){

        printf("Logins: \t m.lamasa@udc.es \t daniel.punal.diaz@udc.es\n");
        printf("Nombres: \t Mario Lamas Angeriz \t Daniel Puñal Diaz\n");

    }else if(strcmp(opciones , "-l") == 0){

        printf("Logins: \t m.lamasa@udc.es \t daniel.punal.diaz@udc.es\n");

    }else if(strcmp(opciones , "-n") == 0){

        printf("Nombres: \t Mario Lamas Angeriz \t Daniel Puñal Diaz\n");

    }else
        printf("Opcion Inexistente");
}

void pid (char opciones[]){

    if(opciones == NULL) {

        printf("pid: %d\n", getpid());

    }else if(strcmp(opciones, "-p") == 0) {

        printf("father pid: %d\n", getppid());

    }else
        printf("Opcion Inexistente");
}

void chdirSO (char opciones[]){

    char cwd[256];
    if(opciones == NULL){
        printf("%s\n" , getcwd(cwd , sizeof(cwd)));
    } else if(chdir(opciones) != 0){
        perror("Diretorio Inexistente");
    }

}

void date (){

    time_t t = time(NULL);
    struct tm *tm  = localtime(&t);
    char hora[100];
    strftime(hora, 100, "%d-%m-%Y", tm);
    printf("%s \n" , hora);

}

void timeSO (){

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char hora[100];
    strftime(hora, 100, "%H:%M:%S", tm);
    printf("%s \n" , hora);

}

void hist (char opciones[] , tList* histCom , int* commNum){

    if(opciones == NULL){
        printList(*histCom , printStrings);

    } else if(strcmp(opciones , "-c") == 0){
        delete_list(histCom);
        *commNum = 0;
    }else if(strtol(opciones , NULL , 10) >= 1 && strtol(opciones , NULL , 10) <= histCom->size){

        tList copy;
        copy = *histCom;
        tPos fin = findCommORdf(*histCom , (void*)(long)strtol(opciones , NULL , 10));
        for (tPos i = first(*histCom); i != fin->next ; i = next(i , *histCom)) {
                (printStrings)(copy.head->data);
                copy.head = copy.head->next;
        }
    }else{
        printf("Opcion Inexistente");
    }
}

void command (char *tr[] , tList *histComm , int* commNum , bool* fin , int* recursividad , tList *listOpen , tList *listBlocks){

    tPos p;
    tNode I;

    if(*recursividad == 5){ //Comprobación de recursividad infinita
        printf("error de recursividad infinita\n");
        return;
    }

    if(tr[1] == NULL || (int)strtol(tr[1] , NULL , 10) >= *commNum || (int)strtol(tr[1] , NULL , 10) <= 0){

        printf("Número de comando no válido");

    }else{

        p = findCommORdf(*histComm , (void*)(long)strtol(tr[1] , NULL , 10));
        I = getNode(*histComm , p);
        (*recursividad)++;

        char* cadenaH = strdup(I.data);// Duplicamos la cadena para no modificar la original
        int pala = TrozearCadena(cadenaH , tr);  //Didimos la cadena en trozos

        int i = 0;
        for(int j = 2 ; j < MAX_TOTAL_COMMAND ; j++) {
            if (j < pala) {
                tr[i] = tr[j];
                i++;
            } else{
                tr[i] = NULL;
                break;
            }
        }
        whichCommand(tr ,  histComm , commNum , fin , recursividad , listOpen , listBlocks);
        free(cadenaH);
    }
}

void openSO (char *tr[] , tList *listOpen) {

    int i,df, mode=0;

    if (tr[1]==NULL) { /*no hay paramentro*/
        listOpenFiles(listOpen);
        return;
    }

    for( i = 2 ; tr[i] != NULL ; i++){
        if(strcmp(tr[i],"cr") == 0){
            mode |= O_CREAT;                //crea un fichero si non existe
        }else if(strcmp(tr[i], "ex") == 0) {
            mode |= O_EXCL;                 //flag de uso exclusivo¿?
        }else if(strcmp(tr[i], "ro") == 0) {
            mode |= O_RDONLY;               //abrir solo lectura
        }else if(strcmp(tr[i], "wo") == 0) {
            mode |= O_WRONLY;               //abrir solo escritura
        }else if(strcmp(tr[i], "rw") == 0) {
            mode |= O_RDWR;                 //abrir lectura/escritura
        }else if(strcmp(tr[i], "ap") == 0) {
            mode |= O_APPEND;               //modo adjuntar¿?
        }else if(strcmp(tr[i], "tr") == 0) {
            mode |= O_TRUNC;                //truca la flag¿?
        }else
            break;
    }

    df = open(tr[1] , mode , 0777);
    if(df == -1){
        perror("Imposible abrir fichero");
    }else{
        insertOpenFiles(df, tr[1], listOpen, mode);
        printf("Añadida entrada a la tabla de ficheros abiertos\n");
    }
}

void closeSO (char *tr[] , tList *listOpen){
    int df;

    if (tr[1]==NULL || (df=atoi(tr[1])) < 0) { /*no hay parametro*/
        listOpenFiles(listOpen);/*o el descriptor es menor que 0*/
        return;
    }
    if (close(df) == -1)
        perror("Imposible cerrar descriptor\n");
    else
        deleteOpenFiles(df , listOpen);
}

void deleteOpenFiles(int df, tList *listOpen){


    tPos fich;
    fich = findCommORdf(*listOpen , (void*)(long)df);
    if (fich == NULL){
        printf("df inexistente\n");
    } else{
        remove_from_list(listOpen, fich);
        listOpenFiles(listOpen);
    }
}

void dupSO (char *tr[] , tList *listOpen){
    int df , duplicado;
    if(tr[1] != NULL)
        df = (int)strtol(tr[1] , NULL , 10);
    char aux[MAX_NAME_LENGTH];
    char *p = malloc(sizeof (char *[MAX_TOTAL_COMMAND])) ;



    if (tr[1]==NULL || df < 0 || df > last(*listOpen)->dfORCommNUm) { /*no hay parametro*/
        listOpenFiles(listOpen);                /*o el descriptor es menor que 0*/
        free(p);
        return;
    }

    duplicado = dup(df);

    tPos p1 = findCommORdf(*listOpen , (void*)(long)df);
    strcpy(p , p1->data);
    char *cadenaT[MAX_TOTAL_COMMAND];

    int num = TrozearCadena(p , cadenaT);

    if(num < 0){
        perror("No se pudo duplicar el archivo\n");
        free(p);
        return;
    }
    snprintf (aux, sizeof(char[MAX_NAME_LENGTH]),"dup %d (%s)",df, cadenaT[3]);
    insertOpenFiles(duplicado , aux , listOpen , fcntl(duplicado , F_GETFL));
    printf("Añadida entrada a la tabla de ficheros abiertos\n");
    free(p);
}

void listOpenFiles (tList *listOpen){  //recorremos la lista e imprimimos su contenido

    if (isEmpty(*listOpen)){
        printf("Esta vacia\n");
    }
    else {
        printList(*listOpen , printStrings);
    }

}

void insertOpenFiles(int df , const char *nombre , tList *listOpen , int mode){

    char* name = malloc(sizeof (char*[23]));

    if(snprintf(name , sizeof(char*[23]) , "descriptor: %d -> %s" , df , nombre) < 0){
        perror("no se pudo  insertar el archivo en la lista de archivos abiertos\n");
        return;
    }

    if ((mode & O_CREAT) != 0)
        strcat(name, " , O_CREAT ");
    if ((mode & O_EXCL) != 0)
        strcat(name, " , O_EXCL ");
    if ((mode & O_RDONLY) != 0)
        strcat(name, " , O_RDONLY ");
    if ((mode & O_WRONLY) != 0)
        strcat(name, " , O_WRONLY ");
    if ((mode & O_RDWR) != 0)
        strcat(name, " , O_RDWR ");
    if ((mode & O_APPEND) != 0)
        strcat(name, " , O_APPEND ");
    if ((mode & O_TRUNC) != 0)
        strcat(name, " , O_TRUNC ");
    strcat(name , "\n");
    add_String_to_list(listOpen , name , df);
    free(name);
}

void infosys (){
    char pc[256];
    struct utsname uts;

    if(gethostname(pc, 255) != 0 || uname(&uts) < 0){
        printf("No se ha obtenido informacion del host\n");
        exit(1);
    }

    printf("INFORMACION SISTEMA:\n");
    printf("Nombre de host del pc: %s\n", pc);
    printf("Sistema: %s\n", uts.sysname);
    printf("Nombre del nodo: %s\n", uts.nodename);
    printf("Operating system release: %s\n", uts.release);
    printf("Version: %s\n", uts.version);
    printf("Hardware: %s\n", uts.machine);
}

//añadir nuevos comandos
void help (char opciones[]){

    if (opciones == NULL){
        printf("Avaliable commands: \n authors [-l|-n] \n pid [-p] \n chdir [dir] \n date \n time \n hist [-c|-N] \n command N \n open [file] mode \n "
               "close [df] \n dup [df] \n listopen \n infosys \n create [-f] [name] \n list [-reca] [-recb] [-hid][-long][-link][-acc] n1 n2 .. \n"
               " stat [-long][-link][-acc] name1 name2 .. \n delete [name1 name2 ..] \n deltree [name1 name2 ..] \n help [cmd] \n quit \n exit \n bye \n");
    }else if(strcmp(opciones , "authors") == 0){
        printf("Prints the names and logins of the program authors. \n authors -l prints"
               "only the logins \n authors -n prints only the names\n");
    }else if(strcmp(opciones , "pid") == 0){
        printf("Prints the pid of the process executing the shell. \n pid -p rints the pid"
               "of the shell’s parent process.\n");
    }else if(strcmp(opciones , "chdir") == 0){
        printf("Changes the current working directory of the shell to dir.\n"
               "When invoked without auguments it prints the"
               "current working directory \n");
    }else if(strcmp(opciones , "date") == 0){
        printf("Prints the current date in the format DD/MM/YYYY\n");
    }else if(strcmp(opciones , "time") == 0){
        printf("Prints the current time in the format hh:mm:ss.\n");
    }else if(strcmp(opciones , "hist") == 0){
        printf("Shows/clears the historic of commands executed by this shell.\n"
               "hist -c clears the historic, that’s to say, empties the list\n"
               "– hist Prints all the commands that have been input with their order number\n"
               "– hist -c Clears (empties) the list of historic commands\n"
               "– hist -N Prints the first N commands\n");
    }else if(strcmp(opciones , "command") == 0){
        printf("Repeats command number N (from historic list)\n");
    }else if(strcmp(opciones , "open") == 0){
        printf("Opens a file and adds it (together with the file descriptor and the "
               "opening mode to the list of shell open files. \n For the mode we’ll use cr for"
               "O_CREAT, ap for O_APPEND, ex for O_EXCL, ro for O_RDONLY, "
               "rw for O_RDWR, wo for O_WRONLY and tr for O_TRUNC. \n");
    }else if(strcmp(opciones , "close") == 0){
        printf("Closes the df file descriptor and eliminates the corresponding item from "
               "the list\n");
    }else if(strcmp(opciones , "dup") == 0){
        printf("Duplicates the df file descriptor (using the dup system call, creating the "
               "corresponding new entry on the file list\n");
    }else if(strcmp(opciones , "listopen") == 0){
        printf("Lists the shell open files. For each file it lists its descriptor, the file "
               "name and the opening mode. \n");
    }else if(strcmp(opciones , "infosys") == 0){
        printf("Prints information on the machine running the shell (as obtained via "
               "the uname system call/library function)\n");
    }else if(strcmp(opciones , "help") == 0){
        printf("help displays a list of available commands. help cmd gives a brief help "
               "on the usage of command cmd\n");
    }else if(strcmp(opciones , "create") == 0){
        printf("creates files \n (-f) or directories\n");
    }else if(strcmp(opciones , "stat") == 0){
        printf("gives information on files or directories\n"
               "\t-long: listado largo\n"
               "\t-acc: acesstime\n"
               "\t-link: si es enlace simbolico, el path contenido\n");
    }else if(strcmp(opciones , "list") == 0){
        printf("lists directories contents \n"
               "\t-hid: incluye los ficheros ocultos\n"
               "\t-recb: recursivo (antes)\n"
               "\t-reca: recursivo (despues)\n"
               "\tresto parametros como stat\n");
    }else if(strcmp(opciones , "delete") == 0){
        printf("deletes files and/or empty directories\n");
    }else if(strcmp(opciones , "deltree") == 0){
        printf("deletes files and/pr non empty directories recursively\n");
    }else if(strcmp(opciones , "quit") == 0 || strcmp(opciones , "bye") == 0 || strcmp(opciones , "exit") == 0){
        printf("Ends the shell\n");
    }else
        printf("Comando Inexistente");
}

void meterDatos(const int* num , char *tr[], tList *hist){

    char *commName = malloc(sizeof(char*[MAX_TOTAL_COMMAND]));          //SIGABRT se fas unha chamada a un comando q ten caracteres de mais e xusto despois fas un hist
    snprintf(commName , sizeof(char*[MAX_TOTAL_COMMAND]), "%d , " , *num );
    for (int i = 0; i < MAX_TOTAL_COMMAND ; ++i) {
        if(tr[i] != NULL){
            strcat(commName, tr[i]);
            strcat(commName, " ");
        }else break;
    }
    add_String_to_list(hist , commName , *num);
    free(commName);
}

void closeShell (bool *fin){
    *fin = true;
}

void whichCommand(char *tr[], tList *histComm , int* commNum , bool* fin , int* recursividad , tList *listOpen , tList *listBlocks){

    if(strcmp(tr[0] , "authors") == 0)
        authors(tr[1]);
    else if(strcmp(tr[0] , "pid") == 0)
        pid(tr[1]);
    else if(strcmp(tr[0] , "chdir") == 0)
        chdirSO(tr[1]);
    else if(strcmp(tr[0] , "date") == 0)
        date();
    else if(strcmp(tr[0] , "time") == 0)
        timeSO();
    else if(strcmp(tr[0] , "hist") == 0)
        hist(tr[1] , histComm , commNum);
    else if(strcmp(tr[0] , "command") == 0)
        command(tr , histComm , commNum , fin , recursividad , listOpen , listBlocks);
    else if(strcmp(tr[0] , "open") == 0)
        openSO(tr , listOpen);
    else if(strcmp(tr[0] , "close") == 0)
        closeSO(tr , listOpen);
    else if (strcmp(tr[0], "dup") == 0)
        dupSO(tr , listOpen);
    else if (strcmp(tr[0], "listopen") == 0)
        listOpenFiles(listOpen);
    else if (strcmp(tr[0], "infosys") == 0)
        infosys();
    else if (strcmp(tr[0] , "create") == 0)
        create(tr);
    else if (strcmp(tr[0] , "stat") == 0)
        statSO(tr);
    else if (strcmp(tr[0] , "list") == 0)
        list(tr);
    else if (strcmp(tr[0] , "delete") == 0)
        delete(tr);
    else if (strcmp(tr[0] , "deltree") == 0)
        deltree(tr);
    else if (strcmp(tr[0], "help") == 0)
        help(tr[1]);
    else if (strcmp(tr[0] , "malloc") == 0)
        mallocSO(tr , listBlocks);
    else if (strcmp(tr[0] , "shared") == 0)
        shared(tr , listBlocks);
    else if ((strcmp(tr[0], "quit") == 0) || (strcmp(tr[0], "exit") == 0) || (strcmp(tr[0], "bye") == 0))
        closeShell(fin);
    else
        printf("Comando inexistente\n");
}

int TrozearCadena(char* cadena , char* tr[]){
    int i = 1;
    if ((tr[0]=strtok(cadena," \n\t"))==NULL)
        return 0;
    while ((tr[i]=strtok(NULL," \n\t"))!=NULL)
        i++;
    i > 49 ? i = -1 : i;
    return i;
}

void procesarEntrada(char c[] , bool *fin , tList *histComm , tList *listOpen , tList *listBlocks){

    char *tr[MAX_TOTAL_COMMAND];

    static int num = 0;
    static int *commNum = &num;

    int controlRecur = 0;
    int *recursividad = &controlRecur;

    int palabras = TrozearCadena(c , tr);
    if(palabras != 0 && palabras != -1){
        num++;
        meterDatos(commNum , tr , histComm);
        whichCommand(tr , histComm , commNum , fin , recursividad , listOpen , listBlocks);
    }else
        if(palabras == -1){                                         //SI CADENA DEMASIADO LARGA COLLEA VARIAS VECES , PURGAR STDIN?
            printf("Cadena demasiado grande");

        }else
            printf("Cadena Vacia");
}

char LetraTF (mode_t m){
    switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
    }
}

char * ConvierteModo (mode_t m)
{
    static char permisos[12];
    strcpy (permisos,"---------- ");

    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';

    return permisos;
}

void create(char* tr[]){

    FILE *fl;
    int df;
    mode_t m;
    m = 0775;

    if (tr[1] == NULL) { /*no hay paramentro*/
        printf("Imposible crear el fichero");
    }else if(strcmp(tr[1] , "-f") == 0) {
        if(access(tr[2], F_OK) == 0){
            printf("El fichero ya existe\n");
            return;
        }
        fl = fopen(tr[2], "w");
        if (fl == NULL){
            perror("Imposible crear el fichero");
            return;
        }
        chmod(tr[2] , m);
        fclose(fl);
    }else{
        df = mkdir(tr[1] , 0777);
        if(df == -1){
            perror("Imposible crear el fichero");
        }
        chmod(tr[1] , 0775);
    }
}

void statSO(char* tr[]){

    int use_long = 0, use_link = 0, use_acc = 0, name = 0;  //contadores para saber si se usa alguna de las opciones
    int i = 1;
    long size = PATH_MAX;
    struct stat info;

    while(i != 4) {
        if(tr[i] == NULL) break;
        if(strcmp(tr[i], "-long") == 0) {
            use_long = 1;
            i++;
        }else if(strcmp(tr[i], "-link") == 0) {
            use_link = 1;
            i++;
        }else if(strcmp(tr[i], "-acc") == 0) {
            use_acc = 1;
            i++;
        }else if(strcmp(tr[i], "-long") != 0 && strcmp(tr[i], "-link") != 0 && strcmp(tr[i], "-acc") != 0){
            name = i;
            break;
        }
    }
    if(name == 0)
        name = i;

    for (; tr[name] != NULL ; name++) {

        if(access(tr[name], F_OK) == 0){

            lstat(tr[name] , &info);
            size = info.st_size;

        if(use_long == 1){

            char hora[50];
            strftime(hora, sizeof(hora), "%c", localtime(&info.st_mtim.tv_sec));//hora de ultima modificacion
            int links = (int) info.st_nlink;
            int inodo = (int) info.st_ino;
            char *permiss = ConvierteModo(info.st_mode);
            char direccionLinkPrint[PATH_MAX + 1] = "";

            if(use_link == 1){//usa long e link
                char direccionLink[PATH_MAX + 1] = "";
                if (readlink(tr[name], direccionLink, PATH_MAX) == -1) {

                }else {
                    if (strlen(direccionLink) > 0) {
                        strcat(direccionLinkPrint, " -> ");
                        strcat(direccionLinkPrint, direccionLink);
                    }
                }
            }

            if(use_acc == 1){//usa long e acc

                strftime(hora, sizeof(hora), "%c", localtime(&info.st_atim.tv_sec));//hora de ultimo acceso

            }//usa solo long

            printf("%25s %3d(%8d) %10s %10s %10s %6ld %15s%15s\n", hora, links, inodo, getpwuid(info.st_uid)->pw_name,
                       getgrgid(info.st_gid)->gr_name, permiss, size, tr[name] , direccionLinkPrint);

        }else{
            printf("%6ld %15s\n" , size , tr[name]);
        }

        }else{
            printf("error al accder a %s : %s\n" , tr[name] , strerror(errno));
        }
    }
    if(tr[i] == NULL){
        chdirSO(tr[i]);
    }
}

void reca(int cnt , char* llamadaAux[] , int use_hid , char* pathInicial){

    struct dirent *dp;
    struct dirent *aux;
    char path[1000];
    struct stat esFile;
    int bin = stat(pathInicial , &esFile);
    DIR* d = opendir(pathInicial);

    if (!d)
        return;

    printf("************%s\n" , pathInicial);
    while ((aux = readdir(d)) != NULL){
        if (use_hid == 1) {
            llamadaAux[cnt] = aux->d_name;
            if (bin == 0 && S_ISDIR(esFile.st_mode))
                chdir(pathInicial);
            statSO(llamadaAux);
        } else if (aux->d_name[0] != '.') {
            llamadaAux[cnt] = aux->d_name;
            if (bin == 0 && S_ISDIR(esFile.st_mode))
                chdir(pathInicial);
            statSO(llamadaAux);
        }
    }

    DIR* c = opendir(pathInicial);
    if (!c)
        return;

    while ((dp = readdir(c)) != NULL){
        if(dp->d_name[0] != '.'){
            strcpy(path , pathInicial);
            strcat(path , "/");
            strcat(path , dp->d_name);
        }else
            strcpy(path , pathInicial);

        if(dp->d_name[0] != '.')
            reca(cnt , llamadaAux , use_hid , path);
    }
    closedir(d);
    closedir(c);
}

void recb(int cnt , char* llamadaAux[] , int use_hid , char* pathInicial){

    struct dirent *dp;
    struct dirent *aux;
    char path[1000];
    struct stat esFile;
    int bin = stat(pathInicial , &esFile);

    DIR* c = opendir(pathInicial);
    if (!c)
        return;

    while ((dp = readdir(c)) != NULL){
        if(dp->d_name[0] != '.'){
            strcpy(path , pathInicial);
            strcat(path , "/");
            strcat(path , dp->d_name);
        }else
            strcpy(path , pathInicial);

        if(dp->d_name[0] != '.')
            recb(cnt , llamadaAux , use_hid , path);
    }

    DIR* d = opendir(pathInicial);

    if (!d)
        return;

    printf("************%s\n" , pathInicial);
    while ((aux = readdir(d)) != NULL){
        if (use_hid == 1) {
            llamadaAux[cnt] = aux->d_name;
            llamadaAux[cnt + 1] = NULL;
            if (bin == 0 && S_ISDIR(esFile.st_mode))
                chdir(pathInicial);
            statSO(llamadaAux);
        } else if (aux->d_name[0] != '.') {
            llamadaAux[cnt] = aux->d_name;
            llamadaAux[cnt + 1] = NULL;
            if (bin == 0 && S_ISDIR(esFile.st_mode))
                chdir(pathInicial);
            statSO(llamadaAux);
        }
    }
    closedir(d);
    closedir(c);
}

void list(char* tr[]){

    char* llamadaAux[MAX_TOTAL_COMMAND];
    for (int i = 0; i < MAX_TOTAL_COMMAND; ++i) {
        llamadaAux[i] = NULL;
    }

    int pos = 0 , i = 1 , cnt = 1 , use_hid = 0 , use_reca = 0 , use_recb = 0;

    while(i != 7) {
        if(tr[i] == NULL) break;
        if(strcmp(tr[i], "-long") == 0) {
            llamadaAux[cnt] = "-long";
            cnt++;
            i++;
        }else if(strcmp(tr[i], "-link") == 0) {
            llamadaAux[cnt] = "-link";
            cnt++;
            i++;
        }else if(strcmp(tr[i], "-acc") == 0) {
            llamadaAux[cnt] = "-acc";
            cnt++;
            i++;
        }else if(strcmp(tr[i], "-hid") == 0) {
            use_hid = 1;
            i++;
        }else if(strcmp(tr[i], "-reca") == 0) {
            use_reca = 1;
            i++;
        }else if(strcmp(tr[i], "-recb") == 0) {
            use_recb = 1;
            i++;
        }else if(tr[i] != NULL){
            pos = i;
            break;
        }
    }
    if(pos == 0)
        pos = i;

    DIR* d;
    char cwd[PATH_MAX];
    getcwd(cwd , sizeof(cwd));
    for (; tr[pos] != NULL ; pos++) {

        if ((d = opendir(tr[pos])) != NULL){

            struct dirent *dp;

            if(use_reca == 1){
                printf(" ________________________Using reca________________________ \n");
                char pathInicial[PATH_MAX];
                if(strchr(tr[pos] , '/') == NULL){
                    getcwd(pathInicial , sizeof (pathInicial));
                    strcat(pathInicial , "/");
                    strcat(pathInicial , tr[pos]);

                }else
                    strcpy(pathInicial , tr[pos]);
                reca(cnt , llamadaAux , use_hid , pathInicial);
                chdir(cwd);
            }
            if (use_recb == 1){
                printf(" ________________________Using recb________________________ \n");
                char pathInicial2[PATH_MAX];
                if(strchr(tr[pos] , '/') == NULL){
                    getcwd(pathInicial2 , sizeof (pathInicial2));
                    strcat(pathInicial2 , "/");
                    strcat(pathInicial2 , tr[pos]);
                }else
                    strcpy(pathInicial2 , tr[pos]);
                recb(cnt , llamadaAux , use_hid , pathInicial2);
                chdir(cwd);
            }

            if(use_reca == 0 && use_recb == 0 ) {
                printf("**********%s\n" , tr[pos]);
                while ((dp = readdir(d))!= NULL){
                    if (use_hid == 1) {
                        llamadaAux[cnt] = dp->d_name;
                        chdir(tr[pos]);
                        statSO(llamadaAux);
                        chdir(cwd);
                    } else if (dp->d_name[0] != '.') {
                        llamadaAux[cnt] = dp->d_name;
                        chdir(tr[pos]);
                        statSO(llamadaAux);
                        chdir(cwd);
                    }
                }
            }
            closedir(d);
        }else{
            llamadaAux[cnt] = tr[pos];
            statSO(llamadaAux);
        }
    }
    if(tr[i] == NULL){
        chdirSO(tr[i]);
    }
}

void delete(char* tr[]){

    if (access(tr[1], F_OK) == 0) {  //Comprobamos que existe el archivo o el directorio
        (rmdir(tr[1]) == 0 || unlink(tr[1]) == 0) ? printf("Borrado de %s Completado\n" , tr[1]) : perror("Error al borrar\n");
    }
    else {
        perror("ERROR. El directorio o el archivo no existen\n"); //Si el archivo o el directorio no existe, se lanzara error
    }
}

void deltree(char* tr[]) {

    struct dirent* enter;  //para esto usamos dirent.h
    DIR* directory = opendir(tr[1]);  //abrimos el directorio y los guardamos en un puntero

    if(!directory) {
        delete(tr);
        return;
    }
    while((enter = readdir(directory))) {  //Recorremos el directorio
        if (strcmp(enter->d_name, ".") == 0 || strcmp(enter->d_name, "..") == 0)
            continue;

        //Accedemos al directorio
        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", tr[1], enter->d_name);  //para ello concatenamos la ruta que teniamos con /"nombre de la carpeta que accedemos"
        char *subtr[] = { NULL,path};
        struct stat info;
        if(stat(path, &info) == 0)
            (S_ISDIR(info.st_mode)) ? deltree(subtr) : delete(subtr);
        //Si es un directorio, llamamos a deltree para borrar su contenido
        //Si es un archivo, llamamos a delete para eliminarlo
    }
    closedir(directory);  //cerramos el directorio actual
    delete(tr);  //borramos el contenido
}

void mallocSO(char* tr[] , tList *listBlocks){

    if(tr[1] != NULL){

        if(strcmp(tr[1] , "-free") == 0 && tr[2] != NULL){
            long search = atoi(tr[2]);
            tPos liberar = findCommORdf(*listBlocks , (void*)search);
            if(liberar == NULL){
                printf("No hay bloque de ese tamano asignado con malloc \n");
                return;
            }
            bloque *bloqueFree = liberar->data;
            if(strcmp("malloc" , bloqueFree->typeOfAlloc) != 0){
                printf("No hay bloque de ese tamano asignado con malloc \n");
                return;
            }
            free(bloqueFree->address);
            remove_from_list(listBlocks , liberar);

        }else if (atoi(tr[1]) != 0){
            unsigned int* mallocPointer;
            long tam = strtol(tr[1] , NULL , 10);
            errno = 0;
            mallocPointer = malloc(tam);
            if(errno != 0){
                perror("Fallo al usar el malloc");
                return;
            }
            bloque *bloque1 = malloc(sizeof (bloque));
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            char hora[100];
            strftime(hora, 100, "%m %d %H:%M", tm);
            bloque1->address = mallocPointer;
            bloque1->size = tam;
            snprintf((char *) bloque1->timeAlloc, sizeof(char[MAX_NAME_LENGTH]) , "%s" , hora);
            bloque1->typeOfAlloc = "malloc";
            add_Struct_to_list(listBlocks , bloque1 , tam);//metemos tamaño en numero de orden de lista para poder usar finditem
            printf("Asignados %ld bytes en %p\n" , tam , bloque1->address);
            free(bloque1);
        }else{
            printf("******Lista de bloques asignados malloc para el proceso %d\n" , getpid());
            printListBlocks(*listBlocks , "malloc" , printStructs);
        }            ///unificar estas duas cousas
    }else{
        printf("******Lista de bloques asignados malloc para el proceso %d\n" , getpid());
        printListBlocks(*listBlocks , "malloc" , printStructs);
    }
}

void * ObtenerMemoriaShmget (key_t clave, size_t tam , tList *listBlocks)
{
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;
    bloque *bloque1 = malloc(sizeof (bloque));

    if (tam)     /*tam distito de 0 indica crear */
        flags=flags | IPC_CREAT | IPC_EXCL;
    if (clave==IPC_PRIVATE)  /*no nos vale*/
    {errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1)
        return (NULL);
    if ((p=shmat(id,NULL,0))==(void*) -1){
        aux=errno;
        if (tam)
            shmctl(id,IPC_RMID,NULL);
        errno=aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s);
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char hora[100];
    strftime(hora, 100, "%m %d %H:%M", tm);
    bloque1->address = p;
    bloque1->typeOfAlloc = "shared";
    snprintf(bloque1->timeAlloc, sizeof(char[MAX_NAME_LENGTH]) , "%s" , hora);
    bloque1->size = s.shm_segsz;
    snprintf(bloque1->other, sizeof(char[MAX_NAME_LENGTH]) , "(key %d)" , clave);
    add_Struct_to_list(listBlocks , bloque1 , s.shm_segsz);
    free(bloque1);
    return (p);
}

void do_AllocateCreateshared (char *tr[] , tList *listBlocks){
    key_t cl;
    size_t tam;
    void *p;

    if (tr[2]==NULL || tr[3]==NULL) {
        printf("******Lista de bloques asignados shared para el proceso %d\n" , getpid());
        printListBlocks(*listBlocks , "shared" , printStructs);
        return;
    }

    cl = (key_t)  strtoul(tr[2],NULL,10);
    tam = (size_t) strtoul(tr[3],NULL,10);
    if (tam==0) {
        printf ("No se asignan bloques de 0 bytes\n");
        return;
    }
    if ((p=ObtenerMemoriaShmget(cl,tam,listBlocks))!=NULL)
        printf ("Asignados %lu bytes en %p\n",(unsigned long) tam, p);
    else
        printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}

void do_DeallocateDelkey (char *args[])
{
    key_t clave;
    int id;
    char *key = args[2];

    if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){
        printf ("      delkey necesita clave_valida\n");
        return;
    }
    if ((id=shmget(clave,0,0666))==-1){
        perror ("shmget: imposible obtener memoria compartida");
        return;
    }
    if (shmctl(id,IPC_RMID,NULL)==-1)
        perror ("shmctl: imposible eliminar memoria compartida\n");
}

void shared(char* tr[] , tList *listBlocks){
    if(tr[1] != NULL){
        if (strcmp(tr[1] , "-create") == 0 ){
            do_AllocateCreateshared(tr , listBlocks);
        }else if(strcmp(tr[1] , "-free") == 0){

        }else if(strcmp(tr[1] , "-delkey") == 0) {
            do_DeallocateDelkey(tr);
        }else{

        }
    }else{
        printf("******Lista de bloques asignados shared para el proceso %d\n" , getpid());
        printListBlocks(*listBlocks , "shared" , printStructs);
    }
}