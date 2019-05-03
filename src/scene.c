#include "rtv1.h"

t_object *objects[] = {
	/*&((t_sphere) {
		.super = {
			TYPE_SPHERE,
			LIGHT_PHONG,
			{ 0, 1.1, 0 },
			{
				138,
				43,
				226
			}
		},
		.r = 0.15
	}),
	&((t_cylinder) {
		.super = {
			TYPE_CYLINDER,
			LIGHT_PHONG,
			{ 0.3, 1, 0 },
			.color = { 
				.r = 0,
				.g = 0,
				.b = 180
			},
			.x_rot = M_PI / 2
		},
		.r = 0.1
		
	}),*/
	&((t_cone) {
		.super = {
			TYPE_CONE,
			LIGHT_PHONG,
			{ 0, 1.1, 0 },
			.color =  { 
				.r = 154,
				.g = 205,
				.b = 50
			},
			//.z_rot = M_PI / 2
			.x_rot = M_PI / 2
		},
		.angle = M_PI / 10
	}),
	/*&((t_object) {
		TYPE_PLANE,
		LIGHT_DIFFUSE,
		{ -2, 0, 0 },
		.color =  {
			0,
			100,
			0
		},
		.x_rot = M_PI / 2
	}),
	&((t_object) {
		TYPE_PLANE,
		LIGHT_DIFFUSE,
		{ 0, 0, 0 },
		.color =  {
			100,
			100,
			100
		}
	}),*/
};

size_t objects_size = sizeof(objects) / sizeof(*objects);

t_light *lights[] = {
	&((t_light){
		.pos = { -9, 1, 0 },
		.color = {
			.r = 255,
			.g = 255,
			.b = 255
		},
		.intensity = 0.2,
		.expose = 21
	}),
	&((t_light){
		.pos = { 0.1, 4.3, 0 },
		.color = {
			.r = 255,
			.g = 255,
			.b = 255
		},
		.intensity = 0.2,
		.expose = 21
	}),
	&((t_light){
		.pos = { 1, 1, 1 },
		.color = {
			.r = 255,
			.g = 255,
			.b = 255
		},
		.intensity = 0.2,
		.expose = 21
	}),
};


size_t lights_size = sizeof(lights) / sizeof(*lights);