#include "cub3d.h"

int get_map(t_game *game)
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
        ft_error("Error. Memory is not allocate for map!\n");
    game->map.map_size = size;
    i = -1;
	while (tmp)
	{
		game->map.map[++i] = tmp->content;
		tmp = tmp->next;
	}
    check_map(game);
    return (0);
}

int    get_resolution(t_game *game)
{
    char *tmp;
    t_list *list;

    list = game->param;
    while (list->next)
    {
        if (check_identifer(list->content, "R ") == 1)
        {   
            if (ft_atoi(++list->content) > 1)
                game->mlx.win_width = ft_atoi(list->content);
            else
                ft_error("Error. Resolution is uncorrect!\n");
            tmp = ft_itoa(game->mlx.win_width);
            list->content += ft_strlen(tmp) + 1;
            free(tmp);
            if (ft_atoi(list->content) > 1)
                game->mlx.win_hight = ft_atoi(list->content);
            else
                ft_error("Error. Resolution is uncorrect!\n");
            break;
        }
        else
            list = list->next;
    }
    return (0);
}

int get_texpack(t_game *game)
{
    t_list *list;

    list = game->param;
    while(list->next)
    {
        if (check_identifer(list->content, "NO ") == 1)
            game->map.no_tex = list->content + 3;

        if (check_identifer(list->content, "SO ") == 1)
            game->map.so_tex = list->content + 3;

        if (check_identifer(list->content, "WE ") == 1)
            game->map.we_tex = list->content + 3;

        if (check_identifer(list->content, "EA ") == 1)
            game->map.ea_tex = list->content + 3;
        if (check_identifer(list->content, "S ") == 1)
            game->map.sprite_tex = list->content + 2;

        list = list->next;
    }
    return (0);
}