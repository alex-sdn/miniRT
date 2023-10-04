/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:30:15 by asadanow          #+#    #+#             */
/*   Updated: 2023/05/30 14:30:17 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	unit(t_vec vec)
{
	double	len;

	len = get_len_vec(vec);
	return (create_vec(vec.x / len, vec.y / len, vec.z / len));
}

double	dot_product(t_vec vec1, t_vec vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec	cross_product(t_vec vec1, t_vec vec2)
{
	t_vec	new_vec;

	new_vec.x = vec1.y * vec2.z - vec1.z * vec2.y;
	new_vec.y = vec1.z * vec2.x - vec1.x * vec2.z;
	new_vec.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (new_vec);
}

t_vec	matrix_multiplication(t_vec og, t_vec matrix[3])
{
	t_vec	new;

	new.x = matrix[0].x * og.x + matrix[0].y * og.y + matrix[0].z * og.z;
	new.y = matrix[1].x * og.x + matrix[1].y * og.y + matrix[1].z * og.z;
	new.z = matrix[2].x * og.x + matrix[2].y * og.y + matrix[2].z * og.z;
	return (new);
}

t_ray	relative_ray(t_ray ray, t_vec real_axis)
{
	t_vec	matrix[3];
	t_vec	rot_axis;
	double	cos_th;
	double	sin_th;

	rot_axis = unit(cross_product(real_axis, create_vec(0.0, 0.0, 1.0)));
	cos_th = dot_product(real_axis, create_vec(0.0, 0.0, 1.0));
	sin_th = sin(acos(cos_th));
	matrix[0].x = rot_axis.x * rot_axis.x * (1 - cos_th) + cos_th;
	matrix[0].y = rot_axis.x * rot_axis.y * (1 - cos_th) - rot_axis.z * sin_th;
	matrix[0].z = rot_axis.x * rot_axis.z * (1 - cos_th) + rot_axis.y * sin_th;
	matrix[1].x = rot_axis.y * rot_axis.x * (1 - cos_th) + rot_axis.z * sin_th;
	matrix[1].y = rot_axis.y * rot_axis.y * (1 - cos_th) + cos_th;
	matrix[1].z = rot_axis.y * rot_axis.z * (1 - cos_th) - rot_axis.x * sin_th;
	matrix[2].x = rot_axis.z * rot_axis.x * (1 - cos_th) - rot_axis.y * sin_th;
	matrix[2].y = rot_axis.z * rot_axis.y * (1 - cos_th) + rot_axis.x * sin_th;
	matrix[2].z = rot_axis.z * rot_axis.z * (1 - cos_th) + cos_th;
	ray.origin = matrix_multiplication(ray.origin, matrix);
	ray.dir = unit(matrix_multiplication(ray.dir, matrix));
	return (ray);
}
