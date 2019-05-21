/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:39:35 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/21 15:42:01 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "toml.h"
#include <fcntl.h>

bool	init_window(t_win *window)
{
	SDL_Init(SDL_INIT_VIDEO);
	if (!(window->win = SDL_CreateWindow(window->name, SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, window->width, window->height,
			SDL_WINDOW_OPENGL))
		|| !(window->renderer = SDL_CreateRenderer(window->win, -1, SDL_RENDERER_ACCELERATED))
		|| !(window->screen = SDL_CreateTexture(window->renderer,
			SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
			window->width, window->height)))
	{
        printf("Could not create window: %s\n", SDL_GetError());
		return (false);
	}
	return (true);
}

void	destroy_window(t_win *window)
{
	if (window->screen)
		SDL_DestroyTexture(window->screen);
	if (window->renderer)
		SDL_DestroyRenderer(window->renderer);
	if (window->win)
		SDL_DestroyWindow(window->win);
	SDL_Quit();
}

uint32_t	to_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	return (((uint32_t)r) << 16 | ((uint32_t)g) << 8 | b);
}

static void	hit_neg(uint32_t *pixel, t_ray *ray, t_scene *scene,
	t_who t)
{
	t_color color_light;
	bool	mod;

	color_light = (t_color) {
		0, 0, 0
	};
	mod = apply_light(&color_light, ray, t, scene);
	*pixel = 
		to_rgb(mod ? clamp_rgb(scene->objects[t.i]->color.r - color_light.r) : 0,
		mod ? clamp_rgb(scene->objects[t.i]->color.g - color_light.g) : 0,
		mod ? clamp_rgb(scene->objects[t.i]->color.b - color_light.b) : 0);
}

void	*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = c;
	return (s);
}

void		poll_events(t_win *window)
{
	SDL_Event	event;
	
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			window->quit = true;
		if (event.type == SDL_KEYDOWN)
			window->quit = true;
	}
}

static void	raytrace(t_scene *scene, t_cam camera, t_win *window)
{
	size_t		x;
	size_t		y;
	t_ray		ray;
	t_who		t;
	uint32_t	*pixels;

	pixels = malloc(sizeof(uint32_t) * window->width * window->height);
	ft_memset(pixels, 0, sizeof(uint32_t) * window->width * window->height);
	y = 0;
	while (y < window->height && !window->quit)
	{
		x = 0;
		while (x < window->width)
		{
			ray = camera_create_ray(&camera, x, window->height - y - 1, window);
			t = in_objects(&ray, scene->objects, scene->objects_size);
			if (t.hit.t >= 0)
				hit_neg(pixels + y * window->width + x, &ray, scene, t);
			else
				pixels[y * window->width + x] = 0;
			x++;
		}
		poll_events(window);
		SDL_UpdateTexture(window->screen, NULL, pixels,
			window->width * sizeof(uint32_t));
		SDL_RenderCopy(window->renderer, window->screen, NULL, NULL);
		SDL_RenderPresent(window->renderer);
		y++;
	}
	free(pixels);
}

void		render(t_scene *scene, t_cam camera, t_win *window)
{
	if (init_window(window))
	{
		raytrace(scene, camera, window);
		while (!window->quit)
			poll_events(window);
	}
	destroy_window(window);
}

bool	render_scene(t_toml_table *toml)
{
	t_scene			scene;
	t_cam			camera;
	t_win			window;

	ft_memset(&window, 0, sizeof(t_win));
	if (!(scene.objects = read_objects(toml, &scene.objects_size)))
		return (false);
	if (!(scene.lights = read_lights(toml, &scene.lights_size)))
		return (false);
	if (!read_camera(toml, &camera))
		return (false);
	if (!read_window(toml, &window))
		return (false);
	render(&scene, camera, &window);
	return (true);
}

int		main(int argc, char *argv[])
{
	t_reader		r;
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
