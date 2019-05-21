/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:39:35 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/21 10:34:18 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "toml.h"
#include <fcntl.h>

#define SHADOW_BIAS 1e-4
uint8_t	clamp_rgb(double value);

void ft_exit(SDL_Renderer* renderer, SDL_Window *win)
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	exit(0);
}

void new_win(SDL_Renderer** renderer, SDL_Window **win, t_win *window)
{
	SDL_Init(SDL_INIT_VIDEO);
	if (!(*win = SDL_CreateWindow(window->name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window->width , window->height, SDL_WINDOW_OPENGL))
	|| !(*renderer = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED)))
	{
        printf("Could not create window: %s\n", SDL_GetError());
		ft_exit (*renderer, *win);
    }
}

void	render(t_object *objects[], size_t objects_size, t_light *lights[], size_t lights_size, t_cam camera, t_win *window)
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	int				quit;

	t_ray 	ray;

	win = NULL;
	renderer = NULL;
	new_win(&renderer, &win, window);

	int x;
	int y;

	y = 0;
	while (y < window->height)
	{
		x = 0;
		while(x < window->width) {
			ray = camera_create_ray(&camera, x, y, window);
			t_who t = in_objects(&ray, objects, objects_size);

			if (t.hit.t >= 0)
			{
				t_vec3 p = vec3_add(vec3_add(ray.origin, vec3_multv(ray.direction, t.hit.t)), vec3_multv(t.hit.n, SHADOW_BIAS));
				t_color color_light = { 0, 0, 0};
				bool mod = apply_light(&color_light, &ray, t, p, objects, objects_size, lights, lights_size);
				SDL_SetRenderDrawColor(renderer,
							mod ? clamp_rgb(objects[t.i]->color.r -  color_light.r) : 0,
							mod ? clamp_rgb(objects[t.i]->color.g -  color_light.g) : 0,
							mod ? clamp_rgb(objects[t.i]->color.b -  color_light.b) : 0,
							255
						);
			}
			else
				SDL_SetRenderDrawColor(renderer, 211, 211, 211, 255);	
			SDL_RenderDrawPoint(renderer, x, window->height - y - 1);
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
		}
	}
	ft_exit(renderer, win);
}

bool	render_scene(t_toml_table *toml) {
	t_object 		**objects;
	size_t			objects_size;
	t_light 		**lights;
	size_t 			lights_size;
	t_cam			camera;
	t_win			window;

	if (!(objects = read_objects(toml, &objects_size)))
		return (false);
	if (!(lights = read_lights(toml, &lights_size)))
		return (false);
	if (!read_camera(toml, &camera))
		return (false);
	if (!read_window(toml, &window))
		return (false);
	render(objects, objects_size, lights, lights_size, camera, &window);
	return (true);
}

int main(int argc, char *argv[]) {
	t_reader 		r;
	t_toml_table	*toml;
	int				fd;
	t_toml_error	err;
	char			buffer[4096];

	if (argc != 2)
	{
		printf("Usage: %s [scene.toml]\n", argv[0]);
		return (1);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		printf("Error Invalid file\n");
		return (1);
	}
	r = create_reader(fd, buffer, sizeof(buffer));
	if ((err = read_toml(&r, &toml, true)) != NO_ERROR)
	{
		printf("Error<%zu:%zu>: %d\n", r.line, r.column, err);
		return (1);
	}
	close(fd);
	render_scene(toml);
	return (0);
}
