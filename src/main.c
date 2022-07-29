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
    int num_of_vertices = atoi(argv[1]);
    double p = atof(argv[2]);
    srand(atoi(argv[3]));
    int verbose = 2;
    if (argc==5 && num_of_vertices<=50)
        verbose = atoi(argv[4]);

    // adjacency matrix
    int adj[num_of_vertices][num_of_vertices];
    create_adj_matrix(num_of_vertices, adj, p);
    if(verbose==1)
        print_adj_matrix(num_of_vertices, adj);

    // bfs
    bfs(num_of_vertices, adj, &verbose);

    return 0;
}
