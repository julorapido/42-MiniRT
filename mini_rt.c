/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:37:14 by jsaintho          #+#    #+#             */
/*   Updated: 2024/09/04 17:49:36 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
// https://raytracing.github.io/books/RayTracingInOneWeekend.html

//  ========= SCENE ==========
// {SPHERE, PLANE}
//
static void	init_scene(t_MiniRT *t)
{
	t_obj	**scene_objects;

	if(!t->rt_scene)
		return ;
	scene_objects = (t_obj **) malloc(sizeof(t_obj *));
	if(!scene_objects)
		return ;

	// 1st Sphere
	*scene_objects = (t_obj *) malloc(sizeof(t_obj ));
	(*scene_objects)->id = "sph";
	(*scene_objects)->pos =  v3_new(0, 0, -1);
	(*scene_objects)->radius = 0.5;

	scene_objects[1] = (t_obj *) malloc(sizeof(t_obj ));
	scene_objects[1]->id = "sph";
	scene_objects[1]->pos =  v3_new(0, -100.5, -1);
	scene_objects[1]->radius = 100.0;

	scene_objects[2] = (t_obj *) malloc(sizeof(t_obj ));
	scene_objects[2]->id = ".";
	t->rt_scene->objs = scene_objects;

	printf("============== SCENE ==============\n");
	int i = 0;
	while(t->rt_scene->objs[i]->id[0] != '.')
	{
		t_obj	*o = t->rt_scene->objs[i];
		printf("%s: POS[%.2f, %.2f, %.2f] RADIUS[%.2f]\n", o->id, o->pos.x, o->pos.y, o->pos.z, o->radius);
		i++;
	}
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
	init_viewport(t);
	init_scene(t);
	render(t);
	mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
	mlx_loop(t->mlx);
	return (0);
}
