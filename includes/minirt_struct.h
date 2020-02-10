# ifndef MINIRT_STRUCT_H
#define MINIRT_STRUCT_H

typedef struct 	s_resolution
{
	int			x;
	int			y;
}				t_resolution;

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct 	s_amblight
{
	float		ratio;
	t_color		color;
	
}				t_amblight;

typedef struct	s_coord
{
	float		x;
	float		y;
	float		z;
}				t_coord;

typedef	struct 	s_camera
{
	t_coord		coord;
	t_coord		vect;
	int			fov;
}				t_camera;

typedef	struct	s_light_or_sphere
{
	char		*name;
	t_coord		coord;
	float		r;
	t_color		color;
}				t_lignt_or_sphere;

typedef	struct	s_plane
{
	char		*name;
	t_coord		coord;
	t_coord		vect;
	t_color		color;
}				t_plane;

typedef	struct	s_square
{
	char		*name;
	t_coord		coord;
	t_coord		vect;
	float		height;
	t_color		color;
}				t_square;

typedef	struct	s_cylinder
{
	char		*name;
	t_coord		coord;
	t_coord		vect;
	float		diam;
	float		height;
	t_color		color;
}				t_cylinder;

typedef	struct	s_triangle
{
	char		*name;
	t_coord		fstpoint;
	t_coord		sndpoint;
	t_coord		trdpoint;
}				t_triangle;

/*On test avec une struct de liste chainee*/

typedef	struct		s_minirt
{
	t_resolution	reso;
	t_amblight		alight;
	t_list			*cam;
	t_list			*obj;
}					t_minirt;

#endif
