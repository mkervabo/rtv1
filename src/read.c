/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:39:51 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/21 10:44:24 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "toml.h"

bool				read_window(t_toml_table *toml, t_win *win)
{
	t_toml	*value;
	double	width;
	double	height;

	if(!(value = table_get(toml, "width")))
		return (false);
	if (!read_digit(value, &width))
		return (false);
	win->width = width;
	if(!(value = table_get(toml, "height")))
		return (false);
	if (!read_digit(value, &height))
		return (false);
	win->height = height;
	if (!(read_toml_type(toml, &value, "name", TOML_STRING)))
		return (false);
	win->name = value->value.string_v;
	return (true);
}

bool				read_digit(t_toml *toml, double *digit)
{
	if (toml->type == TOML_FLOAT)
		*digit = toml->value.float_v;
	else if (toml->type == TOML_INTEGER)
		*digit = toml->value.integer_v;
	else
		return (false);
	return (true);
}

int			ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

t_light		**read_lights(t_toml_table *toml, size_t *size)
{
	t_light		**lights;
	t_toml			*v;
	size_t			i;

	
	if (read_toml_type(toml, &v, "lights", TOML_ARRAY) == false)
		return (NULL);
	if (v->value.array_v->len == 0
		|| v->value.array_v->inner[0].type != TOML_TABLE)
		return (NULL);
	*size = v->value.array_v->len;
	if (!(lights = malloc(sizeof(t_light*) * *size)))
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!(lights[i] = read_light(v->value.array_v->inner[i].value.table_v)))
			return (NULL);
		i++;
	}
	return (lights);
}

t_object		**read_objects(t_toml_table *toml, size_t *size)
{
	t_object		**objects;
	t_toml			*v;
	size_t			i;

	if (read_toml_type(toml, &v, "objects", TOML_ARRAY) == false)
		return (NULL);
	if (v->value.array_v->len == 0
		|| v->value.array_v->inner[0].type != TOML_TABLE)
		return (NULL);
	*size = v->value.array_v->len;
	if (!(objects = malloc(sizeof(t_object*) * *size)))
		return (NULL);
	i = 0;
	while (i < *size)
	{
		if (!(objects[i] = read_object(v->value.array_v->inner[i].value.table_v)))
			return (NULL);
		i++;
	}
	return (objects);
}

bool			read_camera(t_toml_table *toml, t_cam *cam)
{
	t_toml	*camera;
	t_toml	*value;

	if (!read_toml_type(toml, &camera, "camera", TOML_TABLE))
		return (false);
	if (!read_toml_type(camera->value.table_v, &value, "position", TOML_TABLE))
		return (false);
	if (!read_t_vec3(value->value.table_v, &cam->pos))
		return (false);
	if (!read_toml_type(camera->value.table_v, &value, "rotation", TOML_TABLE))
		return (false);
	if (!read_t_vec3(value->value.table_v, &cam->rot))
		return (false);
	cam->rot = vec3_multv(cam->rot, M_PI / 180);
	return (true);
}