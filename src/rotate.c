/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 13:47:30 by mkervabo          #+#    #+#             */
/*   Updated: 2019/04/30 14:18:56 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


static t_vec3	vec3_rotate_x(t_vec3 v, double angle)
{
	const double cos_a = cos(angle);
	const double sin_a = sin(angle);

	return ((t_vec3) {
		.x = v.x,
		.y = v.y * cos_a - v.z * sin_a,
		.z = v.y * sin_a + v.z * cos_a,
	});
	
}

static t_vec3	vec3_rotate_y(t_vec3 v, double angle)
{
	const double cos_a = cos(angle);
	const double sin_a = sin(angle);

	return ((t_vec3) {
		.x = v.x * cos_a + v.z * sin_a,
		.y = v.y,
		.z = -v.x * sin_a + v.z * cos_a,
	});
}

static t_vec3	vec3_rotate_z(t_vec3 v, double angle)
{
	const double cos_a = cos(angle);
	const double sin_a = sin(angle);

	return ((t_vec3) {
		.x = v.x * cos_a - v.y * sin_a,
		.y = v.x * sin_a + v.y * cos_a,
		.z = v.z
	});
}

t_vec3	vec3_rotate(t_vec3 v, double x, double y, double z)
{
	v = vec3_rotate_x(v, x);
	v = vec3_rotate_y(v, y);
	v = vec3_rotate_z(v, z);

	return (v);
}