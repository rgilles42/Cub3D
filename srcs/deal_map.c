/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgilles <rgilles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 17:08:39 by rgilles           #+#    #+#             */
/*   Updated: 2020/09/01 17:08:40 by rgilles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void		trim_map_y(t_params *params)
{
	int		highest;
	int		lowest;
	int		i;

	highest = 0;
	while (params->map[highest] && !ft_strchr(params->map[highest], '1'))
		highest++;
	lowest = 0;
	while (params->map[lowest])
		lowest++;
	lowest--;
	while (lowest >= 0 && params->map[lowest] && !ft_strchr(params->map[lowest], '1'))
		lowest--;
	if (highest > 0 && lowest > highest)
	{
		i = 0;
		while (i < highest)
			free(params->map[i++]);
		while (i <= lowest)
		{
			params->map[i - highest] = params->map[i];
			i++;
		}
		while (i <= lowest + highest)
		{
			params->map[i - highest] = NULL;
			i++;
		}
	}
	else
		i = lowest + highest + 1;
	while (params->map[i - highest])
	{
		free(params->map[i - highest]);
		params->map[i - highest] = NULL;
		i++;
	}
	params->map_y = lowest - highest + 1;
}

void		trim_map_x(t_params *params)
{
	int		i;
	int		j;
	int		leftest;
	int		rightest;
	char	*defausse;

	i = 0;
	leftest = 1000;
	while (params->map[i])
	{
		j = 0;
		while (params->map[i][j] && params->map[i][j] != '1')
			j++;
		if (j < leftest)
			leftest = j;
		i++;
	}
	i = 0;
	rightest = 0;
	while (params->map[i])
	{
		j = ft_strlen(params->map[i]) - 1;
		while (j >= 0 && params->map[i][j] != '1')
			j--;
		if (j > rightest)
			rightest = j;
		i++;
	}
	i = 0;
	while (params->map[i])
	{
		defausse = params->map[i];
		params->map[i++] = ft_substr(defausse, leftest, rightest - leftest + 1);
		free(defausse);
	}
	params->map_x = rightest - leftest + 1;
}

void		check_line(t_params *params, char **line)
{
	int	len;

	len = ft_strlen(*line);
	while (--len >= 0)
		if (!(params->err) && (!(ft_strchr(" 012NSEW", (*line)[len]))))
			params->err = ft_strdup("Map invalid !\n");
}

void		deal_map(t_params *params, char **line, int fd)
{
	int		i;
	char	**splt;

	check_line(params, line);
	params->map = (char**)malloc(sizeof(char*));
	params->map[0] = ft_strdup(*line);
	free(*line);
	get_next_line(fd, line);
	check_line(params, line);
	splt = ft_split(*line, ' ');
	i = 1;
	while (splt[0] != NULL && (ft_isdigit(splt[0][0]) || splt[0][0] == ' ') && (i++))
	{
		params->map = ft_realloc(params->map, (i - 1) * sizeof(char*), i * sizeof(char*));
		params->map[i - 1] = ft_strdup(*line);
		free_split(splt);
		free(*line);
		get_next_line(fd, line);
		check_line(params, line);
		splt = ft_split(*line, ' ');
	}
	free_split(splt);
	params->map = ft_realloc(params->map, i * sizeof(char*), (i + 1) * sizeof(char*));
	params->map[i] = NULL;
	free(*line);
	while (get_next_line(fd, line))
		free (*line);
	trim_map_y(params);
	trim_map_x(params);
}
