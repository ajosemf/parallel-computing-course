#include <stdlib.h>
#include <sys/time.h>


float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec); // seconds
}


void get_time(struct timeval *time)
{
    gettimeofday(time, NULL);
}
