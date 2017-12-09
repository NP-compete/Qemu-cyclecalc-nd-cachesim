#include "../annotation.h"
#include "annotation.h"

/*This is needed to access the TLB in order to know
  if we have I/O access or Mem access
*/
int mmu_idx;


TCGv save_base;

void rabbits_mips_call_before(uint32_t pc, TCGv base, int b)
{

    // icache management
    rabbits_icache(pc);

    //We need to get the value of the Base before Qemu change it
    //We will use it to calculate the Addresse
    save_base = tcg_temp_local_new();
    if(b)
        tcg_gen_mov_tl(save_base,base);
    increment_cycles(1); //each instruction will at least take 1 cycle so we do it here
    //We do this here cause even the Unexecuted instruction take 1 cycle
}


void rabbits_mips_call_after(uint32_t insn, int idx)
{
    // dcache management and cycle calculation
    /* We will use our own decoder in order to :
        - Extract all memory access (load/store)
        - Extract 'exotic' instruction (invalidate, flush, etc)
        - calculate cycles for each instruction that take more than 1 cycle
    */
    mmu_idx=idx;
    binary_decoder(insn);
    tcg_temp_free(save_base);
}


