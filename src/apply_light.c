/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 11:51:30 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/22 13:30:30 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color		color_add(t_color a, t_color b)
{
	return ((t_color) {
		.r = (a.r + b.r),
		.g = (a.g + b.g),
		.b = (a.b + b.b)
	});
}

bool		apply_light(t_color *clr_light, t_ray *r, t_who t, t_scene *s)
{
	t_color	clr;
	size_t	i;
	double	distance;
	bool	mod;
	t_vec3	p;

	i = -1;
	mod = false;
	p = vec3_add(vec3_add(r->origin, vec3_multv(r->direction, t.hit.t)),
		vec3_multv(t.hit.n, SHADOW_BIAS));
	while (++i < s->lights_size)
		if ((distance = receive_light(s->lights[i], p,
					s->objects, s->objects_size)) >= 0)
		{
			if (s->objects[t.i]->light == light_phong)
				clr = phong(s->lights[i], t.hit, r);
			if (s->objects[t.i]->light == light_diffuse)
				clr = diffuse(s->lights[i], t.hit.n, p);
			if (s->objects[t.i]->light == light_specular)
				clr = specular(s->lights[i], t.hit, r);
			*clr_light = color_add(*clr_light, clr);
			mod = true;
		}
	return (mod);
}
