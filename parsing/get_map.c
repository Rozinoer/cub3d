#include "cub3d.h"

static t_list *check_empty_line(t_list *tmp)
{
    char    *str;

    str = tmp->content;
    while(tmp->next)
    {
        while (*str)
        {
            if (*str == ' ')
                str++;
            else
                return (tmp);
        }
        tmp = tmp->next;
        str = tmp->content;
    }
    while (*str)
    {
        if (*str == ' ')
            str++;
        else
            return (tmp);
    }
    return (NULL);
}

static void	allocate_map(int size, t_game *game, t_list *tmp)
{
	int		i;

	game->map.map = ft_calloc(size + 1, sizeof(char *));
	if (!(game->map.map))
		ft_error("Error. Memory is not allocate for map!\n");
	game->map.map_size = size;
	i = -1;
	while (tmp)
	{
		game->map.map[++i] = tmp->content;
		tmp = tmp->next;
	}
	check_map(game);
}

int	get_map(t_game *game)
{
	int		size;
	t_list	*tmp;
	int     i;

    i = 0;
	tmp = game->param;
    while (i != 8)
    {
        if (check_identifer(tmp->content, "R ") > 0)
            i++;
        else if (check_identifer(tmp->content, "NO ") > 0)
            i++;
        else if (check_identifer(tmp->content, "SO ") > 0)
            i++;
        else if (check_identifer(tmp->content, "WE ") > 0)
            i++;
        else if (check_identifer(tmp->content, "EA ") > 0)
            i++;
        else if (check_identifer(tmp->content, "S ") > 0)
            i++;
        else if (check_identifer(tmp->content, "F ") > 0)
            i++;
        else if (check_identifer(tmp->content, "C ") > 0)
            i++;
        tmp = tmp->next;
    }
    tmp = check_empty_line(tmp);
	size = ft_lstsize(tmp);
	allocate_map(size, game, tmp);
	return (0);
}