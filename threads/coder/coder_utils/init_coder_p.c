#include "../../../codexion.h"

static void    set_dongles_index(coder_properties_struct *coder_p, config_struct *loaded_config);

void    init_coder_p(coder_properties_struct *coder_p, monitor_struct *monitor_p, int i)
{
    coder_p->id = i;
    coder_p->times_compiled = 0;
    coder_p->stop = 0;
    coder_p->has_permission = 0;
    pthread_cond_init(&coder_p->wake_coder, NULL);
    set_dongles_index(coder_p, &monitor_p->loaded_config);
    coder_p->last_compile = get_timestamp();
    update_time_to_burnout(monitor_p->loaded_config.time_to_burnout, &coder_p->to_burnout);
    coder_p->monitor_ptr = monitor_p;
}

static void    set_dongles_index(coder_properties_struct *coder_p, config_struct *loaded_config)
{
    coder_p->dongle_1_index = coder_p->id;
    if (coder_p->id == 0)
        coder_p->dongle_2_index = loaded_config->number_of_coders - 1;
    else
        coder_p->dongle_2_index = coder_p->id - 1;
}
