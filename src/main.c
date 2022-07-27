#include <stdio.h>
#include <stdlib.h>
#include "rand.h"


int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("You must pass two arguments:"
                "\n\t(float) p: ErdosRenyi probability in interval [0,1]"
                "\n\t(int) s: Seed\n");
        return 0;
    }

    // arguments
    double p = atof(argv[1]);
    srand(atoi(argv[2]));

    // test rand
    int count = 0;
    for (int i=0; i < 10; i++)
    {
        if (random_bool(p) == 1)
            count += 1;
    }
    printf("\n");
    printf("%d", count);
    printf("\n");

    return 0;
}
