#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COMPILE_TIMES 10
#define CODERS_NUM 2

pthread_mutex_t dongles_mutex[CODERS_NUM];
pthread_cond_t dongles_cond[CODERS_NUM];
int dongle_in_use[CODERS_NUM] = {0};
// pthread_mutex_t stdout_mutex;
// pthread_cond_t stdout_cond;


// void *compile(void *coder_id)
// {
//     int id = (int) coder_id;
//     int f_index = coder_id;
//     int s_index = 0;
//     int has_compiled = 0;
//     if (id == 0)
//         s_index = CODERS_NUM - 1;
//     else
//         s_index = id - 1;
// }
void *coder(void *coder_id)
{
    long id = (long) coder_id;
    long f_dongle = (long) coder_id;
    long s_dongle = 0;
    int has_compiled = 0;
    if (id == 0)
        s_dongle = CODERS_NUM - 1;
    else
        s_dongle = id - 1;
    while (has_compiled < COMPILE_TIMES)
    {
        pthread_mutex_lock(&dongles_mutex[f_dongle]);
        pthread_mutex_lock(&dongles_mutex[s_dongle]);
        while (dongle_in_use[s_dongle] || dongle_in_use[f_dongle])
        {
            printf("Coder n: %ld is waiting", id);
            pthread_cond_wait(&dongles_cond[f_dongle], &dongles_mutex[f_dongle]);
            pthread_cond_wait(&dongles_cond[s_dongle], &dongles_mutex[s_dongle]);
        }
        dongle_in_use[s_dongle] = 1;
        dongle_in_use[f_dongle] = 1;
        printf("Coder n: %ld has compiled effectively for the %d time\n", id, has_compiled + 1);
        has_compiled++;
        pthread_mutex_unlock(&dongles_mutex[f_dongle]);
        pthread_mutex_unlock(&dongles_mutex[s_dongle]);
        dongle_in_use[f_dongle] = 0;
        dongle_in_use[s_dongle] = 0;
        pthread_cond_signal(&dongles_cond[f_dongle]);
        pthread_cond_signal(&dongles_cond[s_dongle]);
        sleep(1);
        if (has_compiled == COMPILE_TIMES + 1)
            {
                pthread_mutex_unlock(&dongles_mutex[f_dongle]);
                pthread_mutex_unlock(&dongles_mutex[s_dongle]);
                pthread_exit(NULL);
            }
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t coders[CODERS_NUM];

    // for (int i = 0; i < CODERS_NUM; i++)
    // {
    //     pthread_mutex_init(&dongles_mutex[i], NULL);
    //     pthread_cond_init(&dongles_cond[i], NULL);
    //     pthread_create(&coders[i], NULL, coder, (void *) &i);
    // }
    long f_id = 0;
    long s_id = 1;
    pthread_mutex_init(&dongles_mutex[f_id], NULL);
    pthread_cond_init(&dongles_cond[f_id], NULL);
    pthread_mutex_init(&dongles_mutex[s_id], NULL);
    pthread_cond_init(&dongles_cond[s_id], NULL);
    pthread_create(&coders[f_id], NULL, coder, (void *) f_id);
    pthread_create(&coders[s_id], NULL, coder, (void *) s_id);
    for (int i = 0; i < CODERS_NUM; i++)
        pthread_join(coders[i], NULL);

    for (int i = 0; i < CODERS_NUM; i++)
    {
        pthread_mutex_destroy(&dongles_mutex[i]);
        pthread_cond_destroy(&dongles_cond[i]);
    }
    pthread_exit(NULL);
    
}