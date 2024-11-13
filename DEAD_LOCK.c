#include <stdio.h>
#include <stdbool.h>

int n, m; 

bool detect_deadlock(int available[], int allocation[][10], int request[][10]) {
    bool finished[10] = {false};
    int work[10];
    
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    bool found_process = true;
    while (found_process) {
        found_process = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool can_allocate = true;
                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finished[i] = true;
                    found_process = true;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!finished[i]) {
            printf("System is in a deadlocked state.\nDeadlocked processes are: ");
            for (int j = 0; j < n; j++) {
                if (!finished[j]) {
                    printf("P%d ", j);
                }
            }
            printf("\n");
            return true;
        }
    }

    printf("System is not in a deadlocked state.\n");
    return false;
}

int main() {
    int allocation[10][10], request[10][10], available[10];

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the Request Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter the Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    detect_deadlock(available, allocation, request);
    return 0;
}
