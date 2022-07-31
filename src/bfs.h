#include <stdio.h>
#include <omp.h>
#include <time.h>


void init_distances(unsigned long int n, int *arr)
{
    arr[0] = 0;
    for (unsigned long int i=1; i<n; i++)
        arr[i] = -1;
}


int extract_from_frontier(unsigned long int F[], unsigned long int *first)
{
    unsigned long int node_idx = F[*first];  // pop first element
    *first += 1;
    return node_idx;
}


void print_distances(unsigned long int n, int distances[])
{
    printf("\nDistances: ");
    for (unsigned long int i=0; i<n; i++)
        printf("%d, ", distances[i]);
    printf("\n\n");
}


double bfs(unsigned long int n, int **adj, int *verbose)
{
    // time execution control
    double time_spent = 0.0;
    clock_t begin = clock();
    
    // init distances
    int distances[n];
    init_distances(n, distances);

    // init Frontier
    unsigned long int F[n+1];
    unsigned long int first = 0;  // index of Frontier's first element
    unsigned long int next = 0;   // index of Frontier's next insertion
    F[next++] = 0;

    // traversal
    if (*verbose==1)
        printf("Nodes extracted from frontier: \n");
    int max_distance = 0;
    while (first != next)
    {
        unsigned long int node = extract_from_frontier(F, &first);
        if (*verbose == 1)
            printf("Extracted node: %lu\n", node);

        #pragma omp parallel for shared(F, next, distances) reduction(max:max_distance)
        for (unsigned long int neighbor = 0; neighbor < n; neighbor++)
        {
            if (*verbose == 1)
            {
                #if _OPENMP
                printf("Thread %d - Col %lu, ", omp_get_thread_num(), neighbor);
                #endif
            }
            if (adj[node][neighbor] == 1 && distances[neighbor] == -1)
            {
                F[next++] = neighbor;
                distances[neighbor] = distances[node] + 1;
                if (max_distance < distances[neighbor])
                    max_distance = distances[neighbor];
            }
        }
        if (*verbose == 1)
            printf("\n\n");
    }

    // elapsed time in seconds
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    // Unreached vertices
    unsigned long int num_unreached_vertices = 0;
    for (unsigned long int i=0; i<n; i++)
        if (distances[i] == -1)
            num_unreached_vertices += 1;

    // result
    printf("Graph diameter: %d\n", max_distance);
    if (num_unreached_vertices > 0)
        printf("Graph is disconected. Number of vertices unreached: %lu\n", num_unreached_vertices);
    else
        printf("Graph is conected\n");
    if (*verbose==1)
        print_distances(n, distances);

    return time_spent;
}
