/*
   wrapper functions for system malloc -- keep malloc stats.
   Truilkan@TMI - 92/04/17
*/

/* config.h gets INLINE */
#include "config.h"

typedef struct stats_s {
	unsigned long free_calls, alloc_calls, realloc_calls;
} stats_t;

static stats_t stats;

void sysmalloc_init()
{
	stats.free_calls = 0;
	stats.alloc_calls = 0;
	stats.realloc_calls = 0;
}

INLINE void *sysrealloc(ptr,size)
void *ptr;
int size;
{
	stats.realloc_calls++;
	return (void *)realloc(ptr,size);
}

INLINE void *sysmalloc(size)
int size;
{
	stats.alloc_calls++;
	return (void *)malloc(size);
}

INLINE void *syscalloc(nitems,size)
int nitems;
int size;
{
	stats.alloc_calls++;
	return (void *)calloc(nitems,size);
}

INLINE void sysfree(ptr)
void *ptr;
{
	stats.free_calls++;
	free(ptr);
}

void dump_malloc_data()
{
	add_message("using system malloc:\n\n");
	add_message("#alloc calls:     %10lu\n",stats.alloc_calls);
	add_message("#free calls:      %10lu\n",stats.free_calls);
	add_message("#alloc - #free:   %10lu\n",
		stats.alloc_calls - stats.free_calls);
	add_message("#realloc calls:   %10lu\n",stats.realloc_calls);
}