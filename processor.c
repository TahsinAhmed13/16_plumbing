#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void rot13(char *, char *); 

int main()
{
    char input[80]; 
    char output[80]; 

    mkfifo("process", 0644); 
    mkfifo("control", 0644); 
    int process = open("process", O_WRONLY); 
    int control = open("control", O_RDONLY); 
    
    while(1)
    {
        read(control, input, sizeof(input)-1); 
        rot13(input, output); 
        write(process, output, sizeof(output)-1); 
    }
}

void rot13(char *in, char *out)
{
    while(*in)
    {
        *out = (((*in - 'a') + 13) % 26) + 'a'; 
        ++out; 
        ++in; 
    }
    *out = 0; 
}
