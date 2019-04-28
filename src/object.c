/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 11:45:29 by mkervabo          #+#    #+#             */
/*   Updated: 2019/04/27 16:17:01 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

float		solve_quadratic(t_polynome poly)
{
	float delta;

	delta = poly.b * poly.b - 4 * poly.a * poly.c;
	if (delta >= 0)
	{
		return (fmin(
			(-poly.b - sqrt(delta)) / (2.0 * poly.a),
			(-poly.b + sqrt(delta)) / (2.0 * poly.a)
		));
	}
	else
		return (-1.0);
}


t_hit_info	in_cone(t_cone *cone, t_ray *ray)
{
	t_polynome	poly;
	t_hit_info	hit;
	t_vec3		v;

	poly.a = ray->direction.y * ray->direction.y - cos(cone->angle) * cos(cone->angle);
	poly.b = 2 * (ray->direction.y * ray->origin.y - vec3_dot(ray->direction, ray->origin) * cos(cone->angle) * cos(cone->angle));
	poly.c = ray->origin.y * ray->origin.y - vec3_dot(ray->origin, ray->origin) * cos(cone->angle) * cos(cone->angle);
	hit.t = solve_quadratic(poly);
	if (hit.t >= 0)
	{
		v = vec3_add(ray->origin, vec3_multv(ray->direction, hit.t));
		//printf("%f", v.y);
	/*	if (v.y > 2)
		{
			hit.t = -1.0;
			return (hit);
		}*/
		v.y = 0;
		v = vec3_unit(v);
		hit.n = vec3_unit((t_vec3) {
			.x = v.x / tan(cone->angle),
			.y = tan(cone->angle),
			.z = v.z / tan(cone->angle)
		});
	}
	return (hit);
}

t_hit_info	in_cylinder(t_cylinder *cylinder, t_ray *r)
{
	t_polynome	poly;
	t_ray 		ray;
	t_hit_info	hit;

	ray = *r;
	ray.direction.y = 0;
	ray.origin.y = 0;
	poly.a = vec3_dot(ray.direction, ray.direction);
	poly.b = 2 * vec3_dot(ray.origin, ray.direction);
	poly.c = vec3_dot(ray.origin, ray.origin) - cylinder->r * cylinder->r;
	hit.t = solve_quadratic(poly);
	if (hit.t >= 0)
		hit.n = vec3_unit(vec3_add(ray.origin, vec3_multv(ray.direction, hit.t)));
	return (hit);
}

t_hit_info	in_sphere(t_sphere *sphere, t_ray *ray)
{
	t_polynome	poly;
	t_hit_info	hit;

	poly.a = vec3_dot(ray->direction, ray->direction);
	poly.b = 2 * vec3_dot(ray->origin, ray->direction);
	poly.c = vec3_dot(ray->origin, ray->origin) - sphere->r * sphere->r;
	hit.t = solve_quadratic(poly);
	if (hit.t >= 0)
		hit.n = vec3_unit(vec3_add(ray->origin, vec3_multv(ray->direction, hit.t)));
	return (hit);
}

t_hit_info	in_plane(t_ray *ray)
{
	t_hit_info	hit;

	if (fabs(ray->direction.y) > 1e-6) {
		hit.t = -ray->origin.y / ray->direction.y;
		if (hit.t >= 0)
			hit.n = (t_vec3) { 0, 1, 0 };
	} else
		hit.t = -1.0;
	return (hit);
}

t_who		in_objects(t_ray *ray, t_object *objects[], size_t size)
{
	t_hit_info hit;
	t_who t_max;
	size_t i;

	i = 0;
	t_max.hit.t = INFINITY;
	while(i < size)
	{
		ray->origin = vec3_sub(ray->origin, objects[i]->pos);
		if (objects[i]->type == TYPE_SPHERE)
			hit = in_sphere((t_sphere *)objects[i], ray);
		if (objects[i]->type == TYPE_CYLINDER)
			hit = in_cylinder((t_cylinder *)objects[i], ray);
		if (objects[i]->type == TYPE_CONE)
			hit = in_cone((t_cone *)objects[i], ray);
		if (objects[i]->type == TYPE_PLANE)
			hit = in_plane(ray);
		if (hit.t > 0 && hit.t < t_max.hit.t)
		{
			t_max.hit = hit;
			t_max.i = i;
		}
		ray->origin = vec3_add(ray->origin, objects[i]->pos);
		i++;
	}
	if (t_max.hit.t == INFINITY)
		t_max.hit.t = -1.0;
	return (t_max);
}
