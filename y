char	*ft_calc_para(char *line, t_file *file)
{
	char	*code;
	char	*new;
	int		i;
	int		bol;
	int		j;
	int		p;

	i = 0;
	bol = 0;
	p = 0;
	code = ft_strdup("\0");
	while (line[i] != '\0')
	{
		p = 0;
		while (line[i] != '\0' && (line[i] == 'r' || line[i] == '%'))
			i++;
		if (line[i] == ':')
			p = 1;
		if (line[i] == 'r' || line[i] == '%')
			i++;
		j = i;
		while (line[i] != '\0' && line[i] != ',')
			i++;
		new = ft_strsub(line, j, i - j);
		if (new != NULL)
		{
			if (new[j] == '%' || ft_strcmp(file->inst, "live") == 0)
			{
				if (new[i] == '\0')
					code = ft_strcat(code, ft_x_octet(file, new, 1, p));
				else
					code = ft_strcat(code, ft_x_octet(file, new, 0, p));
				bol++;
			}
			else
			{
				if (new[i] == '\0')
					code = ft_strcat(code, ft_two_octet(new, 1, p));
				else
					code = ft_strcat(code, ft_two_octet(new, 0, p));
				bol++;
			}
		}
		if (line[i] == ',')
			i++;
	}
	return (code);
}
