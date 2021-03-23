#include "cub3d.h"

void parser(t_game *game, char *str)
{
    char *path;
	int fd;
	char *line;
	t_list *param;

    path = str;
	if((fd = open(path, O_RDONLY)) == -1)
		ft_error("Error. Path to the map file is invalid1\n");
	line = NULL;
	param = NULL;

	while(get_next_line(fd, &line))
		ft_lstadd_back(&param, ft_lstnew(line));
	ft_lstadd_back(&param, ft_lstnew(line));
	game->param = param;
	game->pointer = game->param;
	get_param(game);
}