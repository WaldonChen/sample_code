#include "cpuid.h"

int main()
{
	struct cpuid_regs regs;

	regs.eax = 0x0A;

	cpuid(&regs);

	printf("eax: %08x\tebx:%08x\tecx:%08x\tedx:%08x\n", regs.eax, regs.ebx,
			regs.ecx, regs.edx);

	PRINT_EAX(regs.eax);
	PRINT_EBX(regs.ebx, regs.eax);
	PRINT_EDX(regs.edx, regs.eax);

	return 1;
}
