#include "rtv1.h"
#include "toml.h"

static t_object	*read_plane(t_toml_table *toml)
{
	t_object	*plane;

	(void)toml;
	if (!(plane = malloc(sizeof(t_object))))
		return (NULL);
	if (!read_super(toml, plane))
	{
		free(plane);
		return (NULL);
	}
	plane->type = TYPE_PLANE;
	return (plane);
}

static t_cone	*read_cone(t_toml_table *toml)
{
	t_cone	*cone;
	t_toml	*angle;
	t_toml	*revolution;

	if (!(cone = malloc(sizeof(t_cone))))
		return (NULL);
	if (!(angle = table_get(toml, "angle")))
		return (NULL);
	if (!read_super(toml, &cone->super))
	{
		free(cone);
		return (NULL);
	}
	if (read_digit(angle, &cone->angle) == false)
	{
		free(cone);
		return (NULL);
	}
	if ((revolution = table_get(toml, "revolution")))
	{
		if (revolution->type != TOML_BOOLEAN)
		{
			free(cone);
			return (NULL);
		}
		cone->revolution = revolution->value.boolean_v;
	}
	else
		cone->revolution = true;
	cone->angle *= M_PI / 180;
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
	if (!read_super(toml, &cylinder->super))
	{
		free(cylinder);
		return (NULL);
	}
	if (read_digit(radius, &cylinder->r) == false)
	{
		free(cylinder);
		return (NULL);
	}
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
	if (!read_super(toml, &sphere->super))
	{
		free(sphere);
		return (NULL);
	}
	if (read_digit(radius, &sphere->r) == false)
	{
		free(sphere);
		return (NULL);
	}
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
		return ((t_object *)read_sphere(toml));
	if (ft_strcmp(type->value.string_v, "CYLINDER") == 0)
		return ((t_object *)read_cylinder(toml));
	if (ft_strcmp(type->value.string_v, "PLANE") == 0)
		return ((t_object *)read_plane(toml));
	if (ft_strcmp(type->value.string_v, "CONE") == 0)
		return ((t_object *)read_cone(toml));
	else
		return (NULL);
}