/*
Nombre:    Grupo:
Nombre:    Grupo:
*/
/*
 * cambios q estarian chingones:
 *
 * hacer dup de un archivo q se use pero no este en listopen(dup 3 usando valgrind)
 * ser mais preciso a hora de elegir as flags dos 3 archvios abertos , detectalas de algunha forma porq stderr a veces e solo W
*/
#include "cabeceras.h"

void procesarEntrada(char c[] , bool *fin , tList *histComm , tList *listOpen , tList *listBlocks , tList *listProcss , int argc , char *argv[] , char *env[] , tList *evitarLeaks){

    char *tr[MAX_TOTAL_COMMAND];

    static int num = 0;
    static int *commNum = &num;

    int controlRecur = 0;
    int *recursividad = &controlRecur;

    int palabras = TrozearCadena(c , tr);
    if(palabras != 0 && palabras != -1){
        num++;
        meterDatos(commNum , tr , histComm);
        whichCommand(tr , histComm , commNum , fin , recursividad , listOpen , listBlocks , listProcss , argc , argv , env , evitarLeaks);
    }else
    if(palabras == -1){                                         //SI CADENA DEMASIADO LARGA COLLEA VARIAS VECES , PURGAR STDIN?
        printf("Cadena demasiado grande");

    }else
        printf("Cadena Vacia\n");
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

void closeShell (bool *fin){
    *fin = true;
}

void whichCommand(char *tr[], tList *histComm , int* commNum , bool* fin , int* recursividad , tList *listOpen , tList *listBlocks , tList *listProcss , int argc , char *argv[] , char *env[] , tList *evitarLeaks){

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
        command(tr , histComm , commNum , fin , recursividad , listOpen , listBlocks , listProcss , argc , argv , env , evitarLeaks);
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
    else if (strcmp(tr[0] , "mmap") == 0)
        mmapSO(tr , listBlocks);
    else if (strcmp(tr[0] , "read") == 0)
        readSO(tr);
    else if (strcmp(tr[0] , "write") == 0)
        writeSO(tr);
    else if (strcmp(tr[0] , "mem") == 0)
        mem(tr , listBlocks);
    else if (strcmp(tr[0] , "memfill") == 0)
        memFill(tr);
    else if (strcmp(tr[0] , "recurse") == 0)
        recurse(tr);
    else if (strcmp(tr[0] , "memdump") == 0)
        memdump(tr);
    else if (strcmp(tr[0] , "fork") == 0)
        forkSO(tr , listProcss);
    else if (strcmp(tr[0] , "uid") == 0)
        uid(tr);
    else if (strcmp(tr[0] , "showvar") == 0)
        showvar(tr , argc , argv , env);
    else if (strcmp(tr[0] , "showenv") == 0)
        showenv(tr , env);
    else if (strcmp(tr[0] , "changevar") == 0)
        changevar(tr , env , evitarLeaks);
    else if (strcmp(tr[0] , "subsvar") == 0)
        subsvar(tr , env , evitarLeaks);
    else if (strcmp(tr[0] , "exec") == 0)
        executar(tr);
    else if (strcmp(tr[0] , "jobs") == 0)
        jobsSO(listProcss);
    else if (strcmp(tr[0] , "deljobs") == 0)
        deljobs(tr , listProcss);
    else if (strcmp(tr[0], "job") == 0)
        jobSO(tr, listProcss , evitarLeaks);
    else if ((strcmp(tr[0], "quit") == 0) || (strcmp(tr[0], "exit") == 0) || (strcmp(tr[0], "bye") == 0))
        closeShell(fin);
    else
        ramaFin(tr , listProcss , evitarLeaks);
}

void authors(char opciones[]){
    if(opciones == NULL){

        printf("Logins: \t Si oh \t ahora mismo chos digo \n");
        printf("Nombres: \t non ah oh \t mamala \n");

    }else if(strcmp(opciones , "-l") == 0){

        printf("Logins: \t Si oh \t ahora mismo chos digo \n");

    }else if(strcmp(opciones , "-n") == 0){

        printf("Nombres: \t non ah oh \t mamala \n");

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

void command (char *tr[] , tList *histComm , int* commNum , bool* fin , int* recursividad , tList *listOpen , tList *listBlocks , tList *listProcss , int argc , char *argv[] , char* env[] , tList *evitarLeaks){

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
        whichCommand(tr ,  histComm , commNum , fin , recursividad , listOpen , listBlocks , listProcss , argc , argv , env , evitarLeaks);
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

void help (char opciones[]){

    if (opciones == NULL){
        printf("Avaliable commands: \n authors [-l|-n] \n pid [-p] \n chdir [dir] \n date \n time \n hist [-c|-N] \n command N \n open [file] mode \n "
               "close [df] \n dup [df] \n listopen \n infosys \n create [-f] [name] \n list [-reca] [-recb] [-hid][-long][-link][-acc] n1 n2 .. \n"
               " stat [-long][-link][-acc] name1 name2 .. \n delete [name1 name2 ..] \n deltree [name1 name2 ..] \n help [cmd] \n malloc [-free] \n"
               " shared [-free|-create|-delkey] cl [tam] \n mmap [-free] fich prm \n read fich addr cont \n write [-o] fiche addr cont \n memdump addr cont \n"
               " memfill addr cont byte \n mem [-blocks|-funcs|-vars|-all|-pmap] ..\n recurse [n]\n uid [-get|-set] [-l] [id]\n showvar var\n changevar [-a|-e|-p] var valor \n"
               " subsvar [-a|-e] var1 var2 valor \n showenv [-environ|-addr] \n fork \n exec VAR1 VAR2 ..prog args....[@pri] \n jobs \n deljobs [-term][-sig] \n "
               "job [-fg] pid \n quit \n exit \n bye \n");
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
    }else if(strcmp(opciones, "malloc") == 0){
        printf("malloc [-free] [tam]    allocates a memory block of size tam with malloc \n"
               "\t-free: deallocate a memory block of size allocated with malloc\n ");
    }else if(strcmp(opciones, "shared") == 0){
        printf("shared [-free|-create|-delkey] cl [tam] allocates shared memory with cl key in program \n"
               "\t-create cl tam: allocates (creating) the shared memory block of key cl and size tam \n"
               "\t-free cl: unmap cl key shared memory block \n"
               "\t-delkey cl: removes from the system (without unmapping) the memory key cl\n");
    }else if(strcmp(opciones, "mmap") == 0) {
        printf("mmap [-free] fich prm   maps the fich file with prm permissions \n"
               "\t-free fich: unmap the file\n");
    }else if (strcmp(opciones, "read") == 0) {
        printf("read fich addr cont    Read cont bytes from fich to address addr\n");
    }else if (strcmp(opciones, "write") == 0) {
        printf("write [-o] fiche addr cont  Write cont bytes from address addr to file (-o overwrite)\n");
    }else if(strcmp(opciones, "memdump") == 0){
        printf("memdump addr cont  Dumps the contents (cont bytes) of the addr memory location on screens\n");
    }else if(strcmp(opciones, "memfill") == 0){
        printf("memfill addr cont byte  Fill memory from addr with byte\n");
    }else if(strcmp(opciones, "mem") == 0){
        printf("mem [-blocks|-funcs|-vars|-all|-pmap] ..    Same shows process memory details\n"
               "\t-blocks: the allocated memory blocks\n"
               "\t-funcs: the addresses of the functions\n"
               "\t-vars: the addresses of the variable\n"
               "\t-all: everything\n"
               "\t-pmap: show the output of the pmap command (or similar)\n");
    }else if(strcmp(opciones, "recurse") == 0){
        printf("recurse[n]  Call the recursive function n times\n");
    }else if (strcmp(opciones, "uid") == 0){
        printf("uid [-get|-set] [-l] [id]   Access the credentials of the process that runs the shell\n"
               "\t-get: show credentials\n"
               "\t-set id: sets the credential to the numerical value id\n"
               "\t-set -l id: set the credential to login id\n");
    }else if (strcmp(opciones, "showvar") == 0) {
        printf("showvar var    Displays the value and addresses of the var environment variable\n");
    }else if (strcmp(opciones, "changevar") == 0) {
        printf("changevar [-a|-e|-p] var valor  Change the value of an enviroment variable\n"
               "\t-a: access throught the third arg of main\n"
               "\t-e: access via environ\n"
               "\t-p: access via putenv\n");
    }else if (strcmp(opciones, "subsvar") == 0){
        printf("subsvar [-a|-e] var1 var2 valor     Replaces the var1 environment variable with var2=value\n"
               "\t-a: access through the third arg of main\n"
               "\t-e: access via environ\n");
    }else if (strcmp(opciones, "showenv") == 0) {
        printf("showenv [-environ|-addr]   Shows the process environment\n"
               "\t-environ: access using environ (instead of the third arg of main)\n"
               "\t-addr: show the value and where environ and the 3rd arg main are stored\n");
    }else if(strcmp(opciones, "fork") == 0){
        printf("fork    The shell forks and waits for its child to finish\n");
    }else if (strcmp(opciones, "exec") == 0) {
        printf("exec VAR1 VAR2 ..prog args....[@pri]   Execute, without creating a process, a prog with arguments in an environment\n"
               "that contains only the variables VAR1, VAR2...\n ");
    }else if (strcmp(opciones, "jobs") == 0) {
        printf("jobs    List background processes\n");
    }else if (strcmp(opciones, "deljobs") == 0){
        printf("deljobs [-term][-sig]   Remove processes from the processes list in sp\n"
               "\t-term: the finished ones\n"
               "\t-sig: those terminated by signal\n");
    }else if (strcmp(opciones, "job") == 0){
        printf("job [-fg] pid   Shows information about the pid process\n"
               "\t-fg: brings it to the foreground\n");
    }else if(strcmp(opciones , "quit") == 0 || strcmp(opciones , "bye") == 0 || strcmp(opciones , "exit") == 0){
        printf("Ends the shell\n");
    }
    else
        printf("Comando Inexistente\n");
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
            printf("error al acceder a %s : %s\n" , tr[name] , strerror(errno));
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
        if(strcmp(tr[1] , "-free") == 0){
            if(tr[2] != NULL){
                long search = atoi(tr[2]);
                tPos f;
                for(f = first(*listBlocks) ; f != NULL ; f = next(f , *listBlocks) ){
                    if(f->dfORCommNUm == search){
                        bloque *bloqueFree = f->data;
                        if(strcmp("malloc" , bloqueFree->typeOfAlloc) == 0){
                            free(bloqueFree->address);
                            remove_from_list(listBlocks , f);
                            return;
                        }
                    }
                }
                printf("No hay bloque de ese tamano asignado con malloc \n");
            }else
                printListBlocks(*listBlocks , "malloc" , printStructs);

        }else if (atoi(tr[1]) <= 0){
            printf("Cantidad de memoria a asignar inválida\n");
        }else if (atoi(tr[1]) > 0){
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
            bloque1->other[0] = '\0';
            snprintf(bloque1->fileName, sizeof(char[MAX_NAME_LENGTH]) , " ");
            add_Struct_to_list(listBlocks , bloque1 , tam);//metemos tamaño en numero de orden de lista para poder usar finditem
            printf("Asignados %ld bytes en %p\n" , tam , bloque1->address);
            free(bloque1);
        }else{
            printListBlocks(*listBlocks , "malloc" , printStructs);
        }
    }else{
        printListBlocks(*listBlocks , "malloc" , printStructs);
    }
}

void * ObtenerMemoriaShmget (key_t clave, size_t tam , tList *listBlocks){
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;
    bloque *bloque1 = malloc(sizeof (bloque));

    if (tam)     /*tam distito de 0 indica crear */
        flags = flags | IPC_CREAT | IPC_EXCL;
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
    snprintf(bloque1->fileName, sizeof(char[MAX_NAME_LENGTH]) , " ");
    add_Struct_to_list(listBlocks , bloque1 , clave);
    free(bloque1);
    return (p);
}

void do_AllocateCreateshared (char *tr[] , tList *listBlocks){
    key_t cl;
    size_t tam;
    void *p;

    if (tr[2]==NULL || tr[3]==NULL) {
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

void do_DeallocateDelkey (char *args[]){
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
        perror ("shmctl: imposible eliminar id de memoria compartida\n");
}

void * sinparam (key_t clave, size_t tam , tList *listBlocks){
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;
    bloque *bloque1 = malloc(sizeof (bloque));

    if (tam)     /*tam distito de 0 indica crear */
        flags = flags | IPC_CREAT | IPC_EXCL;
    if (clave==IPC_PRIVATE)  /*no nos vale*/
    {errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1){  //AÑADIDO
        if(errno == EEXIST) {  // Se xa existe, obtemos o ID do segmento existente
            id = shmget(clave, 0, 0);
        }
        else {
            return (NULL);
        }
    }

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
    snprintf(bloque1->fileName, sizeof(char[MAX_NAME_LENGTH]) , " ");
    add_Struct_to_list(listBlocks , bloque1 , clave);
    free(bloque1);
    return (p);
}
///optimizado penosamente
void do_Allocate (char *tr[] , tList *listBlocks){
    key_t cl;
    size_t tam = 0;
    void *p;

    if (tr[1]==NULL) {
        printListBlocks(*listBlocks , "shared" , printStructs);
        return;
    }

    cl = (key_t)  strtoul(tr[1],NULL,10);
    if ((p=sinparam(cl,tam,listBlocks))!=NULL)
        printf ("Memoria compartida de clave %d en %p\n", cl , p);
    else
        printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}

void shared(char* tr[] , tList *listBlocks){//usar comando ipcs para ver como aparecen y desaparecen
    if(tr[1] != NULL){
        if (strcmp(tr[1] , "-create") == 0 ){
            do_AllocateCreateshared(tr , listBlocks);
        }else if(strcmp(tr[1] , "-free") == 0){
            if(tr[2] != NULL){
                long search = atoi(tr[2]);
                tPos f;
                for(f = first(*listBlocks) ; f != NULL ; f = next(f , *listBlocks) ){
                    if(f->dfORCommNUm == search){
                        bloque *bloqueFree = f->data;
                        if(strcmp("shared" , bloqueFree->typeOfAlloc) == 0){
                            shmdt(bloqueFree->address);
                            remove_from_list(listBlocks , f);
                            return;
                        }
                    }
                }
            }
            printf("No hay bloque de ese tamano asignado con shared \n");
        }else if(strcmp(tr[1] , "-delkey") == 0) {
            do_DeallocateDelkey(tr);
        }else{
            do_Allocate(tr , listBlocks); //falta q para shared de n o tamaño se eliga correctamente solo
        }
    }else{
        printListBlocks(*listBlocks , "shared" , printStructs);
    }
}

ssize_t EscribirFichero (char *f, void *p, size_t cont, int overwrite){
    ssize_t  n;
    int df,aux, flags=O_CREAT | O_EXCL | O_WRONLY;

    if (overwrite)
        flags=O_CREAT | O_WRONLY | O_TRUNC;

    if ((df=open(f,flags,0777))==-1)
        return -1;

    if ((n=write(df,p,cont))==-1){
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }
    close (df);
    return n;
}

void writeSO(char *ar[]) {
    if (ar[1] == NULL || ar[2] == NULL || ar[3] == NULL) {  // comprobamos se non pasan -o, o nome do ficheiro, tamaño
        printf("faltan parametros\n");                      // ou si pasan o nome do archivo, tamaño e cnt
        return;
    }

    char *fileName;
    void *address;
    int overwrite = 0;  //Usaremolo para saber se se sobrescribe o ficheiro -o
    size_t count = -1;  //Cantidade de bytes a escribir, inicializada a -1 para indicar ler T0D0 o contido

    if (strcmp(ar[1], "-o") == 0) {
        fileName = ar[2];
        address = (void *)strtoull(ar[3], NULL, 16);
        if (ar[4] != NULL) {
            count = (size_t)atoll(ar[4]);
        }
        overwrite = 1;
    } else {  //Igual que o anterior pero como non se fai sobrescritura, os datos tan unha posicion antes
        fileName = ar[1];
        address = (void *)strtoull(ar[2], NULL, 16);
        if (ar[3] != NULL) {
            count = (size_t)atoll(ar[3]);
        }
    }

    ssize_t writtenBytes = EscribirFichero(fileName, address, count, overwrite);

    if (writtenBytes == -1) {
        perror("Imposible escribir en el fichero");
    } else {
        printf("escritos %lld bytes en %s desde %p\n", (long long)writtenBytes, fileName, address);
    }
}

ssize_t LeerFichero (char *f, void *p, size_t cont){
    struct stat s;
    ssize_t  n;
    int df,aux;

    if (stat (f,&s)==-1 || (df=open(f,O_RDONLY))==-1)
        return -1;
    if (cont==-1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
        cont=s.st_size;
    if ((n=read(df,p,cont))==-1){
        aux=errno;
        close(df);
        errno=aux;
        return -1;
    }

    close (df);
    return n;
}

void readSO (char *ar[]){
    void *p;
    size_t cont=-1;  /* -1 indica leer T0D0 el fichero*/
    ssize_t n;
    if (ar[1]==NULL || ar[2]==NULL){
        printf ("faltan parametros\n");
        return;
    }
    p=(void*) strtoull(ar[2],NULL,16);  /*convertimos de cadena a puntero*/
    if (ar[3]!=NULL)
        cont=(size_t) atoll(ar[3]);

    if ((n=LeerFichero(ar[1],p,cont))==-1)
        perror ("Imposible leer fichero");
    else
        printf ("leidos %lld bytes de %s en %p\n",(long long) n,ar[1],p);
}

void * MapearFichero (char * fichero, int protection , tList *listBlocks){
    int df, map=MAP_PRIVATE,modo=O_RDONLY;
    struct stat s;
    void *p;

    if (protection&PROT_WRITE)
        modo=O_RDWR;
    if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1)
        return NULL;
    if ((p=mmap (NULL,s.st_size,protection,map,df,0))==MAP_FAILED)
        return NULL;
    bloque *bloque1 = malloc(sizeof (bloque));
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char hora[100];
    strftime(hora, 100, "%m %d %H:%M", tm);
    bloque1->address = p;
    bloque1->typeOfAlloc = "mmap";
    snprintf(bloque1->timeAlloc, sizeof(char[MAX_NAME_LENGTH]) , "%s" , hora);
    bloque1->size = s.st_size;
    snprintf(bloque1->other, sizeof(char[MAX_NAME_LENGTH]) , "(descriptor %d)" , df);
    snprintf(bloque1->fileName, sizeof(char[MAX_NAME_LENGTH]) , "%s" , fichero);
    add_Struct_to_list(listBlocks , bloque1 , df);//descriptor para rellenar , en este caso no se usará para elegir el correcto
    free(bloque1);
    return p;
}

void do_AllocateMmap(char *arg[] , tList *listBlocks){
    char *perm;
    void *p;
    int protection=0;

    if (arg[1]==NULL){
        printListBlocks(*listBlocks , "mmap" , printStructs);
        return;
    }
    if ((perm=arg[2])!=NULL && strlen(perm)<4) {
        if (strchr(perm,'r')!=NULL) protection|=PROT_READ;
        if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
        if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
    }
    if ((p=MapearFichero(arg[1],protection,listBlocks))==NULL)
        perror ("Imposible mapear fichero");
    else
        printf ("fichero %s mapeado en %p\n", arg[1], p);
}

void mmapSO (char* tr[] , tList *listBlocks){
    if(tr[1] != NULL){
        if(strcmp("-free" , tr[1]) == 0){
            if(tr[2] == NULL){
                printListBlocks(*listBlocks , "mmap" , printStructs);
                return;
            }
            tPos f;
            for(f = first(*listBlocks) ; f != NULL ; f = next(f , *listBlocks) ){
                bloque *bloqueFree = f->data;
                if(strcmp("mmap" , bloqueFree->typeOfAlloc) == 0){
                    if(strcmp(tr[2] , bloqueFree->fileName) == 0){
                        close(f->dfORCommNUm);
                        munmap(bloqueFree->address , bloqueFree->size);
                        remove_from_list(listBlocks , f);
                        return;
                    }
                }
            }
            printf("Fichero %s no mapeado\n" , tr[2]);
        }else{
            do_AllocateMmap(tr , listBlocks);
        }
    }else{
        printListBlocks(*listBlocks , "mmap" , printStructs);
    }
}

void Do_pmap (void){ //sin argumentos
    pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
    char elpid[32];
    char *argv[4]={"pmap",elpid,NULL};

    sprintf (elpid,"%d", (int) getpid());
    if ((pid=fork())==-1){
        perror ("Imposible crear proceso");
        return;
    }
    if (pid==0){
        if (execvp(argv[0],argv)==-1)
            perror("cannot execute pmap (linux, solaris)");

        argv[0]="procstat"; argv[1]="vm"; argv[2]=elpid; argv[3]=NULL;
        if (execvp(argv[0],argv)==-1)/*No hay pmap, probamos procstat FreeBSD */
            perror("cannot execute procstat (FreeBSD)");

        argv[0]="procmap",argv[1]=elpid;argv[2]=NULL;
        if (execvp(argv[0],argv)==-1)  /*probamos procmap OpenBSD*/
            perror("cannot execute procmap (OpenBSD)");

        argv[0]="vmmap"; argv[1]="-interleave"; argv[2]=elpid;argv[3]=NULL;
        if (execvp(argv[0],argv)==-1) /*probamos vmmap Mac-OS*/
            perror("cannot execute vmmap (Mac-OS)");
        exit(1);
    }
    waitpid (pid,NULL,0);
}

int var_glob_Ini1 = 0;
char var_glob_Ini2= 'B';
long var_glob_Ini3 = 2;
int var_glob_N_Ini1;
char var_glob_N_Ini2;
long var_glob_N_Ini3;

void mem(char* tr[] , tList *listBlocks){
    int var1 = 500;
    char var2 = 'A';
    long var3 = 501;
    static int stat1 = 16;
    static char stat2 = 'Z';
    static long stat3 = 17;
    static int stat_N_1;
    static char stat_N_2;
    static long stat_N_3;
    bool all = false;
    if((tr[1] == NULL) || (strcmp(tr[1] , "-all") == 0)){
        all = true;
    }
    if(all || strcmp(tr[1] , "-vars") == 0){
        printf("Variables locales  %p, %p, %p\n" , &var1 , &var2 , &var3);
        printf("Variables globales %p, %p, %p\n" , &var_glob_Ini1 , &var_glob_Ini2 , &var_glob_Ini3);
        printf("Var (N.I.)globales %p, %p, %p\n" , &var_glob_N_Ini1 , &var_glob_N_Ini2 , &var_glob_N_Ini3);
        printf("Variables staticas %p, %p, %p\n" , &stat1 , &stat2 , &stat3);
        printf("Var (N.I.)staticas %p, %p, %p\n" , &stat_N_1 , &stat_N_2 , &stat_N_3);
        if(!all) return;
    }
    if(all || strcmp(tr[1] , "-funcs") == 0){
        printf("Funciones programa %p, %p, %p\n" , &procesarEntrada , &printListBlocks , &whichCommand);
        printf("Funciones libreria %p, %p, %p\n" , &printf , &getpid , &getcwd);
        if(!all) return;
    }
    if(all || strcmp(tr[1] , "-blocks") == 0){
        printALLListBlocks(*listBlocks,  printStructs);
        return;
    }
    if(strcmp(tr[1] , "-pmap") == 0){
        Do_pmap();
        return;
    }
    printf("Opcion %s no contamplada\n" , tr[1]);
}

void LlenarMemoria (void *p, size_t cont, unsigned char byte){
    unsigned char *arr=(unsigned char *) p;
    size_t i;
    printf("Llenando %zu bytes de memoria con el byte %c(%X) a partir de la direccion %p\n" , cont , byte , byte , p);
    for (i=0; i<cont ;i++)
        arr[i] = byte;
}

void memFill(char* tr[]){
    void *p;
    size_t bytes;
    int byte;
    if(tr[1] != NULL){
        if(tr[2] != NULL){
            if (tr[3] != NULL){
                p =(void*) strtoul( tr[1] , NULL , 16);
                bytes = strtol(tr[2] , NULL , 10);
                byte = atoi(tr[3]);
                LlenarMemoria(p , bytes , (char)byte);
                return;
            }
            p =(void*) strtoul( tr[1] , NULL , 16);
            bytes = strtol(tr[2] , NULL , 10);
            byte = 'A';
            LlenarMemoria(p , bytes , byte);
            return;
        }
        p =(void*) strtoul( tr[1] , NULL , 16);
        bytes = 128;
        byte = 'A';
        LlenarMemoria(p , bytes , byte);
    }
}

void Recursiva (int n){
    char automatico[TAMANO];
    static char estatico[TAMANO];
    printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico);
    if (n>0)
        Recursiva(n-1);
}

void recurse(char* tr[]){
    if(tr[1] != NULL){
        int itera;
        itera = atoi(tr[1]);
        Recursiva(itera);
    }
}

void memdump(char *tr[]) {
    if(tr[1] == NULL)
        return;
    int cont = 25;
    void* p = (void*) strtoul( tr[1] , NULL , 16);
    unsigned char * addr = (unsigned char *) p;
    unsigned char c;

    if(tr[2] != NULL && atoi(tr[2]) >= 0){
        cont = atoi(tr[2]);
    }else
        cont = 25;
    printf("Volcando %d bytes desde la direcion %p\n" , cont , p);
    while(cont != 0){
        if(cont >= 25){
            for (int j = 0; j < 25 ; ++j) {
                c = addr[j];
                if(c >= 0x20 && c < 0x7f){
                    printf(" %2c " , c);
                }else{
                    printf("  ");
                }
            }
            printf("\n");
            for (int j = 0; j < 25; ++j) {
                printf(" %02X " , *addr);
                addr += 1;
            }
            printf("\n");
            cont -= 25;
        }else{
            for (int j = 0; j < cont ; ++j) {
                c = addr[j];
                if(c >= 0x20 && c < 0x7f){
                    printf(" %2c " , c);
                }else{
                    printf("  ");
                }
            }
            printf("\n");
            for (int j = 0; j < cont; ++j) {
                printf(" %02X " , *addr);
                addr += 1;
            }
            printf("\n");
            cont -= cont;
        }
    }
}

void forkSO(char *tr[] , tList *listProcss){
    pid_t pid;
    if ((pid=fork())==0){
        delete_list(listProcss);
        printf ("ejecutando proceso %d\n", getpid());
    }
    else if (pid!=-1) {
        waitpid(pid, NULL, 0);
    }
}

void uid(char *tr[]){//a hora de imprimir imprime mal o nombre ¿talvez?
    int id;
    uid_t uid , euid;
    uid = getuid();
    euid = geteuid();
    struct passwd *userReal;
    struct passwd *userEfectivo;
    userReal = getpwuid(uid);
    userEfectivo = getpwuid(euid);
    if(tr[1] != NULL){
        if(strcmp(tr[1] , "-get") == 0){
            printf("Credencial real: %d, (%s)\n" , uid , userReal->pw_name);
            printf("Credencial efectiva: %d, (%s)\n" , euid , userEfectivo->pw_name);
        }else if(strcmp(tr[1] , "-set") == 0){
            if(tr[2] != NULL){
                if(strcmp(tr[2] , "-l") == 0){
                    if(tr[3] != NULL){
                        struct passwd *idDesdeLogin;
                        idDesdeLogin = (getpwnam(tr[3]));
                        if(idDesdeLogin != NULL){
                            if(setuid(idDesdeLogin->pw_uid) == -1){
                                perror("Error al cambiar credencial efectiva\n");
                            }
                        }else
                            printf("Usuario no existente %s\n" , tr[3]);
                    }
                }else{
                    id = atoi(tr[2]);
                    if(setuid(id) == -1){
                        perror("Error al cambiar credencial efectiva\n");
                    }
                }
            }
        }else{
            printf("Credencial real: %d, (%s)\n" , uid , userReal->pw_name);
            printf("Credencial efectiva: %d, (%s)\n" , euid , userEfectivo->pw_name);
        }
    }else{
        printf("Credencial real: %d, (%s)\n" , uid , userReal->pw_name);
        printf("Credencial efectiva: %d, (%s)\n" , euid , userEfectivo->pw_name);
    }
}
//declarado environ en lista.h
int BuscarVariable (char * var, char *e[]) {/*busca una variable en el entorno que se le pasa como parámetro*/
    int pos=0;
    char aux[MAXNAMLEN];

    strcpy (aux,var);
    strcat (aux,"=");

    while (e[pos]!=NULL)
        if (!strncmp(e[pos],aux,strlen(aux)))
            return (pos);
        else
            pos++;
    errno=ENOENT;   /*no hay tal variable*/
    return(-1);
}

void MuestraEntorno (char **entorno, char * nombre_entorno) {
    int i = 0;
    while (entorno[i]!=NULL) {
        printf ("%p->%s[%d]=(%p) %s\n", &entorno[i] , nombre_entorno, i ,entorno[i],entorno[i]);
        i++;
    }
}

void showvar(char *tr[] , int argc , char *argv[] , char *env[]) {
    if(tr[1] != NULL){
        int posArg3 , posEnviron;
        posArg3 = BuscarVariable(tr[1] , env);
        posEnviron = BuscarVariable(tr[1] , environ);
        if(posArg3 != -1)
            printf("Con arg3 main %s(%p) @%p\n" , env[posArg3] , env[posArg3] , &env[posArg3]);
        if(posEnviron != -1)
            printf("Con environ %s(%p) @%p\n" , environ[posEnviron] , environ[posEnviron] , &environ[posEnviron]);
        if(getenv(tr[1]) != NULL)
            printf("Con getenv %s(%p)\n" , getenv(tr[1]) , getenv(tr[1]));
    }else{
        MuestraEntorno(env , "main arg3");//O TERCEIRO ARGUMENTO DO MAIN COMUENMENTE CHAMASE ENVP (en este caso env porq se me olvidou poñer a p)
    }
}

void showenv(char* tr[] , char *env[]){
    if(tr[1] != NULL) {
        if (strcmp(tr[1], "-environ") == 0){
            MuestraEntorno(environ , "environ");
        }else if(strcmp(tr[1] , "-addr") == 0){
            printf("environ:   %p (almacenado en %p)\n" , environ , &environ );
            printf("main arg3: %p (almacenado en %p)\n" , env , &env );
        }else
            printf("Uso: showenv [-environ|-addr]\n");
    }else{
        MuestraEntorno(env , "main arg3");//terceiro argumento main , nombrado comunmente envp / env
    }
}

int CambiarVariable(char * var, char * valor, char *e[] , tList *evitarLeaks) { /*cambia una variable en el entorno que se le pasa como parámetro*/
    /*lo hace directamente, no usa putenv*/
    int pos;
    char *aux;

    if ((pos=BuscarVariable(var,e))==-1)
        return(-1);

    if ((aux=(char *)malloc(strlen(var)+strlen(valor)+2))==NULL)
        return -1;

    strcpy(aux,var);
    strcat(aux,"=");
    strcat(aux,valor);
    e[pos]=aux;
    add_address_to_list(evitarLeaks , aux);
    return (pos);
}

void changevar(char *tr[] , char *env[] , tList *evitarLeaks){
    if((tr[1] != NULL)&&(tr[2] != NULL)&&(tr[3] != NULL)){
        char *string = malloc(sizeof (char *));
        add_address_to_list(evitarLeaks , string);
        if(strcmp(tr[1] , "-a") == 0){
            if(CambiarVariable(tr[2] , tr[3] , env , evitarLeaks) == -1)
                perror("Imposible cambiar variable\n");
        }else if(strcmp(tr[1] , "-e") == 0){
            if(CambiarVariable(tr[2] , tr[3] , environ , evitarLeaks) == -1)
                perror("Imposible cambiar variable\n");
        }else if(strcmp(tr[1] , "-p") == 0){
            sprintf(string , "%s=%s" , tr[2] , tr[3]);
            if(putenv(string) != 0)
                perror("Error en putenv\n");
        }else{
            printf("Uso: changevar [-a|-e|-p] var valor\n");
        }
    }else
        printf("Uso: changevar [-a|-e|-p] var valor\n");
}

void subsvar(char *tr[] , char* env[] , tList *evitarLeaks){
    if((tr[1] != NULL) && (tr[2] != NULL) && (tr[3] != NULL) && (tr[4] != NULL)){
        char* sol = malloc(sizeof (char *));
        add_address_to_list(evitarLeaks , sol);
        int esteDebeExistir = -1;
        int esteNo = -1;
        if(strcmp(tr[1] , "-e") == 0){
            esteDebeExistir = BuscarVariable(tr[2] , environ);
            if(errno != 0){
                printf("Imposible substituir %s por %s:" , tr[2] , tr[3]);
                perror(" ");
                printf("\n");
            }
            esteNo = BuscarVariable(tr[3] , environ);
            if(esteNo == -1){
                sprintf(sol , "%s=%s" , tr[3] , tr[4]);
                environ[esteDebeExistir] = sol;
            }else{
                printf("Imposible substituir %s por %s , ambos existen ya" , tr[2] , tr[3]);
            }
        }else if(strcmp(tr[1] , "-a") == 0){
            esteDebeExistir = BuscarVariable(tr[2] , env);
            if(errno != 0){
                printf("Imposible substituir %s por %s:" , tr[2] , tr[3]);
                perror(" ");
                printf("\n");
            }
            esteNo = BuscarVariable(tr[3] , env);
            if(esteNo == -1){
                sprintf(sol , "%s=%s" , tr[3] , tr[4]);
                env[esteDebeExistir] = sol;
            }else{
                printf("Imposible substituir %s por %s , ambos existen ya" , tr[2] , tr[3]);
            }
        }else
            printf("Uso: subsvar [-a|-e] var valor\n");
    }else
        printf("Uso: subsvar [-a|-e] var valor\n");
}

void executar(char* tr[]){
    if(tr[1] != NULL){
        char *args[25];
        for (int i = 1; tr[i] != NULL; ++i) {
            args[i-1] = tr[i];
            args[i] = NULL;
        }
        if(execvp(tr[1] , args) == -1)
            perror("Imposible ejecutar\n");
    }
}

void ramaFin(char *tr[] , tList *listProcss , tList *evitarLeaks){//usar man en segundo plano malo
    if(tr[0] != NULL){
        pid_t pid , w;
        int wstatus;
        char *args[256] = {NULL};
        bool plano = false;
        int i, aux = 0;

        for (i = 0; tr[i] != NULL; ++i) {
            if (strcmp(tr[i], "&") == 0) {
                plano = true;
                aux = -1;
            } else {
                args[i + aux] = tr[i];
                args[i + 1 + aux] = NULL;
            }
        }

        if(plano){
            int childPID;
            childPID = fork();
            if(childPID == 0) {
                if(execvp(tr[0] , args) == -1){
                    perror("Error al ejecutar");
                    exit(EXIT_FAILURE);
                }
            }

            job *proceso = malloc(sizeof (struct job));
            if (!proceso) {  ///Comprobacion
                perror("Fallo en malloc para proceso");
                return;
            }

            size_t total_length = 0;
            for(i = 0; args[i] != NULL; i++) {
                total_length += strlen(args[i]) + 1; /// +1 para espacio o nulo
            }

            char *lineaComm = malloc(total_length);
            if (!lineaComm) {  ///Comprobacion
                perror("Fallo en malloc para lineaComm");
                free(proceso);
                return;
            }
            strcpy(lineaComm, args[0]);
            for (i = 1; args[i] != NULL; i++) {
                strcat(lineaComm, " ");
                strcat(lineaComm, args[i]);
            }

            proceso->pid = childPID;
            proceso->user = getlogin();
            time_t tiempo;
            time(&tiempo);
            proceso->create = localtime(&tiempo);
            proceso->status = "ACTIVE";
            proceso->program = lineaComm;
            proceso->senial = "000";
            add_process_to_list(listProcss , proceso , childPID);
            add_address_to_list(evitarLeaks, lineaComm);
            free(proceso);

        }else{
            if((pid = fork()) == 0){
                if(execvp(tr[0] , args) == -1){
                    perror("Error al ejecutar");
                    exit(EXIT_FAILURE);
                }
            }else{
                do {
                    w = waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
                    if (w == -1) {
                        perror("Waitpid:");
                        exit(EXIT_FAILURE);
                    }
                } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
            }
        }
    }
}

static struct SEN sigstrnum[]={
        {"HUP", SIGHUP},
        {"INT", SIGINT},
        {"QUIT", SIGQUIT},
        {"ILL", SIGILL},
        {"TRAP", SIGTRAP},
        {"ABRT", SIGABRT},
        {"IOT", SIGIOT},
        {"BUS", SIGBUS},
        {"FPE", SIGFPE},
        {"KILL", SIGKILL},
        {"USR1", SIGUSR1},
        {"SEGV", SIGSEGV},
        {"USR2", SIGUSR2},
        {"PIPE", SIGPIPE},
        {"ALRM", SIGALRM},
        {"TERM", SIGTERM},
        {"CHLD", SIGCHLD},
        {"CONT", SIGCONT},
        {"STOP", SIGSTOP},
        {"TSTP", SIGTSTP},
        {"TTIN", SIGTTIN},
        {"TTOU", SIGTTOU},
        {"URG", SIGURG},
        {"XCPU", SIGXCPU},
        {"XFSZ", SIGXFSZ},
        {"VTALRM", SIGVTALRM},
        {"PROF", SIGPROF},
        {"WINCH", SIGWINCH},
        {"IO", SIGIO},
        {"SYS", SIGSYS},
/*senales que no hay en todas partes*/
#ifdef SIGPOLL
        {"POLL", SIGPOLL},
#endif
#ifdef SIGPWR
        {"PWR", SIGPWR},
#endif
#ifdef SIGEMT
        {"EMT", SIGEMT},
#endif
#ifdef SIGINFO
        {"INFO", SIGINFO},
#endif
#ifdef SIGSTKFLT
        {"STKFLT", SIGSTKFLT},
#endif
#ifdef SIGCLD
        {"CLD", SIGCLD},
#endif
#ifdef SIGLOST
        {"LOST", SIGLOST},
#endif
#ifdef SIGCANCEL
        {"CANCEL", SIGCANCEL},
#endif
#ifdef SIGTHAW
        {"THAW", SIGTHAW},
#endif
#ifdef SIGFREEZE
        {"FREEZE", SIGFREEZE},
#endif
#ifdef SIGLWP
        {"LWP", SIGLWP},
#endif
#ifdef SIGWAITING
        {"WAITING", SIGWAITING},
#endif
        {NULL,-1},
};    /*fin array sigstrnum */

int ValorSenal(char * sen) {
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (!strcmp(sen, sigstrnum[i].nombre))
            return sigstrnum[i].senal;              /*devuelve el numero de senial a partir del nombre*/
    return -1;
}

char *NombreSenal(int sen) {			            /* para sitios donde no hay sig2str*/
    int i;
    for (i=0; sigstrnum[i].nombre!=NULL; i++)
        if (sen==sigstrnum[i].senal)
            return sigstrnum[i].nombre;
    return ("SIGUNKNOWN");                           /*devuelve el nombre senal a partir de la senal*/
}

void jobsSO(tList *listaPRocss){
    job *proceso;
    char buffer[100];
    int wstatus , status;
    tPos p;
    for (p = first(*listaPRocss) ; p != NULL ; p = next(p , *listaPRocss)) {
        proceso = p->data;
        strftime(buffer, 100, "%d/%m/%Y %X", proceso->create);
        status = waitpid(proceso->pid, &wstatus, WNOHANG | WUNTRACED | WCONTINUED);
        if (status == proceso->pid) {
            if (WIFEXITED(wstatus)) {
                proceso->status = "FINISHED";
                proceso->senial = "000";
            } else if (WIFSIGNALED(wstatus)) {
                proceso->status = "SIGNALED";
                proceso->senial = NombreSenal(WTERMSIG(wstatus));
            } else if (WIFSTOPPED(wstatus)) {
                proceso->status = "STOPPED";
                proceso->senial = NombreSenal(WSTOPSIG(wstatus));
            } else if (WIFCONTINUED(wstatus)) {
                proceso->status = "ACTIVE";
                proceso->senial = NombreSenal(SIGCONT);
            }
        }
        printf("%d %s p=%d %s %s (%s) %s\n" , proceso->pid , proceso->user , getpriority(PRIO_PROCESS , proceso->pid) , buffer ,
               proceso->status , proceso->senial , proceso->program);
    }
}

void deljobs (char *tr[], tList *listaProcss) {//creeo q non hay problemas de recursividad
    if (tr[1] != NULL) {
        tPos i;
        job *pr;
        for (i = first(*listaProcss); i != NULL; i = next(i, *listaProcss)) {
            pr = i->data;
            if (strcmp(tr[1], "-term") == 0) {
                if (strcmp(pr->status , "FINISHED") == 0){
                    remove_from_list(listaProcss, i);
                    i = listaProcss->head;
                }
            } else if (strcmp(tr[1], "-sig") == 0) {
                if (strcmp(pr->status , "SIGNALED") == 0){
                    remove_from_list(listaProcss, i);
                    i = listaProcss->head;
                }
            }
        }
    }
    else {
        jobsSO(listaProcss);
    }
}

void jobSO (char *tr[], tList *listaProcss , tList *evitarLeaks) {
    if (tr[1] != NULL) {
        job *pr = malloc(sizeof(job));
        add_address_to_list(evitarLeaks , pr);
        if (tr[2] != NULL) {//Si tenemos  0:job  1:-fg  2:pid
            if (strcmp(tr[1], "-fg") == 0) {
                tPos i;
                pid_t pid_aux = (pid_t) atoi(tr[2]);   //Guardamos el pid
                for (i = first(*listaProcss); i != NULL; i = next(i, *listaProcss)) {
                    if (i->dfORCommNUm == pid_aux) {
                        int wstatus;
                        pr = i->data;
                        if(tcsetpgrp(STDIN_FILENO, getpgid(pr->pid)) == -1){
                            printf("Proceso %d ya terminado\n" , pr->pid);
                            return;
                        }

                        waitpid(pr->pid, &wstatus, WUNTRACED);
                        if(wstatus == 0){
                            printf("Proceso %d terminado normalmente. Valor devuelto %d\n" , pr->pid , wstatus);
                        }else
                            printf("Proceso %d terminado por la señal %s\n" , pr->pid , NombreSenal(wstatus));

                        remove_from_list(listaProcss, i);
                        break;
                    }
                }
            }
        }else{
            tPos i;
            int pid_aux = atoi(tr[1]);  //Guardamos el pid
            char buffer[100];
            for(i = first(*listaProcss); i != NULL; i = next(i, *listaProcss)) {
                if (i->dfORCommNUm == pid_aux){
                    pr = i->data;
                    strftime(buffer, 100, "%d/%m/%Y %X", pr->create);
                    printf("%d %s p=%d %s %s (%s) %s\n" , pr->pid , pr->user , getpriority(PRIO_PROCESS , pr->pid) , buffer ,
                           pr->status , pr->senial , pr->program);
                }
            }
        }
    }else
        jobsSO(listaProcss);
}
