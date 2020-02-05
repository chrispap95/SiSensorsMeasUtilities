#!/bin/sh
ls -l Data/$2 | grep -i $1 | \
awk '{print substr($NF,0,length($NF))}' > RunLists/List-$2-$1.txt
python makeTree.py - -i RunLists/List-$2-$1.txt -d Data/$2
