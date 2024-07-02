#include "memory_watch.h"


struct memory_watch mem_watch; /*extern*/

void mem_watch_init(){
    mem_watch.ptr_refs = create_dlist(NULL, sizeof(void**));
    mem_watch.ptr_refs->clear(mem_watch.ptr_refs);
    mem_watch.ref_count=0;
}

void mem_watch_destroy(){
    mem_watch.ptr_refs->clear(mem_watch.ptr_refs); /*we cannot free these pointers, cause they are meant to be special pointers like file descriptors and etc*/
    mem_watch.ref_count=0;
    free(mem_watch.ptr_refs);
}

void watch(void* ptr){
    mem_watch.ptr_refs->push_back(mem_watch.ptr_refs, &ptr);
    mem_watch.ref_count++;
}

void unwatch(void* ptr){
    struct dlist_node* actual = mem_watch.ptr_refs->head;
    void** val=NULL;
    int pop_idx=0;

    while(actual!=NULL){
        val = (void**)(actual->val);
        if(&ptr==val){
            mem_watch.ptr_refs->pop(mem_watch.ptr_refs, pop_idx);
            mem_watch.ref_count--;
            return;
        }

        actual = actual->next;
        pop_idx++;
    }
}

void mem_watch_delete_null(){
    struct dlist_node* actual = mem_watch.ptr_refs->head;
    void** val = NULL;
    int pop_idx=0;

    while(actual!=NULL){
        val = actual->val;
        if((*val)==NULL){
            mem_watch.ptr_refs->pop(mem_watch.ptr_refs, pop_idx);
            mem_watch.ref_count--;
        }else pop_idx++;

        actual = actual->next;
        //pop_idx++;
    }
}