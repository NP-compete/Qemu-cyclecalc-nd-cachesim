#include "../annotation.h"
#include "annotation.h"

/*This is needed to access the TLB in order to know
  if we have I/O access or Mem access
*/
int mmu_idx;

TCGv save_Rn;
TCGv save_Rm;

void rabbits_arm_call_before(uint32_t pc, TCGv Rn, TCGv Rm)
{

    // icache management
    rabbits_icache(pc - 4); //Qemu already incremented the PC so we decrement it

    //We need to get the value of Rn before Qmeu made the changes
    //In some cases of Load, Rn is lost so we use this
    save_Rn = tcg_temp_local_new();
    save_Rm = tcg_temp_local_new();
    tcg_gen_mov_tl(save_Rn,Rn);
    tcg_gen_mov_tl(save_Rm,Rm);

    increment_cycles(1); //each instruction will at least take 1 cycle so we do it here
    //We do this here cause even the Unexecuted instruction take 1 cycle
}


void rabbits_arm_call_after(uint32_t insn, int idx)
{
    // dcache management and cycle calculation
    /* We will use our own decoder in order to :
        - Extract all memory access (load/store)
        - Extract 'exotic' instruction (invalidate, flush, etc)
        - calculate cycles for each instruction that take more than 1 cycle
    */
    mmu_idx=idx;
    binary_decoder(insn);
    tcg_temp_free(save_Rn);
    tcg_temp_free(save_Rm);
}


