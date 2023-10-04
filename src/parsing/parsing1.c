/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 10:32:50 by asadanow          #+#    #+#             */
/*   Updated: 2023/06/02 10:32:57 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	set_camera_2(t_camera camera, double aspect_r)
{
	double	vfov;

	camera.fov *= 0.01745329;
	camera.aspect_ratio = aspect_r;
	vfov = 2.0 * atan(tan(camera.fov / 2.0) * camera.aspect_ratio);
	camera.screen_h = 2.0 * tan(vfov / 2.0);
	camera.screen_w = camera.aspect_ratio * camera.screen_h;
	camera.w = unit(multiplication(camera.orientation, -1));
	camera.u = unit(cross_product(create_vec(0, 1, 0), camera.w));
	if (fabs(camera.orientation.y) == 1)
		camera.u = unit(cross_product(create_vec(0, 0, 1), camera.w));
	camera.v = cross_product(camera.w, camera.u);
	camera.horizontal = multiplication(camera.u, camera.screen_w);
	camera.vertical = multiplication(camera.v, camera.screen_h);
	camera.ll_corner = subtraction(subtraction(subtraction(camera.pos,
					multiplication(camera.horizontal, 0.5)),
				multiplication(camera.vertical, 0.5)), camera.w);
	return (camera);
}

t_scene	set_camera(t_scene scene, char **data, int fd)
{
	scene.camera.pos = fill_vec(data, data[1], scene, fd);
	scene.camera.orientation = fill_vec(data, data[2], scene, fd);
	if (!check_unit(scene.camera.orientation))
		error_parsing(scene, data, fd, ERR_PARSING);
	scene.camera.fov = (double)ft_atoi(data[3]);
	if (scene.camera.fov <= 0 || scene.camera.fov > 180)
		error_parsing(scene, data, fd, ERR_PARSING);
	scene.count_cla[0]++;
	return (scene);
}

t_scene	parse_type(t_scene scene, char **data, int fd)
{
	if (check_type(data, "A", 3))
		scene = set_ambient_light(scene, data, fd);
	else if (check_type(data, "C", 4))
		scene = set_camera(scene, data, fd);
	else if (check_type(data, "L", 3))
		scene = set_light(scene, data, fd);
	else if (check_type(data, "sp", 4))
		scene = set_sphere(scene, data, fd);
	else if (check_type(data, "pl", 4))
		scene = set_plane(scene, data, fd);
	else if (check_type(data, "cy", 6))
		scene = set_cylinder(scene, data, fd);
	else
		error_parsing(scene, data, fd, ERR_PARSING);
	return (scene);
}

t_scene	parse(int fd)
{
	t_scene	scene;
	char	*line;
	char	**data;

	data = NULL;
	scene = init_scene();
	line = get_next_line(fd);
	while (line)
	{
		if (!is_spaces(line))
		{
			data = ft_split(line, ' ');
			free(line);
			if (!data)
				error_parsing(scene, NULL, fd, ERR_MALLOC);
			scene = parse_type(scene, data, fd);
			free_tab(data);
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	return (scene);
}

t_scene	get_scene(char *file, double aspect_ratio)
{
	int			fd;
	int			len;
	t_scene		scene;

	len = ft_strlen(file);
	if (!(file[len - 1] == 't' && file[len - 2] == 'r' && file[len - 3] == '.'))
		error_exit(NULL, ERR_NAME);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit(NULL, strerror(errno));
	scene = parse(fd);
	if (scene.count_cla[0] != 1 || scene.count_cla[1] != 1
		|| scene.count_cla[2] != 1)
		error_parsing(scene, NULL, fd, ERR_CLA);
	scene.camera = set_camera_2(scene.camera, aspect_ratio);
	if (close(fd) < 0)
		error_exit(NULL, strerror(errno));
	return (scene);
}
