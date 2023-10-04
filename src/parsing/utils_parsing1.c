/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:33:10 by asadanow          #+#    #+#             */
/*   Updated: 2023/06/02 10:33:10 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_atod_2(char *str, int i, double ans)
{
	double	div;

	div = 0.1;
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		ans = ans + (double)(str[i] - '0') *div;
		i++;
		div /= 10.0;
	}
	if (str[i] != '\0')
		return (0);
	return (ans);
}

double	ft_atod(char *str)
{
	int		i;
	double	sign;
	double	ans;

	i = 0;
	sign = 1;
	ans = 0;
	if (str[i] == '-')
	{
		sign = -1.0;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && str[i] != '\0')
	{
		ans = ans * 10 + (double)(str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		ans = ft_atod_2(str, i + 1, ans);
	else if (str[i] != '\0' || str[0] == '\0')
		return (0);
	return (ans * sign);
}

int	is_valid_double(char *str)
{
	int	i;
	int	dot_count;
	int	digit_count;

	i = 0;
	dot_count = 0;
	digit_count = 0;
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		digit_count++;
		i++;
	}
	if (str[i] == '.')
	{
		dot_count++;
		while (ft_isdigit(str[++i]))
			digit_count++;
	}
	if (digit_count > 0 && dot_count <= 1 && str[i] == '\0')
		return (1);
	return (0);
}

int	is_spaces(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\r' || str[0] == '\n')
		if (!str[1] || (str[1] == '\n' && !str[2]))
			return (1);
	while (str[i])
		if (str[i++] != ' ' )
			return (0);
	return (1);
}
