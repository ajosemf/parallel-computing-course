#!/bin/bash

gcc -fopenmp src/main.c -o bin/parallelrun
./bin/parallelrun $1 $2 $3
