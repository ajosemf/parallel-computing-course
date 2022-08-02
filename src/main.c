#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "graph.h"
#include "bfs.h"


int main(int argc, char** argv)
{
    if (argc < 3)
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
    unsigned long int num_of_vertices = atol(argv[1]);
    double p = atof(argv[2]);

    // optional arguments
    int num_threads = -1;
    if (argc > 3)
        num_threads = atoi(argv[3]);
    #if _OPENMP
    if (num_threads == -1)
        num_threads = omp_get_max_threads();
    omp_set_num_threads(num_threads);
    #endif

    srand(1);
    if (argc > 4)
        srand(atoi(argv[4]));

    int verbose = 2;
    if (argc>5 && num_of_vertices<=50)
        verbose = atoi(argv[5]);

    // adjacency matrix
    int **adj;
    adj = malloc(num_of_vertices * sizeof(int *));
    for (int i = 0; i < num_of_vertices; ++i)
        adj[i] = malloc(num_of_vertices * sizeof(int));
    unsigned long int num_of_edges = create_adj_matrix(num_of_vertices, adj, p);
    if(verbose==1)
        print_adj_matrix(num_of_vertices, adj);

    // header
    #if _OPENMP
        printf("\nApproach: parallel\n");
        printf("Num threads: %d\n", num_threads);
    #else
        printf("\nApproach: sequential\n");
    #endif
    printf("Num vertices: %lu\n", num_of_vertices);
    printf("Num edges: %lu\n", num_of_edges);

    // bfs
    float time_spent = bfs(num_of_vertices, adj, &verbose);

    // result
    printf("BFS time spent in seconds: %0.8f\n\n", time_spent);

    return 0;
}
