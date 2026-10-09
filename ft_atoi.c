static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(unsigned char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_issign(unsigned char c)
{
	return (c == '-' || c == '+');
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (ft_issign(*nptr))
	{
		if (ft_issign(*(nptr + 1)))
			return (0);
		else if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
		result = result * 10 + (*nptr++ - '0');
	return (result * sign);
}
