/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:30:08 by asadanow          #+#    #+#             */
/*   Updated: 2023/05/30 14:30:09 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	ray_color(t_ray ray, t_scene scene)
{
	t_hit	hit;
	t_vec	color_ambnt;
	t_vec	color_spot;
	t_vec	light_dir;
	double	light_int;

	hit = check_hits(ray, scene);
	if (hit.t < 0.0)
		return (create_vec(0, 0, 0));
	light_dir = unit(subtraction(scene.light.pos, hit.poi));
	light_int = dot_product(hit.normal, light_dir);
	if (light_int < 0.0 || check_shadow(hit.poi, light_dir, scene))
		color_spot = create_vec(0.0, 0.0, 0.0);
	else
		color_spot = get_color_spot(hit.color, scene.light.brightness,
				light_int);
	color_ambnt = get_color_ambnt(scene.ambient, hit.color);
	return (sum_lights(addition(color_spot, color_ambnt)));
}

t_ray	get_ray(t_camera cam, double u, double v)
{
	t_ray	ray;

	ray.origin = cam.pos;
	ray.dir = unit(subtraction(addition(addition(cam.ll_corner,
						multiplication(cam.horizontal, u)),
					multiplication(cam.vertical, v)), ray.origin));
	return (ray);
}

void	color_img(t_data *img, t_vars *vars)
{
	int		win_xy[2];
	t_ray	ray;
	t_vec	color;

	win_xy[0] = -1;
	win_xy[1] = -1;
	while (++win_xy[1] < vars->win_wh[1])
	{
		while (++win_xy[0] < vars->win_wh[0])
		{
			ray = get_ray(vars->scene.camera,
					(double)win_xy[0] / (double)(vars->win_wh[0] - 1),
					(double)win_xy[1] / (double)(vars->win_wh[1] - 1));
			color = ray_color(ray, vars->scene);
			my_mlx_pixel_put(img, win_xy[0], vars->win_wh[1] - win_xy[1],
				create_trgb(0, color.x, color.y, color.z));
		}
		win_xy[0] = -1;
	}
}

void	create_img(t_vars *vars)
{
	t_data	img;

	img.img = mlx_new_image(vars->mlx_ptr, vars->win_wh[0], vars->win_wh[1]);
	if (!img.img)
		win_close(vars, 1);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	color_img(&img, vars);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, img.img, 0, 0);
	mlx_destroy_image(vars->mlx_ptr, img.img);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (ac != 2)
		error_exit(NULL, ERR_ARGC);
	vars.win_wh[0] = 1200;
	vars.win_wh[1] = 900;
	vars.scene = get_scene(av[1],
			(double)vars.win_wh[0] / (double)vars.win_wh[1]);
	vars.mlx_ptr = mlx_init();
	if (!vars.mlx_ptr)
		error_exit(NULL, ERR_MLX);
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, vars.win_wh[0],
			vars.win_wh[1], "miniRT");
	if (!vars.win_ptr)
		error_exit(vars.mlx_ptr, ERR_MLX);
	mlx_key_hook(vars.win_ptr, key_hook, &vars);
	mlx_hook(vars.win_ptr, 17, 0, &win_close, &vars);
	create_img(&vars);
	mlx_loop(vars.mlx_ptr);
	return (0);
}
