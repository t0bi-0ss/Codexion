#include "../../codexion.h"

static int check_stop(void *properties);
static int    coder_compilation(coder_properties_struct *coder_p);
static int  coder_action(coder_properties_struct *coder_p, Coder_actions action);

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
        if (coder_action(coder_p, GRAB))
            break;
        if (coder_compilation(coder_p))
            break;
        pthread_cond_signal(&coder_p->monitor_ptr->wake_monitor);
        if (coder_action(coder_p, DEBUG))
            break;
        if (coder_action(coder_p, REFACTOR))
            break;
    }
    return (NULL);
}

static int check_stop(void *properties)
{
    int stop_copy;
    coder_properties_struct *coder;

    coder = (coder_properties_struct *) properties;
    stop_copy = coder->stop;
    return (stop_copy);
}

static int    coder_compilation(coder_properties_struct *coder_p)
{
    if (coder_p->stop)
        return (1);
    log_and_sleep(coder_p, COMPILE);
    pthread_mutex_lock(&coder_p->monitor_ptr->shared_mutex);
    update_both_dongles(coder_p);
    pthread_mutex_unlock(&coder_p->monitor_ptr->shared_mutex);
    return (0);
}

static int  coder_action(coder_properties_struct *coder_p, Coder_actions action)
{
    if (coder_p->stop)
        return (1);
    log_and_sleep(coder_p, action);
    return (0);
}
