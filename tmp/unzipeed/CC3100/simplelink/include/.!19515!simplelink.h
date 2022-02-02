/*
 * simplelink.h - CC31xx/CC32xx Host Driver Implementation
 *
 * Copyright (C) 2014 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*!
    \mainpage SimpleLink Driver

    \section intro_sec Introduction

 The SimpleLink CC31XX family allows to add Wi-Fi and networking capabilities
 to low-cost embedded products without having prior Wi-Fi, RF or networking
 expertise. The CC31XX is an ideal solution for microcontroller-based sensor and
 control applications such as home appliances, home automation and smart
 metering. The CC31XX has integrated a comprehensive TCP/IP network stack, Wi-Fi
 driver and security supplicant leading to easier portability to
 microcontrollers, to an ultra-low memory footprint, all without compromising
 the capabilities and robustness of the final application.



 \section modules_sec Modules
 To make it simple, TI's SimpleLink CC3100 platform capabilities were divided
 into modules by topic (Silo). These capabilities range from basic device
 management through wireless network configuration, standard BSD socket and much
 more. Listed below are the various modules in the SimpleLink CC31XX driver:
     -# \ref device - controls the behavior of the CC3100 device (start/stop,
 events masking and obtaining specific device status)
     -# \ref wlan - controls the use of the WiFi WLAN module including:
