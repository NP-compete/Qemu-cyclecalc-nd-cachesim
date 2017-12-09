#include "annotation.h"


/* We use a BIG table to log all the mem access
   We call the dcache after the execution of each CPU
   So we don't need to store the cpu id in the table
*/

dcache_entry dcache_access[MAX_DCACHE_ENTRIES];
unsigned long dcache_index = 0;


//Log a load access into the table
void rabbits_dcache_load(TCGv addr, uint8_t size)
{
    rabbits_log_access(addr,size,LOAD);
}
//Log a store access into the table
void rabbits_dcache_store(TCGv addr, uint8_t size)
{
    rabbits_log_access(addr,size,STORE);
}
//Log an invalidate into the table
void rabbits_dcache_invalidate_line(TCGv addr)
{
    rabbits_log_access(addr,0,INVALIDATE_LINE);
}
//Log an invalidate all into the table
void rabbits_dcache_invalidate_all(void)
{
    TCGv tmp = tcg_temp_new();
    rabbits_log_access(tmp,0,INVALIDATE_ALL);
    tcg_temp_free(tmp);
}
//Log a flush into the table
void rabbits_dcache_flush_line(TCGv addr)
{
    rabbits_log_access(addr,0,FLUSH_LINE);
}
//Log a flush all into the table
void rabbits_dcache_flush_all(void)
{
    TCGv tmp = tcg_temp_new();
    rabbits_log_access(tmp,0,FLUSH_ALL);
    tcg_temp_free(tmp);
}


//Log something in the structure
void rabbits_log_access(TCGv addr, uint8_t size, uint8_t type)
{
    //This is a ptr to the base addr of dcache_access
    TCGv_ptr access_base = tcg_const_ptr((tcg_target_long)&(dcache_access[0]));
    //This is a ptr to the entry where we will log the access
    TCGv_ptr access_ptr = tcg_temp_new_ptr();
    //This a ptr to dcache_index
    TCGv_ptr index_ptr = tcg_const_ptr((tcg_target_long)&dcache_index);
    //This will contain the index value
    TCGv index = tcg_temp_new();
    tcg_gen_ld32u_tl(index,index_ptr,0);

//    gen_helper_print_r(addr,addr);
    //Add the index to get the needed entry
    tcg_gen_shli_tl(index,index,4); // 2^4 = 16 = sizeof(dcache_entry)
    tcg_gen_add_ptr(access_ptr,access_base,(TCGv_ptr)index);


    //Store the address
    tcg_gen_st32_tl (addr, access_ptr, 0);

    //Store the flags
    TCGv tp = tcg_temp_new();
    tcg_gen_movi_tl(tp, ((type << 4) | size) );
    tcg_gen_st8_tl (tp, access_ptr, 8);


    //Increment the index
    tcg_gen_shri_tl(index,index,4); // 2^4 = 16 = sizeof(dcache_entry)
    tcg_gen_addi_tl(index,index,1);
    tcg_gen_st32_tl(index,index_ptr,0);

    tcg_temp_free(tp);
    tcg_temp_free(index);
    tcg_temp_free_ptr(access_base);
    tcg_temp_free_ptr(access_ptr);
    tcg_temp_free_ptr(index_ptr);
}




