/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:45:29 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/21 14:04:25 by mkervabo         ###   ########.fr       */
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

static bool	cone_revolution(t_cone *cone, t_ray *ray, t_hit_info *hit, float *t)
{
	t_vec3		v;

	v = vec3_add(ray->origin, vec3_multv(ray->direction, t[0]));
	if (cone->revolution == false && v.y > 0)
	{
		v = vec3_add(ray->origin, vec3_multv(ray->direction, t[1]));
		if (v.y > 0)
		{
			hit->t = -1.0;
			return (true);
		}
		else
			hit->t = t[1];
	}
	else
		hit->t = t[0];
	v.y = 0;
	v = vec3_unit(v);
	hit->n = vec3_unit((t_vec3) {
		.x = v.x / tan(cone->angle),
		.y = tan(cone->angle),
		.z = v.z / tan(cone->angle)
	});
	return (false);
}

t_hit_info	in_cone(t_cone *cone, t_ray *ray)
{
	t_polynome	poly;
	t_hit_info	hit;
	float		t[2];

	poly.a = ray->direction.y * ray->direction.y - cos(cone->angle)
		* cos(cone->angle);
	poly.b = 2 * (ray->direction.y * ray->origin.y - vec3_dot(ray->direction,
			ray->origin) * cos(cone->angle) * cos(cone->angle));
	poly.c = ray->origin.y * ray->origin.y - vec3_dot(ray->origin, ray->origin)
		* cos(cone->angle) * cos(cone->angle);
	if (solve_quadratic(poly, &t[0], &t[1]))
	{
		if (cone_revolution(cone, ray, &hit, t))
			return (hit);
	}
	else
		hit.t = -1.0;
	return (hit);
}

t_hit_info	in_cylinder(t_cylinder *cylinder, t_ray *ray)
{
	t_polynome	poly;
	t_ray		r;
	t_hit_info	hit;

	r = *ray;
	r.direction.y = 0;
	r.origin.y = 0;
	poly.a = vec3_dot(r.direction, r.direction);
	poly.b = 2 * vec3_dot(r.origin, r.direction);
	poly.c = vec3_dot(r.origin, r.origin) - cylinder->r * cylinder->r;
	hit.t = solve_quadratic_min(poly);
	if (hit.t >= 0)
		hit.n = vec3_unit(vec3_add(r.origin, vec3_multv(r.direction, hit.t)));
	return (hit);
}

t_hit_info	in_sphere(t_sphere *sphere, t_ray *r)
{
	t_polynome	poly;
	t_hit_info	hit;

	poly.a = vec3_dot(r->direction, r->direction);
	poly.b = 2 * vec3_dot(r->origin, r->direction);
	poly.c = vec3_dot(r->origin, r->origin) - sphere->r * sphere->r;
	hit.t = solve_quadratic_min(poly);
	if (hit.t >= 0)
		hit.n = vec3_unit(vec3_add(r->origin, vec3_multv(r->direction, hit.t)));
	return (hit);
}

t_hit_info	in_plane(t_ray *ray)
{
	t_hit_info	hit;

	if (fabs(ray->direction.y) > 1e-6)
	{
		hit.t = -ray->origin.y / ray->direction.y;
		if (hit.t >= 0)
			hit.n = (t_vec3) {
				0, 1, 0
			};
	}
	else
		hit.t = -1.0;
	return (hit);
}

static void	object_type(t_object *object, t_ray *ray, t_hit_info *hit)
{
	if (object->type == TYPE_SPHERE)
		*hit = in_sphere((t_sphere *)object, ray);
	if (object->type == TYPE_CYLINDER)
		*hit = in_cylinder((t_cylinder *)object, ray);
	if (object->type == TYPE_CONE)
		*hit = in_cone((t_cone *)object, ray);
	if (object->type == TYPE_PLANE)
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
