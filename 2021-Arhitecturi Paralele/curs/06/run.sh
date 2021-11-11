#!/bin/bash

compileAndRun() {
    echo $1
    gcc -o $1 $1.c -lpthread -lm -O0

    time ./$1 1500 0 1

    rm $1
}

compileAndRunMulti() {
    echo $1
    gcc -o $1 $1.c -lpthread -lm -O0

    time ./$1 64 10000000 0 1 # 16 10000000 0 1
    time ./$1 64 10000000 0 2 # 16 10000000 0 2
    time ./$1 64 10000000 0 4 # 16 10000000 0 4

    rm $1
}

#getconf -a | grep CACHE

#compileAndRun "multiplyMatrices-seq-ijk"
#compileAndRun "multiplyMatrices-seq-ikj"
#compileAndRun "multiplyMatrices-seq-jik"
#compileAndRun "multiplyMatrices-seq-jki"
#compileAndRun "multiplyMatrices-seq-kij"
#compileAndRun "multiplyMatrices-seq-kji"


compileAndRunMulti "addVector-group"
compileAndRunMulti "addVector-alternative"