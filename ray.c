/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:37:39 by jsaintho          #+#    #+#             */
/*   Updated: 2024/09/10 14:32:06 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_ray	ray_new(t_v3 origin, t_v3 d)
{
	t_ray	r;

	r.origin = origin;
	r.dir = d;
	return (r);
}

int	color(double r_, double g_, double b_)
{
	int	r = (int)(255.999 * r_);
	int g = (int)(255.999 * g_);
	int b = (int)(255.999 * b_);

	int	c = r;
	c = (c << 8) | g;
	c = (c << 8) | b;
	// return (c);
	return (r* 256*256) + (g * 256) + b;
}

// =============================
//			RAY_COLOR
// ============================
int	ray_color(t_ray r, t_hit *hit, bool t)
{
	double	a;
	t_v3	n;
	t_v3	unit_dir;

	if(t) // OBJECT
	{
		//n = unit_vector(v3_new(point_at(r, hit->t).x, point_at(r, hit->t).y, point_at(r, hit->t).z - - 1.0));
		n = hit->normal;
		free(hit);
		return color( (n.x+1.0) * 0.5, (n.y+1.0) * 0.5, (n.z+1.0) * 0.5); 
	}
	else // SKY
	{
		free(hit);
		unit_dir = unit_vector(r.dir);
		a = 0.5 * (unit_dir.y + 1.0);
		return (
				color(1.0 * (1.0-a), 1.0 * (1.0-a), 1.0 * (1.0-a)) // WHITE
				+ color(0.5 * a, 0.7 * a, 1.0 * a) // BLUE
		);
	}
}


// ==============================================
//					THROW RAY
// ==============================================
// - Goes through each obj of the scene
// - Stops at closest ray hit.
// - => returns a color32
// PLANE : plane color
// SPHERE : v3(x * a, y * a, z * a)
// BACKGROUND : blendedValue = (1 - a) * startValue + a * endValue
int	throw_ray(t_ray r, t_scene *s)
{	
	t_hit	*hit;
	int		i;
	bool	t; // HIT RES
	bool	b = false;
	double	*ray_tmin = (double *) malloc(1 * sizeof(double));
	double	*ray_tmax = (double *) malloc(1 * sizeof(double));

	*ray_tmin = 0.0;
	*ray_tmax = FLT_MAX;
	i = 0;
	t = false;
	hit = (t_hit *) malloc(1 * sizeof(t_hit));
	while (s->objs[i]) // each objs of scene
	{
		if(strcmp(s->objs[i]->id, ".") == 0) break ;
		
		// SPHERE
		if(strcmp(s->objs[i]->id, "sph") == 0)
		{	
			t = sphere(r, hit, s->objs[i], ray_tmin, ray_tmax);
		} 
	
		// PLANE
		// CYLINDER
		// CUBE
		if(t) b = true;
		i++;
	}
	free(ray_tmin); free(ray_tmax);	
	return (ray_color(r, hit, b));
}
