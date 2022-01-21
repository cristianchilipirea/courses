#!/bin/bash

maxRunTime=60
minScalability=1.1
points=0
programToTest=homework
declare -A extraParameters

# Tests parameters
extraParameters[test_1]="in_4.txt"
#extraParameters[test_2]="in_2.txt"

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
		exit 1

	elif [ $ret == 127 ]
	then
		echo -e "\nERROR: Program not found (maybe it did not compile)"
	elif [ $ret == 134 ]
	then
		echo -e "\nERROR: Signal SIGABRT"
		echo "ERROR: maybe something wrong with malloc/free"
		echo "ERROR: check with valgrind --leak-check=full ./$program"
		exit 1

	elif [ $ret == 139 ]
	then
		echo -e "\nERROR: Signal SIGSEGV"
		echo "ERROR: Segfault - maybe something wrong with  malloc, free, pointer, overflow and so on"
		echo "ERROR: check with valgrind --leak-check=full ./$program"
		exit 1

	elif [ $ret -gt 127 ]
	then
		echo -e "\nERROR: Program ended with non-zero return code $ret"
		echo "ERROR: Does your program return 0?"
		echo "ERROR: Problems with system function-calls can also trigger this"
		echo "ERROR: in a terminal type 'trap -l' and see $(($ret-128)) to identify the error"
		exit 1

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
	inputImage=`echo ${extraParameters[$testName]}`

	testResult="FAILED"
	echo -n "Running $testName with $numThreads processes. "
	programArgs="./input/$inputImage ./output/$fullTestName.$inputImage"
    #echo -e "\t$programArgs"

	#/usr/bin/time --quiet -f "%e" -o execTime.$fullTestName timeout $maxRunTime ./$program $programArgs $numThreads &> /dev/null
    /usr/bin/time -f "%e" -o execTime.$fullTestName timeout $maxRunTime ./$program $programArgs $numThreads &> /dev/null
    #echo "/usr/bin/time -f %e -o execTime.$fullTestName timeout $maxRunTime ./$program $programArgs $numThreads &> /dev/null"

	ret=$?
	checkReturnCode $ret
	if [ $ret != 0 ]
	then
	 	echo -e "\n"
	elif [ ! -e ./output/$fullTestName.$inputImage ]
	then
		echo -e "\nERROR: Output file does not exist"
	else
	 	diff ./ref/$testName.$inputImage ./output/$fullTestName.$inputImage &> /dev/null
	 	if [ $? != 0 ]
	 	then
	 		echo -e "\nERROR: Output files differ"
	 	else
	 		testResult="PASSED"
		fi
	fi
	times[$num_threads]="`tail -n 1 execTime.$fullTestName`"
	echo "Finished in ${times[$num_threads]} seconds."
	rm ./output/$fullTestName.$inputImage
}

make
maxRunTime=10
pointsPerTest=2

# for i in $(seq 1 4)
# do
# 	testNameL="Checking outputs for test_$i"
# 	runProgram $programToTest "test_$i" 1
# 	printResult $testNameL $testResult $pointsPerTest
# 	echo ""
# done

function scalabilityTest {
	pointsForScalability=$1
	pointsForOneTest=$2
	sumScalability=0
	testResultAllThreadsAllTests="PASSED"
	for testNameShort in $tests
	do
		testResultAllThreads="PASSED"
		for num_threads in 1 256
		do
			runProgram $programToTest $testNameShort $num_threads
			if [ $testResult == "FAILED" ]
			then
				testResultAllThreads="FAILED"
			fi
		done
		echo "Execution times: 1 Process -"  ${times[1]}"; 256 Processes - " ${times[256]}";"
		scalability=$(echo "(${times[1]}/(${times[256]}+0.00001))" | bc -l)
		echo "Scalability score (1P/256P) is $scalability"
		sumScalability=$(echo "$sumScalability+$scalability" | bc -l)
		if [ $testResultAllThreads == "FAILED" ]
		then
			testResultAllThreadsAllTests="FAILED"
		fi
		testName="Checking outputs for $testNameShort"
		printResult $testName $testResultAllThreads $pointsForOneTest
        echo ""
	done

    numTests=$(echo $tests | wc -w)
    #echo $numTests
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

# Output corect program paralelizat si scalabil
maxRunTime=60
tests="test_1"
scalabilityTest 100 0
echo ""

echo "                                      Total  =  [ $(echo "scale=3; $points" | bc)/100.000 ]"
echo "";

killall $programToTest &> /dev/null