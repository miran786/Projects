#include <stdio.h>
#include <limits.h>

void first_fit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d -> Not Allocated\n", i + 1);
        }
    }
}

void best_fit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d -> Not Allocated\n", i + 1);
        }
    }
}

void worst_fit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d -> Not Allocated\n", i + 1);
        }
    }
}

void next_fit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int lastAllocatedIdx = 0;
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
        int j = lastAllocatedIdx;
        do {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastAllocatedIdx = j;
                break;
            }
            j = (j + 1) % m;
        } while (j != lastAllocatedIdx);
    }
    printf("\nNext Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1) {
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        } else {
            printf("Process %d -> Not Allocated\n", i + 1);
        }
    }
}

int main() {
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize[0]);
    int n = sizeof(processSize) / sizeof(processSize[0]);

    int blockCopy1[m], blockCopy2[m], blockCopy3[m], blockCopy4[m];
    for (int i = 0; i < m; i++) {
        blockCopy1[i] = blockSize[i];
        blockCopy2[i] = blockSize[i];
        blockCopy3[i] = blockSize[i];
        blockCopy4[i] = blockSize[i];
    }

    first_fit(blockCopy1, m, processSize, n);
    best_fit(blockCopy2, m, processSize, n);
    worst_fit(blockCopy3, m, processSize, n);
    next_fit(blockCopy4, m, processSize, n);

    return 0;
}
