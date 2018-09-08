# coding: utf-8
###  $ python3 edit_Makefile.inc.py 【app名】
import os
import sys

cpps = []
dirs = []
def getList_cpp_a_dirs(dir):
    for f in os.listdir(dir):
        d_path = dir + f
        # 最初に '_' がついてるディレクトリは飛ばす設計にした。
        # .cpp ファイルの一覧を取得。（app.cpp は入れるとエラーになる）
        if os.path.isfile(d_path) and f[-4:] == '.cpp' and f != 'app.cpp':
            cpps.append(f)
        # 含めたくない場合は、ディレクトリ名の最初に '_' と付けること。
        elif os.path.isdir(d_path) and f[0] != '_' and f[0] != '.':
            dirs.append(d_path)
            getList_cpp_a_dirs(d_path + '/')


frame_str0 = """
mkfile_path := $(dir $(lastword $(MAKEFILE_LIST)))

APPL_COBJS +=

"""



frame_str1 = """


SRCLANG := c++

ifdef CONFIG_EV3RT_APPLICATION
# Include libraries
include $(EV3RT_SDK_LIB_DIR)/libcpp-ev3/Makefile
endif


"""


frame_str2 = """

COPTS += -fno-use-cxa-atexit
"""


if __name__ == '__main__':
    ## パスの形に整形。
    if sys.argv[1][-1] is '/':
        app_name = sys.argv[1]
    else:
        app_name = sys.argv[1] + '/'
    
    
    ## .cpp と ディレクトリ の一覧を取得
    getList_cpp_a_dirs(app_name)

    ###  APPL_CXXOBJS を作る  ###
    ## .o に直して書き並べる。
    inc_objs = 'APPL_CXXOBJS += '
    for cpp_name in reversed(cpps):
        inc_objs += "\\\n    {0}o ".format(cpp_name[:-3])  # 'cpp' を削除
    inc_objs += '\n'
    #print(inc_objs)


    ###  APPL_DIR, INCLUDES を作る  ###
    ## ディレクトリの一覧を取得
    l_AName = len(app_name)
    mkfile_dirs = [ d_path[l_AName:] for d_path in dirs ]
#    print(mkfile_dirs)

    ## 整形して、文字列にする。
    APPL_DIR = 'APPL_DIR += '
    INCLUDES = 'INCLUDES += '
    for d_name in mkfile_dirs:
        APPL_DIR += "\\\n    $(mkfile_path){0} ".format(d_name)  # 'cpp' を削除
        INCLUDES += "\\\n    -I$(mkfile_path){0} ".format(d_name)  # 'cpp' を削除
    APPL_DIR += '\n\n'
    INCLUDES += '\n\n'
#    print(inc_objs)


    ###  結合して、完成。  ###
    comp_mkfile_contents = frame_str0 + inc_objs + frame_str1 + APPL_DIR + INCLUDES + frame_str2
#    print(comp_mkfile_contents)


    ###  完成版を、Makefile.inc に書き込み  ###
    with open(app_name+'/Makefile.inc', 'w') as f:
        f.write(comp_mkfile_contents)
        print('makefile.inc の書き換えに成功しました！')

    print()
