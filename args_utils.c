#include "custom_structs.c"

void get_args(all_args *args_struct, char **argv)
{
    if (ft_strncmp("fifo", argv[7], 5) == 0)
        args_struct->scheduler = 1;
    else if (ft_strncmp("edf", argv[7], 4) == 0)
        args_struct->scheduler = 2;
    args_struct->number_of_coders = argv[0];
    args_struct->time_to_burnout = argv[1];
    args_struct->time_to_compile = argv[2];
    args_struct->time_to_debug = argv[3];
    args_struct->time_to_refactor = argv[4];
    args_struct->number_of_compiles_required = argv[5];
    args_struct->dongle_cooldown = argv[6];
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	unsigned char	*u_s1;
	unsigned char	*u_s2;

	u_s1 = (unsigned char *)s1;
	u_s2 = (unsigned char *)s2;
	index = 0;
	if (!n)
		return (0);
	while (index < n && (u_s1[index] || u_s2[index]))
	{
		if (u_s1[index] != u_s2[index])
			return (u_s1[index] - u_s2[index]);
		index++;
	}
	return (0);
}