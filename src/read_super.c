#include "rtv1.c"
#include "toml.c"

static t_color			read_color(t_toml_table *toml)
{
	t_color	color;
	t_toml	*value;

	if (!(value = table_get(toml, "r")))
		color.r = 0;
	if (value->type != TOML_INTEGER)
			return (NULL);
	color.r = value->value;
	if (!(value = table_get(toml, "g")))
		color.g = 0;
	if (value->type != TOML_INTEGER)
			return (NULL);
	color.g = value->value;
	if (!(value = table_get(toml, "b")))
		color.r = 0;
	if (value->type != TOML_INTEGER)
			return (NULL);
	color.b = value->value;
	return (color);
}

t_vec3				read_t_vec3(t_toml_table *toml)
{
	t_vec3	vec;
	t_toml	*value;

	if (!(value = table_get(toml, "x")))
		vec.x = 0;
	if (read_digit(value, &vec.x) == false)
		return (NULL);
	if (!(value = table_get(toml, "y")))
		vec.y = 0;
	if (read_digit(value, &vec.y) == false)
		return (NULL);
	if (!(value = table_get(toml, "z")))
		vec.x = 0;
	if (read_digit(value, &vec.z) == false)
		return (NULL);
	return (vec);
}

static	e_light_type	read_light_type(char *light)
{
	if (light == "DIFFUSE")
		return (LIGHT_DIFFUSE);
	if (light == "PHONG")
		return(LIGHT_PHONG);
	return (NULL);
}

bool					read_toml_type(t_toml_table *toml, t_toml **value, char *name, e_toml_type type)
{
	if (!(*value = table_get(toml, name)))
		return (false);
	if (*value->type != type)
		return (false);
	return (true)
}

t_light				*read_light(t_toml_table *toml)
{
	t_toml	*type;
	t_light	*light;

	if (!(light = malloc(sizeof(t_light*))))
		return (NULL);
	if (read_toml_type(toml, &type, "position", TOML_TABLE) == false)
		return (NULL);
	if (!(light->pos = read_t_vec3(toml->table_v)))
		return (NULL);
	if (read_toml_type(toml, &type, "color", TOML_TABLE) == false)
		return (NULL);
	if (!(light->color = read_color(toml->table_v)))
		return (NULL);
	if (!(type = table_get(toml, toml, "intensity")))
		return (NULL);
	if (read_digit(value, &light->intensity) == false)
		return (NULL);
	if (!(type = table_get(toml, "expose")))
		return (NULL);
	if (read_digit(value, &light->expose) == false)
		return (NULL);
	return (light)
}

t_object				read_super(t_toml_table *toml)
{
	t_toml		*value;
	t_object	object;

	if (read_toml_type(toml, &value, "position", TOML_TABLE) == false)
		return (NULL);
	if (!(object->pos = read_t_vec3(toml->table_v)))
		return (NULL);
	if (read_toml_type(toml, &value, "rotation", TOML_TABLE) == false)
		return (NULL);
	if (!(object->rot = read_t_vec3(toml->table_v)))
		return (NULL);
	if (read_toml_type(toml, &value, "color", TOML_TABLE) == false)
		return (NULL);
	if (!(object->color = read_color(toml->table_v)))
		return (NULL);
	if (read_toml_type(toml, &value, "light", TOML_STRING) == false)
		return (NULL);
	if (!(object.light = read_light_type(value->string_v))
	return (object);
}