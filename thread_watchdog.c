void *thread_watchdog(void *id)
{
    while (all_finished < 10)
    {
        pthread_mutex_lock(&quantum_mutex);
        while (can_compile)
            if (pthread_cond_wait(&watchdog_cond, &quantum_mutex) != 0)
            {
                printf("Watchdog error: cond wait error");
                terminate_all++;
            }
        if (!can_compile)
            can_compile++;
        pthread_mutex_unlock(&quantum_mutex);
        pthread_cond_broadcast(&coders_cond);
    }
    printf("\nAll coders have compiled 10 times succesfully!\n");
    return (NULL);
}