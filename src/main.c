/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:39:35 by mkervabo          #+#    #+#             */
/*   Updated: 2019/04/29 18:23:18 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

#define SHADOW_BIAS 1e-4
uint8_t	clamp_rgb(double value);

void ft_exit(SDL_Renderer* renderer, SDL_Window *win)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	exit(0);
}

void new_win(SDL_Renderer** renderer, SDL_Window **win)
{
	SDL_Init(SDL_INIT_VIDEO);
	if (!(*win = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_X , SCREEN_Y, SDL_WINDOW_OPENGL))
	|| !(*renderer = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED)))
	{
        printf("Could not create window: %s\n", SDL_GetError());
		ft_exit (*renderer, *win);
    }
}

int main() {
	t_vec3 	camera;
	t_ray 	ray;
	
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	int				quit;

	win = NULL;
	renderer = NULL;
	new_win(&renderer, &win);

	camera = (t_vec3) {
		.x = 0,
		.y = 1,
		.z = 1
	};

	int x;
	int y;

	y = 0;
	while (y < SCREEN_Y)
	{
		x = 0;
		while(x < SCREEN_X) {
			ray = camera_create_ray(camera, x, y);
			t_who t = in_objects(&ray, objects, objects_size);

			if (t.hit.t >= 0)
			{
				t_vec3 p = vec3_add(vec3_add(ray.origin, vec3_multv(ray.direction, t.hit.t)), vec3_multv(t.hit.n, SHADOW_BIAS));
				double r = 0;
				double g = 0;
				double b = 0;
				bool mod = false;
				size_t i = 0;
				while (i < lights_size)
				{
					double distance = receive_light(lights[i], p, objects, objects_size);
					
					if (distance >= 0)
					{
						t_color color;
						if (objects[t.i]->light == LIGHT_PHONG)
							color = phong(objects[t.i]->color, lights[i], t.hit, &ray);
						if (objects[t.i]->light == LIGHT_DIFFUSE)
							color = diffuse(objects[t.i]->color, lights[i], t.hit.n, p);
						if (objects[t.i]->light == LIGHT_SPECULAR)
							color = specular(objects[t.i]->color, lights[i], t.hit, &ray);
						r += color.r;
						g += color.g;
						b += color.b;
						mod = true;
					}
					
					i++;
				}
				SDL_SetRenderDrawColor(renderer,
							mod ? clamp_rgb(objects[t.i]->color.r - r) : 0,
							mod ? clamp_rgb(objects[t.i]->color.g - g) : 0,
							mod ? clamp_rgb(objects[t.i]->color.b - b) : 0,
							255
						);
			}
			else
				SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255);	
			SDL_RenderDrawPoint(renderer, x, SCREEN_Y - y - 1);
			x++;
		}
		y++;
	}
	SDL_RenderPresent(renderer);

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&event)){
			if (event.type == SDL_QUIT)
				quit = 1;
			if (event.type == SDL_KEYDOWN)
				quit = 1;
			if (event.type == SDL_MOUSEBUTTONDOWN)
				quit = 1;
		}
	}
	ft_exit(renderer, win);
}
