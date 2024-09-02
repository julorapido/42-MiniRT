/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:10:02 by jsaintho          #+#    #+#             */
/*   Updated: 2024/09/02 15:42:58 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


t_v3	v3_constructor(double x, double y, double z)
{
	t_v3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.len = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
	return (v);
}

t_v3	v3_cross(t_v3 a, t_v3 b)
{
	return (v3_constructor( 
		(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z), 
		(a.x * b.y) - (a.y * b.x)
	));
}

t_v3	v3_mult(t_v3 a, t_v3 b)
{
	return (v3_constructor(
		a.x * b.x, a.y * b.y, a.z * b.z
	));
}

t_v3	v3_add(t_v3 a, t_v3 b)
{
	return (v3_constructor(
		a.x + b.x, a.y + b.y, a.z + b.z
	));
}

t_v3	point_at(t_ray ray, double t)
{
	return (v3_add(ray.origin, 
			v3_constructor(ray.dir.x * t, ray.dir.y * t, ray.dir.z * t)
		)
	);
}

t_v3	unit_vector(t_v3 v)
{
	return (v3_constructor(v.x / v.len, v.y / v.len , v.z / v.len));
}

double	v3_dot(t_v3 a, t_v3 b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}
