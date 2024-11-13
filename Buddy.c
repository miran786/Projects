#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LEVELS 10 // Max levels of buddies

struct Block {
    int size;
    int is_free;
    struct Block *next;
};

struct Block *free_list[MAX_LEVELS];

void initialize_buddy_system(int size) {
    int level = (int)log2(size);
    struct Block *initial_block = (struct Block *)malloc(sizeof(struct Block));
    initial_block->size = size;
    initial_block->is_free = 1;
    initial_block->next = NULL;
    free_list[level] = initial_block;
}

int get_level(int size) {
    int level = 0;
    while ((1 << level) < size) {
        level++;
    }
    return level;
}

void *allocate(int size) {
    int level = get_level(size);
    while (level < MAX_LEVELS && free_list[level] == NULL) {
        level++;
    }
    
    if (level == MAX_LEVELS) {
        printf("No available memory to allocate.\n");
        return NULL;
    }
    
    struct Block *block = free_list[level];
    free_list[level] = block->next;
    
    while (block->size / 2 >= size) {
        int buddy_size = block->size / 2;
        struct Block *buddy = (struct Block *)malloc(sizeof(struct Block));
        buddy->size = buddy_size;
        buddy->is_free = 1;
        buddy->next = free_list[--level];
        free_list[level] = buddy;
        block->size = buddy_size;
    }
    
    block->is_free = 0;
    printf("Allocated block of size %d\n", block->size);
    return (void *)block;
}

void deallocate(void *ptr) {
    struct Block *block = (struct Block *)ptr;
    int level = get_level(block->size);
    block->is_free = 1;
    
    struct Block *current = free_list[level];
    struct Block *prev = NULL;
    
    while (current != NULL) {
        if (current == block) {
            return;
        }
        prev = current;
        current = current->next;
    }
    
    if (prev == NULL) {
        free_list[level] = block;
    } else {
        prev->next = block;
    }
    
    printf("Deallocated block of size %d\n", block->size);
}

int main() {
    int total_memory_size = 1024;
    initialize_buddy_system(total_memory_size);

    void *ptr1 = allocate(128);
    void *ptr2 = allocate(64);
    void *ptr3 = allocate(256);

    deallocate(ptr1);
    deallocate(ptr2);
    deallocate(ptr3);

    return 0;
}
