/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * include/configs/ek874.h
 *     This file is ek874 board configuration.
 *
 * Copyright (C) 2019 Renesas Electronics Corporation
 */

#ifndef __EK874_H
#define __EK874_H

#undef DEBUG

#include "rcar-gen3-common.h"

/* Ethernet RAVB */
#define CONFIG_NET_MULTI
#define CONFIG_BITBANGMII
#define CONFIG_BITBANGMII_MULTI

/* Generic Timer Definitions (use in assembler source) */
#define COUNTER_FREQUENCY	0xFE502A	/* 16.66MHz from CPclk */

/* Environment in eMMC, at the end of 2nd "boot sector" */
#define CONFIG_ENV_OFFSET               (-CONFIG_ENV_SIZE)
#define CONFIG_SYS_MMC_ENV_DEV          1
#define CONFIG_SYS_MMC_ENV_PART         2

#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END (CONFIG_SYS_MEMTEST_START + 0x40000000UL)

#ifdef CONFIG_ENV_IS_IN_MMC

#ifdef CONFIG_BOOTCOMMAND
#undef CONFIG_BOOTCOMMAND
#endif

#define CONFIG_BOOTCOMMAND "fatload mmc 1:1 0x48080000 Image; " \
	"fatload mmc 1:1 0x48000000 "CONFIG_DEFAULT_FDT_FILE"; " \
	"booti 0x48080000 - 0x48000000"

#endif

#endif /* __EK874_H */
