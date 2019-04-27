#include "rtv1.h"

t_object *objects[] = {
	&((t_sphere) {
		.super = {
			TYPE_SPHERE,
			{ 0, 1, 0 },
			{ 
				.r = 135,
				.g = 206,
				.b = 235
			}
		},
		.r = 0.15
	}),
	&((t_cylinder) {
		.super = {
			TYPE_CYLINDER,
			{ 0.3, 1, 0 },
			{ 
				.r = 255,
				.g = 105,
				.b = 180
			}
		},
		.r = 0.1
		
	}),
	&((t_cone) {
		.super = {
			TYPE_CONE,
			{ -0.3, 1, 0 },
			{ 
				.r = 154,
				.g = 205,
				.b = 50
			}
		},
		.angle = M_PI / 10
		
	}),
	&((t_object) {
		TYPE_PLANE,
		{ 0, 0.9, 0 },
		{
			.r = 255,
			.g = 215,
			.b = 0
		}
	}),
};

size_t objects_size = sizeof(objects) / sizeof(*objects);

t_light *lights[] = {
	&((t_light){
		.pos = { 0, 2, 1 },
		.color = {
			.r = 255,
			.g = 255,
			.b = 255
		},
		.intensity = 0.5
	}),
};

size_t lights_size = sizeof(lights) / sizeof(*lights);