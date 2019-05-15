#include "rtv1.c"
#include "toml.c"


static t_object	*read_plane(t_toml_table *toml)
{
	t_plane	*plane;

	(void)toml;
	if (!(plane = malloc(sizeof(t_plane))))
		return (NULL);
	plane->super = read_super(toml);
	plane->super.type = TYPE_PLANE;
	return (plane);
}

static t_cone	*read_cone(t_toml_table *toml)
{
	t_cone	*cone;
	t_toml	*angle;

	if (!(cone = malloc(sizeof(t_cone))))
		return (NULL);
	if (!(angle = table_get(toml, "angle")))
		return (NULL);
	if (read_digit(angle, &cone) == false)
	{
		free(cone);
		return (NULL);
	}
	cone->angle *= M_PI / 180;
	cone->super = read_super(toml);
	cone->super.type = TYPE_CONE;
	return (cone);
}

static t_cylinder	*read_cylinder(t_toml_table *toml)
{
	t_cylinder	*cylinder;
	t_toml		*radius;

	if (!(cylinder = malloc(sizeof(t_cylinder))))
		return (NULL);
	if (!(radius = table_get(toml, "radius")))
		return (NULL);
	if (read_digit(radius, &cylinder) == false)
	{
		free(cylinder);
		return (NULL);
	}
	cylinder->super = read_super(toml);
	cylinder->super.type = TYPE_CYLINDER;
	return (cylinder);
}

static t_sphere		*read_sphere(t_toml_table *toml)
{
	t_sphere	*sphere;
	t_toml		*radius;

	if (!(sphere = malloc(sizeof(t_sphere))))
		return (NULL);
	if (!(radius = table_get(toml, "radius")))
		return (NULL);
	if (read_digit(radius, &sphere) == false)
	{
		free(sphere);
		return (NULL);
	}
	sphere->super = read_super(toml);
	sphere->super.type = TYPE_SPHERE;
	return (sphere);
}

t_object			*read_object(t_toml_table *toml)
{
	t_toml	*type;

	if (!(type = table_get(toml, "type")))
		return (NULL);
	if (type->type != TOML_STRING)
		return (NULL);
	if (ft_strcmp(type->value.string_v, "SPHERE") == 0)
		return (read_sphere(toml));
	if (ft_strcmp(type->value.string_v, "CYLINDER") == 0)
		return (read_cylinder(toml));
	if (ft_strcmp(type->value.string_v, "PLANE") == 0)
		return (read_plane(toml));
	if (ft_strcmp(type->value.string_v, "CONE") == 0)
		return (read_cone(toml));
	else
		return (NULL)
	
}