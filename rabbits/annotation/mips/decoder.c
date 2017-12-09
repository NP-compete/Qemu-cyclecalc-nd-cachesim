#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "tcg-op.h"

typedef struct decode_info_t
{
    uint32_t opcode;
    uint32_t opcode5;
    uint32_t rs;
    uint32_t rt;
    uint32_t rd;
    uint32_t sa;
    uint32_t op;
    uint32_t base;
    uint32_t hint;
    uint32_t sel;
    uint32_t cofun_hi;
    uint32_t cofun_lo;
    uint32_t cofun;
    uint32_t immediate;
    uint32_t offset;
    uint32_t target;
    uint32_t code20;
    uint32_t code10;
}
decode_info_t;

/* start function def */
void gen_LB (decode_info_t * info);
void gen_LBU (decode_info_t * info);
void gen_LH (decode_info_t * info);
void gen_LHU (decode_info_t * info);
void gen_LL (decode_info_t * info);
void gen_LW (decode_info_t * info);
void gen_LWL (decode_info_t * info);
void gen_LWR (decode_info_t * info);
void gen_Nope (decode_info_t * info);
void gen_SB (decode_info_t * info);
void gen_SC (decode_info_t * info);
void gen_SH (decode_info_t * info);
void gen_SW (decode_info_t * info);
void gen_SWL (decode_info_t * info);
void gen_SWR (decode_info_t * info);
/* end function def */

int binary_decoder (uint32_t opcode);
int
binary_decoder (uint32_t opcode)
{
    decode_info_t the_info, *info = &the_info;

    switch (opcode & 0xdc000000) {
    case 0x00000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0x80000000:
        {
            switch (opcode & 0x78000000) {
            case 0x00000000:
                {
                    /* Unique match */
                    /* LB */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_LB (info);
                    return 0;
                }
                break;
            case 0x20000000:
                {
                    /* Unique match */
                    /* SB */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_SB (info);
                    return 0;
                }
                break;
            default:
                return 1;
            }
        }
        break;
    case 0x40000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0xc0000000:
        {
            if ((opcode & 0x78000000) == 0x60000000) {
                /* Unique match */
                /* SC */
                info->base = (opcode >> 0x15) & 0x1f;
                info->rt = (opcode >> 0x10) & 0x1f;
                info->offset = (opcode >> 0x0) & 0xffff;
                gen_SC (info);
                return 0;
            } else {
                /* Unique match */
                /* LL */
                info->base = (opcode >> 0x15) & 0x1f;
                info->rt = (opcode >> 0x10) & 0x1f;
                info->offset = (opcode >> 0x0) & 0xffff;
                gen_LL (info);
                return 0;
            }
        }
        break;
    case 0x10000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0x90000000:
        {
            switch (opcode & 0x78000000) {
            case 0x10000000:
                {
                    /* Unique match */
                    /* LBU */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_LBU (info);
                    return 0;
                }
                break;
            case 0x30000000:
                {
                    /* Unique match */
                    /* Nope */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_Nope (info);
                    return 0;
                }
                break;
            default:
                return 1;
            }
        }
        break;
    case 0x50000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0xd0000000:
        {
            switch (opcode & 0x78000000) {
            case 0x50000000:
                {
                    /* Unique match */
                    /* Nope */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_Nope (info);
                    return 0;
                }
                break;
            case 0x70000000:
                {
                    /* Unique match */
                    /* Nope */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_Nope (info);
                    return 0;
                }
                break;
            default:
                return 1;
            }
        }
        break;
    case 0x08000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0x88000000:
        {
            switch (opcode & 0x78000000) {
            case 0x08000000:
                {
                    /* Unique match */
                    /* LWL */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_LWL (info);
                    return 0;
                }
                break;
            case 0x28000000:
                {
                    /* Unique match */
                    /* SWL */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_SWL (info);
                    return 0;
                }
                break;
            default:
                return 1;
            }
        }
        break;
    case 0x48000000:
        {
            if ((opcode & 0x78000000) == 0x68000000) {
                /* Unique match */
                /* Nope */
                info->base = (opcode >> 0x15) & 0x1f;
                info->rt = (opcode >> 0x10) & 0x1f;
                info->offset = (opcode >> 0x0) & 0xffff;
                gen_Nope (info);
                return 0;
            } else {
                /* Unique match */
                /* Nope */
                info->opcode5 = (opcode >> 0x1a) & 0x1f;
                info->base = (opcode >> 0x15) & 0x1f;
                info->rt = (opcode >> 0x10) & 0x1f;
                info->offset = (opcode >> 0x0) & 0xffff;
                gen_Nope (info);
                return 0;
            }
        }
        break;
    case 0xc8000000:
        {
            if ((opcode & 0x78000000) == 0x68000000) {
                /* Unique match */
                /* Nope */
                info->base = (opcode >> 0x15) & 0x1f;
                info->rt = (opcode >> 0x10) & 0x1f;
                info->offset = (opcode >> 0x0) & 0xffff;
                gen_Nope (info);
                return 0;
            } else {
                /* Unique match */
                /* Nope */
                info->base = (opcode >> 0x15) & 0x1f;
                info->rt = (opcode >> 0x10) & 0x1f;
                info->offset = (opcode >> 0x0) & 0xffff;
                gen_Nope (info);
                return 0;
            }
        }
        break;
    case 0x18000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0x98000000:
        {
            switch (opcode & 0x78000000) {
            case 0x18000000:
                {
                    /* Unique match */
                    /* LWR */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_LWR (info);
                    return 0;
                }
                break;
            case 0x38000000:
                {
                    /* Unique match */
                    /* SWR */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_SWR (info);
                    return 0;
                }
                break;
            default:
                return 1;
            }
        }
        break;
    case 0x58000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0xd8000000:
        {
            switch (opcode & 0x78000000) {
            case 0x58000000:
                {
                    /* Unique match */
                    /* Nope */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_Nope (info);
                    return 0;
                }
                break;
            case 0x78000000:
                {
                    /* Unique match */
                    /* Nope */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_Nope (info);
                    return 0;
                }
                break;
            default:
                return 1;
            }
        }
        break;
    case 0x04000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0x84000000:
        {
            switch (opcode & 0x78000000) {
            case 0x00000000:
                {
                    /* Unique match */
                    /* LH */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_LH (info);
                    return 0;
                }
                break;
            case 0x20000000:
                {
                    /* Unique match */
                    /* SH */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_SH (info);
                    return 0;
                }
                break;
            default:
                return 1;
            }
        }
        break;
    case 0x44000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0xc4000000:
        {
            if ((opcode & 0x78000000) == 0x60000000) {
                /* Unique match */
                /* Nope */
                info->base = (opcode >> 0x15) & 0x1f;
                info->rt = (opcode >> 0x10) & 0x1f;
                info->offset = (opcode >> 0x0) & 0xffff;
                gen_Nope (info);
                return 0;
            } else {
                /* Unique match */
                /* Nope */
                info->base = (opcode >> 0x15) & 0x1f;
                info->rt = (opcode >> 0x10) & 0x1f;
                info->offset = (opcode >> 0x0) & 0xffff;
                gen_Nope (info);
                return 0;
            }
        }
        break;
    case 0x14000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0x94000000:
        {
            switch (opcode & 0x78000000) {
            case 0x10000000:
                {
                    /* Unique match */
                    /* LHU */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_LHU (info);
                    return 0;
                }
                break;
            case 0x30000000:
                {
                    /* Unique match */
                    /* Nope */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_Nope (info);
                    return 0;
                }
                break;
            default:
                return 1;
            }
        }
        break;
    case 0x54000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0xd4000000:
        {
            switch (opcode & 0x78000000) {
            case 0x50000000:
                {
                    /* Unique match */
                    /* Nope */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_Nope (info);
                    return 0;
                }
                break;
            case 0x70000000:
                {
                    /* Unique match */
                    /* Nope */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_Nope (info);
                    return 0;
                }
                break;
            default:
                return 1;
            }
        }
        break;
    case 0x0c000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0x8c000000:
        {
            switch (opcode & 0x78000000) {
            case 0x08000000:
                {
                    /* Unique match */
                    /* LW */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_LW (info);
                    return 0;
                }
                break;
            case 0x28000000:
                {
                    /* Unique match */
                    /* SW */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_SW (info);
                    return 0;
                }
                break;
            default:
                return 1;
            }
        }
        break;
    case 0x4c000000:
        {
            if ((opcode & 0x78000000) == 0x68000000) {
                /* Unique match */
                /* Nope */
                info->base = (opcode >> 0x15) & 0x1f;
                info->rt = (opcode >> 0x10) & 0x1f;
                info->offset = (opcode >> 0x0) & 0xffff;
                gen_Nope (info);
                return 0;
            } else {
                /* Unique match */
                /* Nope */
                info->opcode5 = (opcode >> 0x1a) & 0x1f;
                info->base = (opcode >> 0x15) & 0x1f;
                info->rt = (opcode >> 0x10) & 0x1f;
                info->offset = (opcode >> 0x0) & 0xffff;
                gen_Nope (info);
                return 0;
            }
        }
        break;
    case 0xcc000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0x1c000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0x9c000000:
        {
            /* Unique match */
            /* Nope */
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0x5c000000:
        {
            /* Unique match */
            /* Nope */
            info->opcode5 = (opcode >> 0x1a) & 0x1f;
            info->base = (opcode >> 0x15) & 0x1f;
            info->rt = (opcode >> 0x10) & 0x1f;
            info->offset = (opcode >> 0x0) & 0xffff;
            gen_Nope (info);
            return 0;
        }
        break;
    case 0xdc000000:
        {
            switch (opcode & 0x78000000) {
            case 0x58000000:
                {
                    /* Unique match */
                    /* Nope */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_Nope (info);
                    return 0;
                }
                break;
            case 0x78000000:
                {
                    /* Unique match */
                    /* Nope */
                    info->base = (opcode >> 0x15) & 0x1f;
                    info->rt = (opcode >> 0x10) & 0x1f;
                    info->offset = (opcode >> 0x0) & 0xffff;
                    gen_Nope (info);
                    return 0;
                }
                break;
            default:
                return 1;
            }
        }
        break;
    default:
        return 1;
    }
}
/*For Debug Purpose*/
extern unsigned long mem_rabbits_count_load ;
extern unsigned long mem_rabbits_count_store ;

//#define DEBUG_COUNT

#define ADD_COUNT(SUFF) gen_count_##SUFF();

#ifdef DEBUG_COUNT
    #define GEN_COUNT(SUFF) \
    static inline void gen_count_##SUFF(void){ \
        TCGv_ptr    a = tcg_const_ptr ((tcg_target_long) &mem_rabbits_count_##SUFF); \
        TCGv    t1 = tcg_temp_new(); \
        tcg_gen_ld_tl (t1, a, 0); \
        tcg_gen_addi_tl (t1, t1, 1); \
        tcg_gen_st_tl (t1, a, 0); \
        tcg_temp_free (t1); \
        tcg_temp_free_ptr (a); \
    }
#else
    #define GEN_COUNT(SUFF) \
    static inline void gen_count_##SUFF(void){ }
#endif

GEN_COUNT(load)
GEN_COUNT(store)

/*  */


/* This represent the Value of the PC
   of the current instruction
*/
extern unsigned long global_pc;

/* This index is used in order to correctly access the TLB
   It's a bit complicated so no need to tell more about here :)
*/
extern int mmu_idx;

/* This contain the value of the Base register we will use to
   generate our mem access (Load/Store)

   In all the cases we only need to know this value to get the address
*/

extern TCGv save_base;

extern TCGv_ptr cpu_env;

static void load_access(TCGv addr, int size)
{
    TCGv_ptr tlb_addr = tcg_temp_new_ptr();
    TCGv tmp = tcg_temp_new();
    TCGv addr_value = tcg_temp_local_new();
    TCGLabel *io_load_access = gen_new_label();

    tcg_gen_mov_tl(addr_value,addr); //we use a local register to keep adr value over Jump
//    gen_helper_print_r(addr);
    ADD_COUNT(load);

    //Calculate the index from the Virtual Address
    tcg_gen_shri_tl(tmp,addr,TARGET_PAGE_BITS);

    tcg_gen_andi_tl(tmp,tmp,(CPU_TLB_SIZE - 1));

    // We do a shift to multiply with the size of TLB entry
    tcg_gen_shli_tl(tmp,tmp,5); //TODO : Replace 5 by something related with sizeof(CPUTLBEntry)

    /* Get the first address (in mem) of the first entry of TLB Table
       In other words : Get the base address of TLB Table

    */
    tcg_gen_addi_ptr(tlb_addr,cpu_env,offsetof(CPUMIPSState, tlb_table[mmu_idx][0]));

    // Add the Index to get the address of the needed entry
    tcg_gen_add_ptr(tlb_addr,tlb_addr,tmp);

    // Read the addr_read
    tcg_gen_ld32u_tl(tmp,tlb_addr,0);

    /* We do a comparaison to see if we have IO or not
        If we have an IO access we jump and we don't log the access
    */
    tcg_gen_andi_tl(tmp,tmp,~TARGET_PAGE_MASK);


    tcg_gen_brcondi_tl(TCG_COND_NE,tmp,0,io_load_access);
    //We have a mem access here
    rabbits_dcache_load(addr_value,size);

    gen_set_label(io_load_access);

    tcg_temp_free (tmp);
    tcg_temp_free (addr_value);
    tcg_temp_free_ptr (tlb_addr);

}

static void store_access(TCGv addr, int size)
{
    TCGv_ptr tlb_addr = tcg_temp_new_ptr();
    TCGv tmp = tcg_temp_new();
    TCGv addr_value = tcg_temp_local_new();
    TCGLabel *io_store_access = gen_new_label();

    tcg_gen_mov_tl(addr_value,addr); //we use a local register to keep adr value over Jump
//    gen_helper_print_r(addr);
    ADD_COUNT(store);

    /* Calculate the index from the Virtual Address*/
    tcg_gen_shri_tl(tmp,addr,TARGET_PAGE_BITS);

    tcg_gen_andi_tl(tmp,tmp,(CPU_TLB_SIZE - 1));

    // We do a shift to multiply with the size of TLB entry
    tcg_gen_shli_tl(tmp,tmp,5); //TODO : Replace 5 by something related with sizeof(CPUTLBEntry)
    /* */

    /* Get the first address (in mem) of the first entry of TLB Table
       In other words : Get the base address of TLB Table

    */
    tcg_gen_addi_ptr(tlb_addr,cpu_env,offsetof(CPUMIPSState, tlb_table[mmu_idx][0]));

    /* Add the Index to get the address of the needed entry*/
    tcg_gen_add_ptr(tlb_addr,tlb_addr,tmp);

    // Read the addr_write
    tcg_gen_ld32u_tl(tmp,tlb_addr,8);

    /* We do a comparaison to see if we have IO or not
        If we have an IO access we jump and we don't log the access
    */
    tcg_gen_andi_tl(tmp,tmp,~TARGET_PAGE_MASK);


    tcg_gen_brcondi_tl(TCG_COND_NE,tmp,0,io_store_access);
    //We have a mem access here
    rabbits_dcache_store(addr_value,size);

    gen_set_label(io_store_access);

    tcg_temp_free (tmp);
    tcg_temp_free (addr_value);
    tcg_temp_free_ptr (tlb_addr);
}



void gen_LB(decode_info_t *tmp)
{
    TCGv addr = tcg_temp_new();

    if(tmp->base == 0) {
        tcg_gen_movi_tl(addr, (int16_t)tmp->offset);
    } else if (tmp->offset == 0) {
        tcg_gen_mov_tl(addr, save_base);
    } else {
        tcg_gen_mov_tl(addr, save_base);
        tcg_gen_addi_tl(addr, addr, (int16_t)tmp->offset);
    }

    load_access(addr,1);
    tcg_temp_free(addr);

}

void gen_LBU(decode_info_t *tmp)
{
    //Should be the same as LB
    gen_LB(tmp);
}

void gen_LH(decode_info_t *tmp)
{
    TCGv addr = tcg_temp_new();

    if(tmp->base == 0) {
        tcg_gen_movi_tl(addr, (int16_t)tmp->offset);
    } else if (tmp->offset == 0) {
        tcg_gen_mov_tl(addr, save_base);
    } else {
        tcg_gen_mov_tl(addr, save_base);
        tcg_gen_addi_tl(addr, addr, (int16_t)tmp->offset);
    }

    load_access(addr,2);
    tcg_temp_free(addr);

}

void gen_LHU(decode_info_t *tmp)
{
    //Should be the same as LH
    gen_LH(tmp);
}

void gen_LW(decode_info_t *tmp)
{
    TCGv addr = tcg_temp_new();

    if(tmp->base == 0) {
        tcg_gen_movi_tl(addr, (int16_t)tmp->offset);
    } else if (tmp->offset == 0) {
        tcg_gen_mov_tl(addr, save_base);
    } else {
        tcg_gen_mov_tl(addr, save_base);
        tcg_gen_addi_tl(addr, addr, (int16_t)tmp->offset);
    }

    load_access(addr,4);
    tcg_temp_free(addr);

}

void gen_LWU(decode_info_t *tmp)
{
    //Should be the same as LW (used only in MIPS64)
    gen_LW(tmp);
}

void gen_LWL(decode_info_t *tmp)
{
    //here Qemu do a first Byte access in order to possibly trigger a page fault
    //No need to consider this access
    TCGv addr = tcg_temp_new();

    if(tmp->base == 0) {
        tcg_gen_movi_tl(addr, (int16_t)tmp->offset);
    } else if (tmp->offset == 0) {
        tcg_gen_mov_tl(addr, save_base);
    } else {
        tcg_gen_mov_tl(addr, save_base);
        tcg_gen_addi_tl(addr, addr, (int16_t)tmp->offset);
    }

    //We do an alignement, refer to Mips DOC to understand why
    tcg_gen_andi_tl(addr,addr,~3);

    //we load a 32bit but in reality we need only 16bits
    load_access(addr,4);
    tcg_temp_free(addr);

}

void gen_LWR(decode_info_t *tmp)
{
    //We do almost the same as LWL, the only difference
    //is the processing of the data but here we don't have data
    gen_LWL(tmp);
}


void gen_SB(decode_info_t *tmp)
{
    TCGv addr = tcg_temp_new();

    if(tmp->base == 0) {
        tcg_gen_movi_tl(addr, (int16_t)tmp->offset);
    } else if (tmp->offset == 0) {
        tcg_gen_mov_tl(addr, save_base);
    } else {
        tcg_gen_mov_tl(addr, save_base);
        tcg_gen_addi_tl(addr, addr, (int16_t)tmp->offset);
    }

    store_access(addr,1);
    tcg_temp_free(addr);

}

void gen_SH(decode_info_t *tmp)
{
    TCGv addr = tcg_temp_new();

    if(tmp->base == 0) {
        tcg_gen_movi_tl(addr, (int16_t)tmp->offset);
    } else if (tmp->offset == 0) {
        tcg_gen_mov_tl(addr, save_base);
    } else {
        tcg_gen_mov_tl(addr, save_base);
        tcg_gen_addi_tl(addr, addr, (int16_t)tmp->offset);
    }

    store_access(addr,2);
    tcg_temp_free(addr);


}
void gen_SW(decode_info_t *tmp)
{
    TCGv addr = tcg_temp_new();

    if(tmp->base == 0) {
        tcg_gen_movi_tl(addr, (int16_t)tmp->offset);
    } else if (tmp->offset == 0) {
        tcg_gen_mov_tl(addr, save_base);
    } else {
        tcg_gen_mov_tl(addr, save_base);
        tcg_gen_addi_tl(addr, addr, (int16_t)tmp->offset);
    }

    store_access(addr,4);
    tcg_temp_free(addr);

}
void gen_SWL(decode_info_t *tmp)
{
    //Need to see more detail on how this is done on Qemu Side
}
void gen_SWR(decode_info_t *tmp)
{
    //Need to see more detail on how this is done on Qemu Side
}


//We consider Load Link like a normal load, so it's like LW
//Qemu did a lot of complicated things ... maybe we have to consider them
void gen_LL(decode_info_t *tmp)
{
    gen_LW(tmp);
}

//We consider Store Conditional like a normal store, so it's like SW
//Qemu did a lot of complicated things ... maybe we have to consider them
void gen_SC(decode_info_t *tmp)
{
    gen_SW(tmp);
}

void gen_Nope(decode_info_t *tmp)
{

}
