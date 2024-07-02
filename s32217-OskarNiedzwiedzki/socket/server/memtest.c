#include <unistd.h>
#include <stdio.h>
#include "memory_manager.h"
#include "memory_watch.h"


void print_mem_info(char* msg){
    printf("%s\n",msg);
    printf("Bytes allocated: %ld, memory blocks count: %d\n\n", mem_manager.allocated_bytes, mem_manager.block_refs->get_size(mem_manager.block_refs));
}

void print_mem_watch(char* msg){
    printf("%s\n", msg);
    printf("Pointers watched: %ld\n\n", mem_watch.ref_count);
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

    /*memory watch tests*/
    mem_watch_init();
    print_mem_watch("Memory watch init");
    /*
    FILE* null_file=NULL;
    watch(null_file);
    print_mem_watch("Mem watch add null file");
    mem_watch_delete_null();
    print_mem_watch("Mem watch delete null pointers");
    */
    FILE* f = fopen("memtest.c", "rb");
    FILE* Fn =NULL;
    watch(f);
    print_mem_watch("Mem watch watch file pointer");
    watch(Fn);
    mem_watch_delete_null();
    print_mem_watch("Mem watch delete null pointers (file is not null)");
    unwatch(f);
    print_mem_watch("Unwatch file pointer");
    watch(f);
    f = fclose(f);
    print_mem_watch("mem watch file closed");
    mem_watch_delete_null();
    print_mem_watch("mem watch delete null (file was closed)");


    mem_manager_destroy();
    print_mem_info("Memory manager destroy");
    mem_watch_destroy();
    print_mem_watch("Memory watch destroy");



    return 0;
}