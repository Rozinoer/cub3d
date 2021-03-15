#include "cub3d.h"

int get_floor_color(t_game *game)
{
    char *str;

    game->param = game->param->next;
    str = game->param->content;
    if (check_identifer(str, "F "))
    {
        check_color(str + 2, game, 'F');
    }
    else
        return (-1);
    return (0);
}

int get_ceiling_color(t_game *game)
{
    char *str;

    game->param = game->param->next;
    str = game->param->content;
    if (check_identifer(str, "C "))
    {
        check_color(str + 2, game, 'C');
    }
    else
        return (-1);
    return (0);
}

int get_sprite_tex(t_game *game)
{
    char *str;

    game->param = game->param->next;
    game->param = game->param->next;
    str = game->param->content;
    if (check_identifer(str, "S "))
    {
        game->map.sprite_tex = str + 2;
    }
    else
        return (-1);
    return (0);
}