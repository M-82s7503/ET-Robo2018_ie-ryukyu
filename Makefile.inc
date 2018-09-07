
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=
APPL_CXXOBJS += \
    util.o \
    app.o \
    Tracer.o \
    DistMeasure.o \
    Parts.o \
    Moving.o \
    MoveUtil.o \
    AI_answer.o \
    Reading_seg8.o 



SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION
# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile
endif

APPL_DIR += \
	$(mkfile_path)trace \
	$(mkfile_path)ai \
	$(mkfile_path)ai/analyze \
	$(mkfile_path)ai/move \
	$(mkfile_path)block \
	$(mkfile_path)moving \
	$(mkfile_path)moving/core \
	$(mkfile_path)moving/unit \
	$(mkfile_path)util

INCLUDES += \
	-I$(mkfile_path)trace \
	-I$(mkfile_path)ai \
	-I$(mkfile_path)ai/analyze \
	-I$(mkfile_path)ai/move \
	-I$(mkfile_path)block \
	-I$(mkfile_path)moving \
	-I$(mkfile_path)moving/core \
	-I$(mkfile_path)moving/unit \
	-I$(mkfile_path)util


COPTS += -fno-use-cxa-atexit

