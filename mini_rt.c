/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:37:14 by jsaintho          #+#    #+#             */
/*   Updated: 2024/08/26 17:39:26 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
// https://raytracing.github.io/books/RayTracingInOneWeekend.html


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
	printf("Initalized  [Window : %dx%d] [Viewport %d:%d] \n", WIDTH, HEIGHT, 
			t->rt_scene->viewport_width, t->rt_scene->viewport_height);
	//mlx_hook(t->win, 2, 1L << 0, k_hook, t);
	mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
	mlx_loop(t->mlx);
	return (0);
}
