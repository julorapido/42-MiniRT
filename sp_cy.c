/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_cy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsaintho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:40:23 by jsaintho          #+#    #+#             */
/*   Updated: 2024/08/28 17:54:19 by jsaintho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

#define CENTER v3_constructor(0, 0, 0)
//#define RADIUS 0.5

double	sphere(t_ray r)
{
	t_v3	oc;
	double	a;
	double	b;
	double	c;
	double	RADIUS = 1.0;
	int		discriminant;

	oc = v3_constructor(0, 0, 2);
	// Sphere
	// x2 + y2 + z2 = r2

	// Centered Sphere
	// (Cx - x)2 + (Cy - y)2 + (Cz - z) = r2

	// Centered Sphere (Produit Scalaire)
	// P = (x, y, z) 
	// C = (Cx, Cy, Cz)
	// (C - P) • (C - P) = r2

	// a = d • d
	a = v3_dot(r.dir, r.dir);
	
	// b = -2d • (C - Q)
	b = -2.0 * v3_dot(r.dir, oc);

	// c = (C - Q) • (C - Q) - r2
	c = v3_dot(oc, oc) - RADIUS * RADIUS;

	discriminant = b*b - 4*a*c;
	if(discriminant < 0)
		return -1.0;
	else
		return  ((-b - sqrt(discriminant)) / (2.0 * a));
}
