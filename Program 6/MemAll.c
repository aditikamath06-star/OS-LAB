#include <stdio.h>

#define MAX 100

void printAllocation(int processSize[], int n, int allocation[]) {
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
    printf("\n");
}

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int is_allocated[MAX] = {0};

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i] && !is_allocated[j]) {
                allocation[i] = j;
                is_allocated[j] = 1;
                break;
            }
        }
    }
    printf("\n FIRST FIT ALLOCATION ");
    printAllocation(processSize, n, allocation);
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int is_allocated[MAX] = {0};

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i] && !is_allocated[j]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            is_allocated[bestIdx] = 1;
        }
    }
    printf("\nBEST FIT ALLOCATION");
    printAllocation(processSize, n, allocation);
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX];
    int is_allocated[MAX] = {0};

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i] && !is_allocated[j]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            is_allocated[worstIdx] = 1;
        }
    }
    printf("\nWORST FIT ALLOCATION ");
    printAllocation(processSize, n, allocation);
}

int main() {
    int blockSize[MAX], processSize[MAX];
    int m, n;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    firstFit(blockSize, m, processSize, n);
    bestFit(blockSize, m, processSize, n);
    worstFit(blockSize, m, processSize, n);

    return 0;
}