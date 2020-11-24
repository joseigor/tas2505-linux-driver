/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * tas2505.h - ALSA SoC Texas Instruments TAS2505 Mono Audio Amplifier
 *
 * Copyright (C)2020-2021 SVP Worldwide -  http://www.svpworldwide.com/
 *
 * Author: Jose Igor Moreira <jose.igor.moreira.ext@europe.svpworldwide.com>
 */

#ifndef __TAS5720_H__
#define __TAS5720_H__

/* Register Address Map */

#define TAS2505_RATES	SNDRV_PCM_RATE_8000_96000
#define TAS2505_FORMATS SNDRV_PCM_FMTBIT_S24_LE

/* Register Address Map */

/* Page Control Register*/
#define TAS2505_PAGECTL 0x00
/*Software Reset Resiter*/
#define TAS2505_RESET 0x01

#endif