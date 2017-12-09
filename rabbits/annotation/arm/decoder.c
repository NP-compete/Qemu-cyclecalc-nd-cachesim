#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "tcg-op.h"

typedef struct decode_info_t
{
    uint32_t cond;
    uint32_t Rn;
    uint32_t Rm;
    uint32_t Rd;
    uint32_t Rdhi;
    uint32_t Rdlo;
    uint32_t Rs;
    uint32_t Rt;
    uint32_t Rt2;
    uint32_t register_list;
    uint32_t register_list_15;
    uint32_t imm12;
    uint32_t imm8;
    uint32_t imm4;
    uint32_t imm4H;
    uint32_t imm4L;
    uint32_t i;
    uint32_t P;
    uint32_t U;
    uint32_t B;
    uint32_t W;
    uint32_t L;
    uint32_t A;
    uint32_t S;
    uint32_t op2;
    uint32_t S_H;
    uint32_t type;
    uint32_t imm5;
}
decode_info_t;

/* start function def */
void gen_Cache_Inst (decode_info_t * info);
void gen_CLREX (decode_info_t * info);
void gen_LDM (decode_info_t * info);
void gen_LDR_Exclusive (decode_info_t * info);
void gen_LDR_Immediate_1 (decode_info_t * info);
void gen_LDR_Immediate_2 (decode_info_t * info);
void gen_LDR_Immediate_3 (decode_info_t * info);
void gen_LDR_Register_1 (decode_info_t * info);
void gen_LDR_Register_2 (decode_info_t * info);
void gen_LDR_Register_3 (decode_info_t * info);
void gen_MUL_ACC (decode_info_t * info);
void gen_MUL_ACC_long (decode_info_t * info);
void gen_Nope (decode_info_t * info);
void gen_STM (decode_info_t * info);
void gen_STR_Exclusive (decode_info_t * info);
void gen_STR_Immediate_1 (decode_info_t * info);
void gen_STR_Immediate_2 (decode_info_t * info);
void gen_STR_Immediate_3 (decode_info_t * info);
void gen_STR_Register_1 (decode_info_t * info);
void gen_STR_Register_2 (decode_info_t * info);
void gen_STR_Register_3 (decode_info_t * info);
void gen_SWP (decode_info_t * info);
/* end function def */

int binary_decoder (uint32_t opcode);
int
binary_decoder (uint32_t opcode)
{
    decode_info_t the_info, *info = &the_info;

    switch (opcode & 0x0e000000) {
    case 0x00000000:
        {
            if ((opcode & 0xf0000000) == 0xf0000000) {
                /* Unique match */
                /* Nope */
                info->imm4H = (opcode >> 0x18) & 0xf;
                info->imm4L = (opcode >> 0x14) & 0xf;
                info->imm8 = (opcode >> 0xc) & 0xff;
                info->imm12 = (opcode >> 0x0) & 0xfff;
                gen_Nope (info);
                return 0;
            } else {
                if ((opcode & 0x00000060) == 0x00000000) {
                    if ((opcode & 0x00000090) == 0x00000090) {
                        if ((opcode & 0x01000000) == 0x00000000) {
                            if ((opcode & 0x00800000) == 0x00000000) {
                                /* Unique match */
                                /* MUL_ACC */
                                info->cond = (opcode >> 0x1c) & 0xf;
                                info->U = (opcode >> 0x16) & 0x1;
                                info->A = (opcode >> 0x15) & 0x1;
                                info->S = (opcode >> 0x14) & 0x1;
                                info->Rd = (opcode >> 0x10) & 0xf;
                                info->Rn = (opcode >> 0xc) & 0xf;
                                info->Rs = (opcode >> 0x8) & 0xf;
                                info->Rm = (opcode >> 0x0) & 0xf;
                                gen_MUL_ACC (info);
                                return 0;
                            } else {
                                /* Unique match */
                                /* MUL_ACC_long */
                                info->cond = (opcode >> 0x1c) & 0xf;
                                info->U = (opcode >> 0x16) & 0x1;
                                info->A = (opcode >> 0x15) & 0x1;
                                info->S = (opcode >> 0x14) & 0x1;
                                info->Rdhi = (opcode >> 0x10) & 0xf;
                                info->Rdlo = (opcode >> 0xc) & 0xf;
                                info->Rs = (opcode >> 0x8) & 0xf;
                                info->Rm = (opcode >> 0x0) & 0xf;
                                gen_MUL_ACC_long (info);
                                return 0;
                            }
                        } else {
                            if ((opcode & 0x00000f10) == 0x00000f10) {
                                if ((opcode & 0x00900000) == 0x00800000) {
                                    /* Unique match */
                                    /* STR_Exclusive */
                                    info->cond = (opcode >> 0x1c) & 0xf;
                                    info->B = (opcode >> 0x16) & 0x1;
                                    info->W = (opcode >> 0x15) & 0x1;
                                    info->Rn = (opcode >> 0x10) & 0xf;
                                    info->Rd = (opcode >> 0xc) & 0xf;
                                    info->Rt = (opcode >> 0x0) & 0xf;
                                    gen_STR_Exclusive (info);
                                    return 0;
                                } else {
                                    if ((opcode & 0x00f00000) == 0x00700000) {
                                        /* Unique match */
                                        /* Nope */
                                        info->cond = (opcode >> 0x1c) & 0xf;
                                        info->P = (opcode >> 0x18) & 0x1;
                                        info->U = (opcode >> 0x17) & 0x1;
                                        info->B = (opcode >> 0x16) & 0x1;
                                        info->W = (opcode >> 0x15) & 0x1;
                                        info->L = (opcode >> 0x14) & 0x1;
                                        info->Rn = (opcode >> 0x10) & 0xf;
                                        info->Rt = (opcode >> 0xc) & 0xf;
                                        info->Rt2 = (opcode >> 0x8) & 0xf;
                                        info->Rm = (opcode >> 0x0) & 0xf;
                                        gen_Nope (info);
                                        return 0;
                                    } else {
                                        if ((opcode & 0x00800000) == 0x00000000) {
                                            /* Unique match */
                                            /* Nope */
                                            info->cond = (opcode >> 0x1c) & 0xf;
                                            info->P = (opcode >> 0x18) & 0x1;
                                            info->U = (opcode >> 0x17) & 0x1;
                                            info->B = (opcode >> 0x16) & 0x1;
                                            info->W = (opcode >> 0x15) & 0x1;
                                            info->L = (opcode >> 0x14) & 0x1;
                                            info->Rn = (opcode >> 0x10) & 0xf;
                                            info->Rt = (opcode >> 0xc) & 0xf;
                                            info->Rt2 = (opcode >> 0x8) & 0xf;
                                            info->Rm = (opcode >> 0x0) & 0xf;
                                            gen_Nope (info);
                                            return 0;
                                        } else {
                                            if ((opcode & 0x0000000f) ==
                                                0x0000000f) {
                                                /* Unique match */
                                                /* LDR_Exclusive */
                                                info->cond =
                                                    (opcode >> 0x1c) & 0xf;
                                                info->B =
                                                    (opcode >> 0x16) & 0x1;
                                                info->W =
                                                    (opcode >> 0x15) & 0x1;
                                                info->Rn =
                                                    (opcode >> 0x10) & 0xf;
                                                info->Rt =
                                                    (opcode >> 0xc) & 0xf;
                                                gen_LDR_Exclusive (info);
                                                return 0;
                                            } else {
                                                /* Unique match */
                                                /* Nope */
                                                info->cond =
                                                    (opcode >> 0x1c) & 0xf;
                                                info->P =
                                                    (opcode >> 0x18) & 0x1;
                                                info->U =
                                                    (opcode >> 0x17) & 0x1;
                                                info->B =
                                                    (opcode >> 0x16) & 0x1;
                                                info->W =
                                                    (opcode >> 0x15) & 0x1;
                                                info->L =
                                                    (opcode >> 0x14) & 0x1;
                                                info->Rn =
                                                    (opcode >> 0x10) & 0xf;
                                                info->Rt =
                                                    (opcode >> 0xc) & 0xf;
                                                info->Rt2 =
                                                    (opcode >> 0x8) & 0xf;
                                                info->Rm =
                                                    (opcode >> 0x0) & 0xf;
                                                gen_Nope (info);
                                                return 0;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if ((opcode & 0x00f00000) == 0x00700000) {
                                    /* Unique match */
                                    /* Nope */
                                    info->cond = (opcode >> 0x1c) & 0xf;
                                    info->P = (opcode >> 0x18) & 0x1;
                                    info->U = (opcode >> 0x17) & 0x1;
                                    info->B = (opcode >> 0x16) & 0x1;
                                    info->W = (opcode >> 0x15) & 0x1;
                                    info->L = (opcode >> 0x14) & 0x1;
                                    info->Rn = (opcode >> 0x10) & 0xf;
                                    info->Rt = (opcode >> 0xc) & 0xf;
                                    info->Rt2 = (opcode >> 0x8) & 0xf;
                                    info->Rm = (opcode >> 0x0) & 0xf;
                                    gen_Nope (info);
                                    return 0;
                                } else {
                                    if ((opcode & 0x00800000) == 0x00000000) {
                                        if ((opcode & 0x00000f00) == 0x00000000) {
                                            if ((opcode & 0x00300000) ==
                                                0x00000000) {
                                                /* Unique match */
                                                /* SWP */
                                                info->cond =
                                                    (opcode >> 0x1c) & 0xf;
                                                info->B =
                                                    (opcode >> 0x16) & 0x1;
                                                info->Rn =
                                                    (opcode >> 0x10) & 0xf;
                                                info->Rd =
                                                    (opcode >> 0xc) & 0xf;
                                                info->Rm =
                                                    (opcode >> 0x0) & 0xf;
                                                gen_SWP (info);
                                                return 0;
                                            } else {
                                                /* Unique match */
                                                /* Nope */
                                                info->cond =
                                                    (opcode >> 0x1c) & 0xf;
                                                info->P =
                                                    (opcode >> 0x18) & 0x1;
                                                info->U =
                                                    (opcode >> 0x17) & 0x1;
                                                info->B =
                                                    (opcode >> 0x16) & 0x1;
                                                info->W =
                                                    (opcode >> 0x15) & 0x1;
                                                info->L =
                                                    (opcode >> 0x14) & 0x1;
                                                info->Rn =
                                                    (opcode >> 0x10) & 0xf;
                                                info->Rt =
                                                    (opcode >> 0xc) & 0xf;
                                                info->Rt2 =
                                                    (opcode >> 0x8) & 0xf;
                                                info->Rm =
                                                    (opcode >> 0x0) & 0xf;
                                                gen_Nope (info);
                                                return 0;
                                            }
                                        } else {
                                            /* Unique match */
                                            /* Nope */
                                            info->cond = (opcode >> 0x1c) & 0xf;
                                            info->P = (opcode >> 0x18) & 0x1;
                                            info->U = (opcode >> 0x17) & 0x1;
                                            info->B = (opcode >> 0x16) & 0x1;
                                            info->W = (opcode >> 0x15) & 0x1;
                                            info->L = (opcode >> 0x14) & 0x1;
                                            info->Rn = (opcode >> 0x10) & 0xf;
                                            info->Rt = (opcode >> 0xc) & 0xf;
                                            info->Rt2 = (opcode >> 0x8) & 0xf;
                                            info->Rm = (opcode >> 0x0) & 0xf;
                                            gen_Nope (info);
                                            return 0;
                                        }
                                    } else {
                                        /* Unique match */
                                        /* Nope */
                                        info->cond = (opcode >> 0x1c) & 0xf;
                                        info->P = (opcode >> 0x18) & 0x1;
                                        info->U = (opcode >> 0x17) & 0x1;
                                        info->B = (opcode >> 0x16) & 0x1;
                                        info->W = (opcode >> 0x15) & 0x1;
                                        info->L = (opcode >> 0x14) & 0x1;
                                        info->Rn = (opcode >> 0x10) & 0xf;
                                        info->Rt = (opcode >> 0xc) & 0xf;
                                        info->Rt2 = (opcode >> 0x8) & 0xf;
                                        info->Rm = (opcode >> 0x0) & 0xf;
                                        gen_Nope (info);
                                        return 0;
                                    }
                                }
                            }
                        }
                    } else {
                        /* Unique match */
                        /* Nope */
                        info->cond = (opcode >> 0x1c) & 0xf;
                        info->P = (opcode >> 0x18) & 0x1;
                        info->U = (opcode >> 0x17) & 0x1;
                        info->B = (opcode >> 0x16) & 0x1;
                        info->W = (opcode >> 0x15) & 0x1;
                        info->L = (opcode >> 0x14) & 0x1;
                        info->Rn = (opcode >> 0x10) & 0xf;
                        info->Rt = (opcode >> 0xc) & 0xf;
                        info->imm12 = (opcode >> 0x0) & 0xfff;
                        gen_Nope (info);
                        return 0;
                    }
                } else {
                    if ((opcode & 0x00000090) == 0x00000090) {
                        switch (opcode & 0x005000c0) {
                        case 0x00000080:
                            {
                                /* Unique match */
                                /* STR_Register_2 */
                                info->cond = (opcode >> 0x1c) & 0xf;
                                info->P = (opcode >> 0x18) & 0x1;
                                info->U = (opcode >> 0x17) & 0x1;
                                info->W = (opcode >> 0x15) & 0x1;
                                info->Rn = (opcode >> 0x10) & 0xf;
                                info->Rt = (opcode >> 0xc) & 0xf;
                                info->Rm = (opcode >> 0x0) & 0xf;
                                gen_STR_Register_2 (info);
                                return 0;
                            }
                            break;
                        case 0x00400080:
                            {
                                /* Unique match */
                                /* STR_Immediate_2 */
                                info->cond = (opcode >> 0x1c) & 0xf;
                                info->P = (opcode >> 0x18) & 0x1;
                                info->U = (opcode >> 0x17) & 0x1;
                                info->W = (opcode >> 0x15) & 0x1;
                                info->Rn = (opcode >> 0x10) & 0xf;
                                info->Rt = (opcode >> 0xc) & 0xf;
                                info->imm4H = (opcode >> 0x8) & 0xf;
                                info->imm4L = (opcode >> 0x0) & 0xf;
                                gen_STR_Immediate_2 (info);
                                return 0;
                            }
                            break;
                        case 0x00100080:
                            {
                                /* Unique match */
                                /* LDR_Register_2 */
                                info->cond = (opcode >> 0x1c) & 0xf;
                                info->P = (opcode >> 0x18) & 0x1;
                                info->U = (opcode >> 0x17) & 0x1;
                                info->W = (opcode >> 0x15) & 0x1;
                                info->Rn = (opcode >> 0x10) & 0xf;
                                info->Rt = (opcode >> 0xc) & 0xf;
                                info->S_H = (opcode >> 0x5) & 0x3;
                                info->Rm = (opcode >> 0x0) & 0xf;
                                gen_LDR_Register_2 (info);
                                return 0;
                            }
                            break;
                        case 0x00500080:
                            {
                                /* Unique match */
                                /* LDR_Immediate_2 */
                                info->cond = (opcode >> 0x1c) & 0xf;
                                info->P = (opcode >> 0x18) & 0x1;
                                info->U = (opcode >> 0x17) & 0x1;
                                info->W = (opcode >> 0x15) & 0x1;
                                info->Rn = (opcode >> 0x10) & 0xf;
                                info->Rt = (opcode >> 0xc) & 0xf;
                                info->imm4H = (opcode >> 0x8) & 0xf;
                                info->S_H = (opcode >> 0x5) & 0x3;
                                info->imm4L = (opcode >> 0x0) & 0xf;
                                gen_LDR_Immediate_2 (info);
                                return 0;
                            }
                            break;
                        case 0x000000c0:
                            {
                                if ((opcode & 0x00000020) == 0x00000000) {
                                    /* Unique match */
                                    /* LDR_Register_3 */
                                    info->cond = (opcode >> 0x1c) & 0xf;
                                    info->P = (opcode >> 0x18) & 0x1;
                                    info->U = (opcode >> 0x17) & 0x1;
                                    info->W = (opcode >> 0x15) & 0x1;
                                    info->Rn = (opcode >> 0x10) & 0xf;
                                    info->Rt = (opcode >> 0xc) & 0xf;
                                    info->Rm = (opcode >> 0x0) & 0xf;
                                    gen_LDR_Register_3 (info);
                                    return 0;
                                } else {
                                    /* Unique match */
                                    /* STR_Register_3 */
                                    info->cond = (opcode >> 0x1c) & 0xf;
                                    info->P = (opcode >> 0x18) & 0x1;
                                    info->U = (opcode >> 0x17) & 0x1;
                                    info->W = (opcode >> 0x15) & 0x1;
                                    info->Rn = (opcode >> 0x10) & 0xf;
                                    info->Rt = (opcode >> 0xc) & 0xf;
                                    info->Rm = (opcode >> 0x0) & 0xf;
                                    gen_STR_Register_3 (info);
                                    return 0;
                                }
                            }
                            break;
                        case 0x004000c0:
                            {
                                if ((opcode & 0x00000020) == 0x00000000) {
                                    /* Unique match */
                                    /* LDR_Immediate_3 */
                                    info->cond = (opcode >> 0x1c) & 0xf;
                                    info->P = (opcode >> 0x18) & 0x1;
                                    info->U = (opcode >> 0x17) & 0x1;
                                    info->W = (opcode >> 0x15) & 0x1;
                                    info->Rn = (opcode >> 0x10) & 0xf;
                                    info->Rt = (opcode >> 0xc) & 0xf;
                                    info->imm4H = (opcode >> 0x8) & 0xf;
                                    info->imm4L = (opcode >> 0x0) & 0xf;
                                    gen_LDR_Immediate_3 (info);
                                    return 0;
                                } else {
                                    /* Unique match */
                                    /* STR_Immediate_3 */
                                    info->cond = (opcode >> 0x1c) & 0xf;
                                    info->P = (opcode >> 0x18) & 0x1;
                                    info->U = (opcode >> 0x17) & 0x1;
                                    info->W = (opcode >> 0x15) & 0x1;
                                    info->Rn = (opcode >> 0x10) & 0xf;
                                    info->Rt = (opcode >> 0xc) & 0xf;
                                    info->imm4H = (opcode >> 0x8) & 0xf;
                                    info->imm4L = (opcode >> 0x0) & 0xf;
                                    gen_STR_Immediate_3 (info);
                                    return 0;
                                }
                            }
                            break;
                        case 0x001000c0:
                            {
                                /* Unique match */
                                /* LDR_Register_2 */
                                info->cond = (opcode >> 0x1c) & 0xf;
                                info->P = (opcode >> 0x18) & 0x1;
                                info->U = (opcode >> 0x17) & 0x1;
                                info->W = (opcode >> 0x15) & 0x1;
                                info->Rn = (opcode >> 0x10) & 0xf;
                                info->Rt = (opcode >> 0xc) & 0xf;
                                info->S_H = (opcode >> 0x5) & 0x3;
                                info->Rm = (opcode >> 0x0) & 0xf;
                                gen_LDR_Register_2 (info);
                                return 0;
                            }
                            break;
                        case 0x005000c0:
                            {
                                /* Unique match */
                                /* LDR_Immediate_2 */
                                info->cond = (opcode >> 0x1c) & 0xf;
                                info->P = (opcode >> 0x18) & 0x1;
                                info->U = (opcode >> 0x17) & 0x1;
                                info->W = (opcode >> 0x15) & 0x1;
                                info->Rn = (opcode >> 0x10) & 0xf;
                                info->Rt = (opcode >> 0xc) & 0xf;
                                info->imm4H = (opcode >> 0x8) & 0xf;
                                info->S_H = (opcode >> 0x5) & 0x3;
                                info->imm4L = (opcode >> 0x0) & 0xf;
                                gen_LDR_Immediate_2 (info);
                                return 0;
                            }
                            break;
                        default:
                            return 1;
                        }
                    } else {
                        /* Unique match */
                        /* Nope */
                        info->cond = (opcode >> 0x1c) & 0xf;
                        info->P = (opcode >> 0x18) & 0x1;
                        info->U = (opcode >> 0x17) & 0x1;
                        info->B = (opcode >> 0x16) & 0x1;
                        info->W = (opcode >> 0x15) & 0x1;
                        info->L = (opcode >> 0x14) & 0x1;
                        info->Rn = (opcode >> 0x10) & 0xf;
                        info->Rt = (opcode >> 0xc) & 0xf;
                        info->imm12 = (opcode >> 0x0) & 0xfff;
                        gen_Nope (info);
                        return 0;
                    }
                }
            }
        }
        break;
    case 0x08000000:
        {
            if ((opcode & 0xf0000000) == 0xf0000000) {
                /* Unique match */
                /* Nope */
                info->imm4H = (opcode >> 0x18) & 0xf;
                info->imm4L = (opcode >> 0x14) & 0xf;
                info->imm8 = (opcode >> 0xc) & 0xff;
                info->imm12 = (opcode >> 0x0) & 0xfff;
                gen_Nope (info);
                return 0;
            } else {
                if ((opcode & 0x00100000) == 0x00100000) {
                    /* Unique match */
                    /* LDM */
                    info->cond = (opcode >> 0x1c) & 0xf;
                    info->P = (opcode >> 0x18) & 0x1;
                    info->U = (opcode >> 0x17) & 0x1;
                    info->W = (opcode >> 0x15) & 0x1;
                    info->Rn = (opcode >> 0x10) & 0xf;
                    info->register_list = (opcode >> 0x0) & 0xffff;
                    gen_LDM (info);
                    return 0;
                } else {
                    /* Unique match */
                    /* STM */
                    info->cond = (opcode >> 0x1c) & 0xf;
                    info->P = (opcode >> 0x18) & 0x1;
                    info->U = (opcode >> 0x17) & 0x1;
                    info->W = (opcode >> 0x15) & 0x1;
                    info->Rn = (opcode >> 0x10) & 0xf;
                    info->register_list = (opcode >> 0x0) & 0xffff;
                    gen_STM (info);
                    return 0;
                }
            }
        }
        break;
    case 0x04000000:
        {
            if ((opcode & 0xf0000000) == 0xf0000000) {
                if ((opcode & 0x0f000000) == 0x05000000) {
                    if ((opcode & 0x00f00000) == 0x00700000) {
                        if ((opcode & 0x000ff000) == 0x000ff000) {
                            if ((opcode & 0x00000fff) == 0x0000001f) {
                                /* Unique match */
                                /* CLREX */
                                gen_CLREX (info);
                                return 0;
                            } else {
                                /* Unique match */
                                /* Nope */
                                info->imm4H = (opcode >> 0x18) & 0xf;
                                info->imm4L = (opcode >> 0x14) & 0xf;
                                info->imm8 = (opcode >> 0xc) & 0xff;
                                info->imm12 = (opcode >> 0x0) & 0xfff;
                                gen_Nope (info);
                                return 0;
                            }
                        } else {
                            /* Unique match */
                            /* Nope */
                            info->imm4H = (opcode >> 0x18) & 0xf;
                            info->imm4L = (opcode >> 0x14) & 0xf;
                            info->imm8 = (opcode >> 0xc) & 0xff;
                            info->imm12 = (opcode >> 0x0) & 0xfff;
                            gen_Nope (info);
                            return 0;
                        }
                    } else {
                        /* Unique match */
                        /* Nope */
                        info->imm4H = (opcode >> 0x18) & 0xf;
                        info->imm4L = (opcode >> 0x14) & 0xf;
                        info->imm8 = (opcode >> 0xc) & 0xff;
                        info->imm12 = (opcode >> 0x0) & 0xfff;
                        gen_Nope (info);
                        return 0;
                    }
                } else {
                    /* Unique match */
                    /* Nope */
                    info->imm4H = (opcode >> 0x18) & 0xf;
                    info->imm4L = (opcode >> 0x14) & 0xf;
                    info->imm8 = (opcode >> 0xc) & 0xff;
                    info->imm12 = (opcode >> 0x0) & 0xfff;
                    gen_Nope (info);
                    return 0;
                }
            } else {
                if ((opcode & 0x00100000) == 0x00100000) {
                    /* Unique match */
                    /* LDR_Immediate_1 */
                    info->cond = (opcode >> 0x1c) & 0xf;
                    info->P = (opcode >> 0x18) & 0x1;
                    info->U = (opcode >> 0x17) & 0x1;
                    info->B = (opcode >> 0x16) & 0x1;
                    info->W = (opcode >> 0x15) & 0x1;
                    info->Rn = (opcode >> 0x10) & 0xf;
                    info->Rt = (opcode >> 0xc) & 0xf;
                    info->imm12 = (opcode >> 0x0) & 0xfff;
                    gen_LDR_Immediate_1 (info);
                    return 0;
                } else {
                    /* Unique match */
                    /* STR_Immediate_1 */
                    info->cond = (opcode >> 0x1c) & 0xf;
                    info->P = (opcode >> 0x18) & 0x1;
                    info->U = (opcode >> 0x17) & 0x1;
                    info->B = (opcode >> 0x16) & 0x1;
                    info->W = (opcode >> 0x15) & 0x1;
                    info->Rn = (opcode >> 0x10) & 0xf;
                    info->Rt = (opcode >> 0xc) & 0xf;
                    info->imm12 = (opcode >> 0x0) & 0xfff;
                    gen_STR_Immediate_1 (info);
                    return 0;
                }
            }
        }
        break;
    case 0x0c000000:
        {
            if ((opcode & 0xf0000000) == 0xf0000000) {
                /* Unique match */
                /* Nope */
                info->imm4H = (opcode >> 0x18) & 0xf;
                info->imm4L = (opcode >> 0x14) & 0xf;
                info->imm8 = (opcode >> 0xc) & 0xff;
                info->imm12 = (opcode >> 0x0) & 0xfff;
                gen_Nope (info);
                return 0;
            } else {
                /* Unique match */
                /* Nope */
                info->cond = (opcode >> 0x1c) & 0xf;
                info->P = (opcode >> 0x18) & 0x1;
                info->U = (opcode >> 0x17) & 0x1;
                info->B = (opcode >> 0x16) & 0x1;
                info->W = (opcode >> 0x15) & 0x1;
                info->L = (opcode >> 0x14) & 0x1;
                info->Rn = (opcode >> 0x10) & 0xf;
                info->Rt = (opcode >> 0xc) & 0xf;
                info->imm12 = (opcode >> 0x0) & 0xfff;
                gen_Nope (info);
                return 0;
            }
        }
        break;
    case 0x02000000:
        {
            if ((opcode & 0xf0000000) == 0xf0000000) {
                /* Unique match */
                /* Nope */
                info->imm4H = (opcode >> 0x18) & 0xf;
                info->imm4L = (opcode >> 0x14) & 0xf;
                info->imm8 = (opcode >> 0xc) & 0xff;
                info->imm12 = (opcode >> 0x0) & 0xfff;
                gen_Nope (info);
                return 0;
            } else {
                /* Unique match */
                /* Nope */
                info->cond = (opcode >> 0x1c) & 0xf;
                info->P = (opcode >> 0x18) & 0x1;
                info->U = (opcode >> 0x17) & 0x1;
                info->B = (opcode >> 0x16) & 0x1;
                info->W = (opcode >> 0x15) & 0x1;
                info->L = (opcode >> 0x14) & 0x1;
                info->Rn = (opcode >> 0x10) & 0xf;
                info->Rt = (opcode >> 0xc) & 0xf;
                info->imm12 = (opcode >> 0x0) & 0xfff;
                gen_Nope (info);
                return 0;
            }
        }
        break;
    case 0x0a000000:
        {
            if ((opcode & 0xf0000000) == 0xf0000000) {
                /* Unique match */
                /* Nope */
                info->imm4H = (opcode >> 0x18) & 0xf;
                info->imm4L = (opcode >> 0x14) & 0xf;
                info->imm8 = (opcode >> 0xc) & 0xff;
                info->imm12 = (opcode >> 0x0) & 0xfff;
                gen_Nope (info);
                return 0;
            } else {
                /* Unique match */
                /* Nope */
                info->cond = (opcode >> 0x1c) & 0xf;
                info->P = (opcode >> 0x18) & 0x1;
                info->U = (opcode >> 0x17) & 0x1;
                info->B = (opcode >> 0x16) & 0x1;
                info->W = (opcode >> 0x15) & 0x1;
                info->L = (opcode >> 0x14) & 0x1;
                info->Rn = (opcode >> 0x10) & 0xf;
                info->Rt = (opcode >> 0xc) & 0xf;
                info->imm12 = (opcode >> 0x0) & 0xfff;
                gen_Nope (info);
                return 0;
            }
        }
        break;
    case 0x06000000:
        {
            if ((opcode & 0xf0000000) == 0xf0000000) {
                /* Unique match */
                /* Nope */
                info->imm4H = (opcode >> 0x18) & 0xf;
                info->imm4L = (opcode >> 0x14) & 0xf;
                info->imm8 = (opcode >> 0xc) & 0xff;
                info->imm12 = (opcode >> 0x0) & 0xfff;
                gen_Nope (info);
                return 0;
            } else {
                if ((opcode & 0x00000010) == 0x00000000) {
                    if ((opcode & 0x00100000) == 0x00100000) {
                        /* Unique match */
                        /* LDR_Register_1 */
                        info->cond = (opcode >> 0x1c) & 0xf;
                        info->P = (opcode >> 0x18) & 0x1;
                        info->U = (opcode >> 0x17) & 0x1;
                        info->B = (opcode >> 0x16) & 0x1;
                        info->W = (opcode >> 0x15) & 0x1;
                        info->Rn = (opcode >> 0x10) & 0xf;
                        info->Rt = (opcode >> 0xc) & 0xf;
                        info->imm5 = (opcode >> 0x7) & 0x1f;
                        info->type = (opcode >> 0x5) & 0x3;
                        info->Rm = (opcode >> 0x0) & 0xf;
                        gen_LDR_Register_1 (info);
                        return 0;
                    } else {
                        /* Unique match */
                        /* STR_Register_1 */
                        info->cond = (opcode >> 0x1c) & 0xf;
                        info->P = (opcode >> 0x18) & 0x1;
                        info->U = (opcode >> 0x17) & 0x1;
                        info->B = (opcode >> 0x16) & 0x1;
                        info->W = (opcode >> 0x15) & 0x1;
                        info->Rn = (opcode >> 0x10) & 0xf;
                        info->Rt = (opcode >> 0xc) & 0xf;
                        info->imm5 = (opcode >> 0x7) & 0x1f;
                        info->type = (opcode >> 0x5) & 0x3;
                        info->Rm = (opcode >> 0x0) & 0xf;
                        gen_STR_Register_1 (info);
                        return 0;
                    }
                } else {
                    /* Unique match */
                    /* Nope */
                    info->cond = (opcode >> 0x1c) & 0xf;
                    info->P = (opcode >> 0x18) & 0x1;
                    info->U = (opcode >> 0x17) & 0x1;
                    info->B = (opcode >> 0x16) & 0x1;
                    info->W = (opcode >> 0x15) & 0x1;
                    info->L = (opcode >> 0x14) & 0x1;
                    info->Rn = (opcode >> 0x10) & 0xf;
                    info->Rt = (opcode >> 0xc) & 0xf;
                    info->imm5 = (opcode >> 0x7) & 0x1f;
                    info->type = (opcode >> 0x5) & 0x3;
                    info->Rm = (opcode >> 0x0) & 0xf;
                    gen_Nope (info);
                    return 0;
                }
            }
        }
        break;
    case 0x0e000000:
        {
            if ((opcode & 0xf0000000) == 0xf0000000) {
                /* Unique match */
                /* Nope */
                info->imm4H = (opcode >> 0x18) & 0xf;
                info->imm4L = (opcode >> 0x14) & 0xf;
                info->imm8 = (opcode >> 0xc) & 0xff;
                info->imm12 = (opcode >> 0x0) & 0xfff;
                gen_Nope (info);
                return 0;
            } else {
                if ((opcode & 0x00f00000) == 0x00700000) {
                    /* Unique match */
                    /* Nope */
                    info->cond = (opcode >> 0x1c) & 0xf;
                    info->P = (opcode >> 0x18) & 0x1;
                    info->U = (opcode >> 0x17) & 0x1;
                    info->B = (opcode >> 0x16) & 0x1;
                    info->W = (opcode >> 0x15) & 0x1;
                    info->L = (opcode >> 0x14) & 0x1;
                    info->Rn = (opcode >> 0x10) & 0xf;
                    info->Rt = (opcode >> 0xc) & 0xf;
                    info->imm12 = (opcode >> 0x0) & 0xfff;
                    gen_Nope (info);
                    return 0;
                } else {
                    if ((opcode & 0x000ff000) == 0x000ff000) {
                        /* Unique match */
                        /* Nope */
                        info->cond = (opcode >> 0x1c) & 0xf;
                        info->P = (opcode >> 0x18) & 0x1;
                        info->U = (opcode >> 0x17) & 0x1;
                        info->B = (opcode >> 0x16) & 0x1;
                        info->W = (opcode >> 0x15) & 0x1;
                        info->L = (opcode >> 0x14) & 0x1;
                        info->Rn = (opcode >> 0x10) & 0xf;
                        info->Rt = (opcode >> 0xc) & 0xf;
                        info->imm12 = (opcode >> 0x0) & 0xfff;
                        gen_Nope (info);
                        return 0;
                    } else {
                        if ((opcode & 0x00000fff) == 0x0000001f) {
                            /* Unique match */
                            /* Nope */
                            info->cond = (opcode >> 0x1c) & 0xf;
                            info->P = (opcode >> 0x18) & 0x1;
                            info->U = (opcode >> 0x17) & 0x1;
                            info->B = (opcode >> 0x16) & 0x1;
                            info->W = (opcode >> 0x15) & 0x1;
                            info->L = (opcode >> 0x14) & 0x1;
                            info->Rn = (opcode >> 0x10) & 0xf;
                            info->Rt = (opcode >> 0xc) & 0xf;
                            info->imm12 = (opcode >> 0x0) & 0xfff;
                            gen_Nope (info);
                            return 0;
                        } else {
                            if ((opcode & 0x00400000) == 0x00000000) {
                                if ((opcode & 0x000f0000) == 0x00070000) {
                                    if ((opcode & 0x00000f10) == 0x00000f10) {
                                        if ((opcode & 0x01000000) == 0x00000000) {
                                            if ((opcode & 0x00800000) ==
                                                0x00000000) {
                                                if ((opcode & 0x00300000) ==
                                                    0x00000000) {
                                                    /* Unique match */
                                                    /* Cache_Inst */
                                                    info->cond =
                                                        (opcode >> 0x1c) & 0xf;
                                                    info->Rd =
                                                        (opcode >> 0xc) & 0xf;
                                                    info->op2 =
                                                        (opcode >> 0x5) & 0x7;
                                                    info->Rm =
                                                        (opcode >> 0x0) & 0xf;
                                                    gen_Cache_Inst (info);
                                                    return 0;
                                                } else {
                                                    /* Unique match */
                                                    /* Nope */
                                                    info->cond =
                                                        (opcode >> 0x1c) & 0xf;
                                                    info->P =
                                                        (opcode >> 0x18) & 0x1;
                                                    info->U =
                                                        (opcode >> 0x17) & 0x1;
                                                    info->B =
                                                        (opcode >> 0x16) & 0x1;
                                                    info->W =
                                                        (opcode >> 0x15) & 0x1;
                                                    info->L =
                                                        (opcode >> 0x14) & 0x1;
                                                    info->Rn =
                                                        (opcode >> 0x10) & 0xf;
                                                    info->Rt =
                                                        (opcode >> 0xc) & 0xf;
                                                    info->imm12 =
                                                        (opcode >> 0x0) & 0xfff;
                                                    gen_Nope (info);
                                                    return 0;
                                                }
                                            } else {
                                                /* Unique match */
                                                /* Nope */
                                                info->cond =
                                                    (opcode >> 0x1c) & 0xf;
                                                info->P =
                                                    (opcode >> 0x18) & 0x1;
                                                info->U =
                                                    (opcode >> 0x17) & 0x1;
                                                info->B =
                                                    (opcode >> 0x16) & 0x1;
                                                info->W =
                                                    (opcode >> 0x15) & 0x1;
                                                info->L =
                                                    (opcode >> 0x14) & 0x1;
                                                info->Rn =
                                                    (opcode >> 0x10) & 0xf;
                                                info->Rt =
                                                    (opcode >> 0xc) & 0xf;
                                                info->imm12 =
                                                    (opcode >> 0x0) & 0xfff;
                                                gen_Nope (info);
                                                return 0;
                                            }
                                        } else {
                                            /* Unique match */
                                            /* Nope */
                                            info->cond = (opcode >> 0x1c) & 0xf;
                                            info->P = (opcode >> 0x18) & 0x1;
                                            info->U = (opcode >> 0x17) & 0x1;
                                            info->B = (opcode >> 0x16) & 0x1;
                                            info->W = (opcode >> 0x15) & 0x1;
                                            info->L = (opcode >> 0x14) & 0x1;
                                            info->Rn = (opcode >> 0x10) & 0xf;
                                            info->Rt = (opcode >> 0xc) & 0xf;
                                            info->imm12 =
                                                (opcode >> 0x0) & 0xfff;
                                            gen_Nope (info);
                                            return 0;
                                        }
                                    } else {
                                        /* Unique match */
                                        /* Nope */
                                        info->cond = (opcode >> 0x1c) & 0xf;
                                        info->P = (opcode >> 0x18) & 0x1;
                                        info->U = (opcode >> 0x17) & 0x1;
                                        info->B = (opcode >> 0x16) & 0x1;
                                        info->W = (opcode >> 0x15) & 0x1;
                                        info->L = (opcode >> 0x14) & 0x1;
                                        info->Rn = (opcode >> 0x10) & 0xf;
                                        info->Rt = (opcode >> 0xc) & 0xf;
                                        info->imm12 = (opcode >> 0x0) & 0xfff;
                                        gen_Nope (info);
                                        return 0;
                                    }
                                } else {
                                    /* Unique match */
                                    /* Nope */
                                    info->cond = (opcode >> 0x1c) & 0xf;
                                    info->P = (opcode >> 0x18) & 0x1;
                                    info->U = (opcode >> 0x17) & 0x1;
                                    info->B = (opcode >> 0x16) & 0x1;
                                    info->W = (opcode >> 0x15) & 0x1;
                                    info->L = (opcode >> 0x14) & 0x1;
                                    info->Rn = (opcode >> 0x10) & 0xf;
                                    info->Rt = (opcode >> 0xc) & 0xf;
                                    info->imm12 = (opcode >> 0x0) & 0xfff;
                                    gen_Nope (info);
                                    return 0;
                                }
                            } else {
                                /* Unique match */
                                /* Nope */
                                info->cond = (opcode >> 0x1c) & 0xf;
                                info->P = (opcode >> 0x18) & 0x1;
                                info->U = (opcode >> 0x17) & 0x1;
                                info->B = (opcode >> 0x16) & 0x1;
                                info->W = (opcode >> 0x15) & 0x1;
                                info->L = (opcode >> 0x14) & 0x1;
                                info->Rn = (opcode >> 0x10) & 0xf;
                                info->Rt = (opcode >> 0xc) & 0xf;
                                info->imm12 = (opcode >> 0x0) & 0xfff;
                                gen_Nope (info);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
        break;
    default:
        return 1;
    }
}
/*For Debug Purpose*/
extern unsigned long mem_rabbits_count_8s ;
extern unsigned long mem_rabbits_count_8u ;
extern unsigned long mem_rabbits_count_16s ;
extern unsigned long mem_rabbits_count_16u ;
extern unsigned long mem_rabbits_count_32u ;
extern unsigned long mem_rabbits_count_16ua ;
extern unsigned long mem_rabbits_count_32ua ;
extern unsigned long mem_rabbits_count_8 ;
extern unsigned long mem_rabbits_count_16 ;
extern unsigned long mem_rabbits_count_32 ;


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

GEN_COUNT(8s)
GEN_COUNT(8u)
GEN_COUNT(16s)
GEN_COUNT(16u)
GEN_COUNT(32u)
GEN_COUNT(16ua)
GEN_COUNT(32ua)
GEN_COUNT(8)
GEN_COUNT(16)
GEN_COUNT(32)

/*  */

static const char *regnames[] =
    { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7",
      "r8", "r9", "r10", "r11", "r12", "r13", "r14", "pc" };

static TCGv cpu_R[16];

//We need to call this function when doing translation init
void arm_decoder_init(void);

void arm_decoder_init(void) {
    //Arm init
    int i;
    for(i = 0; i < 16; i++) {
        cpu_R[i] = tcg_global_mem_new_i32(TCG_AREG0,
                                          offsetof(CPUARMState, regs[i]),
                                          regnames[i]);
   }
}

/* This represent the Value of the PC
   of the current instruction
*/
extern unsigned long global_pc;

/* This index is used in order to correctly access the TLB
   It's a bit complicated so no need to tell more about here :)
*/
extern int mmu_idx;

/* This contain the initial values of Rn and Rm before any Qemu processing
   We have to use them :
   - In LDM when Rn belong to Reglist
   - In the other Load if Rn = Rt
   - In load with Register where Rm = Rt

  I won't take the Risk to always use this value because what i
  did is working fine for now :)
  Making changes will take a lot of times and may bring errors !
*/

extern TCGv save_Rn;
extern TCGv save_Rm;

extern TCGv_ptr cpu_env;

static void load_access(TCGv addr, int size)
{
    TCGv_ptr tlb_addr = tcg_temp_new_ptr();
    TCGv tmp = tcg_temp_new();
    TCGv addr_value = tcg_temp_local_new();
    TCGLabel *io_load_access = gen_new_label();

    tcg_gen_mov_tl(addr_value,addr); //we use a local register to keep adr value over Jump
//    gen_helper_print_r(addr);

    //Calculate the index from the Virtual Address
    tcg_gen_shri_tl(tmp,addr,TARGET_PAGE_BITS);

    tcg_gen_andi_tl(tmp,tmp,(CPU_TLB_SIZE - 1));

    // We do a shift to multiply with the size of TLB entry
    tcg_gen_shli_tl(tmp,tmp,5); //TODO : Replace 5 by something related with sizeof(CPUTLBEntry)

    /* Get the first address (in mem) of the first entry of TLB Table
       In other words : Get the base address of TLB Table

    */
    tcg_gen_addi_ptr(tlb_addr,cpu_env,offsetof(CPUARMState, tlb_table[mmu_idx][0]));

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

    /* Calculate the index from the Virtual Address*/
    tcg_gen_shri_tl(tmp,addr,TARGET_PAGE_BITS);

    tcg_gen_andi_tl(tmp,tmp,(CPU_TLB_SIZE - 1));

    // We do a shift to multiply with the size of TLB entry
    tcg_gen_shli_tl(tmp,tmp,5); //TODO : Replace 5 by something related with sizeof(CPUTLBEntry)
    /* */

    /* Get the first address (in mem) of the first entry of TLB Table
       In other words : Get the base address of TLB Table

    */
    tcg_gen_addi_ptr(tlb_addr,cpu_env,offsetof(CPUARMState, tlb_table[mmu_idx][0]));

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


//This one is like the previous one but specific to LDM only
static void load_access_m(TCGv addr, int n)
{
    TCGv_ptr tlb_addr = tcg_temp_new_ptr();
    TCGv tmp = tcg_temp_new();
    TCGv addr_value = tcg_temp_local_new();
    TCGLabel *io_load_access = gen_new_label();
    int i;

    tcg_gen_mov_tl(addr_value,addr); //we use a local register to keep adr value over Jump

    //Calculate the index from the Virtual Address
    tcg_gen_shri_tl(tmp,addr_value,TARGET_PAGE_BITS);

    tcg_gen_andi_tl(tmp,tmp,(CPU_TLB_SIZE - 1));

    // We do a shift to multiply with the size of TLB entry
    tcg_gen_shli_tl(tmp,tmp,5); //TODO : Replace 5 by something related with sizeof(CPUTLBEntry)

    /* Get the first address (in mem) of the first entry of TLB Table
       In other words : Get the base address of TLB Table

    */
    tcg_gen_addi_ptr(tlb_addr,cpu_env,offsetof(CPUARMState, tlb_table[mmu_idx][0]));

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
    for(i=0;i<n;i++) {
//        gen_helper_print_r(addr_value);
        rabbits_dcache_load(addr_value,4);
        tcg_gen_addi_tl(addr_value,addr_value,4);
    }

    gen_set_label(io_load_access);

    tcg_temp_free (tmp);
    tcg_temp_free (addr_value);
    tcg_temp_free_ptr (tlb_addr);

}

//This one is like the previous one but specific to STM only
static void store_access_m(TCGv addr, int n)
{
    TCGv_ptr tlb_addr = tcg_temp_new_ptr();
    TCGv tmp = tcg_temp_new();
    TCGv addr_value = tcg_temp_local_new();
    TCGLabel *io_store_access = gen_new_label();
    int i;

    tcg_gen_mov_tl(addr_value,addr); //we use a local register to keep adr value over Jump
/*    for(i=0;i<n;i++) {
        gen_helper_print_r(addr);
        tcg_gen_addi_tl(addr,addr,4);
    }
*/
    //Calculate the index from the Virtual Address
    tcg_gen_shri_tl(tmp,addr_value,TARGET_PAGE_BITS);

    tcg_gen_andi_tl(tmp,tmp,(CPU_TLB_SIZE - 1));

    // We do a shift to multiply with the size of TLB entry
    tcg_gen_shli_tl(tmp,tmp,5); //TODO : Replace 5 by something related with sizeof(CPUTLBEntry)

    /* Get the first address (in mem) of the first entry of TLB Table
       In other words : Get the base address of TLB Table

    */
    tcg_gen_addi_ptr(tlb_addr,cpu_env,offsetof(CPUARMState, tlb_table[mmu_idx][0]));

    // Add the Index to get the address of the needed entry
    tcg_gen_add_ptr(tlb_addr,tlb_addr,tmp);

    // Read the addr_write
    tcg_gen_ld32u_tl(tmp,tlb_addr,8);

    /* We do a comparaison to see if we have IO or not
        If we have an IO access we jump and we don't log the access
    */
    tcg_gen_andi_tl(tmp,tmp,~TARGET_PAGE_MASK);


    tcg_gen_brcondi_tl(TCG_COND_NE,tmp,0,io_store_access);
    //We have a mem access here
    for(i=0;i<n;i++) {
        //gen_helper_print_r(addr_value);
        rabbits_dcache_store(addr_value,4);
        tcg_gen_addi_tl(addr_value,addr_value,4);
    }

    gen_set_label(io_store_access);

    tcg_temp_free (tmp);
    tcg_temp_free (addr_value);
    tcg_temp_free_ptr (tlb_addr);

}

//Seems to work fine
void gen_LDM(decode_info_t *tmp)
{
    TCGv offset = tcg_temp_new();
    TCGv addr = tcg_temp_new();
    int i,n = 0;
    int strange = 0;

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);

    for(i=0;i<16;i++)
        if( tmp->register_list & (1 << i) ) {
            ADD_COUNT(32u)//mem_rabbits_count_32u++;
            n++; //we compute total number of load
            if(i == tmp->Rn)
                strange = 1; //In this case we lost the value of Rn
        }
    //Here we need to be carefull !!
    /* At this stage Qemu has done a lot of complicated things
       We need to check the W flag then [U,P]
       if W=1 (we have a write back) :
        - [1,1] = first addr need to be [Rn]+4 and we have [Rn]+n*4
        - [1,0] = first addr need to be [Rn] and we have [Rn]+n*4
        - [0,1] = first addr need to be [Rn]-(n*4) and we have [Rn]-(n*4)
        - [0,0] = first addr need to be [Rn]-((n-1)*4) and we have [Rn]-n*4
       if W=0 (we don't have write back) :
        - [1,1] = first addr need to be [Rn]+4 and we have [Rn]
        - [1,0] = first addr need to be [Rn] and we have [Rn]
        - [0,1] = first addr need to be [Rn]-(n*4) and we have [Rn]
        - [0,0] = first addr need to be [Rn]-((n-1)*4) and we have [Rn]

    */

    if(!strange) {
        if(tmp->W) {
            if(tmp->U && tmp->P)
                tcg_gen_addi_tl(addr,addr,-((n-1)*4));
            else if(tmp->U && !tmp->P)
                tcg_gen_addi_tl(addr,addr,-(n*4));
            else if(!tmp->U && !tmp->P)
                tcg_gen_addi_tl(addr,addr,4);
        } else {
            if(tmp->U && tmp->P)
                tcg_gen_addi_tl(addr,addr,4);
            else if(!tmp->U && tmp->P)
                tcg_gen_addi_tl(addr,addr,-(n*4));
            else if(!tmp->U && !tmp->P)
               tcg_gen_addi_tl(addr,addr,-((n-1)*4));
        }
    } else {
        //here i will use the save_Rn so i don't care about what Qemu did
        tcg_gen_mov_tl(addr,save_Rn);
        if(tmp->U && tmp->P)
            tcg_gen_addi_tl(addr,addr,4);
        else if(!tmp->U && tmp->P)
            tcg_gen_addi_tl(addr,addr,-(n*4));
        else if(!tmp->U && !tmp->P)
            tcg_gen_addi_tl(addr,addr,-((n-1)*4));
    }

    load_access_m(addr,n);

    increment_cycles(n+1); //In Total = +N+(n-1)S+I+S
    tcg_temp_free(offset);
    tcg_temp_free(addr);
}

//seems to work fine
void gen_STM(decode_info_t *tmp)
{
    TCGv offset = tcg_temp_new();
    TCGv addr = tcg_temp_new();
    int i,n = 0;

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);

    for(i=0;i<16;i++)
        if( tmp->register_list & (1 << i) ) {
            ADD_COUNT(32)//mem_rabbits_count_32u++;
            n++; //we compute total number of store
        }
    //same thing as for LDM
    if(tmp->W) {
        if(tmp->U && tmp->P)
            tcg_gen_addi_tl(addr,addr,-((n-1)*4));
        else if(tmp->U && !tmp->P)
            tcg_gen_addi_tl(addr,addr,-(n*4));
        else if(!tmp->U && !tmp->P)
            tcg_gen_addi_tl(addr,addr,4);
    } else {
        if(tmp->U && tmp->P)
            tcg_gen_addi_tl(addr,addr,4);
        else if(!tmp->U && tmp->P)
            tcg_gen_addi_tl(addr,addr,-(n*4));
        else if(!tmp->U && !tmp->P)
            tcg_gen_addi_tl(addr,addr,-((n-1)*4));
    }

    store_access_m(addr,n);

    increment_cycles(n+1); //In Total = +N+(n-1)S+I+N
    tcg_temp_free(offset);
    tcg_temp_free(addr);
}

//Seems to work fine
void gen_LDR_Immediate_1(decode_info_t *tmp)
{
    int offset;
    TCGv addr = tcg_temp_new();
    int strange = 0;

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else {
        if(tmp->Rn == tmp->Rt) {
            strange = 1;
            tcg_gen_mov_tl(addr,save_Rn);
        } else {
            tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);
        }
    }
    //Here we need to be carefull !!
    /* At this stage Qemu has already calculate the final address
       *If we are in Pre-index (P=1) we need to check the WriteBack flag
         -If W=0 the base address is kept so we need to do the same calculation
           done by Qemu to get the needed address
         -If W=1 the base address is already changed so we do nothing

       *If we are in Post-index (P=0) we need to undo Qemu
       calculation to get the needed address
         - So if U = 0 we do an ADD and if U = 1 we do a SUB
           it's the opposite and it's not wrong !!
    */
    offset=tmp->imm12;

    if(!strange) {
        if(!tmp->P) {
            if(tmp->U)
                offset=-offset;
            tcg_gen_addi_tl(addr,addr,offset);
        } else if(!tmp->W){
            if(!tmp->U)
                offset=-offset;
            tcg_gen_addi_tl(addr,addr,offset);
        }
    } else {
        //here i will use the save_Rn so i don't care about what Qemu did
        if(tmp->P) {
            if(!tmp->U)
                offset=-offset;
            tcg_gen_addi_tl(addr,addr,offset);
        }
    }

    if(tmp->B) {
        ADD_COUNT(8u)//mem_rabbits_count_8u++;
        load_access(addr,1);
    } else {
        ADD_COUNT(32u)// mem_rabbits_count_32u++;
        load_access(addr,4);
    }
    increment_cycles(2); //In Total = +N+I+S
    tcg_temp_free(addr);
}

//Seems to work fine
void gen_LDR_Immediate_2(decode_info_t *tmp)
{
    int offset;
    TCGv addr = tcg_temp_new();
    int strange = 0;

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else {
        if(tmp->Rn == tmp->Rt) {
            strange = 1;
            tcg_gen_mov_tl(addr,save_Rn);
         } else {
            tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);
         }
    }

    //Same as the other load for addr calculation
    offset=(tmp->imm4L | (tmp->imm4H << 4));
    if(!strange) {
        if(!tmp->P) {
            if(tmp->U)
                offset=-offset;
            tcg_gen_addi_tl(addr,addr,offset);
        } else if(!tmp->W){
            if(!tmp->U)
                offset=-offset;
            tcg_gen_addi_tl(addr,addr,offset);
        }
    } else {
        //here i will use the save_Rn so i don't care about what Qemu did
        if(tmp->P) {
            if(!tmp->U)
                offset=-offset;
            tcg_gen_addi_tl(addr,addr,offset);
        }
    }


    if(tmp->S_H == 1) {
        ADD_COUNT(16u)//mem_rabbits_count_16u++;
        load_access(addr,2);
    } else if(tmp->S_H == 2) {
        ADD_COUNT(8s)//mem_rabbits_count_8s++;
        load_access(addr,1);
    } else {
        ADD_COUNT(16s)//mem_rabbits_count_16s++;
        load_access(addr,2);
    }
    increment_cycles(2); //In Total = +N+I+S
    tcg_temp_free(addr);
}

//Seems to work fine
void gen_LDR_Immediate_3(decode_info_t *tmp)
{
    int offset;
    TCGv addr = tcg_temp_new();

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);

    //Same as the other load for addr calculation
    offset=(tmp->imm4L | (tmp->imm4H << 4));
    if(!tmp->P) {
        if(tmp->U)
            offset=-offset;
        tcg_gen_addi_tl(addr,addr,offset);
    }
    else if(!tmp->W){
        if(!tmp->U)
            offset=-offset;
        tcg_gen_addi_tl(addr,addr,offset);
    }

    ADD_COUNT(32u)//mem_rabbits_count_32u+=2;
    ADD_COUNT(32u)
    load_access(addr,8);
    increment_cycles(2); //In Total = +N+I+S
    tcg_temp_free(addr);
}

//Seems to work fine
void gen_STR_Immediate_1(decode_info_t *tmp)
{
    int offset;
    TCGv addr = tcg_temp_new();

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);

    //Here we need to be carefull !!
    /* At this stage Qemu has already calculate the final address
       *If we are in Pre-index (P=1) we need to check the WriteBack flag
         -If W=0 the base address is kept so we need to do the same calculation
           done by Qemu to get the need address
         -If W=1 the base address is already changed so we do nothing

       *If we are in Post-index (P=0) we need to undo Qemu
       calculation to get the needed address
         - So if U = 0 we do an ADD and if U = 1 we do a SUB
           it's the opposite and it's not wrong !!
    */
    offset=tmp->imm12;
    if(!tmp->P) {
        if(tmp->U)
            offset=-offset;
        tcg_gen_addi_tl(addr,addr,offset);
    }
    else if(!tmp->W){
        if(!tmp->U)
            offset=-offset;
        tcg_gen_addi_tl(addr,addr,offset);
    }
    if(tmp->B) {
        ADD_COUNT(8)//mem_rabbits_count_8++;
        store_access(addr,1);
    } else {
        ADD_COUNT(32)//mem_rabbits_count_32++;
        store_access(addr,4);
    }
    increment_cycles(1); //In Total = +N+N
    tcg_temp_free(addr);
}

//Seems to work fine
void gen_STR_Immediate_2(decode_info_t *tmp)
{
    int offset;
    TCGv addr = tcg_temp_new();

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);
    offset=(tmp->imm4L | (tmp->imm4H << 4));
    if(!tmp->P) {
        if(tmp->U)
            offset=-offset;
        tcg_gen_addi_tl(addr,addr,offset);
    }
    else if(!tmp->W){
        if(!tmp->U)
            offset=-offset;
        tcg_gen_addi_tl(addr,addr,offset);
    }
    ADD_COUNT(16)//mem_rabbits_count_16++;
    store_access(addr,2);
    increment_cycles(1); //In Total = +N+N
    tcg_temp_free(addr);
}

//Seems to work fine
void gen_STR_Immediate_3(decode_info_t *tmp)
{
    int offset;
    TCGv addr = tcg_temp_new();

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);
    offset=(tmp->imm4L | (tmp->imm4H << 4));
    if(!tmp->P) {
        if(tmp->U)
            offset=-offset;
        tcg_gen_addi_tl(addr,addr,offset);
    }
    else if(!tmp->W){
        if(!tmp->U)
            offset=-offset;
        tcg_gen_addi_tl(addr,addr,offset);
    }
    ADD_COUNT(32)
    ADD_COUNT(32)//mem_rabbits_count_32+=2;
    store_access(addr,8);
    increment_cycles(1); //In Total = +N+N
    tcg_temp_free(addr);
}

//Seems to work fine (need some optimization in order to avoid calculating offset when not needed)
void gen_LDR_Register_1(decode_info_t *tmp)
{
    TCGv offset = tcg_temp_new();
    TCGv addr = tcg_temp_new();
    int strange = 0;

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else {
        if(tmp->Rn == tmp->Rt) {
            strange = 1;
            tcg_gen_mov_tl(addr,save_Rn);
        } else {
            tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);
        }
    }

    //We calculate the offset
    if(tmp->Rm == 0xf)
        tcg_gen_movi_tl(offset,(global_pc+8));
    else {
        if(tmp->Rm == tmp->Rt) {
            tcg_gen_mov_tl(offset,save_Rm);
         } else {
            tcg_gen_mov_tl(offset,cpu_R[tmp->Rm]);
        }
    }

    switch(tmp->type) {
    case 0:
        if(tmp->imm5)
            tcg_gen_shli_tl(offset,offset,tmp->imm5);
        break;
    case 1:
        if(tmp->imm5)
            tcg_gen_shri_tl(offset,offset,tmp->imm5);
        else
            tcg_gen_movi_tl(offset,0);
        break;
    case 2:
        if(!tmp->imm5)
            tmp->imm5 = 31;
        tcg_gen_sari_tl(offset,offset,tmp->imm5);
        break;
    case 3:
        tcg_gen_rotri_tl(offset,offset,tmp->imm5);
        //need to do the case where Shift == 0
        break;
    }

    //Here we consider the same things as the Immediate load
    if(!strange) {
        if(!tmp->P) {
            if(!tmp->U)
                tcg_gen_add_tl(addr,addr,offset);
            else
                tcg_gen_sub_tl(addr,addr,offset);
        } else if(!tmp->W) {
            if(tmp->U)
                tcg_gen_add_tl(addr,addr,offset);
            else
                tcg_gen_sub_tl(addr,addr,offset);
        }
    } else {
        if(tmp->P) {
            if(tmp->U)
                tcg_gen_add_tl(addr,addr,offset);
            else
                tcg_gen_sub_tl(addr,addr,offset);
        }
    }

    if(tmp->B) {
        ADD_COUNT(8u)//mem_rabbits_count_8u++;
        load_access(addr,1);
    } else {
        ADD_COUNT(32u)//mem_rabbits_count_32u++;
        load_access(addr,4);
    }
    increment_cycles(2); //In Total = +N+I+S
    tcg_temp_free(addr);
    tcg_temp_free(offset);
}

//Seems to work fine
void gen_LDR_Register_2(decode_info_t *tmp)
{
    TCGv offset = tcg_temp_new();
    TCGv addr = tcg_temp_new();
    int strange = 0;

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else {
        if(tmp->Rn == tmp->Rt) {
            strange = 1;
            tcg_gen_mov_tl(addr,save_Rn);
        } else {
            tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);
        }
    }

    //Here we consider the same things as the Immediate load
    //We calculate the offset
    if(tmp->Rm == 0xf)
        tcg_gen_movi_tl(offset,(global_pc+8));
    else {
        if(tmp->Rm == tmp->Rt) {
            tcg_gen_mov_tl(offset,save_Rm);
         } else {
            tcg_gen_mov_tl(offset,cpu_R[tmp->Rm]);
        }
    }

    if(!strange) {
        if(!tmp->P) {
            if(!tmp->U)
                tcg_gen_add_tl(addr,addr,offset);
            else
                tcg_gen_sub_tl(addr,addr,offset);
        } else if(!tmp->W) {
            if(tmp->U)
                tcg_gen_add_tl(addr,addr,offset);
            else
                tcg_gen_sub_tl(addr,addr,offset);
        }
    } else {
        if(tmp->U)
            tcg_gen_add_tl(addr,addr,offset);
        else
            tcg_gen_sub_tl(addr,addr,offset);
    }

    if(tmp->S_H == 1) {
        ADD_COUNT(16u)//mem_rabbits_count_16u++;
        load_access(addr,2);
    } else if(tmp->S_H == 2) {
        ADD_COUNT(8s)//mem_rabbits_count_8s++;
        load_access(addr,1);
    } else {
        ADD_COUNT(16s)//mem_rabbits_count_16s++;
        load_access(addr,2);
    }
    increment_cycles(2); //In Total = +N+I+S
    tcg_temp_free(addr);
    tcg_temp_free(offset);
}

//Seems to work fine
void gen_LDR_Register_3(decode_info_t *tmp)
{
    TCGv offset = tcg_temp_new();
    TCGv addr = tcg_temp_new();

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);


    //Here we consider the same things as the Immediate load
    if(!tmp->P) {
    //We calculate the offset
        if(tmp->Rm == 0xf)
            tcg_gen_movi_tl(offset,(global_pc+8));
        else
            tcg_gen_mov_tl(offset,cpu_R[tmp->Rm]);

        if(!tmp->U)
            tcg_gen_add_tl(addr,addr,offset);
        else
            tcg_gen_sub_tl(addr,addr,offset);
    } else if(!tmp->W) {
        if(tmp->Rm == 0xf)
            tcg_gen_movi_tl(offset,(global_pc+8));
        else
            tcg_gen_mov_tl(offset,cpu_R[tmp->Rm]);

        if(tmp->U)
            tcg_gen_add_tl(addr,addr,offset);
        else
            tcg_gen_sub_tl(addr,addr,offset);
    }
    ADD_COUNT(32u)
    ADD_COUNT(32u)//mem_rabbits_count_32u+=2;
    load_access(addr,8);
    increment_cycles(2); //In Total = +N+I+S
    tcg_temp_free(addr);
    tcg_temp_free(offset);
}

//Seems to work fine
void gen_STR_Register_1(decode_info_t *tmp)
{
    TCGv offset = tcg_temp_new();
    TCGv addr = tcg_temp_new();

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);

    //We calculate the offset
    if(tmp->Rm == 0xf)
        tcg_gen_movi_tl(offset,(global_pc+8));
    else
        tcg_gen_mov_tl(offset,cpu_R[tmp->Rm]);

    switch(tmp->type) {
    case 0:
        if(tmp->imm5)
            tcg_gen_shli_tl(offset,offset,tmp->imm5);
        break;
    case 1:
        if(tmp->imm5)
            tcg_gen_shri_tl(offset,offset,tmp->imm5);
        else
            tcg_gen_movi_tl(offset,0);
        break;
    case 2:
        if(!tmp->imm5)
            tmp->imm5 = 31;
        tcg_gen_sari_tl(offset,offset,tmp->imm5);
        break;
    case 3:
        tcg_gen_rotri_tl(offset,offset,tmp->imm5);
        //need to do the case where Shift == 0
        break;
    }

    //Here we consider the same things as the Immediate load
    if(!tmp->P) {
        if(!tmp->U)
            tcg_gen_add_tl(addr,addr,offset);
        else
            tcg_gen_sub_tl(addr,addr,offset);
    } else if(!tmp->W) {
        if(tmp->U)
            tcg_gen_add_tl(addr,addr,offset);
        else
            tcg_gen_sub_tl(addr,addr,offset);
    }

    if(tmp->B) {
        ADD_COUNT(8)//mem_rabbits_count_8++;
        store_access(addr,1);
    } else {
        ADD_COUNT(32)//mem_rabbits_count_32++;
        store_access(addr,4);
    }
    increment_cycles(1); //In Total = +N+N
    tcg_temp_free(addr);
    tcg_temp_free(offset);
}

//Seems to work fine
void gen_STR_Register_2(decode_info_t *tmp)
{
    TCGv offset = tcg_temp_new();
    TCGv addr = tcg_temp_new();

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);


    //Here we consider the same things as the Immediate load
    if(!tmp->P) {
    //We calculate the offset
        if(tmp->Rm == 0xf)
            tcg_gen_movi_tl(offset,(global_pc+8));
        else
            tcg_gen_mov_tl(offset,cpu_R[tmp->Rm]);

        if(!tmp->U)
            tcg_gen_add_tl(addr,addr,offset);
        else
            tcg_gen_sub_tl(addr,addr,offset);
    } else if(!tmp->W) {
        if(tmp->Rm == 0xf)
            tcg_gen_movi_tl(offset,(global_pc+8));
        else
            tcg_gen_mov_tl(offset,cpu_R[tmp->Rm]);

        if(tmp->U)
            tcg_gen_add_tl(addr,addr,offset);
        else
            tcg_gen_sub_tl(addr,addr,offset);
    }

    ADD_COUNT(16)//mem_rabbits_count_16++;
    store_access(addr,2);
    increment_cycles(1); //In Total = +N+N
    tcg_temp_free(addr);
    tcg_temp_free(offset);
}

//Seems to work fine
void gen_STR_Register_3(decode_info_t *tmp)
{
    TCGv offset = tcg_temp_new();
    TCGv addr = tcg_temp_new();

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);


    //Here we consider the same things as the Immediate load
    if(!tmp->P) {
    //We calculate the offset
        if(tmp->Rm == 0xf)
            tcg_gen_movi_tl(offset,(global_pc+8));
        else
            tcg_gen_mov_tl(offset,cpu_R[tmp->Rm]);

        if(!tmp->U)
            tcg_gen_add_tl(addr,addr,offset);
        else
            tcg_gen_sub_tl(addr,addr,offset);
    } else if(!tmp->W) {
        if(tmp->Rm == 0xf)
            tcg_gen_movi_tl(offset,(global_pc+8));
        else
            tcg_gen_mov_tl(offset,cpu_R[tmp->Rm]);

        if(tmp->U)
            tcg_gen_add_tl(addr,addr,offset);
        else
            tcg_gen_sub_tl(addr,addr,offset);
    }

    ADD_COUNT(32)
    ADD_COUNT(32)//mem_rabbits_count_32+=2;
    store_access(addr,8);
    increment_cycles(1); //In Total = +N+N
    tcg_temp_free(addr);
    tcg_temp_free(offset);
}

void gen_LDR_Exclusive(decode_info_t *tmp)
{
    TCGv addr = tcg_temp_new();

    //Here we don't use the PC
    tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);


    /* Here we do an 'exotic' aligned load
       It's only here and i don't know why
       but we should consider it as normal load*/
    if(tmp->B) {
        if(tmp->W) {
            ADD_COUNT(16ua)//mem_rabbits_count_16ua++;
            //gen_helper_print_r(addr,reg);
            load_access(addr,2);
        } else {
            ADD_COUNT(8u)//mem_rabbits_count_8u++;
            //gen_helper_print_r(addr,reg);
            load_access(addr,1);
        }
    } else {
        if(tmp->W) {
            ADD_COUNT(32u)//mem_rabbits_count_32u++;
            ADD_COUNT(32ua)//mem_rabbits_count_32ua++;
            //gen_helper_print_r(addr,reg);
            load_access(addr,8);
        }
        else {
            ADD_COUNT(32ua)//mem_rabbits_count_32ua++;
            //gen_helper_print_r(addr,reg);
            load_access(addr,4);
        }
    }
    tcg_temp_free(addr);
}

//Seems to work fine
void gen_STR_Exclusive(decode_info_t *tmp)
{
    TCGv addr = tcg_temp_local_new(); //we use local here cause we have branch

    //Here we don't use the PC
    tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);


    /* At this stage Qemu has done everything and the Rd register is set
       We have to test the Rd register to know what happened
        - Rd = 0 : we do a Load and Store for the same address and same size
        - Rd = 1 : we do nothing
    */
    TCGv tp = tcg_temp_local_new();
    tcg_gen_mov_tl(tp,cpu_R[tmp->Rd]);
    TCGLabel *nothing_todo = gen_new_label();
    tcg_gen_brcondi_tl(TCG_COND_NE, tp, 0, nothing_todo);

    if(tmp->B) {
        if(tmp->W) {
            ADD_COUNT(16u)//mem_rabbits_count_16++;
            //gen_helper_print_r(addr,reg);
            load_access(addr,2);
            ADD_COUNT(16)//mem_rabbits_count_16++;
            //gen_helper_print_r(addr,reg);
            store_access(addr,2);
        } else {
            ADD_COUNT(8u)//mem_rabbits_count_8++;
            //gen_helper_print_r(addr,reg);
            load_access(addr,1);
            ADD_COUNT(8)//mem_rabbits_count_8++;
            //gen_helper_print_r(addr,reg);
            store_access(addr,1);
        }
    } else {
        if(tmp->W) {
            ADD_COUNT(32u)
            ADD_COUNT(32u)//mem_rabbits_count_32+=2;
            //gen_helper_print_r(addr,reg);
            load_access(addr,8);
            ADD_COUNT(32)
            ADD_COUNT(32)//mem_rabbits_count_32+=2;
            //gen_helper_print_r(addr,reg);
            store_access(addr,8);
        } else {
            ADD_COUNT(32u)//mem_rabbits_count_32++;
            //gen_helper_print_r(addr,reg);
            load_access(addr,4);
            ADD_COUNT(32)//mem_rabbits_count_32++;
            //gen_helper_print_r(addr,reg);
            store_access(addr,4);
        }
    }

    gen_set_label(nothing_todo);
    tcg_temp_free(addr);
}

void gen_CLREX(decode_info_t *tmp)
{
    //nothing to be done
}

void gen_SWP(decode_info_t *tmp)
{
    TCGv addr = tcg_temp_new();

    if(tmp->Rn == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rn]);

    if(tmp->B) {
        ADD_COUNT(8u)//mem_rabbits_count_8u++;
        ADD_COUNT(8)//mem_rabbits_count_8++;
        //gen_helper_print_r(addr,reg);
        store_access(addr,1);
        load_access(addr,1);
    } else {
        ADD_COUNT(32u)//mem_rabbits_count_32u++;
        ADD_COUNT(32)//mem_rabbits_count_32++;
        //gen_helper_print_r(addr,reg);
        store_access(addr,4);
        load_access(addr,4);
    }

    increment_cycles(3); //in Total : +N+N+I+S
    tcg_temp_free(addr);
}

void gen_MUL_ACC(decode_info_t *tmp)
{
    //try not to make a lot of jump or it will be useless...
}

void gen_MUL_ACC_long(decode_info_t *tmp)
{
    //try not to make a lot of jump or it will be useless...

}

void gen_Cache_Inst(decode_info_t *tmp)
{
    TCGv addr = tcg_temp_new();

    if(tmp->Rd == 0xf)
        tcg_gen_movi_tl(addr,(global_pc+8));
    else
        tcg_gen_mov_tl(addr,cpu_R[tmp->Rd]);

    switch(tmp->Rm) {
    case 5: //instruction Cache
        switch(tmp->op2) {
        case 0: //Invalidate entire Icache
            break;
        case 1: //Invalide Icache line
            break;
        }
    case 6: //Data Cache
        switch(tmp->op2) {
        case 0: //Invalidate entire Dcache
            rabbits_dcache_invalidate_all();
            break;
        case 1: //Invalide Dcache line
            rabbits_dcache_invalidate_line(addr);
            break;
        }
    case 7: //Invalidate both caches
        break;
    case 10: //Flush Dcache
        switch(tmp->op2) {
        case 0: //Flush entire Dcache
            rabbits_dcache_flush_all();
            break;
        case 1: //Flush Dcache line
            rabbits_dcache_flush_line(addr);
            break;
        }
        break;
    case 14: //Flush and invalidate Dcache
        break;
    }

}


void gen_Nope(decode_info_t *tmp)
{

}
