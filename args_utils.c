#include "codexion.h"

static int get_args(config_struct *config_p, char **argv);

int get_and_validate_args(int argc, char **argv, monitor_struct *monitor_p)
{
    if (argc < 9)
    {
        printf("Args error: insufficient arguments\n");
        return (1);
    }
	if (get_args(&monitor_p->loaded_config, argv))
        return (2);
    return (0);
}

static int get_args(config_struct *config_p, char **argv)
{
    if (strncmp("fifo", argv[8], 5) == 0)
        config_p->scheduler_config = FIFO;
    else if (strncmp("edf", argv[8], 4) == 0)
        config_p->scheduler_config = EDF;
    else
    {
        fprintf(stderr, "Args error: 'scheduler' wrong input");
        return (1);
    }
    config_p->number_of_coders = atoi(argv[1]);
    config_p->time_to_burnout = atoi(argv[2]);
    config_p->time_to_compile = atoi(argv[3]);
    config_p->time_to_debug = atoi(argv[4]);
    config_p->time_to_refactor = atoi(argv[5]);
    config_p->dongle_cooldown = atoi(argv[6]);
    config_p->compiles_required = atoi(argv[7]);
    
    return (0);
}
