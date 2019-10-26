#!/bin/bash

FILE=a.out
if test ! -f "$FILE"; then
	gcc make_info.c 
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

./a.out VM
python graph.py
