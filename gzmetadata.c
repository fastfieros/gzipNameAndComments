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
        printGzipFieldName(fp);
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

int checkGzipMagic(FILE *fp)
{
   rewind(fp);
}

int checkGzipOptNameFlag(FILE *fp)
{
    
}

void printGzipFieldName(FILE *fp)
{
    
}
