#include "codexion.h"

void    remove_from_queue(coder_properties_struct *queue, coder_properties_struct remove_me)
{
    if (queue[0].id == remove_me.id)
    {
        if (queue[1] != NULL)
            queue = &queue[1];
    }
}
