#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

static void sighandler(int); 

int main()
{
    signal(SIGINT, sighandler); 

    char input[80]; 
    char output[80]; 

    int process = open("process", O_RDONLY); 
    int control = open("control", O_WRONLY); 

    while(1)
    {
        printf("input: "); 
        scanf("%s", input); 
        write(control, input, sizeof(input)-1);  
        read(process, output, sizeof(output)-1);  
        printf("output: [%s]\n", output); 
    }
}

static void sighandler(int signo)
{
    if(signo == SIGINT)
    {
        remove("process"); 
        remove("control"); 
        exit(0); 
    }
}
