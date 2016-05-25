#!/bin/bash

filepath=$(cd "$(dirname "$0")"; pwd)
file1="dominion1"
file2="dominion2"
output1="difftest1.out"
output2="difftest2.out"
seed=18 

# create two new dominions in two folder respectively
rm -rf $file1
mkdir $file1
cp testdominion.c dominion_helpers.h dominion.h dominion.c makefile interface.c interface.h rngs.c rngs.h $file1

rm -rf $file2
mkdir $file2
cp testdominion.c dominion_helpers.h dominion.h dominion.c makefile interface.c interface.h rngs.c rngs.h $file2

# implement a dominion1 and copy it to root 
cd $filepath"/"$file1
make testdominion
./testdominion $seed > $output1  
cp $output1 $filepath 

# implement a dominion2 and copy it to root
cd $filepath"/"$file2
make testdominion
./testdominion $seed > $output2  
cp $output2 $filepath

# compare results of these two dominion implementation
cd $filepath
rm -rf $file1
rm -rf $file2
rm diff.out
diff $filepath"/"$output1 $filepath"/"$output2 > diff.out

# check result after comparing
if [ $? == 0 ] 
then
    echo 'TEST PASSED'
else
    echo 'TEST FAILED'
fi


