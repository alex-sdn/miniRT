/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:33:14 by asadanow          #+#    #+#             */
/*   Updated: 2023/06/02 10:33:15 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_type(char **data, char *type, int nb_elements)
{
	int	tab_size;

	tab_size = ft_tab_size(data);
	if (!ft_strncmp(data[0], type, ft_strlen(type))
		&& ft_strlen(data[0]) == ft_strlen(type))
		if (tab_size == nb_elements || (tab_size == nb_elements + 1
				&& (ft_strncmp(data[tab_size - 1], "\r\n", 2) == 0
					|| ft_strncmp(data[tab_size - 1], "\n", 1) == 0)))
			return (1);
	return (0);
}

int	is_valid_rgb(char **tab)
{
	int	i;
	int	j;
	int	nbr;

	i = 0;
	if (ft_tab_size(tab) != 3)
		return (0);
	while (i < 3)
	{
		j = -1;
		while (tab[i][++j])
			if (!ft_isdigit(tab[i][j])
				&& !(tab[i][j] == '\r' || tab[i][j] == '\n'))
				return (0);
		nbr = ft_atoi(tab[i]);
		if (nbr < 0 || nbr > 255)
			return (0);
		i++;
	}
	return (1);
}

t_vec	fill_color(char **data, char *str, t_scene scene, int fd)
{
	char	**tab;
	t_vec	vec;

	tab = ft_split(str, ',');
	if (!tab)
		error_parsing(scene, data, fd, ERR_MALLOC);
	if (!is_valid_rgb(tab))
	{
		free_tab(tab);
		error_parsing(scene, data, fd, "fill_color");
	}
	vec = create_vec(ft_atoi(tab[0]), ft_atoi(tab[1]), ft_atoi(tab[2]));
	free_tab(tab);
	return (multiplication(vec, 1.0 / 255.0));
}

int	is_valid_vec(char **tab)
{
	if (ft_tab_size(tab) != 3)
		return (0);
	if (!is_valid_double(tab[0]) || !is_valid_double(tab[1])
		|| !is_valid_double(tab[2]))
		return (0);
	return (1);
}

t_vec	fill_vec(char **data, char *str, t_scene scene, int fd)
{
	char	**tab;
	t_vec	vec;

	tab = ft_split(str, ',');
	if (!tab)
		error_parsing(scene, data, fd, ERR_MALLOC);
	if (!is_valid_vec(tab))
	{
		free_tab(tab);
		error_parsing(scene, data, fd, ERR_PARSING);
	}
	vec = create_vec(ft_atod(tab[0]), ft_atod(tab[1]), ft_atod(tab[2]));
	free_tab(tab);
	return (vec);
}
