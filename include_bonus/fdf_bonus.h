/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asippy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 18:13:35 by asippy            #+#    #+#             */
/*   Updated: 2022/02/23 19:20:31 by asippy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# define BUFFER_SIZE 10000

# define DEFAULT_COLOR 0x761FA2
# define MIN_COLOR 0xFFFFFF
# define MAX_COLOR 0xAB00FF

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define ANGLE 0.005
# define ZOOM 0.04
# define WIDTH 5
# define HEIGHT 5
# define ROT 0.03
# define Z_VAL 0.01

# include <mlx.h> //graphic library
# include <math.h> //math functions
# include <stdlib.h> //functions exit, malloc, free
# include <unistd.h> //functions write, read
# include <fcntl.h> //function open
# include <string.h> //function strerror
# include <errno.h> //variable of errors - errno

typedef struct s_mlx {
	void	*mlx;
	void	*mlx_win;
}				t_mlx;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		llength;
	int		end;
}				t_img;

typedef struct s_el
{
	int				x;
	int				y;
	int				z;
	unsigned int	color;
}	t_el;

typedef struct s_map
{
	size_t		x_size;
	size_t		y_size;
	size_t		global_gradient;
	int			z_max;
	int			z_min;
	float		min_r;
	float		min_g;
	float		min_b;
	float		gr;
	float		gg;
	float		gb;
	t_el		**el;
}				t_map;

typedef struct s_conf
{
	int		menu;
	int		iso;
	float	angle;
	float	zoom;
	float	width;
	float	height;
	float	posx;
	float	posy;
	float	z;
	float	rotx;
	float	roty;
	float	rotz;
}				t_conf;

typedef struct s_data {
	t_mlx	mlx;
	t_img	img;
	t_map	map;
	t_conf	conf;
}				t_data;

typedef struct s_line
{
	float	xc;
	float	yc;
	float	xn;
	float	yn;
	float	ccr;
	float	ccg;
	float	ccb;
	float	cnr;
	float	cng;
	float	cnb;
	float	cgr;
	float	cgg;
	float	cgb;
}				t_line;

//general_utils
void			ft_display_err(const char *str);

//map and map_utils
void			ft_create_map(const char *file_name, t_map *map);
size_t			ft_find_size(char **str);
long long		ft_atoi_dec(const char *str);
unsigned int	ft_atoi_hex(const char *str);

//split
char			**split(char const *s, char c);

//get_next_line and get_next_line_utils
char			*get_next_line(int fd);
ssize_t			ft_find_line(char *buf);
char			*ft_push_all_buf(char **res, char *buf);
char			*ft_push_line(size_t lcntr, char **res, char *buf);

//global_gradient
void			ft_global_gradient_handle(t_map *map);

//mlx
void			ft_run_mlx(t_data *data);

//conf
void			ft_init_conf(t_data *data);
size_t			ft_change_conf1(int keycode, t_data *data);
size_t			ft_change_conf2(int keycode, t_data *data);
size_t			ft_change_conf3(int keycode, t_data *data);

//coordinates
void			ft_correct_coords(t_conf *conf, t_el *elem, float *x, float *y);

//draw draw_color_utils and draw_math_utils
void			ft_draw_map(t_data *data);
void			ft_gradient(int cur, int next, float length, float *res);
void			ft_change_color(t_line *line, int *color);
void			ft_put_yx_pair(t_img *img, float y, float x, int color);
void			ft_put_xy_pair(t_img *img, float x, float y, int color);
void			ft_swap(float *x, float *y);
int				ft_ipart(float x);
int				ft_round(float x);
float			ft_fpart(float x);
float			ft_rfpart(float x);

#endif