#include "../include/copy_files.h"


int safe_read_write(int in, int out){
    char* buffer[BUFFER_SIZE];
    size_t real_size = 0;
    int num = 0;

    while((real_size = read(in, buffer, BUFFER_SIZE))>0){
        for(int i = 0; i < real_size; i -= num)
           if ((num = write(out, buffer+i, real_size-i)) < 0) 
                return -1;
    }
    return 0;
}


int copy_file(char** const files, flags_* flags){
    if (!strcmp(files[0], files[1])){
        printf("cp: '%s' и '%s' - the same file\n", files[0], files[1]);
        return -1;
    }

    if (access(files[1], F_OK) == 0){
        if (flags->inter){
            printf("cp: rewrite '%s'?", files[1]);
            if (getchar() == 'n')
                return 0;
        }
    }
    if (access(files[0], F_OK) != 0){
        printf("cp: failed stat for '%s': No such file or directory", files[0]);
        return -1;
    }
    if (access(files[1], W_OK) && !flags->force && access(files[0], F_OK)){
        printf("cp: unable to open '%s' for writing: Access denied\n", files[1]);
        return -1;
    }
    if (access(files[0], R_OK)){
        printf("cp: unable to open '%s' for reading: Access denied\n", files[0]);
        return -1;
    }

    struct stat file_stat;
    stat(files[0], &file_stat);
    
    int dest_file = open(files[1], O_RDWR|O_CREAT|file_stat.st_mode & 0777);
    int input_file = open(files[0], O_RDONLY);
    if ((flags->pres))
        chmod(files[1], file_stat.st_mode);
    
    if (flags->verb)
        printf("'%s' -> '%s'\n", files[0], files[1]);
    
    int answer = safe_read_write(input_file, dest_file);
    close(input_file);
    close(dest_file);

    return answer;
}


int copy_files(char** files_dir, int len, flags_* flags){
    char buffer[BUFFER_SIZE] = {0};
    
    struct stat file_stat;
    if (access(files_dir[len-1], F_OK) == -1)
        mkdir(files_dir[len-1], 0777);
    
    if ((flags->pres))
        chmod(files_dir[1], file_stat.st_mode);

    if (access(files_dir[len-1], R_OK)){
        printf("cp: unable to use '%s' directory: Access denied\n", files_dir[len-1]);
        return -1;
    }
    
    for (int i = 0; i<len-1; i++){
        strcpy(buffer, files_dir[len-1]);
        strcat(buffer, "/");
        strcat(buffer, files_dir[i]);
        char* files[2] = {files_dir[i], buffer};
        copy_file(files, flags);
    }
}