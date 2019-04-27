#include "utils.h"

#include <sys/time.h>
#include <stdlib.h>
#include <math.h>

double time_now() 
{
    struct timeval time;
    if (gettimeofday(&time,NULL)) return 0;
    return (double)time.tv_sec + (double)time.tv_usec * 1e-6;
}

// From https://en.wikipedia.org/wiki/Box-Muller_transform
float rand_normal()
{
    static int have_spare = 0;
    static double rand1, rand2;

    if(have_spare) {
        have_spare = 0;
        return sqrt(rand1) * sin(rand2);
    }

    have_spare = 1;

    rand1 = rand() / ((double) RAND_MAX);
    if(rand1 < 1e-100) rand1 = 1e-100;
    rand1 = -2 * log(rand1);
    rand2 = (rand() / ((double) RAND_MAX)) * TWO_PI;

    return sqrt(rand1) * cos(rand2);
}

float rand_uniform(float min, float max)
{
    if(max < min) {
        float swap = min;
        min = max;
        max = swap;
    }
    return ((float)rand()/RAND_MAX * (max - min)) + min;
}
