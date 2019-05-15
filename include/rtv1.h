/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 17:11:32 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/15 16:58:56 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <stdlib.h>
# include <stdbool.h>
# include <SDL.h>

# define SCREEN_X 1600
# define SCREEN_Y 880

typedef struct	s_polynome
{
	double		a;
	double		b;
	double		c;
}				t_polynome;

typedef struct s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

typedef struct	s_ray
{
	t_vec3		origin;
	t_vec3		direction;
}				t_ray;

enum e_object_type
{
	TYPE_SPHERE,
	TYPE_CYLINDER,
	TYPE_CONE,
	TYPE_PLANE
};

enum e_light_type
{
	LIGHT_DIFFUSE,
	LIGHT_SPECULAR,
	LIGHT_PHONG
};

typedef struct	s_color
{
	double		r;
	double		g;
	double		b;
}				t_color;

typedef struct s_light
{
	
	t_vec3				pos;
	t_color				color;
	double				intensity;
	int					expose;
}				t_light;

typedef struct s_hit_info
{
	double		t;
	t_vec3		n;
}				t_hit_info;

typedef struct	s_who
{
	t_hit_info	hit;
	size_t		i;
}				t_who;

typedef struct	s_object
{
	enum e_object_type	type;
	enum e_light_type	light;
	t_vec3				pos;
	t_color				color;
	t_vec3				rot;	
}				t_object;

typedef struct	s_sphere
{
	t_object	super;
	double 		r;
}				t_sphere;

typedef struct	s_cylinder
{
	t_object	super;
	double 		r;
}				t_cylinder;

typedef struct	s_cone
{
	t_object	super;
	double		angle;
}				t_cone;

typedef struct	s_cam
{
	t_vec3		pos;
	t_vec3		rot;
}				t_cam;


void		read_file(char *file);

bool		read_digit(t_toml toml, double *digit);
bool		read_toml_type(t_toml **value, char *name, e_toml_type type);

t_vec3		read_t_vec3(t_toml_table *toml);
t_object	*read_object(t_toml_table *toml);
t_object	read_super(t_toml_table *toml);
t_light		*read_light(t_toml_table *toml);
t_ray		camera_create_ray(t_vec3 camera, int x, int y);

t_vec3		vec3_multv(t_vec3 a, double v);
t_vec3		vec3_unit(t_vec3 v);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_mult(t_vec3 a, t_vec3 b);
t_vec3		vec3_divv(t_vec3 a, double v);
double		vec3_dot(t_vec3 a, t_vec3 b);
double		vec3_length(t_vec3 v);

t_vec3		vec3_rotate(t_vec3 v, t_vec3 rot);

t_color		 color_add(t_color a, t_color b);

t_hit_info	in_sphere(t_sphere *sphere, t_ray *ray);
t_hit_info	in_cylinder(t_cylinder *cylinder, t_ray *ray);
t_hit_info	in_cone(t_cone *cone, t_ray *ray);
t_hit_info	in_plane(t_ray *ray);
t_who		in_objects(t_ray *ray, t_object *objects[], size_t size);

double		receive_light(t_light *light, t_vec3 p, t_object *objects[], size_t size);
t_color		 diffuse(t_color object, t_light *light, t_vec3 n, t_vec3 p);
t_color		specular(t_color object, t_light *light, t_hit_info hit, t_ray *ray);
t_color		phong(t_color object, t_light *light, t_hit_info hit, t_ray *ray);
bool		apply_light(t_color *color_light, t_ray *ray, t_who t, t_vec3 p);

extern t_object *objects[];
extern size_t objects_size;
extern t_light *lights[];
extern size_t lights_size;

#endif