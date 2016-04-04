
#include <stdio.h>

#define GZ_OFFSET_MAGIC   (0)
#define GZ_OFFSET_FLAG    (3)
#define GZ_OFFSET_XLEN    (10)

#define GZ_FLAG_FEXTRA    (1<<2)
#define GZ_FLAG_FNAME     (1<<3)
#define GZ_FLAG_FCOMMMENT (1<<4)

#define BLOCKSIZE         (64)

void printGzipMetaData(const char * filename);

int checkGzipMagic(FILE *fp);

int getFlagByte(FILE *fp, unsigned char *flags);
int getXlen(FILE *fp, int *xlen);

int getNameOffset(FILE *fp, unsigned char flags, int *offset);
int getCommentOffset(unsigned char flags, int nameOffset, int nameLen, int *commnetOffset);

char *getGzipName(FILE *fp, unsigned char flags, int *nameOffset, int *nameLen);
char *getGzipComment(FILE *fp, unsigned char flags, int nameOffset, int nameLen);


