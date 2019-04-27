/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:37:58 by mkervabo          #+#    #+#             */
/*   Updated: 2019/04/27 15:48:46 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


double receive_light(t_light *light, t_vec3 p, t_object *objects[], size_t size)
{
	t_ray		shadow;
	t_vec3		to_light;
	double		dist;
	t_hit_info	hit;

	to_light = vec3_sub(light->pos, p);
	dist = vec3_length(to_light);
	shadow = (t_ray){
		.origin = p,
		.direction = vec3_divv(to_light, dist)
	};
	hit = in_objects(&shadow, objects, size).hit;
	if (hit.t >= 0 && hit.t <= dist)
		return (-1.0);
	else
		return (dist);
}

static uint8_t	clamp_rgb(double value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

t_color diffuse(t_color object, t_light *light, t_vec3 n, t_vec3 p)
{
	t_color	color;
	t_vec3	n_light;
	double	i;
	 
	n_light = vec3_unit(vec3_sub(p, light->pos));
	i = vec3_dot(n_light, n) * light->intensity;
	color.r = clamp_rgb(object.r - light->color.r * i);
	color.g = clamp_rgb(object.g - light->color.g * i);
	color.b = clamp_rgb(object.b - light->color.b * i);
	return (color);
}

/*t_color	specular(t_color object, t_light *light, t_vec3 n, t_vec3 p)
{

}*/