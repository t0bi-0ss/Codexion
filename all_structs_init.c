#include "codexion.h"

static thrds_properties_struct *create_threads_properties_arr(long total_coders);

all_structs_handler *init_all_structs(int argc, char **argv)
{
    all_structs_handler *all_structs;

    (all_structs) = (all_structs_handler *) malloc(sizeof(all_structs_handler));
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

static thrds_properties_struct *create_threads_properties_arr(long total_coders)
{
    thrds_properties_struct *threads_properties_arr;

    threads_properties_arr = (thrds_properties_struct *) malloc(sizeof(thrds_properties_struct) * total_coders);
    if (!threads_properties_arr)
        return (NULL);
    
    return (threads_properties_arr);
}
