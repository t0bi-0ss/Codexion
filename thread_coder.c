#include "codexion.h"

int check_stop(void *properties)
{
    int stop_copy;
    coder_properties_struct *coder;

    coder = (coder_properties_struct *) properties;
    if (pthread_mutex_lock(&coder->coder_mutex))
    {
        fprintf(stderr, "Unable to lock coder mutex");
        return (1);
    }
    stop_copy = coder->stop;
    pthread_mutex_unlock(&coder->coder_mutex);
    return (stop_copy);
}

void *thread_coder(void *properties)
{
    coder_properties_struct *coder_p;

    coder_p = (coder_properties_struct *) properties;
    while (coder_p->times_compiled < coder_p->req_compiles)
    {
        pthread_mutex_lock(coder_p->shared_mutex_ptr);
        // make request
        coder_p->has_permission = 0;
        pthread_cond_signal(coder_p->monitor_condvar_ptr);
        while (!coder_p->has_permission && !check_stop(properties))
            pthread_cond_wait(&coder_p->wake_coder, coder_p->shared_mutex_ptr);
        pthread_mutex_unlock(coder_p->shared_mutex_ptr);
        if (check_stop(properties))
            break ;
        
    }
    return (NULL);
}
