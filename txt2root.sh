#!/bin/sh
ls -l Data/$2 | grep -i $1 | \
awk '{print substr($NF,0,length($NF))}' > RunLists/List-$2-$1.txt
mkdir root/$2
for i in `cat RunLists/List-$2-${1}.txt`;
do
tail -n +13 Data/$2/$i | tail -r | tail -n +2 | tail -r > temp/${i};
root -q -l makeGraph.C\(\"temp/${i}\",\"${2}\"\);
done
