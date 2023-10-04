/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:29:36 by asadanow          #+#    #+#             */
/*   Updated: 2023/05/30 14:29:37 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	sphere_distance(t_ray ray, t_sphere sphere)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;

	ray.origin = subtraction(ray.origin, sphere.center);
	a = 1.0;
	b = dot_product(ray.origin, ray.dir);
	c = dot_product(ray.origin, ray.origin) - (sphere.r * sphere.r);
	discriminant = b * b - a * c;
	if (discriminant < 0.0)
		return (-1.0);
	t = (-b - sqrt(discriminant)) / a;
	if (t > 0.00001)
		return (t);
	return (clamp_min((-b + sqrt(discriminant)) / a));
}

t_hit	hit_sphere(t_ray ray, double lowest, t_sphere sphere)
{
	t_hit	hit;

	hit.t = sphere_distance(ray, sphere);
	if (hit.t < 0.0 || (lowest > 0.0 && hit.t > lowest))
		return (hit);
	hit.poi = addition(ray.origin, multiplication(ray.dir, hit.t));
	hit.normal = unit(subtraction(hit.poi, sphere.center));
	if (dot_product(hit.normal, unit(multiplication(ray.dir, -1.0))) < 0.0)
		hit.normal = multiplication(hit.normal, -1.0);
	hit.color = sphere.color;
	return (hit);
}
