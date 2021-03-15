#include "cub3d.h"

static void error_message(char c)
{
    if (c == 'R')
        ft_putstr("Error. Resolution is uncorrect\n");
    else if (c == 'T')
        ft_putstr("Error. Texture pack is uncorrect\n");
    else if (c == 'S')
        ft_putstr("Error. Sprite texture pack is uncorrect\n");
    else if (c == 'E')
        ft_putstr("Error. map.cub is uncorrect\n");
}

int error(int error, char c)
{
    if (error != 0)
    {
        error_message(c);
        exit(1);
    }
    
    return (1);
}