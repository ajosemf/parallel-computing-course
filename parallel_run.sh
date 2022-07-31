#!/bin/bash

gcc -fopenmp src/main.c -o bin/parallel
./bin/parallel $1 $2 $3 $4 $5
