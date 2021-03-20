#include "cub3d.h"

static int get_map(t_game *game)
{
    int size;
    t_list *tmp;
    int i;

    tmp = game->param;
    while (tmp->next)
    {
        if(check_identifer(tmp->content, "C ") == 1)
        {
            tmp = tmp->next;
            break;
        }
        tmp = tmp->next;
    }
    size = ft_lstsize(tmp);
    if(!(game->map.map = ft_calloc(size + 1, sizeof(char *))))
        return (-1);
    game->map.map_size = size;
    i = -1;
	while (tmp)
	{
		game->map.map[++i] = tmp->content;
		tmp = tmp->next;
	}
    if(check_map(game) != 1)
        return (-1);
    return (0);
}

static int    get_resolution(t_game *game)
{
    char *str;
    char *tmp;
    t_list *list;

    list = game->param;
    while (list->next)
    {
        if (check_identifer(list->content, "R ") == 1)
        {   
            str = list->content;
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
            break;
        }
        else
            list = list->next;
    }
    game->param = game->param->next;
    return (0);
}

static int get_texpack(t_game *game)
{
    t_list *list;

    list = game->param;
    while(list->next)
    {
        if (check_identifer(list->content, "NO ") == 1)
            game->map.no_tex = list->content + 3;
        // else
        //     return (-1);
        // game->param = game->param->next;
        if (check_identifer(list->content, "SO ") == 1)
            game->map.so_tex = list->content + 3;
        // else
        //     return (-1);
        // game->param = game->param->next;
        if (check_identifer(list->content, "WE ") == 1)
            game->map.we_tex = list->content + 3;
        // else
        //     return (-1);
        // game->param = game->param->next;
        if (check_identifer(list->content, "EA ") == 1)
            game->map.ea_tex = list->content + 3;
        // else
        //     return (-1);
        list = list->next;
    }
    return (0);
}

static int find_param(t_list *tmp, char *str)
{
    int i = 0;
    while (tmp->next)
    {
        if (check_identifer(tmp->content, str) == 1)
            i++;
        tmp = tmp->next;
    }
    return (i);
}

static int find_params(t_game *game)
{
    t_list *tmp;

    tmp = game->param;
    if (find_param(tmp, "R ") != 1)
        error(-1, 'R', game);
    if (find_param(tmp, "NO ") != 1)
        error(-1, 'T', game);
    if (find_param(tmp, "SO ") != 1)
        error(-1, 'T', game);
    if (find_param(tmp, "WE ") != 1)
        error(-1, 'T', game);
    if (find_param(tmp, "EA ") != 1)
        error(-1, 'T', game);
    if (find_param(tmp, "S ") != 1)
        error(-1, 'S', game);
    if (find_param(tmp, "F ") != 1)
        error(-1, 'F', game);
    if (find_param(tmp, "C ") != 1)
        error(-1, 'C', game);
    return (1);
}

void    get_param(t_game *game)
{
    find_params(game);
    error(get_resolution(game), 'R', game);
    error(get_texpack(game), 'T', game);
    error(get_sprite_tex(game), 'S', game);
    error(get_floor_color(game), 'F', game);
    error(get_ceiling_color(game), 'C', game);
    error(get_map(game), 'M', game);
}