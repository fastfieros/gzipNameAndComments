/* Includes local to this project */
#include "errors.h"
#include "gzmetadata.h"

/* System Includes */
#include <stdio.h>
#include <stdlib.h>

void printGzipMetaData(const char * filename)
{
    int err;
    FILE *fp;
    char *name = NULL;
    unsigned char flags;
    
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
    
    err = getFlagByte(fp, &flags);
    if (ERR_OK != err)
    {
        fprintf(stderr, "error reading Flags\n");
        return; 
    }
    
    name = getGzipName(fp, flags);
    if (NULL != name)
    {
        printf("gzip Name: %s\n", name);
        free(name);
    }
    else
    {
        /*We can't parse the comment if the name did
            not parse correctly */
        fprintf(stderr, "error reading gzip name\n");
        return;
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
    
    //seek to the magic location
    fseek(fp, GZ_OFFSET_MAGIC, SEEK_SET);
    
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
int getFlagByte(FILE *fp, unsigned char *flags)
{
    int ret;
    
    //seek to the flag location
    fseek(fp, GZ_OFFSET_FLAG, SEEK_SET);
    
    //Read flags byte
    if (1 != fread(flags, 1, 1, fp))
    {
        ret = ERR_FILE_READ;
    } 
    else
    {
        ret = ERR_OK;
    }
    
    return ret;
}

//Assumes valid fp
int getXlen(FILE *fp, int *xlen)
{
    int ret;
    unsigned short xlen_word;
    
    //seek to the xlen location
    fseek(fp, GZ_OFFSET_XLEN, SEEK_SET);
    
    //Read 2 bytes of xlen
    if (1 != fread(&xlen_word, 2, 1, fp))
    {
        fprintf(stderr, "Error reading xlen.\n");
        ret = ERR_FILE_READ;
    } 
    else
    {
        *xlen = (int)xlen_word;
        ret = ERR_OK;
    }
    
    return ret;
    
}

//Assumes valid fp
int getNameOffset(FILE *fp, unsigned char flags, int *offset)
{
    int xlen = 0;
    
    if (GZ_FLAG_FNAME != (flags & GZ_FLAG_FNAME))
    {
        fprintf(stderr, "No optional name in this file.\n");
        return ERR_NO_COMMENT;
    }
    
    if (GZ_FLAG_FEXTRA == (flags & GZ_FLAG_FEXTRA))
    {
        if (ERR_OK == getXlen(fp, &xlen))
        {
            xlen += 2; /* Xlen itself */
        }
        else
        {
            return ERR_XLEN;
        }
    }
    
    *offset = (GZ_OFFSET_XLEN + xlen);
    
    return ERR_OK;
}

int getMoreName(FILE *fp, char **name, int *currentLen)
{
    int ret;
    size_t read;
    
    *name = realloc(*name, *currentLen + BLOCKSIZE);
    
    if (NULL == *name)
    {
        fprintf(stderr, "unable to allocate memory for name\n");
        return ERR_OUT_OF_MEMORY;
    }
    
    read = fread(&((*name)[*currentLen]), 1, BLOCKSIZE, fp);
    /* Multple conditions to check here:
       If the read returned 0, we might be at the end of the file, and
       need to check for the null terminator, if the read returned 
       positive, we need to check for the null terminator. If the
       read returned negative, or it returned zero while not setting
       the EOF flag, then we hit an error. */ 
    if ( (read < 0) || ((read == 0) && (!feof(fp))) )
    {
        fprintf(stderr, "Error reading name data\n");
        ret = ERR_FILE_READ;
    } 
    else
    {
        *currentLen += read;
        
        printf ("%s, ", *name);
        
        /* need to check that the full null terminated
        string has been obtained */
        if (strnlen(*name, *currentLen) < *currentLen)
        {
            /* signal caller that this 
                string has a null terminator */
            ret = ERR_DONE;
        }
        else
        {
            /* signal caller that there may
               be more data to gather */
            ret = ERR_OK;
        }
    }
    
    return ret;
}

//Assumes valid fp
char *getGzipName(FILE *fp, unsigned char flags)
{
    int err;
    int nameOffset; 
    int currentLen;
    char *name;
    
    err = getNameOffset(fp, flags, &nameOffset);
    if (ERR_OK != err)
    {
        return NULL; 
    }
    
    //seek to the flag location
    if(-1 == fseek(fp, nameOffset, SEEK_SET))
    {
        fprintf(stderr, "error seeking to name field\n");
        return NULL;
    }
    
    err = ERR_OK;
    name = NULL; 
    currentLen = 0;
    
    /* loop until an error, because getMoreName returns
       ERR_DONE when it finds the null termintor */
    while (err == ERR_OK)
    {
        err = getMoreName(fp, &name, &currentLen);
        
        printf ("currentLen: 0x%x\n", currentLen);
    } 
    
    if (err == ERR_DONE)
    {
        return name;
    }
    else
    {
        if (NULL != name)
        {
            free(name);
        }
        return NULL;
    }
    
}
