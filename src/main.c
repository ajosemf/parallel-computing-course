#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "getargs.h"
#include "graph.h"
#include "bfs.h"


int main(int argc, char** argv)
{
    // arguments
    unsigned long int num_of_vertices;
    double p;
    int num_threads, verbose;
    if(!get_arguments(&argc, argv, &num_of_vertices, &p, &num_threads, &verbose))
        return 0;

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
