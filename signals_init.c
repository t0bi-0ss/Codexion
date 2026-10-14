#include "codexion.h"

static pthread_mutex_t *create_dongles_mutex_arr(long coders_num);

static pthread_cond_t *create_dongles_cond_arr(long coders_num);

static int init_mutexes_and_conds(signals_struct *signals, long coders_num);

static void set_to_zero(signals_struct *signals);

static void free_all(signals_struct **signals_ptr);

signals_struct *init_signals(long coders_num)
{
    signals_struct *signals;

    signals = (signals_struct *) malloc(sizeof(signals_struct));
    if (!signals)
        return (NULL);
    set_to_zero(signals);
    signals->dongles_mutex_arr = create_dongles_mutex_arr(coders_num);
    if (!signals->dongles_mutex_arr)
    {
        free(signals);
        return(NULL);
    }
    signals->dongles_cond_arr = create_dongles_cond_arr(coders_num);
    if (!signals->dongles_cond_arr)
    {
        free(signals);
        free(signals->dongles_mutex_arr);
        return (NULL);
    }
    if (init_mutexes_and_conds(signals, coders_num))
    {
        free_all(&signals);
        return (NULL);
    }
    return (signals);
}

static pthread_mutex_t *create_dongles_mutex_arr(long coders_num)
{
    pthread_mutex_t *dongles_mutex_arr;

    dongles_mutex_arr = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t) * (coders_num));
    if (!dongles_mutex_arr)
        return (NULL);
    return (dongles_mutex_arr);
}

static pthread_cond_t *create_dongles_cond_arr(long coders_num)
{
    pthread_cond_t *dongles_cond_arr;

    dongles_cond_arr = (pthread_cond_t *) malloc(sizeof(pthread_cond_t) * coders_num);
    if (!dongles_cond_arr)
        return (NULL);
    return (dongles_cond_arr);
}

static int init_mutexes_and_conds(signals_struct *signals, long coders_num)
{
    if (pthread_mutex_init(&signals->quantum_mutex, NULL))
        return (1);
    if (pthread_cond_init(&signals->watchdog_cond, NULL))
        return (2);
    if (pthread_cond_init(&signals->coders_general_cond, NULL))
        return (3);
    while(coders_num - 1 >= 0)
    {
        if (pthread_mutex_init(&signals->dongles_mutex_arr[coders_num - 1], NULL))
            return (4);
        if (pthread_cond_init(&signals->dongles_cond_arr[coders_num - 1], NULL))
            return (5);
        coders_num--;
    }

    return (0);
}

static void set_to_zero(signals_struct *signals)
{
    signals->quantum_available = 0;
    signals->all_finished = 0;
    signals->terminate_all = 0;
}

static void free_all(signals_struct **signals_ptr)
{
    free((*signals_ptr)->dongles_mutex_arr);
    (*signals_ptr)->dongles_mutex_arr = NULL;
    free((*signals_ptr)->dongles_cond_arr);
    (*signals_ptr)->dongles_cond_arr = NULL;
    free(*signals_ptr);
    *signals_ptr = NULL;
}
