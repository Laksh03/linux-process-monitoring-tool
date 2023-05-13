#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

void printLogic(char *pos_arg, char *flag, char *pid, int fd_num, char *fd_actual_path, long long int inode);

void printHeader(char *pos_arg, char *flag, int thresholdFlag, int threshold);

#endif