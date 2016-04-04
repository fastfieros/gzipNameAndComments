/* Includes local to this project */
#include "errors.h"
#include "gzmetadata.h"

/* System Includes */
#include <stdio.h>

void printGzipMetaData(const char * filename)
{
    FILE *fp;
    int err;
    
    fp = fopen(filename, "r");
    if (NULL == fp )
    {
        fprintf(stderr, "Could not open File\n");
        return;
    }
    
    err = checkGzipMagic(fp);
    if (ERR_OK != err)
    {
        fprintf(stderr, "Bad Magic\n");
        return; 
    }
    
    err = checkGzipOptNameFlag(fp);
    if (ERR_OK != err)
    {
        fprintf(stderr, "No optional name in this file.\n");
    }
    else
    {
        printf("Here's where we would print the name\n");
        //printGzipFieldName(fp);
    }
    
    //err = checkGzipOptCommentFlag(fp);
    //if (ERR_OK != err)
    //{
    //    fprintf(stderr, "No optional comment in this file.\n");
    //    return; 
    //}
    //else
    //{
    //    printGzipFieldComment(fp);
    //}
    
}

//Assumes valid fp
int checkGzipMagic(FILE *fp)
{
    int ret;
    unsigned char magic[2];
    
    //Start at begining of file
    rewind(fp);
    
    //Read 2 byte 'magic'
    if (2 != fread(magic, 1, 2, fp))
    {
        fprintf(stderr, "error reading magic\n");
        ret = ERR_FILE_READ;
    } 
    else
    {
        //Check for valid magic bytes: 1f, 8b 
        if((magic[0] == 0x1f) && (magic[1] == 0x8b))
        {
            ret = ERR_OK; 
        }
        else
        {
            fprintf(stderr, "bad magic bytes\n");
            ret = ERR_MAGIC;
        }
    }
    
    return ret;
}

//Assumes valid fp
int checkGzipOptNameFlag(FILE *fp)
{
    
}

//Assumes valid fp
void printGzipFieldName(FILE *fp)
{
    
}
