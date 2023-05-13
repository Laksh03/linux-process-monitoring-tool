#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "myfuncs.h"
#include "print_utils.h"
#define BUF_SIZE 1024


void my_func(char *pos_arg, char *flag, int thresholdFlag, int threshold){
    printHeader(pos_arg, flag, thresholdFlag, threshold);

    // Get the UID of the current user
    uid_t uid = getuid();

    // Open the /proc directory
    DIR* proc_dir = opendir("/proc");
    if (proc_dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Iterate over all subdirectories in /proc
    struct dirent* entry;
    char path[BUF_SIZE];
    while ((entry = readdir(proc_dir)) != NULL) {
        // Check if the subdirectory is a process directory
        if (entry->d_type == DT_DIR && atoi(entry->d_name) != 0) {
            // Open the /proc/<pid>/status file
            snprintf(path, BUF_SIZE, "/proc/%s/status", entry->d_name);
            FILE* status_file = fopen(path, "r");
            if (status_file == NULL) {
                perror("fopen");
                continue;
            }

            // Read the UID and State of process from the /proc/<pid>/status file
            char line[BUF_SIZE];
            char *value; 
            char state;
            uid_t pid_uid = 0;

            fgets(line, BUF_SIZE, status_file);
            fgets(line, BUF_SIZE, status_file);
            fgets(line, BUF_SIZE, status_file);
            state = line[7];


            fgets(line, BUF_SIZE, status_file);
            fgets(line, BUF_SIZE, status_file);
            fgets(line, BUF_SIZE, status_file);
            fgets(line, BUF_SIZE, status_file);
            fgets(line, BUF_SIZE, status_file);
            fgets(line, BUF_SIZE, status_file);
            value = strtok(line, "\t ");
            value = strtok(NULL, "\t ");
            pid_uid = atoi(value);
            
            fclose(status_file);

            // Check if the UID of the process matches the UID of the current user
            if (pid_uid == uid && (pos_arg == NULL || atoi(pos_arg) == atoi(entry->d_name)) && state != 'Z' && state != 'X') {
                // Open the /proc/<pid>/fd directory
                snprintf(path, BUF_SIZE, "/proc/%s/fd", entry->d_name);
                DIR* fd_dir = opendir(path);
                if (fd_dir == NULL) {
                    //perror("opendir");
                    continue;
                }

                // Iterate over all files in /proc/<pid>/fd
                struct dirent* fd_entry;
                int fd_num;
                char fd_path[BUF_SIZE];

                FILE *fdinfo;
                char fdinfo_path[BUF_SIZE];
                long long int inode;


                char fd_actual_path[BUF_SIZE];
                ssize_t end; 

                int count = 0;
                while ((fd_entry = readdir(fd_dir)) != NULL) {
                    if(thresholdFlag){
                        count++;
                    }else{
                        if (fd_entry->d_type == DT_LNK) {
                            fd_num = atoi(fd_entry->d_name);
                            snprintf(fd_path, BUF_SIZE, "/proc/%s/fd/%s", entry->d_name, fd_entry->d_name);
                            
                            snprintf(fdinfo_path, BUF_SIZE, "/proc/%s/fdinfo/%s", entry->d_name, fd_entry->d_name);
                            fdinfo = fopen(fdinfo_path, "r");
                            if (fdinfo == NULL) {
                                perror("fopen");
                                continue;
                            }

                            fgets(line, BUF_SIZE, fdinfo);
                            fgets(line, BUF_SIZE, fdinfo);
                            fgets(line, BUF_SIZE, fdinfo);
                            fgets(line, BUF_SIZE, fdinfo);
                            value = strtok(line, "\t ");
                            value = strtok(NULL, "\n");
                            inode = strtoll(value, NULL, 10);
                            fclose(fdinfo);

                            end = readlink(fd_path, fd_actual_path, BUF_SIZE);
                            fd_actual_path[end] = '\0';
                            // Call printLogic to print the correct info. 
                            printLogic(pos_arg, flag, entry->d_name, fd_num, fd_actual_path, inode);
                        }
                    }
                }
                closedir(fd_dir);

                if(thresholdFlag){
                    if(count > threshold){
                        printf(" %s (%d),", entry->d_name, count);
                    }

                }
            }
        }
    }
    closedir(proc_dir);
    
    if(thresholdFlag){
        printf("\n");
    }
}

