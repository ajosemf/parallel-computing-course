#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "bfs.h"


int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("You must pass three arguments:"
                "\n\t  (int) n: Number of vertices"
                "\n\t(float) p: ErdosRenyi probability in interval [0,1]"
                "\n\t  (int) s: Seed to reproducibility"
                "\n");
        return 0;
    }

    // arguments
    int num_of_vertices = atoi(argv[1]);
    double p = atof(argv[2]);
    srand(atoi(argv[3]));

    // adjacency matrix
    int adj[num_of_vertices][num_of_vertices];
    create_adj_matrix(num_of_vertices, adj, p);
    print_adj_matrix(num_of_vertices, adj);

    // bfs
    bfs(num_of_vertices, adj);

    return 0;
}
