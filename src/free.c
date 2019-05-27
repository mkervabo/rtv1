#include "rtv1.h"

void	*free_ptr_array(void **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

void	free_scene(t_scene *scene)
{
	if (scene->objects)
		free_ptr_array((void **)scene->objects, scene->objects_size);
	if (scene->lights)
		free_ptr_array((void **)scene->lights, scene->lights_size);
}
