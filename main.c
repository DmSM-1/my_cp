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
#include "include/copy_files.h"


void print_info(const flags_* flags){
    printf("-------------------\n");
    printf("force: %s\n", (flags->force)?"true":"false");
    printf("inter: %s\n", (flags->inter)?"true":"false");
    printf("verb : %s\n", (flags->verb) ?"true":"false");
    printf("pres : %s\n", (flags->pres) ?"true":"false");
    printf("help : %s\n", (flags->help) ?"true":"false");
    printf("-------------------\n");
}


void print_help(){
    printf("Usage: cp [OPTION]... [-T] SOURCE DEST\n"
           "or:    cp [OPTION]... SOURCE... DIRECTORY\n"  
           "or:    cp [OPTION]... -t DIRECTORY SOURCE...\n" 
           "Copy SOURCE to DEST, or multiple SOURCE(s) to DIRECTORY.\n\n"
           "Mandatory arguments to long options are mandatory for short options too.\n"
           "-f, --force if an existing destination file cannot be opened, remove it and try again (this option is ignored when the -n option is also used)\n" 
           "-i, --interactive prompt before overwrite (overrides a previous -n option)\n"
           "-v, --verbose explain what is being done\n"
           "-p, --preserve same as --preserve=mode,ownership,timestamps preserve the specified attributes\n");
}


int main(int argc, char** argv){ 
    if (argc == 1)
        perror("cp");
    flags_ flags = {0,0,0,0,0}; 
    
    int files_count = getopt_while(argc, argv, &flags);
    
    if (flags.help){
        print_help();
        return 0;
    }

    if (!files_count){
        printf("cp: file operand missing\n");
        return -1;
    }

    if (flags.inter)
        flags.force = 0;

    if (files_count == 2){
        copy_file(&argv[argc-2], &flags);
    }

    if (files_count > 2 ){
        copy_files(&argv[argc-files_count], files_count, &flags);
    }        

    return 0;
}