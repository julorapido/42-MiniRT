/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:57:51 by jsaintho          #+#    #+#             */
/*   Updated: 2024/08/27 18:14:09 by jsaintho         ###   ########.fr       */
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


// ======================================================
//						    RENDER
// ======================================================
int	color(double r_, double g_, double b_)
{
   	int	RGB;
	int	r,g,b;

	r = 255 * r_, g = 255 * g_, b = 255 * b_;
	RGB = (b << 16) + (g >> 8) + r;
	/*printf(
		"blue: %d red: %d green: %d = %d \n",
		(RGB & 0xFF0000) >> 16, (RGB & 0xFF), (RGB & 0xFF00) >> 8,
		RGB
	);*/
	return (RGB);
}

int	ray_color(t_ray r)
{
	t_v3	unit_dir;
	double	a;

	unit_dir = unit_vector(r.dir);
	printf("SO %d \n", unit_dir.y);
	a = 0.5 * (unit_dir.y + 1.0);
	return (
		(1.0 - a) * color(1.0, 1.0, 1.0) 
		+
		a * color(0.5, 0.7, 1.0)
	);
}


void	render(t_MiniRT *t)
{
	t_viewport *vp = t->rt_scene->viewport;

	for(int x = 0; x < 10/*vp->image_w*/; x++)
	{
		for(int y = 0; y < 10/*vp->image_h*/; y++)
		{
			t_v3 pix_center = v3_constructor(vp->upperLeftPixel.x + (x * vp->pixel_delta_u),
					vp->upperLeftPixel.y + (y * vp->pixel_delta_v), vp->upperLeftPixel.z);
			printf("%d %d %d \n", pix_center.x, pix_center.y, pix_center.z);
			// pix_center = pix_center - camera_center
			t_ray r = ray_constructor(t->rt_scene->camera, pix_center);
			set_pixel_color(t, x, y, ray_color(r));
		}
	}

	mlx_put_image_to_window(t->mlx, t->win, t->img, 0, 0);
}



// =======================================================
//					INIT SCENE
// =======================================================
void	init_scene(t_MiniRT *t)
{
	t_viewport	*vp_;

	vp_ = (t_viewport *) malloc(sizeof(t_viewport));
	t->rt_scene->camera = v3_constructor(0, 0, 0);
	if (!vp_)
		return ;
	vp_->focal_length = 1.0;
		
	// Viewport Image
	double ASPECT_RATIO = 16.0 / 9.0;
	vp_->image_w = WIDTH;
	vp_->image_h = ((int)(vp_->image_w / ASPECT_RATIO) < 1) 
			? 1 : ((int)(vp_->image_w / ASPECT_RATIO));

	// Viewport Width && Height
	vp_->height = 5.0;
	vp_->width = vp_->height * ((double)(vp_->image_w)/vp_->image_h);

	// Vector across horizontal(U) && vertical(V) viewport edges
	vp_->vector_u = v3_constructor(vp_->width, 0, 0);
	vp_->vector_v = v3_constructor(0, vp_->height, 0);

	// Detla Vectors (U-V) from pixel to pixel
	vp_->pixel_delta_u = (double)(vp_->width) / (double)(vp_->image_w);
	vp_->pixel_delta_v = (double)(vp_->height) / (double)(vp_->image_h);

	// TopLeft point v3(0, 0, 0)
	vp_->upperLeft = v3_constructor(
			-(vp_->vector_u.x / 2), -(vp_->vector_v.y / 2), -(vp_->focal_length));
	// TopLeft Pixel0,0
	vp_->upperLeftPixel =  v3_constructor(
			vp_->upperLeft.x + vp_->pixel_delta_u, vp_->upperLeft.y + vp_->pixel_delta_v, 
			vp_->upperLeft.z);

	printf(
		"SCENE [IMAGE: %dx%d] [VIEWPORT: %dx%d]  [PIXELDELTA: (U:%f V: %f)] [TOPLEFT-PIXEL : (%d,%d,%d)]\n", 
		vp_->image_w, vp_->image_h, vp_->width, vp_->height,
			vp_->pixel_delta_u, vp_->pixel_delta_v,
			vp_->upperLeftPixel.x, vp_->upperLeftPixel.y, vp_->upperLeftPixel.z
	);
	t->rt_scene->viewport = vp_;
}

//  =====================================================
//   					INIT RENDERER
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
	printf("WINDOW [%dx%d] \n", WIDTH, HEIGHT);
	init_scene(t);
	render(t);
	return (1);
}t_v3	unit_vector(t_v3 v);
