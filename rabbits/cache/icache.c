#include "icache.h"

void init_icache(void)
{
    int i, line;

    icache_tag = (unsigned long **)malloc(nb_cpu_cache *  sizeof (unsigned long *));
    for (i = 0; i < nb_cpu_cache; i++) {
        icache_tag[i] = (unsigned long *)malloc(ICACHE_LINES *  sizeof (unsigned long));
        for (line = 0; line < ICACHE_LINES; line++)
            icache_tag[i][line] = 0x8BADF00D;
    }
    icache_flags = (uint8_t **)malloc(nb_cpu_cache * sizeof (uint8_t *));
    for (i = 0; i < nb_cpu_cache; i++) {
        icache_flags[i] = (uint8_t *)malloc(ICACHE_LINES * sizeof (uint8_t));
        for (line = 0; line < ICACHE_LINES; line++) {
            icache_flags[i][line] = 0;
        }
    }

    nb_icache_access = (unsigned long *)malloc(nb_cpu_cache * sizeof(unsigned long));
    nb_icache_miss = (unsigned long *)malloc(nb_cpu_cache * sizeof(unsigned long));

    ns_icache = (unsigned long *)malloc(nb_cpu_cache * sizeof(unsigned long));
    cumulate_ns_icache = (unsigned long *)malloc(nb_cpu_cache * sizeof(unsigned long));

    for(i = 0; i < nb_cpu_cache; i++) {
        nb_icache_access[i] = 0;
        nb_icache_miss[i] = 0;
        ns_icache[i] = 0;
        cumulate_ns_icache[i] = 0;
    }
}
/*
qemu_icache::~qemu_icache()
{
    int i;

    if(icache_tag) {
        for(i = 0; i < nb_cpu_cache; i++)
            if(icache_tag[i])
                delete icache_tag[i];
        delete icache_tag;
    }

    if(icache_flags) {
        for(i = 0; i < nb_cpu_cache; i++)
            if(icache_flags[i])
                delete icache_flags[i];
        delete icache_flags;
    }

    if(cumulate_ns_icache) {
        delete cumulate_ns_icache;
    }

    if(ns_icache)
         delete ns_icache;

    if(nb_icache_access)
         delete nb_icache_access;

    if(nb_icache_miss)
         delete nb_icache_miss;
}
*/
void icache_info()
{
    int i;
    for(i=0;i<nb_cpu_cache;i++) {
        printf("Icache access for CPU[%d] = %lu\n",i,nb_icache_access[i]);
        printf("Icache miss for CPU[%d] = %lu\n",i,nb_icache_miss[i]);
//        printf("time consumed for CPU[%d] = %lu\n",i,cumulate_ns_icache[i]);
    }

}

int icache_line_present(int cpu, int start_idx, unsigned long tag)
{
    int idx, last_idx = start_idx + (1 << ICACHE_ASSOC_BITS);
    for (idx = start_idx; idx < last_idx; idx++)
        if (tag == icache_tag[cpu][idx])
            return idx;
    return -1;
}

int icache_line_replace(int cpu, int start_idx)
{
    int idx, last_idx = start_idx + (1 << ICACHE_ASSOC_BITS);
    for (idx = start_idx; idx < last_idx; idx++)
        if (icache_flags[cpu][idx] == 0)
            return idx;
    return start_idx + (((1 << ICACHE_ASSOC_BITS) - 1) & random());
}


void icache_read(int cpu, unsigned long addr)
{
    unsigned long   tag = addr >> ICACHE_LINE_BITS;
    int             idx, start_idx;

    nb_icache_access[cpu]++;
    start_idx = tag & (ICACHE_LINES - 1) & ~((1 << ICACHE_ASSOC_BITS) - 1);
    idx = icache_line_present(cpu, start_idx, tag);

    if (idx == -1 || icache_flags[cpu][idx] == 0) {
        nb_icache_miss[cpu]++;

        idx = icache_line_replace(cpu, start_idx);

        icache_tag[cpu][idx] = tag;
        icache_flags[cpu][idx] = 1;

        //calculate cycles (the late cache configuration)
        ns_icache[cpu] += NS_ICACHE;
        cumulate_ns_icache[cpu] += NS_ICACHE;
    }

}

void run_icache(int n, unsigned long* T, int cpu)
{
    int i;
    for(i = 0; i < n; i++) {
        icache_read(cpu,T[i]);
    }
}
