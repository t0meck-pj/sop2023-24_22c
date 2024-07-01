#include "memory_manager.h"
#include <stdio.h>

struct memory_info mem_manager;

void mem_manager_init(){
    mem_manager.block_refs = create_dlist(NULL, sizeof(struct memory_block));
    mem_manager.block_refs->clear(mem_manager.block_refs);
    mem_manager.allocated_bytes=0;
}

void mem_manager_destroy(){
    struct dlist_node* next=NULL;
    void* block=NULL;
    if(mem_manager.block_refs->head==NULL)  return;

    next = mem_manager.block_refs->head->next;
    while(next!=NULL){
        block = mem_manager.block_refs->head->val;

        if(block!=NULL) /*if block is NULL do not delete it, we cannot delete NULL pointers*/
            free(block);

        free(mem_manager.block_refs->head);
        mem_manager.block_refs->head = next;
        next = next->next;
    }

    free(mem_manager.block_refs->head);
    free(mem_manager.block_refs);
    mem_manager.allocated_bytes=0;
}

void* allocate(unsigned char byte_size, unsigned int amount){
    struct memory_block* mem_block = malloc(sizeof(struct memory_block));
    void* block = malloc(byte_size*amount);
    mem_manager.allocated_bytes+=(amount*byte_size);

    mem_block->ptr = block;
    mem_block->block_size = (amount * byte_size);
    mem_manager.block_refs->push_back(mem_manager.block_refs,mem_block);
    return block;
}

void destroy(void* block){
    int pop_idx=0;
    struct dlist_node* actual = mem_manager.block_refs->head;
    struct memory_block* mem_block;
    void* block_ptr=NULL;

    while(actual!=NULL){
        mem_block = (struct memory_block*)actual->val;
        if(mem_block==NULL) goto get_next;

        block_ptr = mem_block->ptr;
        if(block_ptr==block){
            free(block_ptr);
            mem_manager.allocated_bytes-=mem_block->block_size;
            mem_manager.block_refs->pop(mem_manager.block_refs,pop_idx);
            return;
        }

    get_next:
        actual = actual->next;
        pop_idx++;
    }
}