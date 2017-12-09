#include "annotation.h"
#include "../cache/cache.h"


/* We use a BIG table to log all the PC of executed instruction
   We call the icache after the execution of each CPU
   So we don't need to store the cpu id in the table
*/
unsigned long icache_access[MAX_ICACHE_ENTRIES];
unsigned long icache_index = 0;

/*
  We need to store the PC as a global variable
  We may need it when decoding some instructions
  EX : when doing a load in ARM with Rn = PC, we get this value
*/
unsigned long global_pc = 0x0BADF00D;

/* The last PC used with icache call
   this will allow us to only do a new icache call
   if we are in a new line
   we only need the tag

  It's for the current CPU, so we need to reset it
  when the CPU change
*/
unsigned long last_pc_tag = 0xDEADBEEF;

//We decide if we call the icache for each instruction or only each new line
#define NEW_LINE

void rabbits_icache(unsigned long pc)
{

    global_pc = pc;
#ifdef NEW_LINE
    unsigned long tag = pc >> ICACHE_LINE_BITS;
    if(tag != last_pc_tag) {
#endif
        //This is a ptr to the base addr of icache_access
        TCGv_ptr access_base = tcg_const_ptr(&(icache_access[0]));
        //This is a ptr to the entry where we will log the access
        TCGv_ptr access_ptr = tcg_temp_new_ptr();
        //This a ptr to icache_index
        TCGv_ptr index_ptr = tcg_const_ptr(&icache_index);
        //This will contain the index value
        TCGv index = tcg_temp_new();
        tcg_gen_ld32u_tl(index,index_ptr,0);

        //Add the index to get the needed entry
        tcg_gen_shli_tl(index,index,3); // 2^3 = 8 = sizeof(unsigned long)
        tcg_gen_add_ptr(access_ptr,access_base,(TCGv_ptr)index);

        //Store the address
        TCGv tp = tcg_temp_new();
        tcg_gen_movi_tl(tp,pc);
        tcg_gen_st32_tl (tp, access_ptr, 0);

        //Increment the index
        tcg_gen_shri_tl(index,index,3); // 2^3 = 8 = sizeof(unsigned long)
        tcg_gen_addi_tl(index,index,1);
        tcg_gen_st32_tl(index,index_ptr,0);

        tcg_temp_free(index);
        tcg_temp_free_ptr(access_base);
        tcg_temp_free_ptr(access_ptr);
        tcg_temp_free_ptr(index_ptr);
#ifdef NEW_LINE
        last_pc_tag = tag;
    }
#endif
}

