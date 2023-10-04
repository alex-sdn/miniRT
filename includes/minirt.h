/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asadanow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:35:47 by asadanow          #+#    #+#             */
/*   Updated: 2023/05/16 14:35:48 by asadanow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# define ERR_ARGC "Please add one scene as argument."
# define ERR_NAME "Wrong file type requested."
# define ERR_MLX "MLX failed during window creation."
# define ERR_MALLOC "Memory allocation failed."
# define ERR_PARSING "Error during parsing."
# define ERR_CLA "Wrong amount of camera / light / ambient."

typedef struct s_vec {
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef struct s_ray {
	t_vec	origin;
	t_vec	dir;
}			t_ray;

typedef struct s_camera {
	t_vec	pos;
	t_vec	orientation;
	double	fov;
	double	aspect_ratio;
	double	screen_h;
	double	screen_w;
	t_vec	horizontal;
	t_vec	vertical;
	t_vec	ll_corner;
	t_vec	w;
	t_vec	u;
	t_vec	v;
}			t_camera;

typedef struct s_ambient {
	double	brightness;
	t_vec	color;
}			t_ambient;

typedef struct s_light {
	t_vec	pos;
	double	brightness;
}			t_light;

typedef struct s_hit {
	double	t;
	t_vec	poi;
	t_vec	normal;
	t_vec	color;
}			t_hit;

typedef struct s_sphere {
	t_vec	center;
	double	r;
	t_vec	color;
}			t_sphere;

typedef struct s_plane {
	t_vec	coord;
	t_vec	normal;
	t_vec	color;
}			t_plane;

typedef struct s_cylinder {
	t_vec	center;
	t_vec	axis;
	double	r;
	double	h;
	t_vec	color;
}			t_cylinder;

typedef struct s_scene {
	t_camera	camera;
	t_ambient	ambient;
	t_light		light;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
	int			count_cla[3];
}				t_scene;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_vars {
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_wh[2];
	t_scene	scene;
}			t_vars;

/**  MAIN  **/
void	create_img(t_vars *vars);
int		main(int ac, char **av);

/**  HOOKS  **/
int		key_hook(int keycode, t_vars *vars);

/**  CHECK HITS  **/
t_hit	check_hits(t_ray ray, t_scene scene);
int		check_shadow(t_vec origin, t_vec dir, t_scene scene);

t_hit	hit_sphere(t_ray ray, double lowest, t_sphere sphere);
double	sphere_distance(t_ray ray, t_sphere sphere);

t_hit	hit_cylinder(t_ray ray, double lowest, t_cylinder cylinder);
double	cylinder_distance(t_ray ray, t_cylinder cylinder);

t_hit	hit_plane(t_ray ray, double lowest, t_plane plane);
double	plane_distance(t_ray ray, t_plane plane);

/**  LIGHTS  **/
t_vec	get_color_ambnt(t_ambient ambient, t_vec object_color);
t_vec	get_color_spot(t_vec color, double brightness, double light_int);
t_vec	sum_lights(t_vec color);

/**  VEC MATH  **/
t_vec	create_vec(double x, double y, double z);
double	get_len_vec(t_vec vec);
t_vec	addition(t_vec vec1, t_vec vec2);
t_vec	subtraction(t_vec vec1, t_vec vec2);
t_vec	multiplication(t_vec vec, double num);
t_vec	unit(t_vec vec);
double	dot_product(t_vec vec1, t_vec vec2);
t_vec	cross_product(t_vec vec1, t_vec vec2);
t_vec	matrix_multiplication(t_vec og, t_vec matrix[3]);
t_ray	relative_ray(t_ray ray, t_vec real_axis);

/**  PARSING  **/
t_scene	get_scene(char *file, double aspect_ratio);
t_scene	set_camera(t_scene scene, char **data, int fd);
t_scene	set_light(t_scene scene, char **data, int fd);
t_scene	set_ambient_light(t_scene scene, char **data, int fd);
t_scene	set_sphere(t_scene scene, char **data, int fd);
t_scene	set_plane(t_scene scene, char **data, int fd);
t_scene	set_cylinder(t_scene scene, char **data, int fd);

/**  UTILS PARSING  **/
double	ft_atod(char *str);
int		is_valid_double(char *str);
int		is_spaces(char *str);

int		check_type(char **data, char *type, int nb_elements);
int		is_valid_rgb(char **tab);
t_vec	fill_color(char **data, char *str, t_scene scene, int fd);
int		is_valid_vec(char **tab);
t_vec	fill_vec(char **data, char *str, t_scene scene, int fd);

int		ft_tab_size(char **tab);
void	free_tab(char **tab);
t_list	*init_list(void *content);
t_scene	init_scene(void);
void	error_parsing(t_scene scene, char **data, int fd, char *msg);

/**  UTILS  **/
void	error_exit(void *ptr, char *msg);
void	free_objects(t_scene scene);
void	ft_del(void *content);
double	clamp_min(double t);
int		check_unit(t_vec vec);

int		win_close(t_vars *vars, int error);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_trgb(int t, int r, int g, int b);

/**  GNL  **/
char	*ft_strcat(char *dest, char *src);
void	*ft_exit_error(char **str);
void	*ft_exit_error_duo(char **str1, char **str2);
int		ft_check_line(ssize_t rd, char *str);
char	*ft_dupcat(char *dest, char *src);
char	*ft_dup_line(char *str);
char	*ft_remove_line(char *save);
char	*get_next_line(int fd);

#endif
