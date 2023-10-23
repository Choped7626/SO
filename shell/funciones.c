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
        perror("Opcion Inexistente");
}

void pid (char opciones[]){

    if(opciones == NULL) {

        printf("pid: %d\n", getpid());

    }else if(strcmp(opciones, "-p") == 0) {

        printf("father pid: %d\n", getppid());

    }else
        perror("Opcion Inexistente");
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
///borrar pero no eliminar
        delete_list(histCom);
        *commNum = 0;

    }else if(strtol(opciones , NULL , 10) >= 1 && strtol(opciones , NULL , 10) <= histCom->size){
///
        tList copy;
        copy = *histCom;
        tPos fin = findCommORdf(*histCom , (void*)(long)strtol(opciones , NULL , 10));
        for (tPos i = first(*histCom); i != fin->next ; i = next(i , *histCom)) {
                (printStrings)(copy.head->data);
                copy.head = copy.head->next;
        }
    }else{
        perror("Opcion Inexistente");
    }
}

void command (char *tr[] , tList *histComm , int* commNum , bool* fin , int* recursividad , tList *listOpen){

    tPos p;
    tNode I;

    if(*recursividad == 5){
        printf("error de recursividad infinita\n");
        return;
    }

    if(tr[1] == NULL || (int)strtol(tr[1] , NULL , 10) >= *commNum || (int)strtol(tr[1] , NULL , 10) <= 0){

        perror("Número de comando no válido");

    }else{

        p = findCommORdf(*histComm , (void*)(long)strtol(tr[1] , NULL , 10));
        I = getNode(*histComm , p);
        recursividad++;
        ///incapaz de q cando o usa non o borre :(

        char *trozosAux[MAX_TOTAL_COMMAND];
        char* cadenaH = malloc(sizeof (char *[MAX_TOTAL_COMMAND]));//
        strcpy(cadenaH , I.data);
        int pala = TrozearCadena(cadenaH , trozosAux);
        int i = 0;
        for(int j = 2 ; j < MAX_TOTAL_COMMAND ; j++) {
            if (j < pala) {
                trozosAux[i] = trozosAux[j];
                i++;
            } else{
                trozosAux[i] = NULL;
                break;
            }
        }
        whichCommand(trozosAux , histComm , commNum , fin , recursividad , listOpen);
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

    ///
    tPos fich;
    fich = findCommORdf(*listOpen , (void*)(long)df);
    if (fich == NULL){
        perror("df inexistente\n");
    } else{
        remove_from_list(listOpen, fich);
        listOpenFiles(listOpen);
    }
}

void dupSO (char *tr[] , tList *listOpen){

    int df, duplicado;
    char aux[MAX_NAME_LENGTH],*p = malloc(sizeof (char *[MAX_TOTAL_COMMAND])) ;

    if (tr[1]==NULL || (df=atoi(tr[1])) < 0 || (df=atoi(tr[1])) > last(*listOpen)->dfORCommNUm) { /*no hay parametro*/
        listOpenFiles(listOpen);                /*o el descriptor es menor que 0*/
        return;
    }

    duplicado = dup(df);
    ///
    tPos p1 = findCommORdf(*listOpen , (void*)(long)df);
    strcpy(p , p1->data);
    char *cadenaT[MAX_TOTAL_COMMAND];

    int num = TrozearCadena(p , cadenaT);
    free(p);
    if(num < 0)
        perror("error\n");
    sprintf (aux,"dup %d (%s)",df, cadenaT[3]);
    insertOpenFiles(duplicado , aux , listOpen , fcntl(duplicado , F_GETFL));
}

void listOpenFiles (tList *listOpen){  //recorremos la lista e imprimimos su contenido

    if (isEmpty(*listOpen)){
        perror("Esta vacia\n");
    }
    else {
        ///
        printList(*listOpen , printStrings);
    }

}

void insertOpenFiles(int df , const char *nombre , tList *listOpen , int mode){
///
    char* name = malloc(sizeof (char*[15]));
    char* flagOpen = malloc(sizeof (char*[8]));

    if ((mode & O_CREAT) != 0)
        strcat(flagOpen, "O_CREAT ");
    if ((mode & O_EXCL) != 0)
        strcat(flagOpen, "O_EXCL ");
    if ((mode & O_RDONLY) != 0)
        strcat(flagOpen, "O_RDONLY ");
    if ((mode & O_WRONLY) != 0)
        strcat(flagOpen, "O_WRONLY ");
    if ((mode & O_RDWR) != 0)
        strcat(flagOpen, "O_RDWR ");
    if ((mode & O_APPEND) != 0)
        strcat(flagOpen, "O_APPEND ");
    if ((mode & O_TRUNC) != 0)
        strcat(flagOpen, "O_TRUNC ");

    if(sprintf(name , "descriptor: %d -> %s , %s \n" , df , nombre , flagOpen) < 0)
        perror("error");
    add_to_list(listOpen , name , df);

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

void help (char opciones[]){

    if (opciones == NULL){
        printf("Avaliable commands: \nauthors [-l|-n] , pid [-p] , chdir [dir] , date , time \nhist [-c|-N] , command N , open [file] mode , "
               "close [df] \ndup [df] , listOpenFiles , infosys , help [cmd] , quit , exit , bye.\n");
    }else if(strcmp(opciones , "authors") == 0){
        printf("Prints the names and logins of the program authors. authors -l prints\n"
               "only the logins and authors -n prints only the names\n");
    }else if(strcmp(opciones , "pid") == 0){
        printf("Prints the pid of the process executing the shell. pid -p rints the pid\n"
               "of the shell’s parent process.\n");
    }else if(strcmp(opciones , "chdir") == 0){
        printf("Changes the current working directory of the shell to dir.\n"
               "When invoked without auguments it prints the\n"
               "current working directory \n");
    }else if(strcmp(opciones , "date") == 0){
        printf("Prints the current date in the format DD/MM/YYYY\n");
    }else if(strcmp(opciones , "time") == 0){
        printf("Prints the current time in the format hh:mm:ss.\n");
    }else if(strcmp(opciones , "hist") == 0){
        printf("Shows/clears the historic of commands executed by this shell. In order\n"
               "to do this, a list to store all the commands input to the shell must be\n"
               "implemented. hist -c clears the historic, that’s to say, empties the list\n"
               "– hist Prints all the commands that have been input with their order\n"
               "number\n"
               "– hist -c Clears (empties) the list of historic commands\n"
               "– hist -N Prints the first N commands\n");
    }else if(strcmp(opciones , "command") == 0){
        printf("Repeats command number N (from historic list)\n");
    }else if(strcmp(opciones , "open") == 0){
        printf("Opens a file and adds it (together with the file descriptor and the\n"
               "opening mode to the list of shell open files. For the mode we’ll use cr for\n"
               "O_CREAT, ap for O_APPEND, ex for O_EXCL, ro for O_RDONLY,\n"
               "rw for O_RDWR, wo for O_WRONLY and tr for O_TRUNC. \n");
    }else if(strcmp(opciones , "close") == 0){
        printf("Closes the df file descriptor and eliminates the corresponding item from\n"
               "the list\n");
    }else if(strcmp(opciones , "dup") == 0){
        printf("Duplicates the df file descriptor (using the dup system call, creating the\n"
               "corresponding new entry on the file list\n");
    }else if(strcmp(opciones , "listOpenFiles") == 0){
        printf("Lists the shell open files. For each file it lists its descriptor, the file\n"
               "name and the opening mode. \n");
    }else if(strcmp(opciones , "infosys") == 0){
        printf("Prints information on the machine running the shell (as obtained via\n"
               "the uname system call/library function)\n");
    }else if(strcmp(opciones , "help") == 0){
        printf("help displays a list of available commands. help cmd gives a brief help\n"
               "on the usage of command cmd\n");
    }else if(strcmp(opciones , "quit") == 0 || strcmp(opciones , "bye") == 0 || strcmp(opciones , "exit") == 0){
        printf("Ends the shell\n");
    }else
        perror("Comando Inexistente");
}

void meterDatos(const int* num , char *tr[], tList *hist){
    ///
    char *commName = malloc(sizeof(char*[MAX_TOTAL_COMMAND]));          //SIGABRT se fas unha chamada a un comando q ten caracteres de mais e xusto despois fas un hist
    sprintf(commName , "%d , " , *num );
    for (int i = 0; i < MAX_TOTAL_COMMAND ; ++i) {
        if(tr[i] != NULL){
            strcat(commName, tr[i]);
            strcat(commName, " ");
        }else break;
    }
    add_to_list(hist , commName , *num);

}

void closeShell (bool *fin){
    *fin = true;
}

void whichCommand(char *tr[], tList *histComm , int* commNum , bool* fin , int* recursividad , tList *listOpen){

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
        command(tr , histComm , commNum , fin , recursividad , listOpen);
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
        list();
    else if (strcmp(tr[0] , "delete") == 0)
        delete(tr);
    else if (strcmp(tr[0] , "deltree") == 0)
        deltree(tr);
    else if (strcmp(tr[0], "help") == 0)
        help(tr[1]);
    else if ((strcmp(tr[0], "quit") == 0) || (strcmp(tr[0], "exit") == 0) || (strcmp(tr[0], "bye") == 0))
        closeShell(fin);
    else
        perror("Comando inexistente\n");
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

void procesarEntrada(char c[] , bool *fin , tList *histComm , tList *listOpen){

    char *tr[MAX_TOTAL_COMMAND];


    static int num = 0;
    static int *commNum = &num;

    int controlRecur = 0;
    int *recursividad = &controlRecur;

    int palabras = TrozearCadena(c , tr);
    if(palabras != 0 && palabras != -1){
        num++;
        meterDatos(commNum , tr , histComm);
        whichCommand(tr , histComm , commNum , fin , recursividad , listOpen);
    }else
        if(palabras == -1){                                         //SI CADENA DEMASIADO LARGA COLLEA VARIAS VECES , PURGAR STDIN?
            perror("Cadena demasiado grande");

        }else
            perror("Cadena Vacia");
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
        perror("Imposible crear el fichero");
    }else if(strcmp(tr[1] , "-f") == 0) {
        fl = fopen(tr[2] , "w");
        if (fl == NULL)
            perror("Imposible crear el fichero");
        chmod(tr[2] , m);
    }else{
        df = mkdir(tr[1] , 0777);
        if(df == -1){
            perror("Imposible crear el fichero");
        }
        chmod(tr[1] , 0775);
    }
}

void statSO(char *tr[]){
    char cwd[256];

}

void list(){

}

void delete(char* tr[]){

    if (access(tr[1], F_OK) == 0) {  //Comprobamos que existe el archivo o el directorio
        (rmdir(tr[1]) == 0 || unlink(tr[1]) == 0) ? printf("\n") : perror("ERROR\n");
    }
    else {
        perror("ERROR. El directorio o el archivo no existen\n"); //Si el archivo o el directorio no existe, se lanzara error
    }
}

void deltree(char* tr[]) {
    struct dirent* enter;  //para esto usamos dirent.h
    DIR* directory = opendir(tr[1]);  //abrimos el directorio y los guardamos en un puntero

    if(!directory) {
        perror("ERROR\n");  //Lanzamos error si no se puede abrir el directorio
        return;
    }
    while((enter = readdir(directory))) {  //Recorremos el directorio
        if (strcmp(enter->d_name, ".") == 0 || strcmp(enter->d_name, "..") == 0)
            continue;

        //Accedemos al directorio
        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", tr[1], enter->d_name);  //para ello concatenamos la ruta que teniamos con /"nombre de la carpeta que accedemos"
        char *subtr[] = {NULL, path};

        (enter->d_type == DT_DIR) ? deltree(subtr) : delete(subtr);
        //Si es un directorio, llamamos a deltree para borrar su contenido
        //Si es un archivo, llamamos a delete para eliminarlo

    }
    closedir(directory);  //cerramos el directorio actual
    delete(tr);  //borramos el contenido
}

/*
    if((typeCom != 7) && (strcmp(opciones2 , "@") != 0)){
        º("Opcion de comando '%s' inexistente\n" , opciones2);//⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️
        return;
    }
*/

//si meter mas cousas das necesarias q de error q non pete