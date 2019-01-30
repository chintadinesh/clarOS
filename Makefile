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

all: # The default rule

#
# Defines the part type that this project uses.
#
PART=TM4C123GH6PM

#
# The base directory for TivaWare.
#
ROOT=.
TIVA_ROOT=${ROOT}/TivaWare
VALVANO_ROOT=${ROOT}/ValvanoWare

#
# Fetches and builds all dependencies.
#
deps:
	cd .git/hooks && ln -s ../../pre-commit
	git submodule update --init
	brew bundle
	lm4dir = $(shell brew --prefix)/Cellar/lm4tools/master
	$(MAKE) -C lm4tools all install PREFIX=$(lm4dir)
	brew link lm4tools

#
# Include the common make definitions.
#
include ${TIVA_ROOT}/makedefs

#
# Where to find header files that do not live in the source directory.
#
IPATH=	${ROOT}/include \
	${VALVANO_ROOT}/include \
	${TIVA_ROOT}/inc \
	${TIVA_ROOT}/driverlib

#
# The default rule, which causes the project example to be built.
#
all: ${COMPILER}
all: ${COMPILER}/project.axf

#
# The rule to clean out all the build products.
#
clean:
	@rm -rf ${COMPILER} ${wildcard *~}
	@$(MAKE) -C ${TIVA_ROOT} clean
	@$(MAKE) -C ${VALVANO_ROOT}/valvanolib clean

#
# The rule to create the target directory.
#
${COMPILER}:
	@mkdir -p ${COMPILER}

#
# Rules for building the project example.
#
${COMPILER}/project.axf: ${COMPILER}/main.o
${COMPILER}/project.axf: ${COMPILER}/startup_${COMPILER}.o
${COMPILER}/project.axf: ${TIVA_ROOT}/driverlib/${COMPILER}/libdriver.a
${COMPILER}/project.axf: ${VALVANO_ROOT}/valvanolib/${COMPILER}/libvalvano.a
${COMPILER}/project.axf: ${TIVA_ROOT}/examples/project/project.ld
SCATTERgcc_project=${TIVA_ROOT}/examples/project/project.ld
ENTRY_project=ResetISR
CFLAGSgcc=-DTARGET_IS_TM4C123_RB1

#
# Include the automatically generated dependency files.
#
ifneq (${MAKECMDGOALS},clean)
-include ${wildcard ${COMPILER}/*.d} __dummy__
endif
