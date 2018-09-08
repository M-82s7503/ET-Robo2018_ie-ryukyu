#   $ make app=
# を実行する場所に cd する。
#   $ sh a_compile.sh [app名]
# で、自動的に edit_Makefile.inc.py を実行したあとコンパイルしてくれる。

python3 edit_Makefile.inc.py "$1"
make app="$1"

mv 'app' "$1_app"
