/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:33:26 by asadanow          #+#    #+#             */
/*   Updated: 2023/06/02 10:33:27 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_tab_size(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab[i]);
	free(tab);
}

t_list	*init_list(void *content)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_scene	init_scene(void)
{
	t_scene	scene;

	scene.spheres = NULL;
	scene.planes = NULL;
	scene.cylinders = NULL;
	scene.count_cla[0] = 0;
	scene.count_cla[1] = 0;
	scene.count_cla[2] = 0;
	return (scene);
}

void	error_parsing(t_scene scene, char **data, int fd, char *msg)
{
	char	*line;

	free_objects(scene);
	if (data)
		free_tab(data);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	error_exit(NULL, msg);
}
