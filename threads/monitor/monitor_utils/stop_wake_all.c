#include "../../../codexion.h"

void    stop_wake_all(coder_properties_struct *coders_arr,
    config_struct *loaded_config,
    pthread_mutex_t *shared_mutex)
{
    int i;

    i = 0;
    while (i < loaded_config->number_of_coders)
    {
        if (!coders_arr[i].stop)
        {
            coders_arr[i].stop = 1;
            pthread_cond_signal(&coders_arr[i].wake_coder);
        }
        i++;
    }
    pthread_mutex_unlock(shared_mutex);
}
