# coding: utf-8

frame_str0 = """
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=
APPL_CXXOBJS += """



frame_str1 = """


SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION
# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile
endif

APPL_DIR += \\
	$(mkfile_path)trace \\
	$(mkfile_path)ai \\
	$(mkfile_path)ai/analyze \\
	$(mkfile_path)ai/move \\
	$(mkfile_path)block \\
	$(mkfile_path)unit \\
	$(mkfile_path)moving \\
	$(mkfile_path)util

INCLUDES += \\
	-I$(mkfile_path)trace \\
	-I$(mkfile_path)ai \\
	-I$(mkfile_path)ai/analyze \\
	-I$(mkfile_path)ai/move \\
	-I$(mkfile_path)block \\
	-I$(mkfile_path)unit \\
	-I$(mkfile_path)moving \\
	-I$(mkfile_path)util


COPTS += -fno-use-cxa-atexit

"""


###  APPL_CXXOBJS の設定  ###

## .cpp の一覧を取得
import glob
classNames = [r.split('/')[-1] for r in glob.iglob('**/*.cpp', recursive=True)]
#print(classNames)
inc_objs = ''

## .o に直して書き並べる。
for c_name in classNames:
    inc_objs += "\\\n    {0}o ".format(c_name[:-3])  # 'cpp' を削除
inc_objs += '\n'
#print(inc_objs)

## 結合して、完成。
comp_mkfile_contents = frame_str0 + inc_objs + frame_str1
#print(comp_mkfile_contents)


###  完成版を、Makefile.inc に書き込み  ###
with open('Makefile.inc', 'w') as f:
    f.write(comp_mkfile_contents)

