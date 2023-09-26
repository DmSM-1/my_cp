#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>
#include <pwd.h>
#include <grp.h>
#include "getopt_while.h"


#define BUFFER_SIZE 1024

int copy_file(char** const files, flags_* flags);
int copy_files(char** files_dir, int len, flags_* flags);