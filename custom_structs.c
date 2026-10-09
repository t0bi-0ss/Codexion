#include <pthread.h>

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
} coder_properties;

typedef struct {
    pthread_mutex_t quantum_mutex;
    int can_compile;
    int all_finished;
    int terminate_all;
    pthread_cond_t watchdog_cond;
    pthread_cond_t coders_cond;
} signals;

typedef struct {
    long number_of_coders;
    long time_to_burnout;
    long time_to_compile;
    long time_to_debug;
    long time_to_refactor;
    long number_of_compiles_required;
    long dongle_cooldown;
    int scheduler;
} all_args;