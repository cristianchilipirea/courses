#!/bin/bash

compileAndRun() {
    echo $1
    gcc -o $1 $1.c -lpthread -lm -O0

    #./$1 5 1 1

    time ./$1 1500 0 1

    rm $1
}

compileAndRun "multiplyMatrices-seq-ijk" #0m31.304s
compileAndRun "multiplyMatrices-seq-ikj" #0m13.988s
compileAndRun "multiplyMatrices-seq-jik" #0m27.970s
compileAndRun "multiplyMatrices-seq-jki" #0m46.013s
compileAndRun "multiplyMatrices-seq-kij" #0m13.995s
compileAndRun "multiplyMatrices-seq-kji" #0m44.927s
