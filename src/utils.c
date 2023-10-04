/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:48:10 by asadanow          #+#    #+#             */
/*   Updated: 2023/05/30 14:48:12 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error_exit(void *ptr, char *msg)
{
	if (ptr)
		free(ptr);
	printf("Error\n%s\n", msg);
	exit(EXIT_FAILURE);
}

void	free_objects(t_scene scene)
{
	ft_lstclear(&scene.spheres, &ft_del);
	ft_lstclear(&scene.cylinders, &ft_del);
	ft_lstclear(&scene.planes, &ft_del);
}

void	ft_del(void *content)
{
	if (content)
		free(content);
}

double	clamp_min(double t)
{
	if (t < 0.00001)
		return (-1.0);
	return (t);
}

int	check_unit(t_vec vec)
{
	double	len;

	len = get_len_vec(vec);
	if (len < 0.99 || len > 1.01)
		return (0);
	return (1);
}
