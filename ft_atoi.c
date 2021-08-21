static int	num_print(const char *str, int i, int minusnum)
{
	int	num;

	num = 0;
	while (*(str + i) >= '0' && *(str + i) <= '9')
	{
		num = num * 10 + (*(str + i) - 48);
		i++;
	}
	if ((minusnum % 2) == 0)
		return (num);
	else
		return (0 - num);
}

int	ft_atoi(const char *str)
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
		return (0);
}
