/*
 * spi.h - tiva-c launchpad spi interface implementation
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

#ifndef SL_IF_TYPE_UART
#ifndef __SPI_H__
#define __SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/*!
    \brief   type definition for the spi channel file descriptor

    \note    On each porting or platform the type could be whatever is needed
            - integer, pointer to structure etc.
*/
typedef unsigned int Fd_t;

/*!
    \brief open spi communication port to be used for communicating with a
           SimpleLink device

    Given an interface name and option flags, this function opens the spi
    communication port and creates a file descriptor. This file descriptor can
    be used afterwards to read and write data from and to this specific spi
    channel.
    The SPI speed, clock polarity, clock phase, chip select and all other
    attributes are all set to hardcoded values in this function.

    \param[in]      ifName    -    points to the interface name/path. The
                    interface name is an optional attributes that the simple
                    link driver receives on opening the device. in systems that
                    the spi channel is not implemented as part of the os device
                    drivers, this parameter could be NULL.
    \param[in]      flags     -    option flags

    \return         upon successful completion, the function shall open the spi
                    channel and return a non-negative integer representing the
                    file descriptor. Otherwise, -1 shall be returned

    \sa             spi_Close , spi_Read , spi_Write
    \note
    \warning
*/

Fd_t spi_Open(char *ifName, unsigned long flags);

/*!
    \brief closes an opened spi communication port

    \param[in]      fd    -     file descriptor of an opened SPI channel

    \return         upon successful completion, the function shall return 0.
                    Otherwise, -1 shall be returned

    \sa             spi_Open
    \note
    \warning
*/
int spi_Close(Fd_t fd);

/*!
    \brief attempts to read up to len bytes from SPI channel into a buffer
           starting at pBuff.

    \param[in]      fd     -    file descriptor of an opened SPI channel

    \param[in]      pBuff  -    points to first location to start writing the
                    data

    \param[in]      len    -    number of bytes to read from the SPI channel

    \return         upon successful completion, the function shall return 0.
                    Otherwise, -1 shall be returned

    \sa             spi_Open , spi_Write
    \note
    \warning
*/
int spi_Read(Fd_t fd, unsigned char *pBuff, int len);

/*!
    \brief attempts to write up to len bytes to the SPI channel

    \param[in]      fd        -    file descriptor of an opened SPI channel

    \param[in]      pBuff     -    points to first location to start getting the
                    data from

    \param[in]      len       -    number of bytes to write to the SPI channel

    \return         upon successful completion, the function shall return 0.
                    Otherwise, -1 shall be returned

    \sa             spi_Open , spi_Read
    \note           This function could be implemented as zero copy and return
                    only upon successful completion of writing the whole buffer,
                    but in cases that memory allocation is not too tight, the
                    function could copy the data to internal buffer, return
                    back and complete the write in parallel to other activities
                    as long as the other SPI activities would be blocked until
                    the entire buffer write would be completed
    \warning
*/
int spi_Write(Fd_t fd, unsigned char *pBuff, int len);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __SPI_H__ */
#endif /* SL_IF_TYPE_UART */
