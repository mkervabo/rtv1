/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkervabo <mkervabo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:37:04 by mkervabo          #+#    #+#             */
/*   Updated: 2019/04/29 15:27:43 by mkervabo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_ray	camera_create_ray(t_vec3 camera, int x, int y)
{
	t_ray ray;

		ray = (t_ray) {
			.origin = camera,
			.direction = vec3_unit((t_vec3){
				.x = ((x + 0.5) / SCREEN_X - 0.5) * 2,
				.y = ((y + 0.5) / SCREEN_Y - 0.5) * SCREEN_Y / SCREEN_X * 2,
				.z = -1
			})
		};
	return (ray);
}
