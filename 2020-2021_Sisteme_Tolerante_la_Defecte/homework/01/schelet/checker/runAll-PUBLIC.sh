#!/bin/bash

maxRunTime=60
minScalability=1.1
points=2
programToTest=homework
declare -A extraParameters

# Tests parameters
extraParameters[test_1]="lenna_bw.pgm blur"
extraParameters[test_2]="lenna_bw.pgm emboss"
extraParameters[test_3]="lenna_bw.pgm smooth"
extraParameters[test_4]="lenna_bw.pgm mean"
extraParameters[test_5]="lenna_bw.pgm sharpen"
extraParameters[test_6]="lenna_color.pnm blur"
extraParameters[test_7]="lenna_color.pnm emboss"
extraParameters[test_8]="lenna_color.pnm smooth"
extraParameters[test_9]="lenna_color.pnm mean"
extraParameters[test_10]="lenna_color.pnm sharpen"
extraParameters[test_11]="lenna_bw.pgm blur smooth sharpen emboss mean blur smooth sharpen emboss mean"
extraParameters[test_12]="lenna_color.pnm blur smooth sharpen emboss mean blur smooth sharpen emboss mean"
extraParameters[test_13]="city_bw.pgm sharpen"
extraParameters[test_14]="city_color.pnm sharpen"
extraParameters[test_15]="city_bw.pgm blur smooth sharpen emboss mean blur smooth sharpen emboss mean blur emboss"
extraParameters[test_16]="city_color.pnm blur smooth sharpen emboss mean blur smooth sharpen emboss mean blur emboss"

function print_points {
	TEST=$*
	NUM=$((55 - ${#TEST}))
	for i in $(seq $NUM)
	do
		echo -n .
	done
}

function printResult {
	testName=${@:1:$#-2}
	testResult=${@:$#-1:1}
	pointsPerTest=${@: -1}
	if [ $testResult == FAILED ]
	then
		echo "$testName$(print_points $testName)FAILED (0/$pointsPerTest)"
	else
		echo "$testName$(print_points $testName)PASSED ($pointsPerTest/$pointsPerTest)"
		points=$(echo "$points+$pointsPerTest"| bc -l)
	fi
}

function checkReturnCode {
	ret=$1
	if [ $ret == 124 ]
	then
		echo -e "\nERROR: Program took more than $maxRunTime seconds to execute"
		echo "ERROR: It is possible you have an infinte loop bug or a dead-lock"
		echo "ERROR: for dead-locks check with valgrind --tool=helgrind -s ./$program"
	elif [ $ret == 127 ]
	then
		echo -e "\nERROR: Program not found (maybe it did not compile)"
	elif [ $ret == 134 ]
	then
		echo -e "\nERROR: Signal SIGABRT"
		echo "ERROR: maybe something wrong with malloc/free"
		echo "ERROR: check with valgrind --leak-check=full ./$program"
	elif [ $ret == 139 ]
	then
		echo -e "\nERROR: Signal SIGSEGV"
		echo "ERROR: Segfault - maybe something wrong with  malloc, free, pointer, overflow and so on"
		echo "ERROR: check with valgrind --leak-check=full ./$program"
	elif [ $ret -gt 127 ]
	then
		echo -e "\nERROR: Program ended with non-zero return code $ret"
		echo "ERROR: Does your program return 0?"
		echo "ERROR: Problems with system function-calls can also trigger this"
		echo "ERROR: in a terminal type 'trap -l' and see $(($ret-128)) to identify the error"
	elif [ $ret != 0 ]
	then
		echo -e "\nERROR: Program ended with non-zero return code $ret."
		echo "ERROR: Does your program return 0?"
	fi
}

function runProgram {
	program=$1
	testName=$2
	numThreads=$3
	fullTestName=$testName.$numThreads
	inputImage=`echo ${extraParameters[$testName]} | head -n1 | cut -d " " -f1`
	inputImageExtension=`echo $inputImage | cut -d "." -f2`
	filters=`echo ${extraParameters[$testName]} | head -n1 | cut -d " " -f2-100`

	testResult="FAILED"
	echo -n "Running $testName with $numThreads processes. "
	programArgs="./input/$inputImage ./output/$fullTestName.$inputImageExtension $filters"

	/usr/bin/time --quiet -f "%e" -o execTime.$fullTestName timeout $maxRunTime mpirun -np $numThreads $program $programArgs &> /dev/null

	ret=$?
	checkReturnCode $ret
	if [ $ret != 0 ]
	then
	 	echo -e "\n"
	elif [ ! -e ./output/$fullTestName.$inputImageExtension ]
	then
		echo -e "\nERROR: Output file does not exist"
	else
	 	./compare ./ref/$testName.$inputImageExtension ./output/$fullTestName.$inputImageExtension &> /dev/null
	 	if [ $? != 0 ]
	 	then
	 		echo -e "\nERROR: Output files differ"
	 	else
	 		testResult="PASSED"
		fi
	fi
	times[$num_threads]="`tail -n 1 execTime.$fullTestName`"
	echo "Finished in ${times[$num_threads]} seconds."
	rm ./output/$fullTestName.$inputImageExtension
}

make
maxRunTime=10
pointsPerTest=2

for i in $(seq 1 14)
do
	testNameL="Checking outputs for test_$i"
	runProgram $programToTest "test_$i" 1
	printResult $testNameL $testResult $pointsPerTest
	echo ""
done

function scalabilityTest {
	pointsForScalability=$1
	pointsForOneTest=$2
	sumScalability=0
	testResultAllThreadsAllTests="PASSED"
	for testNameShort in $tests
	do
		testResultAllThreads="PASSED"
		for num_threads in 1 2 4
		do
			runProgram $programToTest $testNameShort $num_threads
			if [ $testResult == "FAILED" ]
			then
				testResultAllThreads="FAILED"
			fi
		done
		echo "Execution times: 1 Process -"  ${times[1]}"; 2 Processes - " ${times[2]}"; 4 Processes - "${times[4]}
		scalability=$(echo "((${times[1]}/(${times[2]}+0.00001))+(${times[2]}/(${times[4]}+0.00001)))/2" | bc -l)
		echo "Scalability score ((1P/2P + 2P/4P) / 2) is $scalability"
		sumScalability=$(echo "$sumScalability+$scalability" | bc -l)
		if [ $testResultAllThreads == "FAILED" ]
		then
			testResultAllThreadsAllTests="FAILED"
		fi
		testName="Checking outputs for $testNameShort"
		printResult $testName $testResultAllThreads $pointsForOneTest
	done

	numTests=$(echo $tests | wc -w)
	averageScalability=$(echo "$sumScalability/$numTests" | bc -l)
	isScalable=$(echo "$averageScalability > $minScalability" | bc -l)
	echo "Average scalability score is $averageScalability"
	echo "Average scalability score should be larger than $minScalability"
	testResultScalability="FAILED"
	if [ $testResultAllThreadsAllTests == FAILED ]
	then
		echo "However, scalability is irrelevant if any previous test failed."
	elif [ $isScalable != 0 ]
	then
		testResultScalability="PASSED"
	fi
	testName="Checking scalability on $programToTest"
	printResult $testName $testResultScalability $pointsForScalability
}
maxRunTime=20
tests="test_15 test_16"
scalabilityTest 70 0

echo "                                      Total  =  [ $(echo "scale=3; $points" | bc)/100.000 ]"

killall $programToTest &> /dev/null
killall mpirun &> /dev/null