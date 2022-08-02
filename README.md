# Parallel Computing Course
Tasks developed in the PPCIC Parallel Computing Course at CEFET/RJ

## Course outline
Architectures, systems, algorithms, programming models, languages and software tools. Topics covered include parallel architectures; parallel and distributed computing systems, cloud and grid computing; distributed and parallel algorithms, data structures and programming methodologies; parallelization and distribution models (MPI, Map-Reduce, etc); performance analysis, and applications involving data analysis and scientific workflows.

## Requirements
[Open MP](https://www.openmp.org/) >= 201511

or in case you choose to run in a docker container ***(strongly recommended)***

[Docker](https://www.docker.com/) >= 20.10.17

## To run openMP in docker container
In terminal, execute (just once):
```shell
$ docker build -t openmp .
```
And always you want to use it:
```shell
$ ./run_container.sh
```
## Compiling openMP programs
To make the compiler recognize openMP directives, you must compile programs using `-fopenmp` flag, like this:
```shell
$ gcc -fopenmp src/hello_world.c -o bin/hello
```
If you want to enable warnings:
```shell
$ gcc -g -Wall -fopenmp src/hello_world.c -o bin/hello
```

## Arguments
* arg1: (int) n: Number of vertices
* arg2: (float) p: ErdosRenyi probability in interval [0,1]
* arg3: (int) t: (optional) Number of threads to be allocated. Default MAX_NUM_THREADS.
* arg4: (int) s: (optional) Seed to reproducibility. Default 1.
* arg5: (int) v: (optional) Verbose mode (only for n<=50) {1: on, 2: off}. Default: 2.
> `Note 1: to see BFS things happen, set verbose to 1.`
> 
> `Note 2: to see parallel approach performance, use n >= 10000.`
> 
> `Note 3: n = 25000 can allocate approximately 2.5GB RAM so use sparingly :)`

## Running Sequential BFS
Inside openMP container, run:
```shell
$ gcc src/main.c -o bin/sequential
$ ./bin/sequential <args>
```

## Running Parallel BFS
Inside openMP container, run:
```shell
$ gcc -fopenmp src/main.c -o bin/parallel
$ ./bin/parallel <args>
```
