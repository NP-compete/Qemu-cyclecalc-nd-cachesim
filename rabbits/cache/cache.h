
#ifndef CACHE_CONFIG
#define CACHE_CONFIG

#include<stdint.h>
#include<stdlib.h>
#include<stdio.h>

// Data Cache
#define DCACHE_LINES 1024
#define DCACHE_ASSOC_BITS 1
#define DCACHE_LINE_BITS 5
#define DCACHE_LINE_WORDS   (1 << (DCACHE_LINE_BITS - 2))
#define DCACHE_LINE_SIZE   (1 << DCACHE_LINE_BITS)
#define DCACHE_LINE_MASK    (DCACHE_LINE_SIZE - 1)


//Time we should wait when we will perform read/write
#define NS_DCACHE_READ 10
#define NS_DCACHE_WRITE 10


enum {
   MODIFIED = 2,
   SHARED = 1,
   INVALID = 0
};

typedef struct {
   uint8_t dirty; //Used only for write back
   uint8_t state; //Used for validity and cache coherency
} d_flags;




// Instruction Cache
#define ICACHE_LINES 1024
#define ICACHE_ASSOC_BITS 1
#define ICACHE_LINE_BITS 5

//Time we should wait when we have a miss and will perform mem access
#define NS_ICACHE 10


#endif


