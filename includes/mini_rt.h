/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 17:54:56 by jsaintho          #+#    #+#             */
/*   Updated: 2024/09/09 13:08:15 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H
#include "mlx.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h> 
#include <float.h>


# define WIDTH 800
# define HEIGHT 400
# define MAXFLOAT 18446744073709551615
# define RANDOM_FLOAT(min, max) ((max - min) * ((float)rand() / RAND_MAX)) + min 

//# define IMAGE_WIDTH 1080
//# define IMAGE_height int(image_width / ASPECT_RATIO) < 1 ? 1 : int(image_width / ASPECT_RATIO)
//# define VIEWPORT_HEIGHT 2.0
//# define VIEWPORT_WIDTH VIEWPORT_HEIGHT * (double(IMAGE_width)/IMAGE_height)


// ------------------------
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
typedef struct s_hit
{
	t_v3	p;
	t_v3	normal;
	double	t;
	bool	front_face;
}				t_hit;
typedef struct s_obj
{
	char	*id;
	t_v3	pos;
	int		rgb[3];
	double	radius;
}				t_obj;
// -------------------------


// -------------------------
typedef struct s_viewport
{
	int		height;
	int		width;
	int		image_w;
	int		image_h;
	t_v3	vector_u;
	t_v3	vector_v;
	double	pixel_delta_u;
	double	pixel_delta_v;

	double	focal_length;
	t_v3	upperLeft;
	t_v3	upperLeftPixel;
}				t_viewport;

typedef struct s_scene
{
	t_v3		camera;
	t_viewport	*viewport;
	t_obj		**objs;
}				t_scene;
// -------------------------



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
int		init_renderer(t_MiniRT *t);
int		clean_exit(t_MiniRT *t);
void	render(t_MiniRT *t);
void	init_viewport(t_MiniRT *t);



//  v3 (VECTORIAL MATH)
t_v3	v3_add(t_v3 a, t_v3 b);
t_v3	v3_cross(t_v3 a, t_v3 b);
t_v3 	v3_mult(t_v3 a, t_v3 b);
double	v3_dot(t_v3 a, t_v3 b);
t_v3	unit_vector(t_v3 v);
t_v3	v3_new(double x, double y, double z);
t_v3	v3_random(double min, double max);
float	rand_float(float min, float max);
t_v3	rand_unit_vector(void);
t_v3	rand_on_hemisphere(t_v3 normal);



// ray 
t_v3	point_at(t_ray ray, double t);
t_ray	ray_constructor(t_v3 origin, t_v3 d);

// SP_CY_PL
bool	sphere(t_ray r, t_hit *h, t_obj	*b, double *tmin, double *tmax);

// RAY
t_v3	point_at(t_ray ray, double t);
t_ray	ray_new(t_v3 origin, t_v3 d);
int		throw_ray(t_ray r, t_scene *s);
// int		color(double r_, double g_, double b_);


#endif
