/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:29:25 by asadanow          #+#    #+#             */
/*   Updated: 2023/05/30 14:29:27 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_shadow_2(double t_light, t_ray ray, t_scene scene)
{
	double	t;

	while (scene.planes)
	{
		t = plane_distance(ray, *((t_plane *)scene.planes->content));
		if (t > 0.0 && t < t_light)
			return (1);
		scene.planes = scene.planes->next;
	}
	return (0);
}

int	check_shadow(t_vec poi, t_vec dir, t_scene scene)
{
	t_ray	ray;
	double	t_light;
	double	t;

	ray.origin = poi;
	ray.dir = dir;
	t_light = sqrt((scene.light.pos.x - poi.x) * (scene.light.pos.x - poi.x)
			+ (scene.light.pos.y - poi.y) * (scene.light.pos.y - poi.y)
			+ (scene.light.pos.z - poi.z) * (scene.light.pos.z - poi.z));
	while (scene.spheres)
	{
		t = sphere_distance(ray, *((t_sphere *)scene.spheres->content));
		if (t > 0.0 && t < t_light)
			return (1);
		scene.spheres = scene.spheres->next;
	}
	while (scene.cylinders)
	{
		t = cylinder_distance(ray, *((t_cylinder *)scene.cylinders->content));
		if (t != 0.0 && fabs(t) < t_light)
			return (1);
		scene.cylinders = scene.cylinders->next;
	}
	return (check_shadow_2(t_light, ray, scene));
}

t_hit	check_hits_2(t_hit hit, t_ray ray, t_scene scene)
{
	t_hit	new;

	while (scene.planes)
	{
		new = hit_plane(ray, hit.t, *((t_plane *)scene.planes->content));
		if (new.t > 0.0 && (new.t < hit.t || hit.t < 0.0))
			hit = new;
		scene.planes = scene.planes->next;
	}
	return (hit);
}

t_hit	check_hits(t_ray ray, t_scene scene)
{
	t_hit	hit;
	t_hit	new;

	hit.t = -1.0;
	while (scene.spheres)
	{
		new = hit_sphere(ray, hit.t, *((t_sphere *)scene.spheres->content));
		if (new.t > 0.0 && (new.t < hit.t || hit.t < 0.0))
			hit = new;
		scene.spheres = scene.spheres->next;
	}
	while (scene.cylinders)
	{
		new = hit_cylinder(ray, hit.t, *(t_cylinder *)scene.cylinders->content);
		if (new.t > 0.0 && (new.t < hit.t || hit.t < 0.0))
			hit = new;
		scene.cylinders = scene.cylinders->next;
	}
	return (check_hits_2(hit, ray, scene));
}
