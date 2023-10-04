/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:30:02 by asadanow          #+#    #+#             */
/*   Updated: 2023/05/30 14:30:02 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	plane_distance(t_ray ray, t_plane plane)
{
	double	t;

	t = (1.0 / dot_product(ray.dir, plane.normal))
		* (dot_product(plane.coord, plane.normal)
			- dot_product(ray.origin, plane.normal));
	return (clamp_min(t));
}

t_hit	hit_plane(t_ray ray, double lowest, t_plane plane)
{
	t_hit	hit;

	hit.t = plane_distance(ray, plane);
	if (hit.t < 0.0 || (lowest > 0.0 && hit.t > lowest))
		return (hit);
	hit.poi = addition(ray.origin, multiplication(ray.dir, hit.t));
	hit.normal = plane.normal;
	if (dot_product(hit.normal, unit(multiplication(ray.dir, -1.0))) < 0.0)
		hit.normal = multiplication(hit.normal, -1.0);
	hit.color = plane.color;
	return (hit);
}
