#include "rtv1.h"

void	free_scene(t_scene *scene)
{
	size_t	i;

	i = 0;
	while (i < scene->objects_size)
	{
		free(scene->objects[i]);
		i++;
	}
	free(scene->objects);

	i = 0;
	while (i < scene->lights_size)
	{
		free(scene->lights[i]);
		i++;
	}
	free(scene->lights);
}
