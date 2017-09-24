  /* ---------- Cortex-M3 port ----- */
  /* ------------------------------- */

#if defined (__ICCARM__)    // IAR ARM

#define align_attr_start
#define align_attr_end

#elif defined (__GNUC__)    //-- GNU Compiler

#define align_attr_start
#define align_attr_end     __attribute__((aligned(0x8)))

#elif defined ( __CC_ARM )  //-- RealView Compiler

#define align_attr_start   __align(8)
#define align_attr_end

#else

  #error "Unknown compiler"

#endif

void int_exit(void);
void arm_disable_interrupts(void);
void arm_enable_interrupts(void);
void switch_context(void);

