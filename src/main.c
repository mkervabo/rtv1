/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:39:35 by mkervabo          #+#    #+#             */
/*   Updated: 2019/05/22 12:07:49 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "toml.h"
#include <fcntl.h>
#include <unistd.h>

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
