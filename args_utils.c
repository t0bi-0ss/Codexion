#include "codexion.h"
#include <string.h>

static int get_args(config_struct *all_args, char **argv)
{
    if (strncmp("fifo", argv[8], 5) == 0)
        all_args->scheduler = 1;
    else if (strncmp("edf", argv[8], 4) == 0)
        all_args->scheduler = 2;
	else
    {
		fprintf(2, "Args error: 'scheduler' wrong input");
		return (1);
    }
    all_args->number_of_coders = argv[1];
    all_args->time_to_burnout = argv[2];
    all_args->time_to_compile = argv[3];
    all_args->time_to_debug = argv[4];
    all_args->time_to_refactor = argv[5];
    all_args->number_of_compiles_required = argv[6];
    all_args->dongle_cooldown = argv[7];
    
    return (0);
}

config_struct *get_and_validate_args(int argc, char **argv)
{
    config_struct *all_args;

    all_args = (config_struct *) malloc(sizeof(config_struct));
    if (argc < 9)
    {
        printf("Args error: insufficient arguments\n");
        return (NULL);
    }
	if (get_args(all_args, argv))
		return (NULL);

    return (all_args);
}
