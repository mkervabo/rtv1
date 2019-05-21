/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_super.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 14:16:01 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/21 14:21:47 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "toml.h"

static bool	read_color(t_toml_table *toml, t_color *color)
{
	t_toml	*value;

	if (!(value = table_get(toml, "r")))
		color->r = 0;
	if (value->type != TOML_INTEGER)
		return (false);
	color->r = value->value.integer_v;
	if (!(value = table_get(toml, "g")))
		color->g = 0;
	if (value->type != TOML_INTEGER)
		return (false);
	color->g = value->value.integer_v;
	if (!(value = table_get(toml, "b")))
		color->r = 0;
	if (value->type != TOML_INTEGER)
		return (false);
	color->b = value->value.integer_v;
	return (true);
}

bool		read_t_vec3(t_toml_table *toml, t_vec3 *vec)
{
	t_toml	*value;

	if (!(value = table_get(toml, "x")))
		vec->x = 0;
	if (read_digit(value, &vec->x) == false)
		return (false);
	if (!(value = table_get(toml, "y")))
		vec->y = 0;
	if (read_digit(value, &vec->y) == false)
		return (false);
	if (!(value = table_get(toml, "z")))
		vec->x = 0;
	if (read_digit(value, &vec->z) == false)
		return (false);
	return (true);
}

static bool	read_light_type(char *light, enum e_light_type *type)
{
	if (ft_strcmp(light, "DIFFUSE") == 0)
		*type = LIGHT_DIFFUSE;
	else if (ft_strcmp(light, "PHONG") == 0)
		*type = LIGHT_PHONG;
	else
		return (false);
	return (true);
}

bool		read_toml_type(t_toml_table *toml, t_toml **value, char *name,
	enum e_toml_type type)
{
	if (!(*value = table_get(toml, name)))
		return (false);
	if ((*value)->type != type)
		return (false);
	return (true);
}

t_light		*read_light(t_toml_table *toml)
{
	t_toml	*type;
	t_light	*light;
	double	expose;

	if (!(light = malloc(sizeof(t_light))))
		return (NULL);
	if (read_toml_type(toml, &type, "position", TOML_TABLE) == false)
		return (NULL);
	if (!read_t_vec3(type->value.table_v, &light->pos))
		return (NULL);
	if (read_toml_type(toml, &type, "color", TOML_TABLE) == false)
		return (NULL);
	if (!read_color(type->value.table_v, &light->color))
		return (NULL);
	if (!(type = table_get(toml, "intensity")))
		return (NULL);
	if (read_digit(type, &light->intensity) == false)
		return (NULL);
	if (!(type = table_get(toml, "expose")))
		return (NULL);
	if (read_digit(type, &expose) == false)
		return (NULL);
	light->expose = expose;
	return (light);
}

static bool	read_super_p_r(t_toml_table *toml, t_object *object)
{
	t_toml		*value;

	if (read_toml_type(toml, &value, "position", TOML_TABLE))
	{
		if (!read_t_vec3(value->value.table_v, &object->pos))
			return (false);
	}
	else
		object->pos = (t_vec3) {
			0, 0, 0
		};
	if (read_toml_type(toml, &value, "rotation", TOML_TABLE))
	{
		if (!read_t_vec3(value->value.table_v, &object->rot))
			return (false);
		object->rot = vec3_multv(object->rot, M_PI / 180);
	}
	else
		object->rot = (t_vec3) {
			0, 0, 0
		};
	return (true);
}

bool		read_super(t_toml_table *toml, t_object *object)
{
	t_toml		*value;

	if (!read_super_p_r(toml, object))
		return (false);
	if (read_toml_type(toml, &value, "color", TOML_TABLE) == false)
		return (false);
	if (!read_color(value->value.table_v, &object->color))
		return (false);
	if (read_toml_type(toml, &value, "light", TOML_STRING) == false)
		return (false);
	if (!read_light_type(value->value.string_v, &object->light))
		return (false);
	return (true);
}
