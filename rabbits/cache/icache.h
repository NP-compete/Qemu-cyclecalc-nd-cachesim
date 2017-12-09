#ifndef RABBITS_ICACHE_H
#define RABBITS_ICACHE_H

#include "cache.h"

extern int nb_cpu_cache;

uint8_t (**icache_flags);
unsigned long (**icache_tag);
unsigned long *nb_icache_access;
unsigned long *nb_icache_miss;

unsigned long *ns_icache;
unsigned long *cumulate_ns_icache;


void init_icache(void);

void icache_read(int cpu, unsigned long addr);

void icache_info(void);

int icache_line_present(int cpu, int start_idx, unsigned long tag);
int icache_line_replace(int cpu, int start_idx);

void run_icache(int n, unsigned long* T, int cpu);
#endif
