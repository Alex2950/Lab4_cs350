#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define INPUT_FILE "./input/if1"
#define OUTPUT_FILE "./input/result"
//re-associate fd STDIN_FILENO with INPUT_FILE
//the fd of the actual input file
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
        int file_desc = open(INPUT_FILE, O_RDONLY);
        int result = open(OUTPUT_FILE, O_WRONLY);
        if(file_desc < 0 || result < 0)printf("Error opening the file\n");
        dup2(file_desc,0);
        dup2(result,1);

        execvp(argv[1],&argv[1]);
        
        printf("Command %s Does Not Exist \n",argv[1]);
        exit(EXIT_FAILURE);
    }
    else{
        exit(EXIT_FAILURE);
    }
    return 0;
}
