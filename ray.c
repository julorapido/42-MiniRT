/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:37:39 by jsaintho          #+#    #+#             */
/*   Updated: 2024/09/02 15:42:46 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_ray	ray_constructor(t_v3 origin, t_v3 d)
{
	t_ray	r;

	r.origin = origin;
	r.dir = d;
	return (r);
}

int	color(double r_, double g_, double b_)
{
	//int r = 255 * r_, g = 255 * g_, b = 255 * b_;
	int	r = (int)(255.999 * r_);
	int g = (int)(255.999 * g_);
	int b = (int)(255.999 * b_);

	int	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	// return (c);
	return (r* 256*256) + (g * 256) + b;
}


// ==============================================
//					RAY COLOR
// ==============================================
// blendedValue = (1 - a) * startValue + a * endValue
int	ray_color(t_ray r)
{
	t_v3	unit_dir;
	double	a;
	
	double t = sphere(v3_constructor(0,0, -1.0), r);

	if(t > 0.0) // sphere hit
	{
		t_v3 n = unit_vector(v3_constructor(point_at(r, t).x, point_at(r, t).y, point_at(r, t).z - - 1.0));
		return color( (n.x+1.0) * 0.5, (n.y+1.0) * 0.5, (n.z+1.0) * 0.5); 	
	}
	else // not sphere hit
	{
		unit_dir = unit_vector(r.dir);
		a = 0.5 * (unit_dir.y + 1.0);
		return (
				color(1.0 * (1.0-a), 1.0 * (1.0-a), 1.0 * (1.0-a)) // WHITE
				+
				color(0.5 * a, 0.7 * a, 1.0 * a) // BLUE
		);
	}
}
