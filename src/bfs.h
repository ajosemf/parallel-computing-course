#include <stdio.h>
#include <omp.h>


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


void bfs(unsigned int n, int adj[n][n])
{
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
    printf("Nodes extracted from frontier: \n");
    int level = 0;
    while (first != last)
    {
        printf("Level %d", level);
        int node = extract_from_frontier(F, &first);
        printf(", Extracted node: %d with neighbors: ", node);

        #if _OPENMP
        omp_set_num_threads(omp_get_max_threads());
        #endif

        #pragma omp parallel for shared(distances)
        for (int neighbor = 0; neighbor < n; neighbor++)
        {
            #if _OPENMP
            printf("Thread %d - Node %d, ", omp_get_thread_num(), neighbor);
            #else
            printf("%d, ", neighbor);
            #endif
            if (adj[node][neighbor] == 1 && distances[neighbor] == -1)
            {
                F[last++] = neighbor;
                distances[neighbor] = distances[node] + 1;
            }
        }
        level += 1;
        printf("\n\n");
    }

    // distances
    print_distances(n, distances);
}
