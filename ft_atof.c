static double	num_print(const char *str, int i, int minusnum)
{
	double	num;
	double	j;

	num = 0.0;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		num = num * 10 + (*(str + i) - 48);
		i++;
	}
	if (*(str + i) == '.')
	{
		i++;
		j = 0.1;
		while (*(str + i) >= '0' && *(str + i) <= '9')
		{
			num = num + (*(str + i) - 48) * j;
			i++;
			j /= 10.0;
		}
	}
	if ((minusnum % 2) == 0)
		return (num);
	else
		return (0 - num);
}

double	ft_atof(const char *str)
{
	int	i;
	int	minusnum;

	i = 0;
	while (*(str + i) == ' ' || *(str + i) == '\t' || *(str + i) == '\n'
		|| *(str + i) == '\v' || *(str + i) == '\f' || *(str + i) == '\r')
		i++;
	minusnum = 0;
	if ((*(str + i) == '-') || (*(str + i) == '+'))
	{
		if (*(str + i) == '-')
			minusnum = minusnum + 1;
		i++;
	}
	if (*(str + i) >= '0' && *(str + i) <= '9')
		return (num_print(str, i, minusnum));
	else
		return (0.0);
}
