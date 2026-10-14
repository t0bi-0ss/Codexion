#include "codexion.h"

void *thread_coder(void *properties)
{
    thrds_properties_struct *start_values;

    start_values = (thrds_properties_struct *) properties;

    while (start_values->times_compiled < COMPILE_TIMES)
    {
        pthread_mutex_lock(&quantum_mutex);
        while (!quantum_available)
            if (pthread_cond_wait(&coders_cond, &quantum_mutex) != 0)
            {
                printf("Coder n: %ld has burnout\n", start_values->id);
                terminate_all++;
                free(properties);
                pthread_exit(NULL);
            }
        quantum_available--;
        compile(start_values->id, start_values->times_compiled);
        start_values->times_compiled++;
        pthread_mutex_unlock(&quantum_mutex);
        pthread_cond_signal(&watchdog_cond);
    }
    all_finished++;
    free(properties);
    return (NULL);
}