/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:16:04 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:16:06 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_rgb(int r, int g, int b)
{
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
		return (r << 16 | g << 8 | b);
	else
		return (-1);
}

char	*skip(char *str, int flag)
{
	if (flag == 0)
	{
		while (*str == ' ' && *str != '\0')
			str++;
		if (*str == ',')
			str++;
		else
			ft_error("Error. Bad symbols in color declaration!\n");
		
	}
	else if (flag == 1)
	{
		while (*str == ' ' && *str != '\0')
			str++;
		if (*str < '0' || *str > '9')
			ft_error("Error. Bad symbols in color declaration!\n");
	}
	else
		while (*str == ' ')
			str++;
	return (str);
}

int	check_color(char **dst, t_game *game, char c)
{
	int		r;
	int		g;
	int		b;
	int		color;

	color = -1;
	r = ft_atoi(dst[0]);
	g = ft_atoi(dst[1]);
	b = ft_atoi(dst[2]);
	color = create_rgb(r, g, b);
	if (color != -1 && c == 'F')
		game->map.floor_color = color;
	else if (color != -1 && c == 'C')
		game->map.ceiling_color = color;
	else
		return (-1);
	return (0);
}

int	check_identifer(char *str, char *iden)
{
	int		i;
	int		j;

	i = ft_strlen(iden);
	j = 0;
	while (*str == ' ')
		str++;
	while (j <= i && iden[j] != '\0')
	{
		if (str[j] != iden[j])
			return (-1);
		j++;
	}
	return (1);
}

void	allocate_memory(t_game *game)
{
	game->sprt_pos = sprt_pos_new(0, 0, -1);
	if (!(game->sprt_pos))
		ft_error("Error memory allocation\n");
	game->spr_dist = malloc(game->sprs.amount_sprt * sizeof(double));
	if (!(game->spr_dist))
		ft_error("Error memory allocation\n");
	game->spr_oder = malloc(game->sprs.amount_sprt * sizeof(int));
	if (!(game->spr_oder))
		ft_error("Error memory allocation\n");
	game->z_buff = malloc(game->mlx.win_width * sizeof(double));
	if (!(game->z_buff))
		ft_error("Error memory allocation\n");
}
