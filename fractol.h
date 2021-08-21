#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		wid;
	int		hig;
}				t_data;

typedef struct s_poly {
	float	re_c;
	float	im_c;
	float	re_z;
	float	im_z;
	float	radius;
	float	miter;
	char	type;
	float	xm;
	float	ym;
	float	zoom;
	int		ct;
}				t_poly;

typedef struct s_point {
	void	*mlx;
	void	*mlx_win;
	t_poly	*f_m;
	t_data	*data_m;
}			t_point;

int		ft_atoi(const char *str);
double	ft_atof(const char *str);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		create_rgb(float r, float g, float b, int type);
int		key_handler(int keycode, void *param);
int		mouse_handler(int button, int x, int y, void *param);
void	calc_color(t_poly *f, t_data *data, t_point *arr);
void	mand_check(t_poly *f);

#endif
