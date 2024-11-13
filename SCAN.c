#include <stdio.h>
#include <stdlib.h>
void scan(int requests[], int n, int head, int disk_size) {
    int total_distance = 0;
    int left[disk_size], right[disk_size];
    int left_index = 0, right_index = 0;
    for (int i = 0; i < n; i++) {
        if (requests[i] < head) {
            left[left_index++] = requests[i];
        } else {
            right[right_index++] = requests[i];
        }
    }
    for (int i = 0; i < left_index - 1; i++) {
        for (int j = i + 1; j < left_index; j++) {
            if (left[i] < left[j]) {
                int temp = left[i];
                left[i] = left[j];
                left[j] = temp;
            }
        }
    }
    for (int i = 0; i < right_index - 1; i++) {
        for (int j = i + 1; j < right_index; j++) {
            if (right[i] > right[j]) {
                int temp = right[i];
                right[i] = right[j];
                right[j] = temp;
            }
        }
    }
    total_distance = abs(head - left[0]) + abs(left[0] - 0) + abs(right[right_index - 1] - left[0]);
    total_distance += abs(right[right_index - 1] - disk_size);
    total_distance += abs(disk_size - right[0]);

    printf("SCAN Disk Scheduling:\n");
    printf("Total distance traveled (SCAN): %d\n", total_distance);
}
int main() {
    int requests[] = {176, 79, 34, 60, 92, 11, 41, 114};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 50;  
    int disk_size = 200; 
    scan(requests, n, head, disk_size);
    return 0;
}
