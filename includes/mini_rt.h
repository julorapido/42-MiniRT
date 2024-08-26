/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:54:56 by jsaintho          #+#    #+#             */
/*   Updated: 2024/08/26 17:47:07 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
#include "mlx.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

# define WIDTH 1920
# define HEIGHT 1080
// # define ASPECT_RATIO 16/9

//# define IMAGE_WIDTH 1080
//# define IMAGE_height int(image_width / ASPECT_RATIO) < 1 ? 1 : int(image_width / ASPECT_RATIO)
//# define VIEWPORT_HEIGHT 2.0
//# define VIEWPORT_WIDTH VIEWPORT_HEIGHT * (double(IMAGE_width)/IMAGE_height)


typedef struct s_v3
{
	double	x;
	double	y;
	double	z;
	double	len;
}			t_v3;

typedef struct s_ray
{
	t_v3	origin;
	t_v3	dir;
}				t_ray;


typedef struct s_scene
{
	t_v3	camera;
	int		viewport_height;
	int		viewport_width;
}			t_scene;

typedef struct s_MiniRT
{
	int		*ambient_lighting;
	int		endian;
	int		bpp;
	int		linelen;
	void	*mlx;
	void	*win;
	void	*img;
	void	*buf; // pixel grid
	t_scene	*rt_scene;
}				t_MiniRT;


// RENDERER
int	init_renderer(t_MiniRT *t);
int	clean_exit(t_MiniRT *t);

//  (VECTORIAL MATH)
t_v3	point_at(t_ray *ray, double t);
t_v3	v3_add(t_v3 a, t_v3 b);
t_v3	v3_cross(t_v3 a, t_v3 b);
t_v3 	v3_mult(t_v3 a, t_v3 b);
t_v3	unit_vector(t_v3 v);
t_v3	unit_vector(t_v3 v);
t_v3	v3_constructor(int x, int y, int z);

#endif
