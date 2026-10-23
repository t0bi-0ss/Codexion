#include "../../codexion.h"

void    *thread_coder(void *properties)
{
    coder_properties_struct *start_values;

    start_values = (coder_properties_struct *) properties;
    while (start_values->times_compiled < start_values->config->compiles_required)
    {
        make_requests(start_values);
    }
}
