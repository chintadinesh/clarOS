//*****************************************************************************
//
// epi.h - Prototypes and macros for the EPI module.
//
// Copyright (c) 2008-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 2.1.0.12573 of the Tiva Peripheral Driver Library.
//
//*****************************************************************************

#ifndef __DRIVERLIB_EPI_H__
#define __DRIVERLIB_EPI_H__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//
// Values that can be passed to EPIModeSet()
//
//*****************************************************************************
#define EPI_MODE_GENERAL 0x00000010
#define EPI_MODE_SDRAM 0x00000011
#define EPI_MODE_HB8 0x00000012
#define EPI_MODE_HB16 0x00000013
#define EPI_MODE_DISABLE 0x00000000

//*****************************************************************************
//
// Values that can be passed to EPIConfigSDRAMSet()
//
//*****************************************************************************
#define EPI_SDRAM_CORE_FREQ_0_15 0x00000000
#define EPI_SDRAM_CORE_FREQ_15_30 0x40000000
#define EPI_SDRAM_CORE_FREQ_30_50 0x80000000
#define EPI_SDRAM_CORE_FREQ_50_100 0xC0000000
#define EPI_SDRAM_LOW_POWER 0x00000200
#define EPI_SDRAM_FULL_POWER 0x00000000
#define EPI_SDRAM_SIZE_64MBIT 0x00000000
#define EPI_SDRAM_SIZE_128MBIT 0x00000001
#define EPI_SDRAM_SIZE_256MBIT 0x00000002
#define EPI_SDRAM_SIZE_512MBIT 0x00000003

//*****************************************************************************
//
// Values that can be passed to EPIConfigGPModeSet()
//
//*****************************************************************************
#define EPI_GPMODE_CLKPIN 0x80000000
#define EPI_GPMODE_CLKGATE 0x40000000
#define EPI_GPMODE_FRAME50 0x04000000
#define EPI_GPMODE_WRITE2CYCLE 0x00080000
#define EPI_GPMODE_ASIZE_NONE 0x00000000
#define EPI_GPMODE_ASIZE_4 0x00000010
#define EPI_GPMODE_ASIZE_12 0x00000020
#define EPI_GPMODE_ASIZE_20 0x00000030
#define EPI_GPMODE_DSIZE_8 0x00000000
#define EPI_GPMODE_DSIZE_16 0x00000001
#define EPI_GPMODE_DSIZE_24 0x00000002
#define EPI_GPMODE_DSIZE_32 0x00000003

//*****************************************************************************
//
// Values that can be passed to EPIConfigHB8ModeSet()
//
//*****************************************************************************
#define EPI_HB8_USE_TXEMPTY 0x00800000
#define EPI_HB8_USE_RXFULL 0x00400000
#define EPI_HB8_WRHIGH 0x00200000
#define EPI_HB8_RDHIGH 0x00100000
#define EPI_HB8_ALE_HIGH 0x00080000
#define EPI_HB8_ALE_LOW 0x00000000
#define EPI_HB8_WRWAIT_0 0x00000000
#define EPI_HB8_WRWAIT_1 0x00000040
#define EPI_HB8_WRWAIT_2 0x00000080
#define EPI_HB8_WRWAIT_3 0x000000C0
#define EPI_HB8_RDWAIT_0 0x00000000
#define EPI_HB8_RDWAIT_1 0x00000010
#define EPI_HB8_RDWAIT_2 0x00000020
#define EPI_HB8_RDWAIT_3 0x00000030
#define EPI_HB8_MODE_ADMUX 0x00000000
#define EPI_HB8_MODE_ADDEMUX 0x00000001
#define EPI_HB8_MODE_SRAM 0x00000002
#define EPI_HB8_MODE_FIFO 0x00000003
#define EPI_HB8_WORD_ACCESS 0x00000100
#define EPI_HB8_CSCFG_ALE 0x00000000
#define EPI_HB8_CSCFG_CS 0x00000200
#define EPI_HB8_CSCFG_DUAL_CS 0x00000400
#define EPI_HB8_CSCFG_ALE_DUAL_CS 0x00000600
#define EPI_HB8_CSCFG_ALE_SINGLE_CS 0x00001000
#define EPI_HB8_CSCFG_QUAD_CS 0x00001200
#define EPI_HB8_CSCFG_ALE_QUAD_CS 0x00001400
#define EPI_HB8_CSBAUD 0x00000800
#define EPI_HB8_CLOCK_GATE 0x80000000
#define EPI_HB8_CLOCK_GATE_IDLE 0x40000000
#define EPI_HB8_CLOCK_INVERT 0x20000000
#define EPI_HB8_IN_READY_EN 0x10000000
#define EPI_HB8_IN_READY_EN_INVERT 0x18000000
#define EPI_HB8_CSCFG_MASK 0x00001600

//*****************************************************************************
//
// Values that can be passed to EPIConfigHB16ModeSet()
//
//*****************************************************************************
#define EPI_HB16_USE_TXEMPTY 0x00800000
#define EPI_HB16_USE_RXFULL 0x00400000
#define EPI_HB16_WRHIGH 0x00200000
#define EPI_HB16_RDHIGH 0x00100000
#define EPI_HB16_WRWAIT_0 0x00000000
#define EPI_HB16_WRWAIT_1 0x00000040
#define EPI_HB16_WRWAIT_2 0x00000080
#define EPI_HB16_WRWAIT_3 0x000000C0
#define EPI_HB16_RDWAIT_0 0x00000000
#define EPI_HB16_RDWAIT_1 0x00000010
#define EPI_HB16_RDWAIT_2 0x00000020
#define EPI_HB16_RDWAIT_3 0x00000030
#define EPI_HB16_MODE_ADMUX 0x00000000
#define EPI_HB16_MODE_ADDEMUX 0x00000001
#define EPI_HB16_MODE_SRAM 0x00000002
#define EPI_HB16_MODE_FIFO 0x00000003
#define EPI_HB16_BSEL 0x00000004
#define EPI_HB16_WORD_ACCESS 0x00000100
#define EPI_HB16_CSCFG_ALE 0x00000000
#define EPI_HB16_CSCFG_CS 0x00000200
#define EPI_HB16_CSCFG_DUAL_CS 0x00000400
#define EPI_HB16_CSCFG_ALE_DUAL_CS 0x00000600
#define EPI_HB16_CSCFG_ALE_SINGLE_CS 0x00001000
#define EPI_HB16_CSCFG_QUAD_CS 0x00001200
#define EPI_HB16_CSCFG_ALE_QUAD_CS 0x00001400
#define EPI_HB16_CLOCK_GATE 0x80000000
#define EPI_HB16_CLOCK_GATE_IDLE 0x40000000
#define EPI_HB16_CLOCK_INVERT 0x20000000
#define EPI_HB16_IN_READY_EN 0x10000000
#define EPI_HB16_IN_READY_EN_INVERTED 0x18000000
#define EPI_HB16_ALE_HIGH 0x00080000
#define EPI_HB16_ALE_LOW 0x00000000
#define EPI_HB16_BURST_TRAFFIC 0x00010000
#define EPI_HB16_CSBAUD 0x00000800
#define EPI_HB16_CSCFG_MASK 0x00001600

//*****************************************************************************
//
// Values that can be passed to EPIConfigHB8TimingSet().
//
//*****************************************************************************
#define EPI_HB8_IN_READY_DELAY_1 0x01000000
#define EPI_HB8_IN_READY_DELAY_2 0x02000000
#define EPI_HB8_IN_READY_DELAY_3 0x03000000
#define EPI_HB8_CAP_WIDTH_1 0x00001000
#define EPI_HB8_CAP_WIDTH_2 0x00002000
#define EPI_HB8_WRWAIT_MINUS_DISABLE 0x00000000
#define EPI_HB8_WRWAIT_MINUS_ENABLE 0x00000010
#define EPI_HB8_RDWAIT_MINUS_DISABLE 0x00000000
#define EPI_HB8_RDWAIT_MINUS_ENABLE 0x00000001

//*****************************************************************************
//
// Values that can be passed to EPIConfigHB16TimingSet().
//
//*****************************************************************************
#define EPI_HB16_IN_READY_DELAY_1 0x01000000
#define EPI_HB16_IN_READY_DELAY_2 0x02000000
#define EPI_HB16_IN_READY_DELAY_3 0x03000000
#define EPI_HB16_PSRAM_NO_LIMIT 0x00000000
#define EPI_HB16_PSRAM_128 0x00010000
#define EPI_HB16_PSRAM_256 0x00020000
#define EPI_HB16_PSRAM_512 0x00030000
#define EPI_HB16_PSRAM_1024 0x00040000
#define EPI_HB16_PSRAM_2048 0x00050000
#define EPI_HB16_PSRAM_4096 0x00060000
#define EPI_HB16_PSRAM_8192 0x00070000
#define EPI_HB16_CAP_WIDTH_1 0x00001000
#define EPI_HB16_CAP_WIDTH_2 0x00002000
#define EPI_HB16_WRWAIT_MINUS_DISABLE 0x00000000
#define EPI_HB16_WRWAIT_MINUS_ENABLE 0x00000008
#define EPI_HB16_RDWAIT_MINUS_DISABLE 0x00000000
#define EPI_HB16_RDWAIT_MINUS_ENABLE 0x00000001

//*****************************************************************************
//
// Values that can be passed to EPIAddressMapSet().
//
//*****************************************************************************
#define EPI_ADDR_PER_SIZE_256B 0x00000000
#define EPI_ADDR_PER_SIZE_64KB 0x00000040
#define EPI_ADDR_PER_SIZE_16MB 0x00000080
#define EPI_ADDR_PER_SIZE_256MB 0x000000C0
#define EPI_ADDR_PER_BASE_NONE 0x00000000
#define EPI_ADDR_PER_BASE_A 0x00000010
#define EPI_ADDR_PER_BASE_C 0x00000020
#define EPI_ADDR_RAM_SIZE_256B 0x00000000
#define EPI_ADDR_RAM_SIZE_64KB 0x00000004
#define EPI_ADDR_RAM_SIZE_16MB 0x00000008
#define EPI_ADDR_RAM_SIZE_256MB 0x0000000C
#define EPI_ADDR_RAM_BASE_NONE 0x00000000
#define EPI_ADDR_RAM_BASE_6 0x00000001
#define EPI_ADDR_RAM_BASE_8 0x00000002
#define EPI_ADDR_QUAD_MODE 0x00000033
#define EPI_ADDR_CODE_SIZE_256B 0x00000000
#define EPI_ADDR_CODE_SIZE_64KB 0x00000400
#define EPI_ADDR_CODE_SIZE_16MB 0x00000800
#define EPI_ADDR_CODE_SIZE_256MB 0x00000C00
#define EPI_ADDR_CODE_BASE_NONE 0x00000000
#define EPI_ADDR_CODE_BASE_1 0x00000100

//*****************************************************************************
//
// Values that can be passed to EPINonBlockingReadConfigure()
//
//*****************************************************************************
#define EPI_NBCONFIG_SIZE_8 1
#define EPI_NBCONFIG_SIZE_16 2
#define EPI_NBCONFIG_SIZE_32 3

//*****************************************************************************
//
// Values that can be passed to EPIFIFOConfig()
//
//*****************************************************************************
#define EPI_FIFO_CONFIG_WTFULLERR 0x00020000
#define EPI_FIFO_CONFIG_RSTALLERR 0x00010000
#define EPI_FIFO_CONFIG_TX_EMPTY 0x00000000
#define EPI_FIFO_CONFIG_TX_1_4 0x00000020
#define EPI_FIFO_CONFIG_TX_1_2 0x00000030
#define EPI_FIFO_CONFIG_TX_3_4 0x00000040
#define EPI_FIFO_CONFIG_RX_1_8 0x00000001
#define EPI_FIFO_CONFIG_RX_1_4 0x00000002
#define EPI_FIFO_CONFIG_RX_1_2 0x00000003
#define EPI_FIFO_CONFIG_RX_3_4 0x00000004
#define EPI_FIFO_CONFIG_RX_7_8 0x00000005
#define EPI_FIFO_CONFIG_RX_FULL 0x00000006

//*****************************************************************************
//
// Values that can be passed to EPIIntEnable(), EPIIntDisable(), or returned
// as flags from EPIIntStatus()
//
//*****************************************************************************
#define EPI_INT_DMA_TX_DONE 0x00000010
#define EPI_INT_DMA_RX_DONE 0x00000008
#define EPI_INT_TXREQ 0x00000004
#define EPI_INT_RXREQ 0x00000002
#define EPI_INT_ERR 0x00000001

//*****************************************************************************
//
// Values that can be passed to EPIIntErrorClear(), or returned as flags from
// EPIIntErrorStatus()
//
//*****************************************************************************
#define EPI_INT_ERR_DMAWRIC 0x00000010
#define EPI_INT_ERR_DMARDIC 0x00000008
#define EPI_INT_ERR_WTFULL 0x00000004
#define EPI_INT_ERR_RSTALL 0x00000002
#define EPI_INT_ERR_TIMEOUT 0x00000001

#ifdef rvmdk
//*****************************************************************************
//
// Keil case.
//
//*****************************************************************************
inline void EPIWorkaroundWordWrite(uint32_t *pui32Addr, uint32_t ui32Value) {
  uint32_t ui32Scratch;

  __asm
  {
  //
