#include <stdio.h>
#include <stdbool.h>

int n, m; // n = number of processes, m = number of resources

bool is_safe(int available[], int max[][10], int allocation[][10], int need[][10]) {
    bool finished[10] = {false};
    int safe_sequence[10];
    int work[10];
    
    for (int i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool can_allocate = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }
                    safe_sequence[count++] = i;
                    finished[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", safe_sequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int allocation[10][10], max[10][10], available[10];
    int need[10][10];

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

    printf("Enter the Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    is_safe(available, max, allocation, need);
    return 0;
}

