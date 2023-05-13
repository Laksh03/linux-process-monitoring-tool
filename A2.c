#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myfuncs.h"

int main(int argc, char **argv){
    int thresholdFlag = 0;
    int threshold = -1;
    int n;

    if(argc == 1){
        my_func(NULL, NULL, 0, 0);
    }else if (argc == 2){
        if(argv[1][0] != '-'){
            my_func(argv[1], NULL, 0, 0);
        }else{
            n = strlen(argv[1]);
            if(n < strlen("--threshold=") - 1){
                my_func(NULL, argv[1], 0, 0);
            }else if(strncmp(argv[1], "--threshold=", strlen("--threshold=")) == 0){
                thresholdFlag = 1;
                char *value;
                value = strtok(argv[1], "=");
                value = strtok(NULL, "\n");
                threshold = atoi(value);
            }else{
                my_func(NULL, argv[1], 0, 0);
            }
        }
    }else{
        int x;
        if(argv[1][0] != '-'){
            for(x = 2; x < argc; x++){
                n = strlen(argv[x]);
                if(n < strlen("--threshold=") - 1){
                    my_func(argv[1], argv[x], 0, 0);
                }else if(strncmp(argv[x], "--threshold=", strlen("--threshold=")) == 0){
                    thresholdFlag = 1;
                    char *value;
                    value = strtok(argv[x], "=");
                    value = strtok(NULL, "\n");
                    threshold = atoi(value); 
                }else{
                    my_func(argv[1], argv[x], 0, 0);
                }
            }
        }else{
            for(x = 1; x < argc; x++){
                n = strlen(argv[x]);
                if(n < strlen("--threshold=") - 1){
                    my_func(NULL, argv[x], 0, 0);
                }else if(strncmp(argv[x], "--threshold=", strlen("--threshold=")) == 0){
                    thresholdFlag = 1;
                    char *value;
                    value = strtok(argv[x], "=");
                    value = strtok(NULL, "\n");
                    threshold = atoi(value);
                }else{
                    my_func(NULL, argv[x], 0, 0);
                }
            }
        }
    }

    if(thresholdFlag){
        my_func(NULL, NULL, thresholdFlag, threshold);
    }

    return 0;
}