#include "cub3d.h"

static void get_map(t_game *game)
{
    int size;
    t_list *tmp;
    int i;

    tmp = game->param;
    size = ft_lstsize(game->param);
    game->map.map = ft_calloc(size + 1, sizeof(char *));
    i = -1;
	while (tmp)
	{
		game->map.map[++i] = tmp->content;
		tmp = tmp ->next;
	}
}

static void    get_resolution(t_game *game)
{
    char *str;
    str = game->param->content;
    if (*str == 'R')
    {
        while(!ft_isdigit(*(++str)))
        game->mlx.win_hight = ft_atoi(str);
        str = str + ft_strlen(ft_itoa(game->mlx.win_hight));
        game->mlx.win_width = ft_atoi(str);
    }
    str = game->param->content;
    while(*str != 'M')
    {
        game->param = game->param->next;
        str = game->param->content;
    }
    game->param = game->param->next;
}

void    get_param(t_game *game)
{
    get_resolution(game);
    get_map(game);
}