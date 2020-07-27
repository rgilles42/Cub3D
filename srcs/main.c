/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 12:36:18 by rgilles           #+#    #+#             */
/*   Updated: 2020/07/24 12:36:20 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <cub3d.h>

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*win;
	t_params	params;

	if (argc == 2)
	{
		mlx = mlx_init();
		params = parse_file(argv[1]);
		ft_printf("X = %d\n",params.res_x);
		ft_printf("Y = %d\n",params.res_y);
		win = mlx_new_window(mlx, params.res_x, params.res_y, "Hello world!");
		mlx_loop(mlx);
	}
	return (0);
}