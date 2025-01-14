#******************************************************************************
#
# Makefile - Rules for building the project example.
#
# Copyright (c) 2013-2017 Texas Instruments Incorporated.  All rights reserved.
# Software License Agreement
#
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions
#   are met:
#
#   Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
#
#   Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the
#   distribution.
#
#   Neither the name of Texas Instruments Incorporated nor the names of
#   its contributors may be used to endorse or promote products derived
#   from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# This is part of revision 2.1.4.178 of the Tiva Firmware Development Package.
#
#******************************************************************************

#******************************************************************************
# Modified January 30, 2019 by Clara Schaertl Short <clarity@utexas.edu>
#******************************************************************************

export DEBUG # enable debugging options

all: # The default rule

#
# Defines the part type that this project uses.
#
PART=TM4C123GH6PM
BOARD=ti_ek-tm4c123gxl

#
# The base directory for TivaWare.
#
#ROOT=.
TIVA_ROOT=${ROOT}/TivaWare
VALVANO_ROOT=${ROOT}/ValvanoWare

#
# Fetches and builds all dependencies.
#
deps:
	-cd .git/hooks && ln -s ../../.githooks/* .
	git submodule update --init
	brew bundle

#
# Include the common make definitions.
#
ifneq ("$(wildcard ${TIVA_ROOT}/makedefs)","")
include ${TIVA_ROOT}/makedefs
endif

#
# Where to find header files that do not live in the source directory.
#
IPATH=	${ROOT}/include \
	${VALVANO_ROOT}/include \
	${TIVA_ROOT} \
	${TIVA_ROOT}/inc \
	${TIVA_ROOT}/driverlib

#
# The default rule, which causes the project example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/project.axf
all: ${COMPILER}/project.bin

#
# The rules to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~} doc

realclean: clean
	@$(MAKE) -C ${TIVA_ROOT} clean
	@$(MAKE) -C ${VALVANO_ROOT}/valvanolib clean

distclean: clean
	@rm -rf ${TIVA_ROOT} ${VALVANO_ROOT}
	@mkdir -p ${TIVA_ROOT} ${VALVANO_ROOT}

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the project.
#
C_SOURCES=$(wildcard *.c)
ASM_SOURCES=$(wildcard *.s)
OBJECTS=$(addprefix ${COMPILER}/,$(C_SOURCES:.c=.o)) \
	$(addprefix ${COMPILER}/,$(ASM_SOURCES:.s=.o))

LIBDRIVER=${TIVA_ROOT}/driverlib/${COMPILER}/libdriver.a
LIBVALVANO=${VALVANO_ROOT}/valvanolib/${COMPILER}/libvalvano.a
LDSCRIPT=${TIVA_ROOT}/examples/project/project.ld

${LIBDRIVER}:
	$(MAKE) -C ${TIVA_ROOT}/driverlib all
${LIBVALVANO}:
	$(MAKE) -C ${VALVANO_ROOT}/valvanolib all

${COMPILER}/project.axf: ${OBJECTS} ${LIBDRIVER} ${LIBVALVANO} ${LDSCRIPT}
${COMPILER}/project.bin: ${COMPILER}/project.axf

SCATTERgcc_project=${LDSCRIPT}
ENTRY_project=Reset_Handler
CFLAGSgcc=-DTARGET_IS_TM4C123_RB1

#
# Rules for debugging the project.
#
LM4FLASH=lm4flash
OPENOCD=openocd
GDB=${PREFIX}-gdb

flash: ${COMPILER}/project.bin
	$(LM4FLASH) $<

debug: ${COMPILER}/project.axf
	$(OPENOCD) -f board/${BOARD}.cfg &
	$(GDB) $<
	-killall $(OPENOCD)

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
