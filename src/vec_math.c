/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:29:54 by asadanow          #+#    #+#             */
/*   Updated: 2023/05/30 14:29:55 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	create_vec(double x, double y, double z)
{
	t_vec	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

double	get_len_vec(t_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec	addition(t_vec vec1, t_vec vec2)
{
	return (create_vec(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z));
}

t_vec	subtraction(t_vec vec1, t_vec vec2)
{
	return (create_vec(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z));
}

t_vec	multiplication(t_vec vec, double num)
{
	return (create_vec(vec.x * num, vec.y * num, vec.z * num));
}
