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
    game->map.map_size = size;
    i = -1;
	while (tmp)
	{
		game->map.map[++i] = tmp->content;
		tmp = tmp->next;
	}
    // if(check_map(game) != 0)
    //     return (-1);
    return (0);
}

static int    get_resolution(t_game *game)
{
    char *str;
    char *tmp;
    str = game->param->content;

    if (check_identifer(str, "R "))
    {
        str++;
        if (ft_atoi(str) > 1)
            game->mlx.win_width = ft_atoi(str);
        else
            return (-1);
        tmp = ft_itoa(game->mlx.win_width);
        str += ft_strlen(tmp) + 1;
        free(tmp);
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
    if (check_identifer(game->param->content, "NO "))
        game->map.no_tex = game->param->content + 3;
    else
        return (-1);
    game->param = game->param->next;
    if (check_identifer(game->param->content, "SO "))
        game->map.so_tex = game->param->content + 3;
    else
        return (-1);
    game->param = game->param->next;
    if (check_identifer(game->param->content, "WE "))
        game->map.we_tex = game->param->content + 3;
    else
        return (-1);
    game->param = game->param->next;
    if (check_identifer(game->param->content, "EA "))
       game->map.ea_tex = game->param->content + 3;
    else
        return (-1);
    return (0);
}

void    get_param(t_game *game)
{
    // char *str = NULL;
    error(get_resolution(game), 'R', game);
    error(get_texpack(game), 'T', game);
    error(get_sprite_tex(game), 'S', game);
    error(get_floor_color(game), 'F', game);
    error(get_ceiling_color(game), 'C', game);
    game->param = game->param->next;
    game->param = game->param->next;
    error(get_map(game), 'M', game);
}