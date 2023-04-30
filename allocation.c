#include<stdio.h>
#include<stdlib.h>

void first_fit(int *blocks, int n, int *procs, int m) {
    int *temp_blocks = malloc(n * sizeof(int));
    for(int i=0;i<n;i++) {
        temp_blocks[i] = blocks[i];
    }
    printf("\n             FIRST FIT                \n");
    printf("-------------------------------------------\n");
    printf("Process No.   Process Size   Block no.\n");
    for(int i=0;i<m;i++) {
        int flag = 0;
        for(int j=0;j<n;j++) {
            if(procs[i] <= temp_blocks[j]) {
                temp_blocks[j] -= procs[i];
                printf("    %d             %d            %d   \n", i+1, procs[i], j+1);
                flag = 1;
                break;
            }
        }
        if(flag == 0) {
            printf("    %d             %d        Not Allocated\n", i+1, procs[i]);
        }
    }
    printf("-------------------------------------------\n");
    free(temp_blocks);
}

void worst_fit(int *blocks, int n, int *procs, int m) {
    int *temp_blocks = malloc(n * sizeof(int));
    for(int i=0;i<n;i++) {
        temp_blocks[i] = blocks[i];
    }
    printf("\n             WORST FIT                \n");
    printf("-------------------------------------------\n");
    printf("Process No.   Process Size   Block no.\n");
    for(int i=0;i<m;i++) {
        int worst_block = -999999;
        int worst_index = -1;
        for(int j=0;j<n;j++) {
            if(procs[i] <= temp_blocks[j] && temp_blocks[j]>worst_block) {
                worst_block = temp_blocks[j];
                worst_index = j;
            }
        }
        if(worst_index == -1) {
            printf("    %d             %d        Not Allocated\n", i+1, procs[i]);    
        }
        else {
            temp_blocks[worst_index] -= procs[i];
            printf("    %d             %d            %d   \n", i+1, procs[i], worst_index+1);
        }
    }
    printf("-------------------------------------------\n");
    free(temp_blocks);
}

void best_fit(int *blocks, int n, int *procs, int m) {
    int *temp_blocks = malloc(n * sizeof(int));
    for(int i=0;i<n;i++) {
        temp_blocks[i] = blocks[i];
    }
    printf("\n             BEST FIT                \n");
    printf("-------------------------------------------\n");
    printf("Process No.   Process Size   Block no.\n");
    for(int i=0;i<m;i++) {
        int best_block = 999999;
        int best_index = -1;
        for(int j=0;j<n;j++) {
            if(procs[i] <= temp_blocks[j] && temp_blocks[j]<best_block) {
                best_block = temp_blocks[j];
                best_index = j;
            }
        }
        if(best_index == -1) {
            printf("    %d             %d        Not Allocated\n", i+1, procs[i]);    
        }
        else {
            temp_blocks[best_index] -= procs[i];
            printf("    %d             %d            %d   \n", i+1, procs[i], best_index+1);
        }
    }
    printf("-------------------------------------------\n");
    free(temp_blocks);
}

int main() {
    int n,m;
    printf("Enter the no. of memory blocks : ");
    scanf("%d", &n);
    int *blocks = malloc(n * sizeof(int));
    printf("Enter the size of memory blocks : \n");
    for(int i=0;i<n;i++) {
        scanf("%d", &blocks[i]);
    }

    printf("Enter the no. of processes for memory allocation : ");
    scanf("%d", &m);
    int *procs = malloc(m * sizeof(int));
    printf("Enter the size of processes : \n");
    for(int i=0;i<m;i++) {
        scanf("%d", &procs[i]);
    }

    first_fit(blocks, n, procs, m);
    worst_fit(blocks, n, procs, m);
    best_fit(blocks, n, procs, m);

    return 0;
}