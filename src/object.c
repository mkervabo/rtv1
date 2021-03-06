/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:45:29 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/22 14:03:56 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

bool		solve_quadratic(t_polynome poly, float *t1, float *t2)
{
	float	delta;
	float	p1;
	float	p2;

	delta = poly.b * poly.b - 4 * poly.a * poly.c;
	if (delta >= 0)
	{
		p1 = (-poly.b - sqrt(delta)) / (2.0 * poly.a);
		p2 = (-poly.b + sqrt(delta)) / (2.0 * poly.a);
		*t1 = fmin(p1, p2);
		*t2 = fmax(p1, p2);
		return (true);
	}
	else
		return (false);
}

float		solve_quadratic_min(t_polynome poly)
{
	float	t1;
	float	t2;

	if (solve_quadratic(poly, &t1, &t2))
	{
		if (t1 < 0)
			return (t2);
		else
			return (t1);
	}
	else
		return (-1.0);
}

static void	object_type(t_object *object, t_ray *ray, t_hit_info *hit)
{
	if (object->type == Type_Sphere)
		*hit = in_sphere((t_sphere *)object, ray);
	if (object->type == Type_Cylinder)
		*hit = in_cylinder((t_cylinder *)object, ray);
	if (object->type == Type_Cone)
		*hit = in_cone((t_cone *)object, ray);
	if (object->type == Type_Plane)
		*hit = in_plane(ray);
}

t_who		in_objects(t_ray *ray, t_object *objects[], size_t size)
{
	t_hit_info	hit;
	t_who		t_max;
	t_ray		r;
	size_t		i;

	i = 0;
	t_max.hit.t = INFINITY;
	while (i < size)
	{
		r = *ray;
		r.origin = vec3_sub(r.origin, objects[i]->pos);
		r.origin = vec3_rotate(r.origin, vec3_multv(objects[i]->rot, -1));
		r.direction = vec3_rotate(r.direction, vec3_multv(objects[i]->rot, -1));
		object_type(objects[i], &r, &hit);
		if (hit.t > 0 && hit.t < t_max.hit.t)
		{
			hit.n = vec3_rotate(hit.n, objects[i]->rot);
			t_max.hit = hit;
			t_max.i = i;
		}
		i++;
	}
	if (t_max.hit.t == INFINITY)
		t_max.hit.t = -1.0;
	return (t_max);
}
