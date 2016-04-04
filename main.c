/* Includes local to this project */
#include "errors.h"

/* System Includes */
#include <stdio.h>

/* function prototypes */
int checkArguments(int argc, char **argv);
void usage(char *argv0);

int main(int argc, char **argv)
{
    int err;
    
    err = checkArguments(argc, argv);
    
    if (ERR_OK == err)
    {
        //todo Parse Header here
    }
    else
    {
        usage(argv[0]); 
    }
    
    return -err;
}

int checkArguments(int argc, char **argv)
{
    /* for this program there are NO acceptable arguments */
    if (argc == 1)
    {
        return ERR_OK;
    }
    
    return ERR_INVALID_ARGUMENTS;
}

void usage(char *argv0)
{
    fprintf(stderr, "usage: %s\n", argv0);
    fprintf(stderr, "Must run without any arguments\n");
}