#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char * argv[]) {
    int childpid = fork();
    int currpid = getpid();
    int status;
    if(childpid>0){
        wait(&status);
        printf("IN PARENT: successfully waited child (pid = %d)\n",childpid);
    }
    if(childpid == 0){
        printf("IN CHILD: pid = %d\n",currpid);
        execvp(argv[1],&argv[1]);
        printf("Command %s Does Not Exist \n",argv[1]);
         exit(EXIT_FAILURE);
    }
    else{
        exit(EXIT_FAILURE);
    }
    return 0;
}
