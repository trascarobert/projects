#ifndef __FILE_H__
#define __FILE_H__
#include "list.h"

typedef struct Directory {
char *name;
struct list *startFile;
struct list *startDirectory;
struct Directory *parentDir;
} Directory;

typedef struct File {
char *name;
int size;
char *data;
Directory *dir;
} File;

#endif
