#include "cub3d.h"

// static void clear_memory(t_game *game)
// {
    
// }

static void error_message(char c)
{
    if (c == 'R')
        ft_putstr("Error. Resolution is uncorrect\n");
    else if (c == 'T')
        ft_putstr("Error. Texture pack is uncorrect\n");
    else if (c == 'S')
        ft_putstr("Error. Sprite texture pack is uncorrect\n");
    else if (c == 'M')
        ft_putstr("Error. map.cub is uncorrect\n");
    else if (c == 'F')
        ft_putstr("Error. floor color is uncorrect\n");
    else if (c == 'C')
        ft_putstr("Error. ceiling color is uncorrect\n");
}

int error(int error, char c, __unused t_game *game)
{
    if (error != 0)
    {
        error_message(c);
        // clear_memory(game);
        exit(1);
    }
    
    return (1);
}