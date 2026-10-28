#include "../../../codexion.h"

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
