#include <stdio.h>
#include <stdlib.h>


int random_bool(double p)
{
    double tmp = (rand() % 99)/100.0;
    if (tmp >= 1-p)
        return 1;
    else
        return 0;
}


unsigned long int create_adj_matrix(unsigned long int n, int **adj, double p)
{
    unsigned long int num_of_edges = 0;
    for (unsigned long int i=0; i < n; i++)
    {
        adj[i][i] = 0;  // no self-loops
        if (i == n-1)   // bottom right of matrix
            break;
        for (unsigned long int j=i+1; j < n; j++)
        {
            int relation_value = random_bool(p);
            adj[i][j] = relation_value;
            adj[j][i] = relation_value;
            if (relation_value == 1)
                num_of_edges += 1;
        }
    }
    return num_of_edges;
}


void print_adj_matrix(unsigned long int n, int **adj)
{
    unsigned long int i, j;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
            printf("%d   ", adj[i][j]);
        printf("\n");
    }
}
