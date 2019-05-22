/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:06:53 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/22 12:07:37 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	*ft_memset(void *s, int c, size_t n)
{
	while (n--)
		((unsigned char *)s)[n] = c;
	return (s);
}

void	poll_events(t_win *window)
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

bool	init_window(t_win *window)
{
	SDL_Init(SDL_INIT_VIDEO);
	if (!(window->win = SDL_CreateWindow(window->name, SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, window->width, window->height,
			SDL_WINDOW_OPENGL))
		|| !(window->renderer = SDL_CreateRenderer(window->win, -1,
			SDL_RENDERER_ACCELERATED))
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
