#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#define COMPILE_TIMES 10
#define CODERS_NUM 10

typedef struct {
    long start_time;
    long id;
    long times_compiled;
} thrds_properties;

typedef struct {
    long number_of_coders;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    long number_of_compiles_required;
    long dongle_cooldown;
    char *scheduler;
}

pthread_mutex_t quantum_mutex;
int can_compile = 0;
int all_finished = 0;
int terminate_all = 0;
pthread_cond_t watchdog_cond;
pthread_cond_t coders_cond;

void compile(long id, int compilations);

void debug(long id);

void refactor(long id);

void *coder(void *coder_id);

void *watchdog(void *id);

long time_since_start(long start_time);

thrds_properties *init_properties(long start_time, long id);

int main()
{
    pthread_t coders[CODERS_NUM];
    pthread_t monitor;
    struct timeval now;
    long    start_time;
    thrds_properties *start_values;

    // Initialize mutexes
    pthread_cond_init(&coders_cond, NULL);
    pthread_mutex_init(&quantum_mutex, NULL);

    // Get time at start
    gettimeofday(&now, NULL);
    start_time = now.tv_usec;

    // Create threads
    for (long i = 0; i < CODERS_NUM; i++)
    {
        start_values = init_properties(start_time, i);
        pthread_create(&coders[i], NULL, coder, (void *) start_values);
    }
    pthread_create(&monitor, NULL, watchdog, NULL);

    // Wait for threads to finish
    for (int i = 0; i < CODERS_NUM; i++)
        pthread_join(coders[i], NULL);
    pthread_join(monitor, NULL);

    // Destroy variables
    pthread_cond_destroy(&coders_cond);
    pthread_mutex_destroy(&quantum_mutex);
    
    return (0);
}

void compile(long id, int compilations)
{
    printf("Coder n: %ld has compiled effectively for the %d time\n", id, compilations + 1);
    usleep(100000);
}

void debug(long id)
{
    printf("Coder n: %ld is debugging\n", id);
}

void refactor(long id)
{
    printf("Coder n: %ld is refactoring\n", id);
}

void *watchdog(void *id)
{
    while (all_finished < 10)
    {
        pthread_mutex_lock(&quantum_mutex);
        while (can_compile)
            if (pthread_cond_wait(&watchdog_cond, &quantum_mutex) != 0)
            {
                printf("Watchdog error: cond wait error");
                terminate_all++;
            }
        if (!can_compile)
            can_compile++;
        pthread_mutex_unlock(&quantum_mutex);
        pthread_cond_broadcast(&coders_cond);
    }
    printf("\nAll coders have compiled 10 times succesfully!\n");
    return (NULL);
}

void *coder(void *properties)
{
    thrds_properties *start_values;

    start_values = (thrds_properties *) properties;

    while (start_values->times_compiled < COMPILE_TIMES)
    {
        pthread_mutex_lock(&quantum_mutex);
        while (!can_compile)
            if (pthread_cond_wait(&coders_cond, &quantum_mutex) != 0)
            {
                printf("Coder n: %ld has burnout\n", start_values->id);
                terminate_all++;
                free(properties);
                pthread_exit(NULL);
            }
        can_compile--;
        compile(start_values->id, start_values->times_compiled);
        start_values->times_compiled++;
        pthread_mutex_unlock(&quantum_mutex);
        pthread_cond_signal(&watchdog_cond);
    }
    all_finished++;
    free(properties);
    return (NULL);
}

thrds_properties *init_properties(long start_time, long id)
{
    thrds_properties *element;

    element = (thrds_properties *) malloc(sizeof(thrds_properties));
    if (!element)
        return (NULL);
    element->id = id;
    element->start_time = start_time;
    element->times_compiled = 0;

    return (element);
}

long time_since_start(long start_time)
{
    struct timeval now;
    long diff;

    gettimeofday(&now, NULL);
    diff = now.tv_usec - start_time;
    
    return (diff);
}