// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2012 Nobuhiro Iwamatsu <nobuhiro.iwamatsu.yj@renesas.com>
 * (C) Copyright 2012 Renesas Solutions Corp.
 * [r8a774a1 revision specific]
 * (C) Copyright 2019 Renesas Electronics Corporation
 */
#include <common.h>
#include <asm/io.h>
#include <linux/ctype.h>

#ifdef CONFIG_ARCH_CPU_INIT
int arch_cpu_init(void)
{
	icache_enable();
	return 0;
}
#endif

/* R-Car Gen3 d-caches are enabled in memmap-gen3.c */
#ifndef CONFIG_RCAR_GEN3
#ifndef CONFIG_SYS_DCACHE_OFF
void enable_caches(void)
{
	dcache_enable();
}
#endif
#endif

#ifdef CONFIG_DISPLAY_CPUINFO
static u32 __rmobile_get_cpu_type(void)
{
	return 0x0;
}
u32 rmobile_get_cpu_type(void)
		__attribute__((weak, alias("__rmobile_get_cpu_type")));

static u32 __rmobile_get_cpu_rev_integer(void)
{
	return 0;
}
u32 rmobile_get_cpu_rev_integer(void)
		__attribute__((weak, alias("__rmobile_get_cpu_rev_integer")));

static u32 __rmobile_get_cpu_rev_fraction(void)
{
	return 0;
}
u32 rmobile_get_cpu_rev_fraction(void)
		__attribute__((weak, alias("__rmobile_get_cpu_rev_fraction")));

/* CPU infomation table */
static const struct {
	u16 cpu_type;
	u8 cpu_name[10];
} rmobile_cpuinfo[] = {
	{ RMOBILE_CPU_TYPE_SH73A0, "SH73A0" },
	{ RMOBILE_CPU_TYPE_R8A7740, "R8A7740" },
	{ RMOBILE_CPU_TYPE_R8A7790, "R8A7790" },
	{ RMOBILE_CPU_TYPE_R8A7791, "R8A7791" },
	{ RMOBILE_CPU_TYPE_R8A7792, "R8A7792" },
	{ RMOBILE_CPU_TYPE_R8A7793, "R8A7793" },
	{ RMOBILE_CPU_TYPE_R8A7794, "R8A7794" },
	{ RMOBILE_CPU_TYPE_R8A774E1, "R8A774E1" },
	{ RMOBILE_CPU_TYPE_R8A774A1, "R8A774A1" },
	{ RMOBILE_CPU_TYPE_R8A774B1, "R8A774B1" },
	{ RMOBILE_CPU_TYPE_R8A77970, "R8A77970" },
	{ RMOBILE_CPU_TYPE_R8A774C0, "R8A774C0" },
	{ RMOBILE_CPU_TYPE_R8A77995, "R8A77995" },
	{ 0x0, "CPU" },
};

static int rmobile_cpuinfo_idx(void)
{
	unsigned int i = 0;
	u32 cpu_type = rmobile_get_cpu_type();

	for (; i < ARRAY_SIZE(rmobile_cpuinfo); i++)
		if (rmobile_cpuinfo[i].cpu_type == cpu_type)
			break;

	return i;
}

#ifdef CONFIG_ARCH_MISC_INIT
int arch_misc_init(void)
{
	int i, idx = rmobile_cpuinfo_idx();
	char cpu[10] = { 0 };
	u16 cut_ver;

	if ((rmobile_cpuinfo[idx].cpu_type == RMOBILE_CPU_TYPE_R8A774A1) &&
		(rmobile_get_cpu_rev_integer() == 3) &&
		(rmobile_get_cpu_rev_fraction() == 0))
	{
		env_set("platform", "r8a774a3");
	}
	else
	{
		for (i = 0; i < sizeof(cpu); i++)
			cpu[i] = tolower(rmobile_cpuinfo[idx].cpu_name[i]);

		env_set("platform", cpu);
	}

	i = rmobile_cpuinfo_idx();
	if ((rmobile_cpuinfo[i].cpu_type == RMOBILE_CPU_TYPE_R8A774A1) &&
		(rmobile_get_cpu_rev_integer() == 1) &&
		(rmobile_get_cpu_rev_fraction() == 1))
	{
		cut_ver = 0x12;
	}
	else
	{
		cut_ver = (rmobile_get_cpu_rev_integer() * 0x10) + rmobile_get_cpu_rev_fraction();
	}
	env_set_hex("cut_ver", cut_ver);

	return 0;
}
#endif

int print_cpuinfo(void)
{
	int i = rmobile_cpuinfo_idx();

	/* specific case */
	if (rmobile_cpuinfo[i].cpu_type == RMOBILE_CPU_TYPE_R8A774A1) {
		if ((rmobile_get_cpu_rev_integer() == 1) &&
		    (rmobile_get_cpu_rev_fraction() == 1)) {
			printf("CPU: Renesas Electronics R8A774A1 rev 1.1/rev 1.2\n");
			return 0;
		}

		if ((rmobile_get_cpu_rev_integer() == 3) &&
		    (rmobile_get_cpu_rev_fraction() == 0)) {
			printf("CPU: Renesas Electronics R8A774A3\n");
			return 0;
		}
	}

	printf("CPU: Renesas Electronics %s rev %d.%d\n",
	       rmobile_cpuinfo[i].cpu_name, rmobile_get_cpu_rev_integer(),
		rmobile_get_cpu_rev_fraction());

	return 0;
}
#endif /* CONFIG_DISPLAY_CPUINFO */
