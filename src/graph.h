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


void create_adj_matrix(unsigned long int n, int **adj, double p)
{
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
        }
    }
}


void print_adj_matrix(unsigned long int n, int **adj)
{
    unsigned long int i, j, count=0;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            printf("%d   ", adj[i][j]);
            if (adj[i][j] == 1)
                count += 1;
        }
        printf("\n");
    }
    printf("Number of edges: %lu\n\n", count);
}
