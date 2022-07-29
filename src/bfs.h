#include <stdio.h>
#include <omp.h>
#include <time.h>


void init_distances(unsigned int n, int *arr)
{
    arr[0] = 0;
    for (int i=1; i<n; i++)
        arr[i] = -1;
}


int extract_from_frontier(int F[], int *first)
{
    int node_idx = F[*first];  // pop first element
    *first += 1;
    return node_idx;
}


void print_distances(unsigned int n, int distances[])
{
    printf("\nDistances: ");
    for (int i=0; i<n; i++)
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
    int F[n+1];
    int first = -1; // index of Frontier's first element 
    int last = 0;   // index of Frontier's next insertion
    F[last++] = 0;
    first++;

    // traversal
    if (*verbose==1)
        printf("Nodes extracted from frontier: \n");
    int level = 0;
    while (first != last)
    {
        if (*verbose==1)
            printf("Level %d", level);
        int node = extract_from_frontier(F, &first);
        if (*verbose==1)
            printf(", Extracted node: %d with neighbors: ", node);

        #if _OPENMP
        omp_set_num_threads(omp_get_max_threads());
        #endif

        #pragma omp parallel for shared(distances)
        for (int neighbor = 0; neighbor < n; neighbor++)
        {
            if (*verbose == 1)
            {
                #if _OPENMP
                printf("Thread %d - Node %d, ", omp_get_thread_num(), neighbor);
                #else
                printf("%d, ", neighbor);
                #endif
            }
            if (adj[node][neighbor] == 1 && distances[neighbor] == -1)
            {
                F[last++] = neighbor;
                distances[neighbor] = distances[node] + 1;
            }
        }
        level += 1;
        if (*verbose == 1)
            printf("\n\n");
    }

    // elapsed time in seconds
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    // result
    if (*verbose==1)
        print_distances(n, distances);

    return time_spent;
}
