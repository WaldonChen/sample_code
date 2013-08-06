#ifndef _CPUID_H_
#define _CPUID_H_

#include <stdio.h>
#include <linux/types.h>

struct cpuid_regs {
	__u32 eax, ebx, ecx, edx;
};

/** CPUID.0AH
EAX	Bits 07 - 00: Version ID of architectural performance monitoring
	Bits 15- 08: Number of general-purpose performance monitoring counter per logical processor
    Bits 23 - 16: Bit width of general-purpose, performance monitoring counter
	Bits 31 - 24: Length of EBX bit vector to enumerate architectural performance monitoring events
EBX Bit 00: Core cycle event not available if 1
	Bit 01: Instruction retired event not available if 1
	Bit 02: Reference cycles event not available if 1
	Bit 03: Last-level cache reference event not available if 1
	Bit 04: Last-level cache misses event not available if 1
	Bit 05: Branch instruction retired event not available if 1
	Bit 06: Branch mispredict retired event not available if 1
	Bits 31- 07: Reserved = 0
ECX Reserved = 0
EDX Bits 04 - 00: Number of fixed-function performance counters (if Version ID > 1)
	Bits 12- 05: Bit width of fixed-function performance counters (if Version ID > 1)
	Reserved = 0
*/
#define PERFMON_VERSION_ID(x)			(x & 0x0FF)
#define PERFMON_VERSION_ID_STR			\
			"Version ID of architectural performance monitoring"
#define PERFMON_GP_CNT_PER_PROCESSOR(x)	((x >> 8) & 0x0FF)
#define PERFMON_GP_CNT_PER_PROCESSOR_STR	\
			"Number of general-purpose performance monitoring "\
				"counter per logical processor"
#define PERFMON_GP_CNT_BIT_WIDTH(x)		((x >> 16) & 0x0FF)
#define PERFMON_GP_CNT_BIT_WIDTH_STR	\
			"Bit width of general-purpose, performance monitoring counter"
#define PERFMON_EBX_LEN(x)				((x >> 24) & 0x0FF)
#define PERFMON_EBX_LEN_STR				\
			"Length of EBX bit vector to enumerate architectural " \
				"performance monitoring events"

#define PRINT_EAX(x)	{ \
	printf("\n" PERFMON_VERSION_ID_STR ":\n\t%d\n", PERFMON_VERSION_ID(x)); \
	printf(PERFMON_GP_CNT_PER_PROCESSOR_STR ":\n\t%d\n", \
			PERFMON_GP_CNT_PER_PROCESSOR(x)); \
	printf(PERFMON_GP_CNT_BIT_WIDTH_STR ":\n\t%d\n", \
			PERFMON_GP_CNT_BIT_WIDTH(x)); \
	printf(PERFMON_EBX_LEN_STR ":\n\t%d\n", \
			PERFMON_EBX_LEN(x)); }

#define PERFMON_EVENT(x, bit_width, index)	\
		((index < bit_width) && (~x & (0x01 << index)))

#define PERFMON_CORE_CYCLE(x, w)		PERFMON_EVENT(x, w, 0)		// (~x & 0x00000001)
#define PERFMON_CORE_CYCLE_STR			"Core cycle event"
#define PERFMON_INSTR_RETIRED(x, w)		PERFMON_EVENT(x, w, 1)		// (x & 0x00000002)
#define PERFMON_INSTR_RETIRED_STR		"Instruction retired event"
#define PERFMON_REF_CYCLE(x, w)			PERFMON_EVENT(x, w, 2)		// (x & 0x00000004)
#define PERFMON_REF_CYCLE_STR			"Reference cycles event"
#define PERFMON_LLC_REF(x, w)			PERFMON_EVENT(x, w, 3)		//	(x & 0x00000008)
#define PERFMON_LLC_REF_STR				"Last-level cache reference event"
#define PERFMON_LLC_MISS(x, w)			PERFMON_EVENT(x, w, 4)		//	(x & 0x00000010)
#define PERFMON_LLC_MISS_STR			"Last-level cache misses event"
#define PERFMON_BRH_INSTR_RETIRED(x, w)	PERFMON_EVENT(x, w, 5)		// (x & 0x00000020)
#define PERFMON_BRH_INSTR_RETIRED_STR	"Branch instruction retired event"
#define PERFMON_BRH_MIS_PREDICT(x, w)	PERFMON_EVENT(x, w, 6)		//	(x & 0x00000040)
#define PERFMON_BRH_MIS_PREDICT_STR		"Branch mispredict retired event"

#define PRINT_EBX(ebx, eax)	{ \
	printf("\nArchitectural performance monitoring events supported by this processor:\n"); \
	if (PERFMON_CORE_CYCLE(ebx, PERFMON_EBX_LEN(eax))) { \
		printf("\t" PERFMON_CORE_CYCLE_STR "\n"); \
	} \
	if (PERFMON_INSTR_RETIRED(ebx, PERFMON_EBX_LEN(eax))) { \
		printf("\t" PERFMON_INSTR_RETIRED_STR "\n"); \
	} \
	if (PERFMON_REF_CYCLE(ebx, PERFMON_EBX_LEN(eax))) { \
		printf("\t" PERFMON_REF_CYCLE_STR "\n"); \
	} \
	if (PERFMON_LLC_REF(ebx, PERFMON_EBX_LEN(eax))) { \
		printf("\t" PERFMON_LLC_REF_STR "\n"); \
	} \
	if (PERFMON_LLC_MISS(ebx, PERFMON_EBX_LEN(eax))) { \
		printf("\t" PERFMON_LLC_MISS_STR "\n"); \
	} \
	if (PERFMON_BRH_INSTR_RETIRED(ebx, PERFMON_EBX_LEN(eax))) { \
		printf("\t" PERFMON_BRH_INSTR_RETIRED_STR "\n"); \
	} \
	if (PERFMON_BRH_MIS_PREDICT(ebx, PERFMON_EBX_LEN(eax))) { \
		printf("\t" PERFMON_BRH_MIS_PREDICT_STR "\n"); \
	} \
}

#define PERFMON_FIXED_CNT_NUM(x)		(x & 0x01F)
#define PERFMON_FIXED_CNT_NUM_STR		"Number of fixed-function performance counters"
#define PERFMON_FIXED_CNT_BIT_WIDTH(x)	((x >> 5) & 0x0FF)
#define PERFMON_FIXED_CNT_BIT_WIDTH_STR	"Bit width of fixed-function performance counters"

#define	PRINT_EDX(edx, eax)		\
	if (PERFMON_VERSION_ID(eax) > 1) { \
		printf("\n" PERFMON_FIXED_CNT_NUM_STR ":\t\t%d", PERFMON_FIXED_CNT_NUM(edx)); \
		printf("\n" PERFMON_FIXED_CNT_BIT_WIDTH_STR ":\t%d\n", \
				PERFMON_FIXED_CNT_BIT_WIDTH(edx)); \
	}


static inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
		unsigned int *ecx, unsigned int *edx)
{
	asm volatile("cpuid"
			: "=a" (*eax),
			  "=b" (*ebx),
			  "=c" (*ecx),
			  "=d" (*edx)
			: "0" (*eax), "2" (*ecx)
			: "memory");
}

inline void cpuid(struct cpuid_regs *regs)
{
	native_cpuid(&(regs->eax), &(regs->ebx), &(regs->ecx), &(regs->edx));
}

#endif
