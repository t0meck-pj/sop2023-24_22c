#include <unistd.h>
#include <stdio.h>
#include "memory_manager.h"


void print_mem_info(char* msg){
    printf("%s\n",msg);
    printf("Bytes allocated: %ld, memory blocks count: %d\n\n", mem_manager.allocated_bytes, mem_manager.block_refs->get_size(mem_manager.block_refs));
}

struct test_struct{
    int numbers[10];
    long int numl[10];
};

int main(){
    mem_manager_init();
    print_mem_info("Mem manager init");

    int* nums = allocate(sizeof(nums),10);
    print_mem_info("Allocated 10 INT number (4 byte size)");

    struct test_struct* tstruct = allocate(sizeof(struct test_struct), 10);
    printf("test struct size: %lu\n", sizeof(struct test_struct));
    print_mem_info("Allocated 10 struct_test structs");

    
    destroy(nums);
    print_mem_info("Destroying 10 ints");
    destroy(tstruct);
    print_mem_info("Destroying 10 test structs");


    return 0;
}