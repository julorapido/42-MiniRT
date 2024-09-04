/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_cy_pl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:40:23 by jsaintho          #+#    #+#             */
/*   Updated: 2024/09/04 17:17:03 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

#define CENTER v3_constructor(0, 0, 0)
//#define RADIUS 0.5
#define ray_tmin 0.0
#define ray_tmax 15.0

//	===============================================
//	||					SPHERE				 	 ||
//	===============================================
//	QUADRATIC EQUATION = ax2 + bx + c = 0
//
//	QUADRATIC FORMULA =  -b +- sqrt(b2 - 4ac)
//	QUADRATIC FORMULA = ----------------------
//	QUADRATIC FORMULA = 		2a
//
//	........ SPHERE EQUATION = x2 + y2 + c2 = r2
//  CENTERED-SPHERE EQUATION = (Cx - x)2 + (Cy - y)2 + (Cz - z)2 = r2
//
bool	sphere(t_v3 center, t_ray r, t_hit *hit, t_obj *o)
{
	t_v3	oc;
	double	a;
	double	b;
	double	c;
	double	RADIUS = o->radius;
	double	discriminant;
	double	root;

	oc = v3_new(center.x - r.origin.x, center.y - r.origin.y, center.z - r.origin.z);
	// a = d • d
	a = v3_dot(r.dir, r.dir);
	// b = -2d • (C - Q)
	b = -2.0 * v3_dot(oc, r.dir);
	// c = (C - Q) • (C - Q) - r2
	c = v3_dot(oc, oc) - RADIUS * RADIUS;

	discriminant = (b*b) - 4.0*a*c;
	if(discriminant < 0)
		return false;
	else
	{
		root = (-b - sqrt(discriminant)) / (2.0 * a);
		/*if (root <= ray_tmin || root >= ray_tmax)
		{
			root = (-b + sqrt(discriminant)) / (2.0 * a);
			if (root <= ray_tmin || root >= ray_tmax)
				return false;
		}*/
		hit->t = root;
		hit->p = point_at(r, hit->t);
		t_v3 outward_normal = v3_new(
			(hit->p.x - center.x) / RADIUS,
			(hit->p.y - center.y) / RADIUS,
			(hit->p.z - center.z) / RADIUS
		);
		hit->front_face = v3_dot(r.dir, outward_normal) < 0 ? true : false;
		hit->normal = (hit->front_face) ? 
			(outward_normal) : (v3_new(-outward_normal.x, -outward_normal.y, -outward_normal.z));
		return true;
	}
}


//	===============================================
//	||					PLANE				 	 ||
//	===============================================
double	plane()
{
	return 0.0;
}
