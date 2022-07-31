#!/bin/bash

gcc src/main.c -o bin/sequential
./bin/sequential $1 $2 $3 $4 $5
