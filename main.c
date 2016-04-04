/* Includes local to this project */
#include "errors.h"
#include "gzmetadata.h"

/* System Includes */
#include <stdio.h>
#include <unistd.h>

/* function prototypes */
int checkArguments(int argc, char **argv);
void usage(char *argv0);
int isFile(const char *filename);
int checkEndianness();

int main(int argc, char **argv)
{
    int err;
    const char *filename;
    
    err = checkArguments(argc, argv);
    
    if (ERR_OK == err)
    {
        //Parse the header of this file!
        filename = argv[1];
        printGzipMetaData(filename);
    }
    else
    {
        usage(argv[0]); 
    }
    
    return -err;
}

int checkArguments(int argc, char **argv)
{
    int ret;
    
    /* for this program there must be one argument */
    if (argc == 2)
    {
        if (ERR_OK == isFile(argv[1]))
        {
            ret = ERR_OK;
        }
        else
        {
            fprintf(stderr, "Could not open specified file.\n");
            ret = ERR_NO_FILE;
        } 
    }
    else
    {
        fprintf(stderr, "Incorrect number of arguments.\n");
         ret = ERR_INVALID_ARGUMENTS;
    }
    
    return ret;
}

void usage(char *argv0)
{
    fprintf(stderr, "usage: %s <fileaname>\n", argv0);
    fprintf(stderr, "\t filename [required]: name of gzip file to open\n");
} 

int isFile(const char *filename)
{
    /* Use R_OK because we only need read access */
    if( access( filename, R_OK ) != -1 ) 
    { 
        return ERR_OK;
    }
    else
    {
        return ERR_NO_FILE;
    }
}