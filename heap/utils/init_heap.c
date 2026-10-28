# include "../../codexion.h"

static int  select_func(heap *initiated_heap, Scheduler scheduler_config);

heap    *init_heap(config_struct *loaded_config)
{
    int coders_num;
    heap    *initiated_heap;

    initiated_heap = (heap *) malloc(sizeof(heap));
    if (!initiated_heap)
        return (NULL);
    coders_num = loaded_config->number_of_coders;
    initiated_heap->capacity = coders_num;
    initiated_heap->size = 0;
    initiated_heap->requests = (heap_request *) malloc(sizeof(heap_request) * coders_num + 1);
    if (!initiated_heap->requests)
        return (free(initiated_heap), NULL);
    if (select_func(initiated_heap, loaded_config->scheduler_config))
    {
        free(initiated_heap->requests);
        free(initiated_heap);
        return (NULL);
    }
    return (initiated_heap);
}

static int  select_func(heap *initiated_heap, Scheduler scheduler_config)
{
    if (scheduler_config == FIFO)
        initiated_heap->cmp_f = &cmp_timeof_request;
    else if (scheduler_config == EDF)
        initiated_heap->cmp_f = &cmp_burnout;
    else
        return (1);
    return (0);
}
