#!/bin/bash

seq_program=$1
par_program=$2
N=$3
NumTests=$4
printLevel=2
if [ -n "$5" ]; then
	runs=$5
else
	runs="1 2 4 8"
fi

rm out*
./$seq_program $N $printLevel 1 > out
# we add 1 here just so we can use a par_program instead of a missing sequential one
echo The result of your parallel program is
echo ======================================
cat out
echo ======================================
echo Running intensive correctness test with $P threads
for i in `seq 1 $NumTests`; do
	echo Test $i/$NumTests
	for P in $runs; do
		./$par_program $N $printLevel $P > out.$i.$P 
	done
done

diff -q --from-file out out.*
if [ $? -eq 0 ]; then
	echo Output correct on intensive test
	rm out*
fi

