
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=

APPL_CXXOBJS += \
    AI_answer.o \
    Reading_seg8.o \
    MoveUtil.o \
    Moving.o \
    Pointers.o \
    Moving_ex.o \
    DistMeasure.o \
    Tracer.o \
    util.o 



SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION
# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile
endif


APPL_DIR += \
    $(mkfile_path)trace \
    $(mkfile_path)util \
    $(mkfile_path)moving \
    $(mkfile_path)moving/unit \
    $(mkfile_path)moving/core \
    $(mkfile_path)ai \
    $(mkfile_path)ai/move \
    $(mkfile_path)ai/analyze \
    $(mkfile_path)block 

INCLUDES += \
    -I$(mkfile_path)trace \
    -I$(mkfile_path)util \
    -I$(mkfile_path)moving \
    -I$(mkfile_path)moving/unit \
    -I$(mkfile_path)moving/core \
    -I$(mkfile_path)ai \
    -I$(mkfile_path)ai/move \
    -I$(mkfile_path)ai/analyze \
    -I$(mkfile_path)block 



COPTS += -fno-use-cxa-atexit
