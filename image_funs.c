#include "fractol.h"

void	mand_check(t_poly *f)
{
	if (f->type == 'M')
	{
		f->re_c = f->re_z;
		f->im_c = f->im_z;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_rgb(float r, float g, float b, int type)
{
	if (type == 1)
	{
		r = 235 * powf(r, 6.7) / (powf(0.47, 6.7) + powf(r, 6.7));
		g = 266 * powf(g, 2.6) / (powf(0.3, 2.6) + powf(g, 2.6));
	}
	else
	{
		g = 235 * powf(r, 6.7) / (powf(0.47, 6.7) + powf(r, 6.7));
		r = 266 * powf(g, 2.6) / (powf(0.3, 2.6) + powf(g, 2.6));
	}
	b = 16 + 5000 * powf(b, 2) - 18000 * powf(b, 3) + 21000
		* powf(b, 4) - 8000 * powf(b, 5);
	return ((int)(ceilf(r)) << 16 | (int)(ceilf(g)) << 8 | (int)(ceilf(b)));
}

/*
123: left
124: right
125: down
126: up
*/
int	key_handler(int keycode, void *arr)
{
	if (keycode == 53)
	{
		mlx_destroy_window (((t_point *)arr)->mlx, ((t_point *)arr)->mlx_win);
		exit (0);
	}
	if (keycode == 123)
		((t_point *)arr)->f_m->xm += 0.1;
	else if (keycode == 124)
		((t_point *)arr)->f_m->xm -= 0.1;
	else if (keycode == 125)
		((t_point *)arr)->f_m->ym -= 0.1;
	else if (keycode == 126)
		((t_point *)arr)->f_m->ym += 0.1;
	calc_color(((t_point *)arr)->f_m, ((t_point *)arr)->data_m, (t_point *)arr);
	return (0);
}

/*
1: left click
4: zoomin
5: away zoomout
*/
int	mouse_handler(int button, int x, int y, void *arr)
{
	if (button == 4 || button == 5)
	{
		if (button == 4)
			((t_point *)arr)->f_m->zoom *= 2;
		else
			((t_point *)arr)->f_m->zoom /= 2;
		((t_point *)arr)->f_m->xm += (x - ((t_point *)arr)->data_m->wid / 2)
			/ fmin(((t_point *)arr)->data_m->wid / 2,
				((t_point *)arr)->data_m->hig / 2)
			/ ((t_point *)arr)->f_m->zoom * 2;
		((t_point *)arr)->f_m->ym += (y - ((t_point *)arr)->data_m->hig / 2)
			/ fmin(((t_point *)arr)->data_m->wid / 2,
				((t_point *)arr)->data_m->hig / 2)
			/ ((t_point *)arr)->f_m->zoom * 2;
		calc_color(((t_point *)arr)->f_m, ((t_point *)arr)->data_m,
			(t_point *)arr);
	}
	return (0);
}
