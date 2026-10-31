#include "../../codexion.h"

static int check_stop(void *properties);
static void    coder_compilation(coder_properties_struct *coder_p);

void *coder_routine(void *properties)
{
    coder_properties_struct *coder_p;

    coder_p = (coder_properties_struct *) properties;
    while (1)
    {
        pthread_mutex_lock(&coder_p->monitor_ptr->shared_mutex);
        add_request(coder_p);
        coder_p->has_permission = 0;
        pthread_cond_signal(&coder_p->monitor_ptr->wake_monitor);
        while (!coder_p->has_permission && !coder_p->stop)
            pthread_cond_wait(&coder_p->wake_coder, &coder_p->monitor_ptr->shared_mutex);
        pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
        if (check_stop(properties))
            break ;
        log_and_sleep(coder_p, GRAB);
        if (check_stop(properties))
            break ;
        coder_compilation(coder_p);
        pthread_cond_signal(&coder_p->monitor_ptr->wake_monitor);
        if (check_stop(properties))
            break;
        log_and_sleep(coder_p, DEBUG);
        if (check_stop(properties))
            break;
        log_and_sleep(coder_p, REFACTOR);
    }
    return (NULL);
}

static int check_stop(void *properties)
{
    int stop_copy;
    coder_properties_struct *coder;

    coder = (coder_properties_struct *) properties;
    stop_copy = coder->stop;
    if (stop_copy)
        log_event(coder->monitor_ptr, "has stopped", coder->id);
    return (stop_copy);
}

static void    coder_compilation(coder_properties_struct *coder_p)
{
    log_and_sleep(coder_p, COMPILE);
    pthread_mutex_lock(&coder_p->monitor_ptr->shared_mutex);
    update_both_dongles(coder_p);
    pthread_cond_signal(&coder_p->monitor_ptr->wake_monitor);
    pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
}
