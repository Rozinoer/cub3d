#include "cub3d.h"

int get_floor_color(t_game *game)
{
    int i;
    t_list *list;

    i = -1;
    list = game->param;
    while (list->next)
    {
        if (check_identifer(list->content, "F ") != -1)
        {
            i = check_color(list->content + 2, game, 'F');
            break;
        }
        list = list->next;
    }
    return (i);
}

int get_ceiling_color(t_game *game)
{
    int i;
    t_list *list;

    i = -1;
    list = game->param;
    while (list->next)
    {
        if (check_identifer(list->content, "C ") != -1)
        {
            i = check_color(list->content + 2, game, 'C');
            break;
        }
        list = list->next;
    }
    return (i);
}

int get_sprite_tex(t_game *game)
{
    t_list *list;

    list = game->param;
    while (list->next)
    {
        if (check_identifer(list->content, "S "))
            game->map.sprite_tex = list->content + 2;
        list = list->next;
    }
    return (0);
}