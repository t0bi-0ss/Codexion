#include "codexion.h"

static int	ft_isspace(unsigned char c);
static int	ft_issign(unsigned char c);

int	overflow_check(const char *nptr)
{
	int	sign;
	long	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*nptr))
		nptr++;
    while (ft_issign(*nptr))
    {
        if (sign == 1 && *nptr == '-')
            sign = -1;
        nptr++;
    }
	while (*nptr >= '0' && *nptr <= '9')
		result = result * 10 + (*nptr++ - '0');
    if (result <= MIN_INT || result >= MAX_INT)
	{
        return (1);
	}
	return (0);
}

static int	ft_isspace(unsigned char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_issign(unsigned char c)
{
	return (c == '-' || c == '+');
}
