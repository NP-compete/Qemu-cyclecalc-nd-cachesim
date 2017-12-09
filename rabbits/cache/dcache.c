/*
 *  This file is part of Rabbits
 *  Copyright (C) 2015  Clement Deschamps and Luc Michel
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "dcache.h"


void init_dcache()
{
    int i, line, w;

    dcache_tag = (unsigned long **)malloc(nb_cpu_cache *  sizeof (unsigned long *));
    for (i = 0; i < nb_cpu_cache; i++) {
        dcache_tag[i] = (unsigned long *)malloc(DCACHE_LINES *  sizeof (unsigned long));
        for (line = 0; line < DCACHE_LINES; line++)
            dcache_tag[i][line] = 0x8BADF00D;
    }
    dcache_flags = (d_flags **)malloc(nb_cpu_cache * sizeof (d_flags *));
    for (i = 0; i < nb_cpu_cache; i++) {
        dcache_flags[i] = (d_flags *)malloc(DCACHE_LINES * sizeof (d_flags));
        for (line = 0; line < DCACHE_LINES; line++) {
            dcache_flags[i][line].dirty = 0;
            dcache_flags[i][line].state = INVALID;
        }
    }


    nb_dcache_miss = (unsigned long *)malloc(nb_cpu_cache * sizeof(unsigned long));

    nb_mem_read = (unsigned long *)malloc(nb_cpu_cache * sizeof(unsigned long));
    nb_dcache_read = (unsigned long *)malloc(nb_cpu_cache * sizeof(unsigned long));

    nb_mem_write = (unsigned long *)malloc(nb_cpu_cache * sizeof(unsigned long));
    nb_dcache_write = (unsigned long *)malloc(nb_cpu_cache * sizeof(unsigned long));

    ns_dcache = (unsigned long *)malloc(nb_cpu_cache * sizeof(unsigned long));
    cumulate_ns_dcache = (unsigned long *)malloc(nb_cpu_cache * sizeof(unsigned long));

    for(i = 0; i < nb_cpu_cache; i++) {
        nb_dcache_miss[i] = 0;
        nb_mem_read[i] = 0;
        nb_dcache_read[i] = 0;
        nb_mem_write[i] = 0;
        nb_dcache_write[i] = 0;
        ns_dcache[i] = 0;
        cumulate_ns_dcache[i] = 0;
    }
}
/*
qemu_dcache::~qemu_dcache()
{
    int i;

    if(dcache_tag) {
        for(i = 0; i < nb_cpu_cache; i++)
            if(dcache_tag[i])
                delete dcache_tag[i];
        delete dcache_tag;
    }

    if(dcache_flags) {
        for(i = 0; i < nb_cpu_cache; i++)
            if(dcache_flags[i])
                delete dcache_flags[i];
        delete dcache_flags;
    }

    if(cumulate_ns_dcache) {
        delete cumulate_ns_dcache;
    }

    if(ns_dcache)
         delete ns_dcache;

    if(nb_mem_read)
         delete nb_mem_read;

    if(nb_mem_write)
         delete nb_mem_write;

    if(nb_dcache_miss)
         delete nb_dcache_miss;
}
*/
void dcache_info()
{
    int i;
    for(i=0;i<nb_cpu_cache;i++) {
        printf("Dcache read for CPU[%d] = %lu\n",i,nb_dcache_read[i]);
        printf("Dcache miss for CPU[%d] = %lu\n",i,nb_dcache_miss[i]);
        printf("Mem read for CPU[%d] = %lu\n",i,nb_mem_read[i]);
        printf("Dcache write for CPU[%d] = %lu\n",i,nb_dcache_write[i]);
        printf("Mem write for CPU[%d] = %lu\n",i,nb_mem_write[i]);
//        printf("time consumed for CPU[%d] = %lu\n",i,cumulate_ns_dcache[i]);
    }

}


int dcache_line_present(int cpu, int start_idx, unsigned long tag)
{
    int idx, last_idx = start_idx + (1 << DCACHE_ASSOC_BITS);
    for (idx = start_idx; idx < last_idx; idx++)
        if (tag == dcache_tag[cpu][idx])
            return idx;
    return -1;
}

int dcache_line_replace(int cpu, int start_idx)
{
    int idx, last_idx = start_idx + (1 << DCACHE_ASSOC_BITS);
    for (idx = start_idx; idx < last_idx; idx++)
        if (dcache_flags[cpu][idx].state == INVALID)
            return idx;
    return start_idx + (((1 << DCACHE_ASSOC_BITS) - 1) & random());
}

void dcache_read(int cpu, unsigned long addr)
{
    int idx, start_idx;
    unsigned long tag;

    tag = addr >> DCACHE_LINE_BITS;
    start_idx = tag & (DCACHE_LINES - 1) & ~((1 << DCACHE_ASSOC_BITS) - 1);
    idx = dcache_line_present(cpu, start_idx, tag);

    if (idx == -1 || dcache_flags[cpu][idx].state == INVALID) { /* cache miss */
        nb_dcache_miss[cpu]++;

        idx = dcache_line_replace(cpu, start_idx);
        dcache_tag[cpu][idx] = tag;
        dcache_flags[cpu][idx].state = SHARED;

        //If a processor own the data (state = Modified) we should update it to Shared
        //Only one CPU can have the Modified state
        // --> At the end we only have Shared state for this data in all the CPU
        int c, ic;
        for(c = 0; c < nb_cpu_cache && c != cpu; c++) {
            ic = dcache_line_present(c, start_idx, tag);
            if(ic != -1 && dcache_flags[c][ic].state == MODIFIED) {
                dcache_flags[c][ic].state = SHARED;
            }
        }

        //calculate cycles (the late cache configuration)
        ns_dcache[cpu] += NS_DCACHE_READ;
        cumulate_ns_dcache[cpu] += NS_DCACHE_READ;
        nb_mem_read[cpu]++;
     }

}

void dcache_read_q(int cpu, unsigned long addr,
                    int count)
{

    if(count == 1) {//here we are sure it will be always 1 cause we cannot call recursivly the read_q
        nb_dcache_read[cpu]++;
    }

    dcache_read_l(cpu, addr, 0);
    dcache_read_l(cpu, addr + 4, 0);

}

void dcache_read_l(int cpu, unsigned long addr,
                    int count)
{
    if(count == 1) {
        nb_dcache_read[cpu]++;
    }

    if ( ((addr & DCACHE_LINE_MASK) + 3) < DCACHE_LINE_SIZE ) /* We are not at a cache line boundary so we don't care about alignement*/
        dcache_read(cpu, addr);
    else { /* Here we are at a cache line boundary, we have 2 cases*/
        if (addr & 1) {
            dcache_read_b(cpu, addr + 0, 0);
            dcache_read_w(cpu, addr + 1, 0); /* half word aligned for sure, next cache line if 3 */
            dcache_read_b(cpu, addr + 3, 0); /* on next cache line */
        } else {
            dcache_read_w(cpu, addr + 0, 0); /* half word aligned for sure */
            dcache_read_w(cpu, addr + 2, 0); /* half word aligned on next cache line */
        }
    }
}

void dcache_read_w(int cpu, unsigned long addr,
                    int count)
{
    if(count == 1) {
        nb_dcache_read[cpu]++;
    }

    if ( ((addr & DCACHE_LINE_MASK) + 1) < DCACHE_LINE_SIZE ) /* We are not at a cache line boundary */
        dcache_read(cpu, addr);
    else {/* Here we are at a cache line boundary, we have only 1 case */
        dcache_read_b(cpu, addr + 0, 0);
        dcache_read_b(cpu, addr + 1, 0);
    }
}

void dcache_read_b(int cpu, unsigned long addr,
                    int count)
{
    if(count == 1) {
        nb_dcache_read[cpu]++;
    }

    dcache_read(cpu, addr);
}



void dcache_write(int cpu, unsigned long addr)
{

    unsigned long tag = addr >> DCACHE_LINE_BITS;
    unsigned long ofs = addr & DCACHE_LINE_MASK;
    int idx, start_idx;

    start_idx = tag & (DCACHE_LINES - 1) & ~((1 << DCACHE_ASSOC_BITS) - 1);
    idx = dcache_line_present(cpu, start_idx, tag);

    if (idx == -1 || dcache_flags[cpu][idx].state == INVALID) { /* cache miss  */
        //we work with allocate on write, so in all the cases we will write on cache and mem
        idx = dcache_line_replace(cpu, start_idx);
        dcache_tag[cpu][idx] = tag;
    }
    if(dcache_flags[cpu][idx].state != MODIFIED) //we don't own the data (cache miss or state = shared)
    {
        dcache_flags[cpu][idx].state = MODIFIED;
        //we need to invalidate the other caches
        int c, ic;
        for(c = 0; c < nb_cpu_cache && c != cpu; c++) {
            ic = dcache_line_present(c, start_idx, tag);
            if(ic != -1 && dcache_flags[c][ic].state != INVALID) //maybe we will find one Modifed or many Shared
                dcache_flags[c][ic].state = INVALID;
        }
    }

    //calculate cycles (the late cache configuration)
    ns_dcache[cpu] += NS_DCACHE_WRITE;
    cumulate_ns_dcache[cpu] += NS_DCACHE_WRITE;
    nb_mem_write[cpu]++;
}

void dcache_write_q(int cpu, unsigned long addr,
                    int count)
{
    if(count == 1) {
        nb_dcache_write[cpu]++;
    }

    dcache_write_l(cpu, addr + 0, 0);
    dcache_write_l(cpu, addr + 4, 0);
}

void dcache_write_l(int cpu, unsigned long addr,
                    int count)
{
    if(count == 1) {
        nb_dcache_write[cpu]++;
    }

    if (( (addr & DCACHE_LINE_MASK) + 3) < DCACHE_LINE_SIZE) {
        dcache_write(cpu, addr);
    } else { /* Unaligned*/
        if (addr & 1) {
            dcache_write_b(cpu, addr + 0, 0);
            dcache_write_w(cpu, addr + 1, 0);
            dcache_write_b(cpu, addr + 3, 0);
        } else {
            dcache_write_w(cpu, addr + 0, 0);
            dcache_write_w(cpu, addr + 2, 0);
        }
   }

}

void dcache_write_w(int cpu, unsigned long addr,
                    int count)
{
    if(count == 1) {
        nb_dcache_write[cpu]++;
    }

    if (((addr & DCACHE_LINE_MASK) + 1) < DCACHE_LINE_SIZE) {
        dcache_write(cpu, addr);
    } else { /* Unaligned */
        dcache_write_b(cpu, addr + 0, 0);
        dcache_write_b(cpu, addr + 1, 0);
    }
}


void dcache_write_b(int cpu, unsigned long addr,
                    int count)
{
    if(count == 1) {
        nb_dcache_write[cpu]++;
    }

    dcache_write(cpu, addr);
}

void dcache_invalidate(int cpu, unsigned long addr)
{
    int idx, start_idx;
    unsigned long tag;

    tag = addr >> DCACHE_LINE_BITS;
    start_idx = tag & (DCACHE_LINES - 1) & ~((1 << DCACHE_ASSOC_BITS) - 1);
    idx = dcache_line_present(cpu, start_idx, tag);

    if(idx != -1)
        dcache_flags[cpu][idx].state = INVALID;
}

void dcache_flush(int cpu, unsigned long addr)
{
//To be implemented when we deal with write back
//now we just call cache invalidate

    dcache_invalidate(cpu,addr);
}


void run_dcache(int n, dcache_entry* T, int cpu)
{
    int i,type,size;
    for(i = 0; i < n; i++) {
        type = T[i].flag >> 4;
        size = T[i].flag & 0xf;
        if(type == 0) { //STORE
            switch (size) {
            case 1:
                dcache_write_b(cpu,T[i].addr,1);
                break;
            case 2:
                dcache_write_w(cpu,T[i].addr,1);
                break;
            case 4:
                dcache_write_l(cpu,T[i].addr,1);
                break;
            case 8:
                dcache_write_q(cpu,T[i].addr,1);
                break;
            }
        } else if(type == 1){ //LOAD
            switch (size) {
            case 1:
                dcache_read_b(cpu,T[i].addr,1);
                break;
            case 2:
                dcache_read_w(cpu,T[i].addr,1);
                break;
            case 4:
                dcache_read_l(cpu,T[i].addr,1);
                break;
            case 8:
                dcache_read_q(cpu,T[i].addr,1);
                break;
            }
        }


    }


}
