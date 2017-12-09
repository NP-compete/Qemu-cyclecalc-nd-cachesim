#ifndef ANNOTATION
#define ANNOTATION


#include<stdio.h>
#include "tcg-op.h"


//#define DEBUG_ANNOTATION

#ifdef DEBUG_ANNOTATION
# define DPRINTF(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
# define DPRINTF(fmt, ...) do {} while(0)
#endif



/***Generic Annotion (architecture independant)***/

/* Update the Current CPU */
void init_cpus(int nb);
void rabbits_cpu_update(void);

/* increment nb_cycles*/
void increment_cycles(int nb);

/* Instruction Cache */
#define MAX_ICACHE_ENTRIES 2000000

void rabbits_icache(unsigned long pc);


/* Data Cache */
#define MAX_DCACHE_ENTRIES 10000000

enum {
    STORE = 0,
    LOAD = 1,
    INVALIDATE_LINE = 2,
    INVALIDATE_ALL = 3,
    FLUSH_LINE = 4,
    FLUSH_ALL = 5
    //
};

typedef struct {
    unsigned long addr;
    uint8_t flag;
    /* [Type(4bits) Size(4bits)] :
        Type : 1 if load and 0 if store and ...
        Size : [1,2,4,8] = [8bits, 16bits, 32bits, 64bits]
    */
} dcache_entry; //sizeof(dcache_entry) = 16


void rabbits_dcache_load(TCGv addr, uint8_t size);
void rabbits_dcache_store(TCGv addr, uint8_t size);
void rabbits_dcache_invalidate_line(TCGv addr);
void rabbits_dcache_invalidate_all(void);
void rabbits_dcache_flush_line(TCGv addr);
void rabbits_dcache_flush_all(void);

void rabbits_log_access(TCGv addr, uint8_t size, uint8_t type);

#endif
