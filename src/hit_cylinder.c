/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:29:30 by asadanow          #+#    #+#             */
/*   Updated: 2023/05/30 14:29:31 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	cylinder_caps(t_ray ray, t_cylinder cylinder)
{
	double	t[2];
	double	r2;
	t_vec	poi;

	r2 = cylinder.r * cylinder.r;
	t[0] = (cylinder.h / 2.0 - ray.origin.z) / ray.dir.z;
	t[1] = ((cylinder.h / 2.0 * -1.0) - ray.origin.z) / ray.dir.z;
	poi = addition(ray.origin, multiplication(ray.dir, t[0]));
	if (t[0] > 0.00001 && (t[0] < t[1] || t[1] < 0.0)
		&& (poi.x * poi.x + poi.y * poi.y <= r2))
		return (-t[0]);
	poi = addition(ray.origin, multiplication(ray.dir, t[1]));
	if (t[1] > 0.00001 && (poi.x * poi.x + poi.y * poi.y <= r2))
		return (-t[1]);
	return (0.0);
}

double	cyl_distance_3(t_ray ray, double h2, double t[4], t_vec poi[2])
{
	if (!(poi[0].z > h2 || poi[0].z < -h2)
		&& (poi[1].z > h2 || poi[1].z < -h2) && t[0] < 0.0)
	{
		t[2] = (h2 - ray.origin.z) / ray.dir.z;
		t[3] = (-h2 - ray.origin.z) / ray.dir.z;
		if (t[2] > 0.00001 && (t[2] < t[3] || t[3] < 0.0))
			return (-t[2]);
		if (t[3] > 0.00001)
			return (-t[3]);
		return (0.0);
	}
	if (t[0] > 0.00001)
		return (t[0]);
	return (t[1]);
}

double	cyl_distance_2(t_ray ray, double h2, double t[4], t_vec poi[2])
{
	if ((poi[0].z > h2 && poi[1].z > h2) || (poi[0].z < -h2 && poi[1].z < -h2))
		return (0.0);
	if ((poi[0].z > h2 || poi[0].z < -h2) && (poi[1].z > h2 || poi[1].z < -h2))
	{
		t[2] = (h2 - ray.origin.z) / ray.dir.z;
		t[3] = (-h2 - ray.origin.z) / ray.dir.z;
		if (t[2] > 0.00001 && (t[2] < t[3] || t[3] < 0.0))
			return (-t[2]);
		if (t[3] > 0.00001)
			return (-t[3]);
		return (0.0);
	}
	if ((poi[0].z > h2 || poi[0].z < -h2) && (poi[1].z < h2 && poi[1].z > -h2))
	{
		t[2] = (h2 - ray.origin.z) / ray.dir.z;
		t[3] = (-h2 - ray.origin.z) / ray.dir.z;
		if (t[2] > 0.00001 && (t[2] < t[3] || t[3] < 0.0))
			return (-t[2]);
		if (t[3] > 0.00001)
			return (-t[3]);
		if (t[1] > 0.00001)
			return (t[1]);
		return (0.0);
	}
	return (cyl_distance_3(ray, h2, t, poi));
}

double	cylinder_distance(t_ray ray, t_cylinder cylinder)
{
	double	abc[3];
	double	discriminant;
	double	t[4];
	t_vec	poi[2];

	ray.origin = subtraction(ray.origin, cylinder.center);
	if (!(cylinder.axis.x == 0.0 && cylinder.axis.y == 0.0
			&& cylinder.axis.z == 1.0))
		ray = relative_ray(ray, cylinder.axis);
	abc[0] = ray.dir.x * ray.dir.x + ray.dir.y * ray.dir.y;
	abc[1] = 2.0 * ((ray.origin.x) * ray.dir.x + (ray.origin.y) * ray.dir.y);
	abc[2] = (ray.origin.x) * (ray.origin.x)
		+ (ray.origin.y) * (ray.origin.y) - (cylinder.r * cylinder.r);
	discriminant = abc[1] * abc[1] - 4.0 * abc[0] * abc[2];
	if (discriminant < 0.0)
		return (cylinder_caps(ray, cylinder));
	t[0] = (-abc[1] - sqrt(discriminant)) / (2.0 * abc[0]);
	t[1] = (-abc[1] + sqrt(discriminant)) / (2.0 * abc[0]);
	if (t[0] < 0.00001 && t[1] < 0.00001)
		return (0.0);
	poi[0] = addition(ray.origin, multiplication(ray.dir, t[0]));
	poi[1] = addition(ray.origin, multiplication(ray.dir, t[1]));
	return (cyl_distance_2(ray, cylinder.h / 2.0, t, poi));
}

t_hit	hit_cylinder(t_ray ray, double lowest, t_cylinder cylinder)
{
	t_hit	hit;

	hit.t = cylinder_distance(ray, cylinder);
	if (hit.t == 0.0 || (lowest > 0.0 && fabs(hit.t) > lowest))
	{
		hit.t = -1.0;
		return (hit);
	}
	if (hit.t < 0.0)
	{
		hit.t *= -1;
		hit.poi = addition(ray.origin, multiplication(ray.dir, hit.t));
		hit.normal = cylinder.axis;
	}
	else
	{
		hit.poi = addition(ray.origin, multiplication(ray.dir, hit.t));
		hit.normal = unit(subtraction(hit.poi, cylinder.center));
		hit.normal = unit(subtraction(hit.normal, multiplication(cylinder.axis,
						dot_product(hit.normal, cylinder.axis))));
	}
	if (dot_product(hit.normal, unit(multiplication(ray.dir, -1.0))) < 0.0)
		hit.normal = multiplication(hit.normal, -1.0);
	hit.color = cylinder.color;
	return (hit);
}
