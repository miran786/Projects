#include <stdio.h>

void fifo(int pages[], int n, int frames) {
    int page_frame[frames];
    int page_faults = 0, index = 0;

    // Initialize page frame to -1 (empty)
    for (int i = 0; i < frames; i++) {
        page_frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in memory
        for (int j = 0; j < frames; j++) {
            if (page_frame[j] == page) {
                found = 1;
                break;
            }
        }

        // If page not found in memory, page fault occurs
        if (!found) {
            page_frame[index] = page;
            index = (index + 1) % frames;
            page_faults++;
        }

        // Print current page frames
        printf("Page frames: ");
        for (int j = 0; j < frames; j++) {
            printf("%d ", page_frame[j]);
        }
        printf("\n");
    }

    printf("Total page faults (FIFO): %d\n", page_faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3};
    int n = sizeof(pages) / sizeof(pages[0]);
    int frames = 3;

    fifo(pages, n, frames);
    return 0;
}
