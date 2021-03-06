#==============================================================================
#
# Makefile
#
#==============================================================================

#===================================
# Directory
#===================================
INSTALL_BIN		= ./bin
INCDIR 			= ./include
SRCDIR			= ./src
ifeq "$(strip $(SRCDIR))" ""
	SRCDIR		= .
endif
PRJDIR			= ./_project
EXPDIR			= ../release

#===================================
# gcc : Exe
#===================================
CC		= gcc
LD      = gcc
CP		= "cp"
RM		= "rm"
MKDIR	= "mkdir"
CAT		= "cat"
TOUCH	= "touch"
CMP		= "cmp"
TEE		= "tee"
MV		= "mv"
DOXYGEN	= "doxygen"
GIT		= "git"

#===================================
# OS
#===================================
UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
# MacOS
CDEFINE			+= OS_MAC
else
ifeq ($(UNAME), Linux)
# Linux
CDEFINE			+= OS_LINUX
else
# Cygwin
CDEFINE			+= OS_WINDOWS
endif
endif

#==============================================================================
# Compile Options(Common)
#==============================================================================
COMMON_COPTS += -Wall
COMMON_COPTS += -Wextra
COMMON_COPTS += -Winit-self
COMMON_COPTS += -Wno-missing-field-initializers

#===================================
# Compile Options(C)
#===================================
COPTS += ${COMMON_COPTS}

#===================================
# Compile Options(DEBUG)
#===================================
COPTS_DEBUG += ${COMMON_COPTS}
#COPTS_DEBUG += --verbose

#==============================================================================
# Include path
#==============================================================================
INCLUDE			= ${INCDIR}
SYSINCS			= 

#===================================
# Target Module
#===================================
TARGET		= poker

#=============================================
# Define specify compilation
#=============================================
CDEFINE			+= 

#=============================================
# Define specify compilation
#=============================================
CDEFINE_DEBUG   += _DEBUG
CDEFINE_DEBUG   += TEST

#===================================
# [C : Include path]
#===================================
CINC		= $(INCLUDE:%=-I%) $(SYSINCS)

#===================================
# [C : Define]
#===================================
ifdef debug
CDEF		= $(CDEFINE:%=-D%) $(CDEFINE_DEBUG:%=-D%)
else
CDEF		= $(CDEFINE:%=-D%)
endif

#===================================
# [C : Compile Options]
#===================================
ifdef debug
CFLAGS		= $(COPTS_DEBUG) $(CDEF) $(CINC)
else
CFLAGS		= $(COPTS) $(CDEF) $(CINC)
endif

#===================================
# Source Files
#===================================
SRC_FILES += src/main.c
SRC_FILES += src/card.c
SRC_FILES += src/system.c
SRC_FILES += src/player.c
SRC_FILES += src/poker.c
SRC_FILES += src/game.c
SRC_FILES += src/ui.c
SRC_FILES += src/debug.c

#==============================================================================
# Primary target
#==============================================================================
#.PHONY: all
all: clean $(TARGET) install_bin

#==============================================================================
# Clean
#==============================================================================
clean: clean_bin
	$(RM) -f $(TARGET)

clean_bin:
	$(RM) -f $(INSTALL_BIN)/$(TARGET)

#==============================================================================
# Build
#==============================================================================
$(TARGET):$(SRC_FILES) 
	-@echo "[build] compile : $@"
	-@echo "[src] $(SRC_FILES)"
	$(CC) -o $@ $^ $(CFLAGS)

#===================================
# Install executable file
#===================================
.PHONY:
install_bin:
	@if [ ! -d $(INSTALL_BIN) ] ; then \
		${MKDIR} -p $(INSTALL_BIN) ; \
	fi ; \
	$(MV) $(TARGET) $(INSTALL_BIN)
	-@echo "[finish] install to $(INSTALL_BIN)/$(TARGET)"

#===================================
# Running target
#===================================
run:
	$(INSTALL_BIN)/$(TARGET) ${ARG}

#===================================
# Doxygen
#===================================
doxygen:	
	$(DOXYGEN) $(PRJDIR)/Doxyfile

#===================================
# Release(git export)
#===================================
release:	
	$(RM) -Rf $(EXPDIR)
	if [ ! -d $(EXPDIR) ] ; then \
		${MKDIR} -p $(EXPDIR) ; \
	fi ; \
	$(GIT) checkout-index -a -f --prefix=$(EXPDIR)/poker/
