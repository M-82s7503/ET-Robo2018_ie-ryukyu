
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=

APPL_CXXOBJS += \
    Block_answer.o \
    Color_recognition..o \
    Code_Solve.o \
    Map_Move.o \
    MoveUtil_Block.o \
    Parking.o \
    MoveTemps.o \
    Move_Basic.o \
    Turn_oneSide.o \
    Straight.o \
    Turn.o \
    Moving.o \
    Pointers.o \
    DistMeasure.o \
    util.o \
    MoveUtil.o \
    test_main.o \
    answer_arrays.o \
    PatternMatcher.o \
    Move_block.o \
    AI_answer.o \
    Reading_return3.o \
    Reading_seg8.o \
    Run_RL.o \
    Tracer.o 



SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION
# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile
endif


APPL_DIR += \
    $(mkfile_path)trace \
    $(mkfile_path)ai \
    $(mkfile_path)ai/reading \
    $(mkfile_path)ai/answer \
    $(mkfile_path)ai/analyze \
    $(mkfile_path)ai/analyze/pattern_match \
    $(mkfile_path)coreAPI \
    $(mkfile_path)coreAPI/move \
    $(mkfile_path)coreAPI/util \
    $(mkfile_path)coreAPI/moving \
    $(mkfile_path)coreAPI/moving_impls \
    $(mkfile_path)parking \
    $(mkfile_path)block \
    $(mkfile_path)block/move \
    $(mkfile_path)block/analyze 

INCLUDES += \
    -I$(mkfile_path)trace \
    -I$(mkfile_path)ai \
    -I$(mkfile_path)ai/reading \
    -I$(mkfile_path)ai/answer \
    -I$(mkfile_path)ai/analyze \
    -I$(mkfile_path)ai/analyze/pattern_match \
    -I$(mkfile_path)coreAPI \
    -I$(mkfile_path)coreAPI/move \
    -I$(mkfile_path)coreAPI/util \
    -I$(mkfile_path)coreAPI/moving \
    -I$(mkfile_path)coreAPI/moving_impls \
    -I$(mkfile_path)parking \
    -I$(mkfile_path)block \
    -I$(mkfile_path)block/move \
    -I$(mkfile_path)block/analyze 



COPTS += -fno-use-cxa-atexit
