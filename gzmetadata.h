
#include <stdio.h>

void printGzipMetaData(const char * filename);

int checkGzipMagic(FILE *fp);
int checkGzipOptNameFlag(FILE *fp);
int checkGzipOptCommentFlag(FILE *fp);

void printGzipFieldName(FILE *fp);
void printGzipFieldComment(FILE *fp);