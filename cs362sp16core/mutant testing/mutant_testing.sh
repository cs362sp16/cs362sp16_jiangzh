#!/bin/bash
filepath=$(cd "$(dirname "$0")"; pwd)

mutant="mutant"
original="original"

if test $# = 1
then
	CARD=$1
else
	echo Usage: $0 card-name
fi

if [ $CARD = "adventurer" ] 
then
	make_command="randomtestadventurer"
elif [ $CARD = "council_room" ]
then	
	make_command="cardtest2"

elif [ $CARD = "smity" ]
then
	make_command="randomtestcard2"

elif [ $CARD = "steward" ] 
then
 	make_command="randomtestcard1"
else
	echo No this card
fi

echo "--------------- Mutant testing for $CARD-----------------------" &> $CARD"_result.out" 
echo > $CARD"_result.out" 
echo > $CARD"_result.out" 

int=0
filename=1
while(($int<5))
do 
	echo "Differentce $filename:----------------------------------" >> $CARD"_result.out" 
	echo >> $CARD"_result.out"
	diff -urN $original"/dominion.c" $mutant"/"$CARD"/"$filename".c" >> $CARD"_result.out"
	echo >> $CARD"_result.out"


	echo "Coverage $filename:----------------------------------" >> $CARD"_result.out" 
	cd $mutant
	cp $CARD"/"$filename".c" $filepath"/"$mutant
	mv $filename".c" "dominion.c"
	make $make_command
	./$make_command >> $CARD"_result.out"
	gcov dominion.c >> $filepath"/"$CARD"_result.out"
	make clean
	cd ..

	cd $original
	make $make_command
	./$make_command >> $CARD"_result.out"
	gcov dominion.c >> $filepath"/"$CARD"_result.out" 
	make clean
	cd ..

	echo "Test Results $filename:---------------------------------" >> $CARD"_result.out"
	diff -urN $mutant"/"$CARD"_result.out" $original"/"$CARD"_result.out" >> $CARD"_result.out"
	echo >> $CARD"_result.out"	

	rm $mutant"/"$CARD"_result.out"
	rm $original"/"$CARD"_result.out" 

	let "filename+=1"
	let "int+=1"

done





