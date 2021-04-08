#include "cub3d.h"

void ft_error(char *str)
{
    ft_putstr(str);
    exit(0);
}

static int find_param(t_list *tmp, char *str)
{
    int i;
    
    i = 0;
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
        ft_error("Error. R param duplicate or not found\n");
    if (find_param(tmp, "NO ") != 1)
        ft_error("Error. Texture param duplicate or not found\n");
    if (find_param(tmp, "SO ") != 1)
        ft_error("Error. Texture param duplicate or not found\n");
    if (find_param(tmp, "WE ") != 1)
        ft_error("Error. Texture param duplicate or not found\n");
    if (find_param(tmp, "EA ") != 1)
        ft_error("Error. Texture param duplicate or not found\n");
    if (find_param(tmp, "S ") != 1)
        ft_error("Error. Sprite param duplicate or not found\n");
    if (find_param(tmp, "F ") != 1)
        ft_error("Error. Floor param duplicate or not found\n");
    if (find_param(tmp, "C ") != 1)
        ft_error("Error. Ceiling param duplicate or not found\n");
    return (1);
}

void static get_param(t_game *game)
{
    find_params(game);
    get_resolution(game);
    if (game->mlx.win_width > game->mlx.monitor_width 
    || game->mlx.win_hight > game->mlx.monitor_hight)
    {
        game->mlx.win_width = game->mlx.monitor_width;
        game->mlx.win_hight = game->mlx.monitor_hight;
    }
    get_texpack(game);
    get_sprite_tex(game);
    get_floor_color(game);
    get_ceiling_color(game);
    get_map(game);
}

void parser(t_game *game, char *str)
{
	int fd;
	char *line;
	t_list *param;

	line = NULL;
	param = NULL;
	if((fd = open(str, O_RDONLY)) == -1)
		ft_error("Error. Path to the map file is invalid1\n");
	while(get_next_line(fd, &line))
	{
		ft_lstadd_back(&param, ft_lstnew(line));
	}
	ft_lstadd_back(&param, ft_lstnew(line));
	game->param = param;
	game->pointer = game->param;
	get_param(game);
}