#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "bfs.h"


int main(int argc, char** argv)
{
    if (argc < 4)
    {
        printf("You must pass three arguments:"
                "\n\t  (int) n: Number of vertices"
                "\n\t(float) p: ErdosRenyi probability in interval [0,1]"
                "\n\t  (int) s: Seed to reproducibility"
                "\n\t  (int) v: Verbose mode (only for n<=50) {1: on, 2: off, default: 2}"
                "\n");
        return 0;
    }

    // arguments
    unsigned long int num_of_vertices = atol(argv[1]);
    double p = atof(argv[2]);
    srand(atoi(argv[3]));
    int verbose = 2;
    if (argc==5 && num_of_vertices<=50)
        verbose = atoi(argv[4]);

    // adjacency matrix
    int **adj;
    adj = malloc(num_of_vertices * sizeof(int *));
    for (int i = 0; i < num_of_vertices; ++i)
        adj[i] = malloc(num_of_vertices * sizeof(int));

    create_adj_matrix(num_of_vertices, adj, p);
    if(verbose==1)
        print_adj_matrix(num_of_vertices, adj);

    // bfs
    double time_spent = bfs(num_of_vertices, adj, &verbose);

    // result
    #if _OPENMP
        printf("\nParallel approach\n");
    #else
        printf("\nSequential approach\n");
    #endif
    printf("Time elapsed: %f\n\n", time_spent);

    return 0;
}
