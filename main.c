#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/times.h>
#include <time.h>
#include <ctype.h>
#include <sys/resource.h>
#include <stdbool.h>

// a test struct with the data spanning more than  1 cache line (64 bytes).
// the final char element ("second") is outside the 64 byte cache line, and accessing
// causes a cache miss.
typedef struct _non_aligned_t
{
    char first;
    int64_t temp_int01;
    int64_t temp_int02;
    int64_t temp_int03;
    int64_t temp_int04;
    int64_t temp_int05;
    int64_t temp_int06;
    int64_t temp_int07;
    int32_t temp_int08;
    char second;        // won't be in first cache line (64bytes)
} non_aligned_t;


// a test struct such that the 2 elements are retrieved on
// a single cahce line
typedef struct _aligned_t
{
    char first;
    char second;        // will be in same cacheline as "first"
    int32_t temp_int08;
    int64_t temp_int01;
    int64_t temp_int02;
    int64_t temp_int03;
    int64_t temp_int04;
    int64_t temp_int05;
    int64_t temp_int06;
    int64_t temp_int07;
} aligned_t;


#define NUM_STRUCTS 50000
#define NUM_LOOPS 10000


void do_one_cache_line(bool do_logging);
int handle_cli_args(int argc, char *argv[]);

/*
 * Tests cache line access to structs and benchmarks performance
 */
int main(int argc, char *argv[])
{
    if (handle_cli_args(argc, argv) < 0)
    {
        return -1;
    }

    // call once to warm up cpu (compensate for down-shift of clock freq during idle)
    do_one_cache_line(false);

    do_one_cache_line(true);

    return 0;
}


int handle_cli_args(int argc, char *argv[])
{
    // format
    //  arg[1] = affinity .... options Y|N
    //  arg[2] = max priority ......options Y|N
    if (argc != 3)
    {
        printf("Invalid args: arg1 affinity (Y|N), arg2 Max PRI (Y|N)");
        return -1;
    }

    char affinity = toupper(*argv[1]);
    if(affinity == 'Y')
    {
        cpu_set_t my_set;
        CPU_ZERO(&my_set);
        CPU_SET(1, &my_set);
        if (sched_setaffinity(0, sizeof(cpu_set_t), &my_set) > 0)
        {
            printf("affinity error");
            return -1;
        }
    }

    char maxprio = toupper(*argv[2]);
    if (maxprio == 'Y')
    {
        if (setpriority (PRIO_PROCESS, 0, PRIO_MAX) != 0)
        {
            return -1;
        }
    }
    return 0;
}




void do_one_cache_line(const bool do_logging)
{
    clock_t start, end;
    int cpu_time_used;

    non_aligned_t* nonaligned = (non_aligned_t*) malloc( NUM_STRUCTS * sizeof(non_aligned_t) );

    int reps,i = 0;

    for(reps = 0; reps < NUM_LOOPS; reps++)
    {
        non_aligned_t* na = nonaligned;
        char val = reps % 8;    // some random value to write to struct
        start = clock();

        for(i = 0; i < NUM_STRUCTS; i++)
        {
            na->first = val;
            na->second = val;
            na++;
        }
        end = clock();
        cpu_time_used = end - start;

        if(do_logging)
            printf("time (ticks), %d\n", cpu_time_used);
    }
    free(nonaligned);


    aligned_t* aligned = (aligned_t*) malloc( NUM_STRUCTS * sizeof(aligned_t) );
    for(reps = 0; reps < NUM_LOOPS; reps++)
    {
        aligned_t* a = aligned;
        char val = reps % 8;        // some random value to write to struct
        start = clock();

        for(i = 0; i < NUM_STRUCTS; i++)
        {
            a->first = val;
            a->second = val;
            a++;
        }
        end = clock();
        cpu_time_used = end - start;
        if (do_logging)
            printf("time (ticks), %d\n", cpu_time_used);
    }
    free(aligned);
}


