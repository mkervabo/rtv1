/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:39:51 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/15 17:05:47 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "toml.h"

bool				read_digit(t_toml toml, double *digit)
{
if (radius->type == TOML_FLOAT)
		*digit = toml->value.float_v;
	else if (radius->type == TOML_INTEGER)
		*digit = toml->value.integer_v;
	else
		return (false)
}

static int			ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static t_light		**read_lights(t_toml_table *toml)
{
	t_light		**lights;
	t_toml			*v;
	size_t			i;

	
	if (read_toml_type(toml, &v, "lights", TOML_ARRAY) == false)
		return (NULL);
	if (v->value.array_v->len == 0
		|| v->value.array_v->inner[0].type != TOML_TABLE)
		return (NULL);
	if (!(lights = malloc(sizeof(t_light*) * v->value.array_v->len)))
		return (NULL);
	i = 0;
	while (i < v->value.array_v->len)
	{
		lights[i] = read_light(v->value.array_v->inner[i].value.table_v)
		i++;
	}
	return(lights)
}

static t_object		**read_objects(t_toml_table *toml)
{
	t_object		**objects;
	t_toml			*v;
	size_t			i;

	if (read_toml_type(toml, &v, "objects", TOML_ARRAY) == false)
		return (NULL);
	if (v->value.array_v->len == 0
		|| v->value.array_v->inner[0].type != TOML_TABLE)
		return (NULL);
	if (!(objects = malloc(sizeof(t_object*) * v->value.array_v->len)))
		return (NULL);
	i = 0;
	while (i < v->value.array_v->len)
	{
		objects[i] = read_object(v->value.array_v->inner[i].value.table_v)
		i++;
	}
	return(objects)
}

t_vec3			read_camera(t_toml_table *toml)
{
	t_toml	*camera;
	t_toml	*value;
	t_vec3	pos;
	/*t_cam cam;*/

	if (read_toml_type(toml, &camera, "objects", TOML_TABLE) == false)
		return (NULL);
	if (read_toml_type(camera, &value, "position", TOML_TABLE) == false)
		return (NULL);
	if (!(pos = read_t_vec3(value)))
		return (NULL);
	/*
	if (!(camera.pos = read_t_vec3(value)))
		return (NULL);
	if (read_toml_type(camera, &value, "rotation", TOML_TABLE) == false)
		return (NULL);
	if (!(cam.rot = read_t_vec3(value)))
		return (NULL);
	return (cam);
	*/
	return (pos);¸

}

bool	read_file(char *file, t_object ***object, t_light ***light, t_vec3 *camera)
{
	int				fd;
	t_toml_error	err;
	t_reader 		r;
	t_toml_table	*toml

	fd = open(file, O_RDONLY);
	r = create_reader(fd, buffer, sizeof(buffer));
	close(fd);
	if ((err = read_toml(&r, &toml, true)) != NO_ERROR)
	{
		printf("Error<%zu:%zu>: %d\n", r.line, r.column, err);
		return false
	}
	if (!(*object = read_objects(toml)))
		return (false);
	if (!(*light = read_lights(toml)))
		return (false);
	if (!(*camera = read_camera(toml)))
		return (false);
	return (true);
}
