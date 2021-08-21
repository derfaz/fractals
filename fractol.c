#include "fractol.h"

int	iter_fun(t_poly *f)
{
	int		iter;
	float	tmp;

	iter = 0;
	while (iter < f->miter)
	{
		tmp = powf(f->re_z, 2) - powf(f->im_z, 2) + f->re_c;
		f->im_z = 2.0 * f->re_z * f->im_z + f->im_c;
		f->re_z = tmp;
		if (powf(f->re_z, 2) + powf(f->im_z, 2) > powf(f->radius, 2))
			break ;
		iter++;
	}
	return (iter);
}

void	calc_color(t_poly *f, t_data *data, t_point *arr)
{
	int	x;
	int	y;
	int	iter;

	x = 0;
	while (x < data->wid)
	{
		y = 0;
		while (y < data->hig)
		{
			f->re_z = (x - data->wid / 2) / fmin(data->wid / 2, data->hig / 2)
				/ f->zoom + f->xm;
			f->im_z = (-1) * ((y - data->hig / 2) / fmin(data->wid / 2,
						data->hig / 2) / f->zoom + f->ym);
			mand_check(f);
			iter = iter_fun(f);
			my_mlx_pixel_put(data, x, y, 0x00000000
				+ create_rgb(iter / f->miter, iter / f->miter,
					iter / f->miter, f->ct));
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(arr->mlx, arr->mlx_win, data->img, 0, 0);
}

static int	check_arg_type(char *str, t_poly *f)
{
	if ((str[0] == 'J' || str[0] == 'M') && str[1] == 0)
	{
		if (str[0] == 'J')
			f->type = 'J';
		else
			f->type = 'M';
		return (1);
	}
	else
		return (0);
}

static int	check_args(int argc, char **argv, t_poly *f)
{
	if (check_arg_type(argv[1], f))
	{
		if (argc == 5 && f->type == 'J')
		{
			f->re_c = ft_atof(argv[2]);
			f->im_c = ft_atof(argv[3]);
			f->radius = (1 + sqrtf(1 + 4.0 * sqrtf(powf(f->re_c, 2)
							+ powf(f->im_c, 2)))) / 2.0;
			f->ct = ft_atoi(argv[4]);
			return (1);
		}
		if (argc == 3 && f->type == 'M')
		{
			f->radius = 2;
			f->ct = ft_atoi(argv[2]);
			return (1);
		}
	}
	printf("Invalid parameter.\n");
	printf("Enter the type: J or M, (Re_c, Im_c,) colormap.\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_point	arr;
	t_data	data;
	t_poly	f;

	if (!check_args(argc, argv, &f))
		return (0);
	data.wid = 1000;
	data.hig = 500;
	arr.mlx = mlx_init();
	arr.mlx_win = mlx_new_window(arr.mlx, data.wid, data.hig, "Fractol");
	arr.f_m = &f;
	arr.data_m = &data;
	f.miter = 100.0;
	f.zoom = 1;
	f.xm = 0;
	f.ym = 0;
	data.img = mlx_new_image(arr.mlx, data.wid, data.hig);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	calc_color(&f, &data, &arr);
	mlx_key_hook (arr.mlx_win, key_handler, &arr);
	mlx_mouse_hook(arr.mlx_win, mouse_handler, &arr);
	mlx_loop(arr.mlx);
}
