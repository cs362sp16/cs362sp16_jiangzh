#!/bin/bash

make unittest1
make unittest2
make unittest3
make unittest4

./unittest1 >> unittestresults.out 
./unittest2 >> unittestresults.out 
./unittest3 >> unittestresults.out 
./unittest4 >> unittestresults.out

gcov dominion.c
cat dominion.c.gcov >> unittestresults.out 
