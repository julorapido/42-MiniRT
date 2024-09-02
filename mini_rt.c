/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:37:14 by jsaintho          #+#    #+#             */
/*   Updated: 2024/09/02 17:44:19 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
// https://raytracing.github.io/books/RayTracingInOneWeekend.html

static void	init_scene(t_MiniRT *t)
{
	t_obj	*scene_objects;

	if(!t->rt_scene)
		return ;
	scene_objects = (t_obj *) malloc(2 * sizeof(t_obj));
	if(!scene_objects)
		return ;

	// 1st Sphere
	scene_objects[0].id = "sy";
	scene_objects[0].pos =  v3_constructor(0, 0, -1);
	scene_objects[0].diameter = 0.5;

	scene_objects[1].id = NULL;
}

int main(int argc, char **argv)
{
	t_MiniRT	*t;
	int			c;

	if(argc != 2)
		return (0);
	t = (t_MiniRT *) malloc(sizeof(t_MiniRT));
	t->rt_scene = (t_scene *) malloc(sizeof(t_scene));
	if (!t || !t->rt_scene)
		return (0);
	c = init_renderer(t);
	if (!c)
	{
		clean_exit(t);
		return (0);
	}
	init_scene(t);
	mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
	mlx_loop(t->mlx);
	return (0);
}
