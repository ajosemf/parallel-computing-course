#!/bin/bash

gcc src/main.c -o bin/sequential
gcc -fopenmp src/main.c -o bin/parallel

for n in 12500 25000 50000; do
    for i in 1 2 3; do
        echo "# sequential $n $i"
        ./bin/sequential $n 0.02
    done
    for p in 2 4 6 8 10 12; do
        for j in 1 2 3; do
            echo "# parallel $n $p $j"
            ./bin/parallel $n 0.02 $p
        done
    done
done
