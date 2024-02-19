/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:57:54 by ggiertzu          #+#    #+#             */
/*   Updated: 2024/01/26 22:29:41 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <math.h>
# include <MLX42/MLX42.h>
# include <ft_printf.h>
# define WIDTH 1024
# define HEIGHT 1024
# define THRESH 4
# ifndef MAXRUNS
#  define MAXRUNS 100 
# endif

typedef double	(*t_f)(double *input1, double *input2);

typedef struct limits_s
{
	mlx_t		*window;
	mlx_image_t	*img;
	int			type;
	int			cmap;
	double		c[2];
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
	double		dx;
	double		dy;
}	t_limits;

typedef struct input_s
{
	int	type;
	int	julia;
	int	cmap;
	int	success;
}	t_input;

t_limits	init_lim(mlx_t *mlx, mlx_image_t *img, t_input input);
int			get_steps(int i, int j, t_limits lim);
void		draw_image(mlx_image_t *img, t_limits lim);
void		move_view(void *input);
void		zoom_hook(double xdelta, double ydelta, void *param);
void		put_error(int code);
t_input		check_input(int32_t argc, const char *argv[]);
#endif
