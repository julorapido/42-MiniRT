/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:10:02 by jsaintho          #+#    #+#             */
/*   Updated: 2024/09/10 12:49:24 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float rand_float(float min, float max)
{
   return ((max - min) * ((float)rand() / RAND_MAX)) + min;
}

t_v3	v3_new(double x, double y, double z)
{
	t_v3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.len = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return (v);
}

t_v3	v3_random(double min, double max)
{
	return (v3_new(rand_float(min, max), rand_float(min, max), rand_float(min, max)));
}

t_v3	v3_cross(t_v3 a, t_v3 b)
{
	return (v3_new( 
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z), 
		(a.x * b.y) - (a.y * b.x)
	));
}

t_v3	v3_mult(t_v3 a, t_v3 b)
{
	return (v3_new(
		a.x * b.x, a.y * b.y, a.z * b.z
	));
}

t_v3	v3_add(t_v3 a, t_v3 b)
{
	return (v3_new(
		a.x + b.x, a.y + b.y, a.z + b.z
	));
}

t_v3	point_at(t_ray ray, double t)
{
	return (v3_add(ray.origin, 
			v3_new(ray.dir.x * t, ray.dir.y * t, ray.dir.z * t)
		)
	);
}

t_v3	unit_vector(t_v3 v)
{
	return (v3_new(v.x / v.len, v.y / v.len , v.z / v.len));
}

t_v3	rand_unit_vector(void)
{
	t_v3	p;
	double	len_sq;
	
	while(true)
	{
		p = v3_random(-1, 1);
		len_sq = p.len * p.len;
		if (len_sq <= 1 && 1e-160 < len_sq)
			return v3_new(
				p.x / sqrt(len_sq), p.y / sqrt(len_sq), p.z / sqrt(len_sq)
			);
	}
}

t_v3	rand_on_hemisphere(t_v3 normal)
{
	t_v3	on_unit_sphere = unit_vector(rand_unit_vector());

	if(v3_dot(on_unit_sphere, normal) > 0.0)
		return (on_unit_sphere);
	else
		return (v3_new(-1 * on_unit_sphere.x, -1 * on_unit_sphere.y, -1 * on_unit_sphere.z));
}

double	v3_dot(t_v3 a, t_v3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

