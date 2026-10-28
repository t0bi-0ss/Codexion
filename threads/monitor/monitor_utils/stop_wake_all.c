#include "../../../codexion.h"

void    stop_wake_all(coder_properties_struct *coders_arr, config_struct *loaded_config)
{
    int i;

    i = 1;
    while (i < loaded_config->number_of_coders)
    {
        coders_arr[i].stop = 1;
        pthread_cond_signal(&coders_arr[i].wake_coder);
    }
}
