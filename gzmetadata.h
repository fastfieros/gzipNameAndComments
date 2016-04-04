
#include <stdio.h>

/* Static offsets into the file */
#define GZ_OFFSET_MAGIC   (0)
#define GZ_OFFSET_FLAG    (3)
#define GZ_OFFSET_XLEN    (10)

/* zlib flag values */
#define GZ_FLAG_FEXTRA    (1<<2)
#define GZ_FLAG_FNAME     (1<<3)
#define GZ_FLAG_FCOMMMENT (1<<4)

/* how much of the file to read in at a time */
#define BLOCKSIZE         (64)

/**** Prototypes ****/
void printGzipMetaData(const char * filename);

int checkGzipMagic(FILE *fp);

int getFlagByte(FILE *fp, unsigned char *flags);

int getXlen(FILE *fp, int *xlen);

int getCommentOffset(unsigned char flags, int nameOffset, int nameLen, 
                     int *commentOffset);
                     
int getNameOffset(FILE *fp, unsigned char flags, int *offset);

int validateChars(char *name, int currentLen);

int getMoreName(FILE *fp, char **name, int *currentLen);

char *getGzipName(FILE *fp, unsigned char flags, int *nameOffset, int *nameLen);

char *getGzipComment(FILE *fp, unsigned char flags, int nameOffset, int nameLen);

