#include "rtv1.h"

bool	apply_light(t_color *color_light, t_ray *ray, t_who t, t_vec3 p, t_object *objects[], size_t objects_size, t_light *lights[], size_t lights_size)
{
	t_color color;
	size_t i;
	double distance;
	bool mod;
	
	i = 0;
	mod = false;
	while (i < lights_size)
	{
		distance = receive_light(lights[i], p, objects, objects_size);
		if (distance >= 0)
		{
			if (objects[t.i]->light == LIGHT_PHONG)
				color = phong(objects[t.i]->color, lights[i], t.hit, ray);
			if (objects[t.i]->light == LIGHT_DIFFUSE)
				color = diffuse(objects[t.i]->color, lights[i], t.hit.n, p);
			if (objects[t.i]->light == LIGHT_SPECULAR)
				color = specular(objects[t.i]->color, lights[i], t.hit, ray);
			color_light->r += color.r;
			color_light->g += color.g;
			color_light->b += color.b;
			mod = true;
		}
		
		i++;
	}
	return (mod);
}