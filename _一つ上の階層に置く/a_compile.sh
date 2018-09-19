#   $ make app=
# を実行する場所に cd する。
#   $ sh a_compile.sh [app名]
# で、自動的に edit_Makefile.inc.py を実行したあとコンパイルしてくれる。


python3 edit_Makefile.inc.py "$1"

## 第２引数に R, L を指定すると、指定したコースのプログラムをコンパイルする。
if [ $# -eq 2 ]; then
    # appR.cpp を app.cpp に
    mv "$1/app$2.cpp" "$1/app.cpp" 
fi

make app="$1"

if [ $# -eq 2 ]; then
    # app.cpp を appR.cpp に
    mv "$1/app.cpp" "$1/app$2.cpp" 
fi

mv 'app' "$1_app"
echo
echo "$1_app"
