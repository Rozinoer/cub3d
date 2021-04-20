#include "cub3d.h"

int			ft_get_pxl_clr(t_data *txtr, int x, int y)
{
	int		*ptr;
	int		color;

	ptr = (void *)txtr->addr + (y * txtr->line_length + x * \
												(txtr->bits_per_pixel / 8));
	color = *(int*)ptr;
	return (color);
}

void print_back(t_game *game)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x != game->mlx.win_width)
    {
        while (y != game->mlx.win_hight)
        {
            if (y <= game->mlx.win_hight * 0.5)
                my_mlx_pixel_put(game->data, x, y, game->map.ceiling_color);
            else
                my_mlx_pixel_put(game->data, x, y, game->map.floor_color);
            y++;    
        }
        x++;
        y = 0;
    }
}

t_sprt_pos		*sprt_pos_new(int x, int y, int index)
{
	t_sprt_pos *new;

	if (!(new = (t_sprt_pos *)malloc(sizeof(t_sprt_pos))))
		return (NULL);
	if (x < 0)
		new->x = -1;
    else
        new->x = x;
    if (y < 0)
		new->y = -1;
    else
        new->y = y;
    new->index = index;
	new->next = NULL;
	return (new);
}

void	sprt_pos_add_back(t_sprt_pos **lst, t_sprt_pos *new)
{
	t_sprt_pos	*tmp;

	if (lst != NULL)
	{
		tmp = *lst;
		if (*lst == NULL)
			*lst = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
}

t_sprt_pos *get_sprite(t_game *game, int index)
{
	t_sprt_pos *tmp;

	tmp = game->sprt_pos;
	while(tmp->next != NULL)
	{
		if (tmp->index == index)
			return (tmp);
		tmp = tmp->next;
	}
	if (tmp->index == index)
		return (tmp);
	return (NULL);
}