#include "codexion.h"
#include <string.h>

static int get_args(all_args *args_struct, char **argv)
{
    if (strncmp("fifo", argv[8], 5) == 0)
        args_struct->scheduler = 1;
    else if (strncmp("edf", argv[8], 4) == 0)
        args_struct->scheduler = 2;
	else
		fprintf(2, "Args error: 'scheduler' wrong input");
		return (1);
    args_struct->number_of_coders = argv[1];
    args_struct->time_to_burnout = argv[2];
    args_struct->time_to_compile = argv[3];
    args_struct->time_to_debug = argv[4];
    args_struct->time_to_refactor = argv[5];
    args_struct->number_of_compiles_required = argv[6];
    args_struct->dongle_cooldown = argv[7];
}

int validate_args(int argc, char **argv, all_args *args_struct)
{
    if (argc < 9)
    {
        printf("Args error: insufficient arguments\n");
        return (1);
    }
	if (get_args(args_struct, argv))
		return (2);

    return (0);
}
