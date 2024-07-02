#ifndef MEMORY_WATCH_H
#define MEMORY_WATCH_H
#include "DList.h"
#include <stdio.h>

struct memory_watch{
    struct dlist* ptr_refs;
    unsigned long ref_count;
}extern mem_watch;

void watch(void*); /*adds given pointer to watch*/
void unwatch(void*); /*removes given pointer from watch if it is watched*/
void mem_watch_delete_null(); /*deletes all freed pointeres from watch*/

void mem_watch_init();
void mem_watch_destroy();

#endif