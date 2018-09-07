#   $ make app=
# を実行する場所に cd して、
#   $ sh ETRobo-runAll/compile.sh
# で、自動的に Makefile.inc.py を実行したあとコンパイルしてくれる。

cd ETRobo-runAll/
python3 edit_Makefile.inc.py
cd ../
make app=ETRobo-runAll 
