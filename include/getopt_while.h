#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <getopt.h>

typedef struct Flags{
    int force;
    int inter;
    int verb;
    int pres;
    int help;
}flags_;

int getopt_while(int argc, char** argv, flags_* flags);