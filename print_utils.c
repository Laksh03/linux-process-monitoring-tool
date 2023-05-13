#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "print_utils.h"

void printLogic(char *pos_arg, char *flag, char *pid, int fd_num, char *fd_actual_path, long long int inode){
    int n;
    if(flag == NULL){
        printf("\t%-10s %-10d %-30s      %lld\n", pid, fd_num, fd_actual_path, inode);
    }else{
        n = strlen(flag);
        if(strncmp(flag, "--per-process", n) == 0){
            printf("\t%-10s %-10d\n", pid, fd_num);
        }else if((strncmp(flag, "--systemWide", n) == 0)){
            printf("\t%-10s %-10d %s\n", pid, fd_num, fd_actual_path);
        }else if((strncmp(flag, "--Vnodes", n) == 0)){
            printf("\t%-10d %lld\n", fd_num, inode);
        }else if((strncmp(flag, "--composite", n) == 0)){
            printf("\t%-10s %-10d %-30s      %lld\n", pid, fd_num, fd_actual_path, inode);
        }
    }
}


void printHeader(char *pos_arg, char *flag, int thresholdFlag, int threshold){
    if(thresholdFlag){
        printf("\n## Offending Processes -- #FD threshold=%d\n", threshold);
    }else{
        if(pos_arg != NULL){
            printf("\n>>> Target PID: %s\n", pos_arg);
        }

        int n;
        if(flag == NULL){
            printf("\n\t%-10s %-10s %-30s      %s\n", "PID", "FD", "Filename", "Inode");
        }else{
            n = strlen(flag);
            if(strncmp(flag, "--per-process", n) == 0){
                printf("\n\t%-10s %-10s\n", "PID", "FD");
            }else if((strncmp(flag, "--systemWide", n) == 0)){
                printf("\n\t%-10s %-10s %s\n", "PID", "FD", "Filename");
            }else if((strncmp(flag, "--Vnodes", n) == 0)){
                printf("\n\t%-10s %s\n", "FD", "Inode");
            }else if((strncmp(flag, "--composite", n) == 0)){
                printf("\n\t%-10s %-10s %-30s      %s\n", "PID", "FD", "Filename", "Inode");
            }
        }
        printf("\t========================================================================\n");
    }
}