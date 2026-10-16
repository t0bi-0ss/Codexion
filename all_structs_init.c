#include "codexion.h"

static coder_properties_struct *create_threads_properties_arr(long total_coders);

monitor_struct *init_all_structs(int argc, char **argv)
{
    monitor_struct *all_structs;

    (all_structs) = (monitor_struct *) malloc(sizeof(monitor_struct));
    if (!(all_structs))
        return (NULL);
    (all_structs)->all_args = get_and_validate_args(argc, argv);
    if (!(all_structs)->all_args)
        return (NULL);
    (all_structs)->signals = init_signals((all_structs)->all_args->number_of_coders);
    if (!(all_structs)->signals)
    {
        free((all_structs)->all_args);
        return (NULL);
    }
    (all_structs)->threads_properties_arr = create_threads_properties_arr((all_structs)->all_args->number_of_coders);
    if (!(all_structs)->threads_properties_arr)
    {
        free((all_structs)->all_args);
        free((all_structs)->signals);
        return (NULL);
    }
    
    return (all_structs);
}

static coder_properties_struct *create_threads_properties_arr(long total_coders)
{
    coder_properties_struct *threads_properties_arr;

    threads_properties_arr = (coder_properties_struct *) malloc(sizeof(coder_properties_struct) * total_coders);
    if (!threads_properties_arr)
        return (NULL);
    
    return (threads_properties_arr);
}
