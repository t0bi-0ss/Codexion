#include "../../../codexion.h"

int check_compilations_num(heap_request *request, config_struct *loaded_config)
{
    return (request->coder->times_compiled == loaded_config->compiles_required);
}

// Returns 1 if burnout is detected
int burnout_check(struct timespec burnout_time)
{
    struct timespec now;

    now = get_timestamp();
    if (burnout_time.tv_sec < now.tv_sec)
        return (1);
    if (burnout_time.tv_sec == now.tv_sec && burnout_time.tv_nsec < now.tv_nsec)
        return (1);
    return (0);
}

int cooldown_check(struct timespec cooldown_time)
{
    struct timespec now;

    now = get_timestamp();
    if (cooldown_time.tv_sec < now.tv_sec)
        return (1);
    if (cooldown_time.tv_sec == now.tv_sec)
        return (cooldown_time.tv_nsec <= now.tv_nsec);
    return (0);
}
