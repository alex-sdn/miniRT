/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:29:44 by asadanow          #+#    #+#             */
/*   Updated: 2023/05/30 14:29:45 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	get_color_ambnt(t_ambient ambient, t_vec object_color)
{
	t_vec	color_ambnt;

	color_ambnt.x = ambient.color.x * ambient.brightness * object_color.x;
	color_ambnt.y = ambient.color.y * ambient.brightness * object_color.y;
	color_ambnt.z = ambient.color.z * ambient.brightness * object_color.z;
	return (color_ambnt);
}

t_vec	get_color_spot(t_vec color, double brightness, double light_int)
{
	t_vec	color_spot;

	color_spot.x = color.x * brightness * light_int;
	color_spot.y = color.y * brightness * light_int;
	color_spot.z = color.z * brightness * light_int;
	return (color_spot);
}

t_vec	sum_lights(t_vec color)
{
	if (color.x > 1.0)
		color.x = 1.0;
	if (color.y > 1.0)
		color.y = 1.0;
	if (color.z > 1.0)
		color.z = 1.0;
	color.x = (int)(color.x * 255);
	color.y = (int)(color.y * 255);
	color.z = (int)(color.z * 255);
	return (color);
}
