/* Based on CPU DB MC9S08QG8_24, version 3.00.012 (RegistersPrg V2.32) */
/* DataSheet : MC9S08QG8 Rev. 4 2/2008 */

#include <mc9s08qg8.h>

/*lint -save -esym(765, *) */


/* * * * *  8-BIT REGISTERS  * * * * * * * * * * * * * * * */
volatile PTADSTR _PTAD;                                    /* Port A Data Register; 0x00000000 */
volatile PTADDSTR _PTADD;                                  /* Port A Data Direction Register; 0x00000001 */
volatile PTBDSTR _PTBD;                                    /* Port B Data Register; 0x00000002 */
volatile PTBDDSTR _PTBDD;                                  /* Port B Data Direction Register; 0x00000003 */
volatile KBISCSTR _KBISC;                                  /* KBI Status and Control Register; 0x0000000C */
volatile KBIPESTR _KBIPE;                                  /* KBI Pin Enable Register; 0x0000000D */
volatile KBIESSTR _KBIES;                                  /* KBI Edge Select Register; 0x0000000E */
volatile IRQSCSTR _IRQSC;                                  /* Interrupt request status and control register; 0x0000000F */
volatile ADCSC1STR _ADCSC1;                                /* Status and Control Register 1; 0x00000010 */
volatile ADCSC2STR _ADCSC2;                                /* Status and Control Register 2; 0x00000011 */
volatile ADCCFGSTR _ADCCFG;                                /* Configuration Register; 0x00000016 */
volatile APCTL1STR _APCTL1;                                /* Pin Control 1 Register; 0x00000017 */
volatile ACMPSCSTR _ACMPSC;                                /* ACMP Status and Control Register; 0x0000001A */
volatile SCIC1STR _SCIC1;                                  /* SCI Control Register 1; 0x00000022 */
volatile SCIC2STR _SCIC2;                                  /* SCI Control Register 2; 0x00000023 */
volatile SCIS1STR _SCIS1;                                  /* SCI Status Register 1; 0x00000024 */
volatile SCIS2STR _SCIS2;                                  /* SCI Status Register 2; 0x00000025 */
volatile SCIC3STR _SCIC3;                                  /* SCI Control Register 3; 0x00000026 */
volatile SCIDSTR _SCID;                                    /* SCI Data Register; 0x00000027 */
volatile SPIC1STR _SPIC1;                                  /* SPI Control Register 1; 0x00000028 */
volatile SPIC2STR _SPIC2;                                  /* SPI Control Register 2; 0x00000029 */
volatile SPIBRSTR _SPIBR;                                  /* SPI Baud Rate Register; 0x0000002A */
volatile SPISSTR _SPIS;                                    /* SPI Status Register; 0x0000002B */
volatile SPIDSTR _SPID;                                    /* SPI Data Register; 0x0000002D */
volatile IICASTR _IICA;                                    /* IIC Address Register; 0x00000030 */
volatile IICFSTR _IICF;                                    /* IIC Frequency Divider Register; 0x00000031 */
volatile IICCSTR _IICC;                                    /* IIC Control Register; 0x00000032 */
volatile IICSSTR _IICS;                                    /* IIC Status Register; 0x00000033 */
volatile IICDSTR _IICD;                                    /* IIC Data I/O Register; 0x00000034 */
volatile ICSC1STR _ICSC1;                                  /* ICS Control Register 1; 0x00000038 */
volatile ICSC2STR _ICSC2;                                  /* ICS Control Register 2; 0x00000039 */
volatile ICSTRMSTR _ICSTRM;                                /* ICS Trim Register; 0x0000003A */
volatile ICSSCSTR _ICSSC;                                  /* ICS Status and Control Register; 0x0000003B */
volatile MTIMSCSTR _MTIMSC;                                /* MTIM Clock Configuration Register; 0x0000003C */
volatile MTIMCLKSTR _MTIMCLK;                              /* MTIM Clock Configuration Register; 0x0000003D */
volatile MTIMCNTSTR _MTIMCNT;                              /* MTIM Counter Register; 0x0000003E */
volatile MTIMMODSTR _MTIMMOD;                              /* MTIM Modulo Register; 0x0000003F */
volatile TPMSCSTR _TPMSC;                                  /* TPM Status and Control Register; 0x00000040 */
volatile TPMC0SCSTR _TPMC0SC;                              /* TPM Timer Channel 0 Status and Control Register; 0x00000045 */
volatile TPMC1SCSTR _TPMC1SC;                              /* TPM Timer Channel 1 Status and Control Register; 0x00000048 */
volatile SRSSTR _SRS;                                      /* System Reset Status Register; 0x00001800 */
volatile SBDFRSTR _SBDFR;                                  /* System Background Debug Force Reset Register; 0x00001801 */
volatile SOPT1STR _SOPT1;                                  /* System Options Register 1; 0x00001802 */
volatile SOPT2STR _SOPT2;                                  /* System Options Register 2; 0x00001803 */
volatile SRTISCSTR _SRTISC;                                /* System Real-Time Interrupt Status and Control Register; 0x00001808 */
volatile SPMSC1STR _SPMSC1;                                /* System Power Management Status and Control 1 Register; 0x00001809 */
volatile SPMSC2STR _SPMSC2;                                /* System Power Management Status and Control 2 Register; 0x0000180A */
volatile SPMSC3STR _SPMSC3;                                /* System Power Management Status and Control 3 Register; 0x0000180C */
volatile DBGCSTR _DBGC;                                    /* Debug Control Register; 0x00001816 */
volatile DBGTSTR _DBGT;                                    /* Debug Trigger Register; 0x00001817 */
volatile DBGSSTR _DBGS;                                    /* Debug Status Register; 0x00001818 */
volatile FCDIVSTR _FCDIV;                                  /* FLASH Clock Divider Register; 0x00001820 */
volatile FOPTSTR _FOPT;                                    /* FLASH Options Register; 0x00001821 */
volatile FCNFGSTR _FCNFG;                                  /* FLASH Configuration Register; 0x00001823 */
volatile FPROTSTR _FPROT;                                  /* FLASH Protection Register; 0x00001824 */
volatile FSTATSTR _FSTAT;                                  /* Flash Status Register; 0x00001825 */
volatile FCMDSTR _FCMD;                                    /* FLASH Command Register; 0x00001826 */
volatile PTAPESTR _PTAPE;                                  /* Port A Pull Enable Register; 0x00001840 */
volatile PTASESTR _PTASE;                                  /* Port A Slew Rate Enable Register; 0x00001841 */
volatile PTADSSTR _PTADS;                                  /* Port A Drive Strength Selection Register; 0x00001842 */
volatile PTBPESTR _PTBPE;                                  /* Port B Pull Enable Register; 0x00001844 */
volatile PTBSESTR _PTBSE;                                  /* Port B Slew Rate Enable Register; 0x00001845 */
volatile PTBDSSTR _PTBDS;                                  /* Port B Drive Strength Selection Register; 0x00001846 */
/* NVFTRIM - macro for reading non volatile register       Nonvolatile ICS Fine Trim; 0x0000FFAE */
/* Tip for register initialization in the user code:  const byte NVFTRIM_INIT @0x0000FFAE = <NVFTRIM_INITVAL>; */
/* NVICSTRM - macro for reading non volatile register      Nonvolatile ICS Trim Register; 0x0000FFAF */
/* Tip for register initialization in the user code:  const byte NVICSTRM_INIT @0x0000FFAF = <NVICSTRM_INITVAL>; */
/* NVBACKKEY0 - macro for reading non volatile register    Backdoor Comparison Key 0; 0x0000FFB0 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY0_INIT @0x0000FFB0 = <NVBACKKEY0_INITVAL>; */
/* NVBACKKEY1 - macro for reading non volatile register    Backdoor Comparison Key 1; 0x0000FFB1 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY1_INIT @0x0000FFB1 = <NVBACKKEY1_INITVAL>; */
/* NVBACKKEY2 - macro for reading non volatile register    Backdoor Comparison Key 2; 0x0000FFB2 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY2_INIT @0x0000FFB2 = <NVBACKKEY2_INITVAL>; */
/* NVBACKKEY3 - macro for reading non volatile register    Backdoor Comparison Key 3; 0x0000FFB3 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY3_INIT @0x0000FFB3 = <NVBACKKEY3_INITVAL>; */
/* NVBACKKEY4 - macro for reading non volatile register    Backdoor Comparison Key 4; 0x0000FFB4 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY4_INIT @0x0000FFB4 = <NVBACKKEY4_INITVAL>; */
/* NVBACKKEY5 - macro for reading non volatile register    Backdoor Comparison Key 5; 0x0000FFB5 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY5_INIT @0x0000FFB5 = <NVBACKKEY5_INITVAL>; */
/* NVBACKKEY6 - macro for reading non volatile register    Backdoor Comparison Key 6; 0x0000FFB6 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY6_INIT @0x0000FFB6 = <NVBACKKEY6_INITVAL>; */
/* NVBACKKEY7 - macro for reading non volatile register    Backdoor Comparison Key 7; 0x0000FFB7 */
/* Tip for register initialization in the user code:  const byte NVBACKKEY7_INIT @0x0000FFB7 = <NVBACKKEY7_INITVAL>; */
/* NVPROT - macro for reading non volatile register        Nonvolatile FLASH Protection Register; 0x0000FFBD */
/* Tip for register initialization in the user code:  const byte NVPROT_INIT @0x0000FFBD = <NVPROT_INITVAL>; */
/* NVOPT - macro for reading non volatile register         Nonvolatile Flash Options Register; 0x0000FFBF */
/* Tip for register initialization in the user code:  const byte NVOPT_INIT @0x0000FFBF = <NVOPT_INITVAL>; */


/* * * * *  16-BIT REGISTERS  * * * * * * * * * * * * * * * */
volatile ADCRSTR _ADCR;                                    /* Data Result Register; 0x00000012 */
volatile ADCCVSTR _ADCCV;                                  /* Compare Value Register; 0x00000014 */
volatile SCIBDSTR _SCIBD;                                  /* SCI Baud Rate Register; 0x00000020 */
volatile TPMCNTSTR _TPMCNT;                                /* TPM Timer Counter Register; 0x00000041 */
volatile TPMMODSTR _TPMMOD;                                /* TPM Timer Counter Modulo Register; 0x00000043 */
volatile TPMC0VSTR _TPMC0V;                                /* TPM Timer Channel 0 Value Register; 0x00000046 */
volatile TPMC1VSTR _TPMC1V;                                /* TPM Timer Channel 1 Value Register; 0x00000049 */
volatile SDIDSTR _SDID;                                    /* System Device Identification Register; 0x00001806 */
volatile DBGCASTR _DBGCA;                                  /* Debug Comparator A Register; 0x00001810 */
volatile DBGCBSTR _DBGCB;                                  /* Debug Comparator B Register; 0x00001812 */
volatile DBGFSTR _DBGF;                                    /* Debug FIFO Register; 0x00001814 */

/*lint -restore */

/* EOF */
