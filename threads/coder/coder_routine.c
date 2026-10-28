#include "../../codexion.h"

static int check_stop(void *properties);
static void    coder_compilation(coder_properties_struct *coder_p);

void *coder_routine(void *properties)
{
    coder_properties_struct *coder_p;

    coder_p = (coder_properties_struct *) properties;
    while (coder_p->times_compiled < coder_p->monitor_ptr->loaded_config->compiles_required)
    {
        add_request(coder_p);
        coder_p->has_permission = 0;
        pthread_cond_signal(coder_p->monitor_ptr->wake_monitor);
        while (!coder_p->has_permission && !check_stop(properties))
            pthread_cond_wait(&coder_p->wake_coder, &coder_p->monitor_ptr->shared_mutex);
        pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
        if (check_stop(properties))
            break ;
        coder_compilation(coder_p);
        if (check_stop(properties))
            break;
        log_and_sleep(coder_p->monitor_ptr, DEBUG);
        if (check_stop(properties))
            break;
        log_and_sleep(coder_p->monitor_ptr, REFACTOR);
    }
    return (NULL);
}

static int check_stop(void *properties)
{
    int stop_copy;
    coder_properties_struct *coder;

    coder = (coder_properties_struct *) properties;
    pthread_mutex_lock(&coder->coder_mutex);
    stop_copy = coder->stop;
    pthread_mutex_unlock(&coder->coder_mutex);
    return (stop_copy);
}

static void    coder_compilation(coder_properties_struct *coder_p)
{
    pthead_mutex_lock(&coder_p->monitor_ptr->shared_mutex);
    update_time_to_burnout(coder_p->monitor_ptr->loaded_config.time_to_burnout, &coder_p->to_burnout);
    coder_p->times_compiled++;
    update_both_dongles(coder_p);
    pthread_cond_signal(&coder_p->monitor_ptr->wake_monitor);
    pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
    log_and_sleep(coder_p->monitor_ptr, COMPILE);
}
