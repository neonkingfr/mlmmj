#ifndef __MYGETLINE_H__
#define __MYGETLINE_H__
#include <stdio.h>

#define BUFSIZE 256

char *myfgetline(FILE *infile);
char *mygetline(int fd);

#endif /* #ifndef __MYGETLINE_H__ */
