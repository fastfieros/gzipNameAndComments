/* Includes local to this project */
#include "errors.h"
#include "gzmetadata.h"

/* System Includes */
#include <stdio.h>

void printGzipFieldName(FILE *fp)
{
    
}

void printGzipMetaData(const char * filename)
{
    FILE * fp = fopen(filename "r");
    int err;
    err = checkGzipMagic(*fp);
    if (ERR_OK != err)
    {
        fprintf(stderr, "Bad Magic\n");
        return; 
    }
    
    err = checkGzipOptNameFlag(*fp);
    if (ERR_OK != err)
    {
        fprintf(stderr, "No optional name in this file.\n");
    }
    else
    {
        printGzipFieldName(fp);
    }
    
    //err = checkGzipOptCommentFlag(*fp);
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