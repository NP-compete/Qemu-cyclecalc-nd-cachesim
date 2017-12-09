#ifndef RABBITS_DCACHE_H
#define RABBITS_DCACHE_H

#include "cache.h"

//TODO: try to remove this !!
#include "../annotation/annotation.h"


//This contain the number of CPU.
int nb_cpu_cache;


d_flags (**dcache_flags);
unsigned long (**dcache_tag);

unsigned long *nb_dcache_miss;
unsigned long *nb_dcache_read;
unsigned long *nb_mem_read;


unsigned long *nb_dcache_write;
unsigned long *nb_mem_write;

unsigned long *ns_dcache;
unsigned long *cumulate_ns_dcache;


void init_dcache(void);

void dcache_read_b(int cpu, unsigned long addr,
                        int count); /*since we can call recursivly our functions
                                    we use this var to avoid over counting*/

void dcache_read_w(int cpu, unsigned long addr,
                        int count);

void dcache_read_l(int cpu, unsigned long addr,
                        int count);

void dcache_read_q(int cpu, unsigned long addr,
                        int count);

void dcache_write_b(int cpu, unsigned long addr,
                        int count);

void dcache_write_w(int cpu, unsigned long addr,
                        int count);

void dcache_write_l(int cpu, unsigned long addr,
                        int count);

void dcache_write_q(int cpu, unsigned long addr,
                        int count);

void dcache_info(void);

//Use by a CPU to invalidate it's own cache (generally sw invalidation)
void dcache_invalidate(int cpu, unsigned long addr);

//Use by a CPU to flush it's own cache (generally sw flush)
void dcache_flush(int cpu, unsigned long addr);

int dcache_line_present(int cpu, int start_idx, unsigned long tag);
int dcache_line_replace(int cpu, int start_idx);

void dcache_read(int cpu, unsigned long addr);

void dcache_write(int cpu, unsigned long addr);

void run_dcache(int n, dcache_entry* T, int cpu);

#endif
