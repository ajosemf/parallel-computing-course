#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


int get_arguments(int *argc, 
                   char** argv, 
                   unsigned long int *num_of_vertices, 
                   double *p, 
                   int *num_threads, 
                   int *verbose)
{
    if (*argc < 3)
    {
        printf("You must pass at least two arguments:"
                "\n\t  (int) n: Number of vertices."
                "\n\t(float) p: ErdosRenyi probability in interval [0,1]."
                "\n\t  (int) t: (optional) Number of threads to be allocated. Default MAX_NUM_THREADS."
                "\n\t  (int) s: (optional) Seed to reproducibility. Default 1."
                "\n\t  (int) v: (optional) Verbose mode (only for n<=50) {1: on, 2: off}. Default: 2."
                "\n");
        return 0;
    }

    // mandatory arguments
    *num_of_vertices = atol(argv[1]);
    *p = atof(argv[2]);

    // optional arguments
    *num_threads = -1;
    if (*argc > 3)
        *num_threads = atoi(argv[3]);
    #if _OPENMP
    if (*num_threads == -1)
        *num_threads = omp_get_max_threads();
    omp_set_num_threads(*num_threads);
    #endif

    srand(1);
    if (*argc > 4)
        srand(atoi(argv[4]));

    *verbose = 2;
    if (*argc>5 && *num_of_vertices<=50)
        *verbose = atoi(argv[5]);
    
    return 1;
}