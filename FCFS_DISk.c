#include <stdio.h>
#include <stdlib.h>

void fcfs(int requests[], int n, int head) {
    int total_distance = 0;
    int current_position = head;

    printf("FCFS Disk Scheduling:\n");

    for (int i = 0; i < n; i++) {
        int distance = abs(current_position - requests[i]);
        total_distance += distance;
        current_position = requests[i];

        printf("Serve request at %d, Distance: %d\n", requests[i], distance);
    }

    printf("Total distance traveled (FCFS): %d\n", total_distance);
}

int main() {
    int requests[] = {176, 79, 34, 60, 92, 11, 41, 114};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 50;  // Initial position of disk head

    fcfs(requests, n, head);
    return 0;
}
