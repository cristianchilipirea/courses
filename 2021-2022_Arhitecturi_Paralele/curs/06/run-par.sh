#!/bin/bash


compileAndRun() {
    echo $1
    gcc -o $1 $1.c -lpthread -lm -O0

    #./$1 5 1 1
    #./$1 5 1 2
    #./$1 5 1 4

    time ./$1 1500 0 1
    time ./$1 1500 0 2
    time ./$1 1500 0 4

    rm $1
}

compileAndRun "multiplyMatrices-par-a"
#1m11.493s 2m56.447s 3m6.316s
compileAndRun "multiplyMatrices-par-b"
#0m31.301s 0m25.408s 0m33.274s
compileAndRun "multiplyMatrices-par-c"
#0m31.208s 0m20.023s 0m20.161s
compileAndRun "multiplyMatrices-par-d"
#0m32.747s 0m19.804s 0m19.431s
compileAndRun "multiplyMatrices-par-psum-a"
#0m20.103s 0m7.433s 0m4.698s
compileAndRun "multiplyMatrices-par-psum-b"
#0m14.063s 0m7.058s 0m4.343s
