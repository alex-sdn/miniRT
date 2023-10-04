/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:33:01 by asadanow          #+#    #+#             */
/*   Updated: 2023/06/02 10:33:03 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	set_light(t_scene scene, char **data, int fd)
{
	char	*tmp;

	scene.light.pos = fill_vec(data, data[1], scene, fd);
	tmp = ft_strtrim(data[2], "\r\n");
	if (!tmp)
		error_parsing(scene, data, fd, ERR_PARSING);
	scene.light.brightness = ft_atod(tmp);
	if (scene.light.brightness < 0.0 || scene.light.brightness > 1.0
		|| !is_valid_double(tmp))
	{
		free(tmp);
		error_parsing(scene, data, fd, ERR_PARSING);
	}
	free(tmp);
	scene.count_cla[1]++;
	return (scene);
}

t_scene	set_ambient_light(t_scene scene, char **data, int fd)
{
	scene.ambient.brightness = ft_atod(data[1]);
	if (scene.ambient.brightness < 0.0 || scene.ambient.brightness > 1.0
		|| !is_valid_double(data[1]))
		error_parsing(scene, data, fd, ERR_PARSING);
	scene.ambient.color = fill_color(data, data[2], scene, fd);
	scene.count_cla[2]++;
	return (scene);
}

t_scene	set_sphere(t_scene scene, char **data, int fd)
{
	t_sphere	*sphere;
	t_list		*new;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_parsing(scene, data, fd, ERR_MALLOC);
	new = init_list(sphere);
	if (!new)
	{
		free(sphere);
		error_parsing(scene, data, fd, ERR_MALLOC);
	}
	ft_lstadd_back(&(scene.spheres), new);
	sphere->center = fill_vec(data, data[1], scene, fd);
	sphere->r = ft_atod(data[2]) / 2.0;
	if (sphere->r <= 0)
		error_parsing(scene, data, fd, ERR_PARSING);
	sphere->color = fill_color(data, data[3], scene, fd);
	return (scene);
}

t_scene	set_plane(t_scene scene, char **data, int fd)
{
	t_plane	*plane;
	t_list	*new;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		error_parsing(scene, data, fd, ERR_MALLOC);
	new = init_list(plane);
	if (!new)
	{
		free(plane);
		error_parsing(scene, data, fd, ERR_MALLOC);
	}
	ft_lstadd_back(&(scene.planes), new);
	plane->coord = fill_vec(data, data[1], scene, fd);
	plane->normal = fill_vec(data, data[2], scene, fd);
	if (!check_unit(plane->normal))
		error_parsing(scene, data, fd, ERR_PARSING);
	plane->color = fill_color(data, data[3], scene, fd);
	return (scene);
}

t_scene	set_cylinder(t_scene scene, char **data, int fd)
{
	t_cylinder	*cylinder;
	t_list		*new;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		error_parsing(scene, data, fd, ERR_MALLOC);
	new = init_list(cylinder);
	if (!new)
	{
		free(cylinder);
		error_parsing(scene, data, fd, ERR_MALLOC);
	}
	ft_lstadd_back(&(scene.cylinders), new);
	cylinder->center = fill_vec(data, data[1], scene, fd);
	cylinder->axis = fill_vec(data, data[2], scene, fd);
	if (!check_unit(cylinder->axis))
		error_parsing(scene, data, fd, ERR_PARSING);
	cylinder->r = ft_atod(data[3]) / 2.0;
	cylinder->h = ft_atod(data[4]);
	if (cylinder->r <= 0 || cylinder->h <= 0)
		error_parsing(scene, data, fd, ERR_PARSING);
	cylinder->color = fill_color(data, data[5], scene, fd);
	return (scene);
}
