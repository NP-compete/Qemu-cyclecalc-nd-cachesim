#include "annotation.h"

//The number of CPU emulated by Qemu
int rabbits_cpu = 1;
//The current CPU being run by Qemu
int32_t rabbits_cpu_index = -1;

/* The current number of cycles of the current CPU
   this number is reset when the CPU change
*/
unsigned long nb_cycles = 0;

// The total number of cycles for all the CPU
unsigned long *total_nb_cycles;

//extern declartion
extern int nb_cpu_cache;
extern unsigned long last_pc_tag;
extern dcache_entry dcache_access[MAX_DCACHE_ENTRIES];
extern unsigned long dcache_index;
extern unsigned long icache_access[MAX_ICACHE_ENTRIES];
extern unsigned long icache_index;


//This function is called anywhere to increment nb_cycles by nb
void increment_cycles(int nb)
{
    TCGv_ptr tmp = tcg_const_ptr((tcg_target_long)&nb_cycles);
    TCGv tp = tcg_temp_new();

    tcg_gen_ld32u_tl(tp,tmp,0);
    tcg_gen_addi_tl(tp,tp,nb);
    tcg_gen_st32_tl(tp,tmp,0);

    tcg_temp_free(tp);
    tcg_temp_free_ptr(tmp);
}


//We call this within qemu_main to do some initialization
void init_cpus(int nb)
{
    int i;
    rabbits_cpu = nb;
    total_nb_cycles = (unsigned long *)malloc(rabbits_cpu*sizeof(unsigned long));
    for(i = 0; i < rabbits_cpu; i++)
        total_nb_cycles[i]=0;
    dcache_index = 0;
    icache_index = 0;

    /* Cache Init */
    nb_cpu_cache = rabbits_cpu;
    init_icache();
    init_dcache();
}

//This function is called when Qemu change the CPU
void rabbits_cpu_update(void)
{
//    printf("UPDATE CALLED with %d\n",rabbits_cpu_index);
    if(rabbits_cpu_index != -1) {
//        printf(" DCache = %lu - ICache = %lu\n",dcache_index,icache_index);
        run_dcache(dcache_index,dcache_access,rabbits_cpu_index);
        run_icache(icache_index,icache_access,rabbits_cpu_index);
        total_nb_cycles[rabbits_cpu_index]+=nb_cycles;
//        printf("ICache = %lu - DCache = %lu \n",icache_index,dcache_index);
        //we do something to collect NB_Cycles and send them to SystemC
    }


    if(rabbits_cpu_index == -1)
        rabbits_cpu_index = 0;
    else
        rabbits_cpu_index++;


    if(rabbits_cpu_index == rabbits_cpu) {
    //Here we have run all the CPU once ...

    }

    //Change the CPU Index
    rabbits_cpu_index %= rabbits_cpu;

    //reset the values
    nb_cycles = 0;
    last_pc_tag = 0xDEADBEEF;
    dcache_index = 0;
    icache_index = 0;
}


static void rabbits_report(void)
{
    int i;

    for(i = 0; i < rabbits_cpu; i++)
        printf("nb cycles for CPU[%d] = %lu\n",i,total_nb_cycles[i]);
    icache_info();
    dcache_info();
}

__attribute__((constructor)) void rabbits_init(void);

void rabbits_init(void)
{
    atexit(rabbits_report);
}

