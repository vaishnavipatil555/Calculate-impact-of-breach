#!/bin/bash

FILE=a.out
if test ! -f "$FILE"; then
	gcc test1.c
fi

FILE=IPtables.txt
if test -f "$FILE"; then
	rm IPtables.txt
fi

FILE=IPnames.txt
if test -f "$FILE"; then
	rm IPnames.txt
fi

FILE=info.txt
if test -f "$FILE"; then
	rm info.txt
fi
chmod -R 777 a.out
./a.out $1
python graph_py1.py
