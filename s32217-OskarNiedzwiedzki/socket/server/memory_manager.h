#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H
#include "DList.h"


struct memory_block{
    void* ptr;
    int block_size;
};

struct memory_info{
    struct dlist* block_refs;
    unsigned long allocated_bytes;
}extern mem_manager;

void* allocate(unsigned char, unsigned int);
void destroy(void*);
void mem_manager_init();
void mem_manager_destroy();

#endif