/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:57:51 by jsaintho          #+#    #+#             */
/*   Updated: 2024/08/26 17:46:50 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// ========================================
//				SET PIXEL COLOR
// ========================================
void	set_pixel_color(t_MiniRT *f, long x, long y, int c)
{
	char	*dst;
	long	offset;
	long	color;
	
	if (x < 0 || y < 0 || y > HEIGHT || x > WIDTH)
		return ;
	color = (c >> 24);
	offset = (y * f->linelen + x * (f->bpp / 8));
	dst = f->buf + (offset);
	*(unsigned int *)dst = color;
}


// =================================
//             CLEAN EXIT
// =================================
int	clean_exit(t_MiniRT *t)
{
	if (t->img)
	{
		mlx_destroy_image(t->mlx, t->img);
	}
	if (t->mlx && t->win)
	{
		mlx_loop_end(t->mlx);
		mlx_destroy_window(t->mlx, t->win);
		free(t);
		t = NULL;
	}
	exit(0);
}


// ================================
//				RENDER
// ================================
void	render(t_MiniRT *t)
{
	mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
}

//  =====================================================
//   					      INIT
//  =====================================================
//  Creates a new MLX instance, a new window and set
int	init_renderer(t_MiniRT *t)
{
	t->mlx = mlx_init();
	if (!t->mlx)
	{
		clean_exit(t);
		return (-1);
	}
	t->win = mlx_new_window(t->mlx, WIDTH, HEIGHT, "MiniRT");
	t->img = mlx_new_image(t->mlx, WIDTH, HEIGHT);	
	t->buf = mlx_get_data_addr(t->img, &t->bpp, &t->linelen, &t->endian);
	if (!t->win || !(t->img))
	{
		clean_exit(t);
		return (-1);
	}
	double ASPECT_RATIO = 16.0 / 9.0;
	int image_width = 1080;
	int image_height = (int)(image_width / ASPECT_RATIO);
	image_height = (image_height < 1) ? 1 : image_height;

	t->rt_scene->viewport_height = 4.0;
	t->rt_scene->viewport_width = t->rt_scene->viewport_height * ((double)(image_width)/image_height);
	t->rt_scene->camera = v3_constructor(0, 0, 0);
	render(t);
	return (1);
}

