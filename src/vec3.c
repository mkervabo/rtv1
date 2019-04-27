/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:37:37 by mkervabo          #+#    #+#             */
/*   Updated: 2019/04/27 15:49:03 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	vec3_length(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3 vec3_unit(t_vec3 v)
{
	return (vec3_divv(v, vec3_length(v)));
}

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3) {
		.x = a.x + b.x,
		.y = a.y + b.y,
		.z = a.z + b.z
	});
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3) {
		.x = a.x - b.x,
		.y = a.y - b.y,
		.z = a.z - b.z
	});
}

t_vec3 vec3_multv(t_vec3 a, double v)
{
	return ((t_vec3) {
		.x = a.x * v,
		.y = a.y * v,
		.z = a.z * v
	});
}

t_vec3	vec3_mult(t_vec3 a, t_vec3 b)
{
	return ((t_vec3) {
		.x = a.x * b.x,
		.y = a.y * b.y,
		.z = a.z * b.z
	});
}

t_vec3	vec3_divv(t_vec3 a, double v)
{
	return ((t_vec3) {
		.x = a.x / v,
		.y = a.y / v,
		.z = a.z / v
	});
}

double	vec3_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
