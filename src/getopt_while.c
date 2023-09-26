#include "../include/getopt_while.h"

int getopt_while(int argc, char** argv, flags_* flags){
    const struct option longopt[] =    {{"help",           0, &flags->help, 1},
                                        {"preserve",       0, &flags->pres, 1},
                                        {"verbore",        0, &flags->verb, 1},
                                        {"interective",    0, &flags->inter,1},
                                        {"force",          0, &flags->force,1},
                                        {0,                0, 0, 0}};
    
    int files_count = argc - 1;
    char ch = 0;
    while ((ch = getopt_long(argc, argv, "hpvif", longopt, NULL)) >= 0){
        switch (ch){
        case 'h': 
            flags->help = 1;
            break;
        case 'f': 
            flags->force = 1;
            break;
        case 'p': 
            flags->pres = 1;
            break;
        case 'i': 
            flags->inter = 1;
            break;
        case 'v':
            flags->verb = 1;
            break;
        default:
            break;
        }
    }
    for (int i = 1; i<argc; i++){
        if (argv[i][0] == '-')
            files_count--;
    }

    return files_count;
}