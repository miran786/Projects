#include <stdio.h>
#include <stdlib.h>

int find_closest_request(int requests[], int n, int head) {
    int min_distance = 2147483647;  // Maximum int value
    int closest_request_index = -1;

    for (int i = 0; i < n; i++) {
        int distance = abs(requests[i] - head);
        if (distance < min_distance) {
            min_distance = distance;
            closest_request_index = i;
        }
    }

    return closest_request_index;
}

void sstf(int requests[], int n, int head) {
    int total_distance = 0;
    int served_requests = 0;
    int visited[n];

    for (int i = 0; i < n; i++) {
        visited[i] = 0;  // mark all requests as not visited
    }

    printf("SSTF Disk Scheduling:\n");

    while (served_requests < n) {
        int closest_request_index = find_closest_request(requests, n, head);

        if (visited[closest_request_index] == 0) {
            int distance = abs(requests[closest_request_index] - head);
            total_distance += distance;
            head = requests[closest_request_index];
            visited[closest_request_index] = 1;
            served_requests++;

            printf("Serve request at %d, Distance: %d\n", head, distance);
        }
    }

    printf("Total distance traveled (SSTF): %d\n", total_distance);
}

int main() {
    int requests[] = {176, 79, 34, 60, 92, 11, 41, 114};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 50;  // Initial position of disk head

    sstf(requests, n, head);
    return 0;
}
