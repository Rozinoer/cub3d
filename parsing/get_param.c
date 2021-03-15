#include "cub3d.h"

static int get_map(t_game *game)
{
    int size;
    t_list *tmp;
    int i;

    tmp = game->param;
    size = ft_lstsize(game->param);
    if(!(game->map.map = ft_calloc(size + 1, sizeof(char *))))
        return (-1);
    i = -1;
	while (tmp)
	{
		game->map.map[++i] = tmp->content;
		tmp = tmp ->next;
	}
    // if(check_map(game) != 0)
    //     return (-1);
    return (0);
}

static int    get_resolution(t_game *game)
{
    char *str;

    str = game->param->content;

    if (check_identifer(str, "R"))
    {
        str++;
        if (ft_atoi(str) > 1)
            game->mlx.win_width = ft_atoi(str);
        else
            return (-1);
        str += ft_strlen(ft_itoa(game->mlx.win_width)) + 1;
        if (ft_atoi(str) > 1)
            game->mlx.win_hight = ft_atoi(str);
        else
            return (-1);
    }
    else
        return (-1);
    game->param = game->param->next;
    return (0);
}

static int get_texpack(t_game *game)
{
    char *str;

    str = game->param->content;
    if (check_identifer(str, "NO "))
        game->map.no_tex = str + 3;
    else
        return (-1);
    game->param = game->param->next;
    str = game->param->content;
    if (check_identifer(str, "SO "))
        game->map.so_tex = str + 3;
    else
        return (-1);
    game->param = game->param->next;
    str = game->param->content;
    if (check_identifer(str, "WE "))
        game->map.we_tex = str + 3;
    else
        return (-1);
    game->param = game->param->next;
    str = game->param->content;
    if (check_identifer(str, "EA "))
       game->map.ea_tex = str + 3;
    else
        return (-1);
    return (0);
}

void    get_param(t_game *game)
{
    // char *str = NULL;

    error(get_resolution(game), 'R');
    error(get_texpack(game), 'T');
    error(get_sprite_tex(game), 'S');
    error(get_floor_color(game), 'F');
    error(get_ceiling_color(game), 'C');
    game->param = game->param->next;
    game->param = game->param->next;
    get_map(game);
}