/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grezette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 15:55:40 by grezette          #+#    #+#             */
/*   Updated: 2020/02/16 15:59:01 by grezette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCT_H
# define MINIRT_STRUCT_H

enum					e_objects
{
						LIGHT,
						SPHERE,
						PLANE,
						SQUARE,
						CYLINDER,
						TRIANGLE
};

typedef struct			s_resolution
{
	int					x;
	int					y;
}						t_resolution;

typedef struct			s_color
{
	int					red;
	int					green;
	int					blue;
}						t_color;

typedef struct			s_amblight
{
	float				ratio;
	t_color				color;
}						t_amblight;

typedef struct			s_coord
{
	float				x;
	float				y;
	float				z;
}						t_coord;

typedef	struct			s_camera
{
	t_coord				coord;
	t_coord				vect;
	int					fov;
}						t_camera;

typedef	struct			s_square
{
	t_coord				vect;
	float				height;
}						t_square;

typedef	struct			s_cylinder
{
	t_coord				vect;
	float				diam;
	float				height;
}						t_cylinder;

typedef	struct			s_triangle
{
	t_coord				sndpoint;
	t_coord				trdpoint;
}						t_triangle;

typedef	struct			s_union
{
	//le r c'est pour le diametre/ration de la sphere ou de la light
	float				r;
	// Le plane c'est pour le vecteur du plane;
	t_coord				plane;
	t_square			square;
	t_cylinder			cylinder;
	t_triangle			triangle;
}						t_union;

typedef struct			s_object
{
	int					type;
	t_coord				coord;
	t_color				color;
	t_union				*obj;
	//rajouter un pointeur sur fonction
}						t_object;

typedef	struct			s_minirt
{
	t_resolution		reso;
	t_amblight			alight;
	t_list				*cam;
	t_list				*obj;
}						t_minirt;

#endif
