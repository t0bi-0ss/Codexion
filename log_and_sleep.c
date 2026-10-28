#include "codexion.h"

static long time_since_start(struct timespec start_time);
static void    log_event(monitor_struct *monitor_ptr, char *event, int id);
static void    sleep_for(useconds_t sleep_time);
static void dongles_grab(monitor_struct *monitor_ptr, int id);

void    log_and_sleep(coder_properties_struct *coder_p, Coder_actions action)
{
    char    *event;
    long    start_time;
    useconds_t  sleep_time;
    
    if (action == COMPILE)
    {
        event = "is compiling";
        sleep_time = coder_p->monitor_ptr->loaded_config.time_to_compile;
    }
    else if (action == DEBUG)
    {
        event = "is debugging";
        sleep_time = coder_p->monitor_ptr->loaded_config.time_to_debug;
    }
    else if (action == REFACTOR)
    {
        event = "is refactoring";
        sleep_time = coder_p->monitor_ptr->loaded_config.time_to_refactor;
    }
    else if (action == GRAB)
        return (dongles_grab(coder_p->monitor_ptr, coder_p->id));
    log_event(coder_p->monitor_ptr, event, coder_p->id);
    sleep_for(sleep_time);
}

static long time_since_start(struct timespec start_time)
{
    long    time_since_start;
    struct timespec now;
    
    now = get_timestamp();
    now.tv_nsec -= start_time.tv_nsec;
    now.tv_sec -= start_time.tv_sec;
    time_since_start = now.tv_nsec / 1000 + now.tv_sec * 1000;
}

static void    log_event(monitor_struct *monitor_ptr, char *event, int id)
{
    long    start_time;

    pthread_mutex_lock(&monitor_ptr->mutex_stdout);
    start_time = time_since_start(monitor_ptr->start_time);
    printf("%ld %i %s\n", start_time, id, event);
    pthread_mutex_unlock(&monitor_ptr->mutex_stdout);
}
static void    sleep_for(useconds_t sleep_time)
{
    usleep(sleep_time);
}

static void dongles_grab(monitor_struct *monitor_ptr, int id)
{
    log_event(monitor_ptr, "has taken a dongle", id);
    log_event(monitor_ptr, "has taken a dongle", id);
}
