#include "cub3d.h"

static int create_rgb(int r, int g, int b)
{
    if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255 )
        return(r << 16 | g << 8 | b);
    else
        return(-1);
}

int check_color(char *str, t_game *game, char c)
{
    int r;
    int g;
    int b;
    char *tmp;
    int color;

    color = -1;
    r = ft_atoi(str);
    tmp = ft_itoa(r);
    str += ft_strlen(tmp) + 1;
    g = ft_atoi(str);
    free(tmp);
    tmp = ft_itoa(g); 
    str += ft_strlen(tmp) + 1;
    b = ft_atoi(str);
    free(tmp);
    color = (create_rgb(r, g, b) != -1) ? create_rgb(r, g, b) : color;
    if (color != -1 && c == 'F')
        game->map.floor_color = color;
    else if (color != -1 && c == 'C')
        game->map.ceiling_color = color;
    else
        return (-1);
    return (0);
}

int check_identifer(char *str, char *iden)
{
    int i;
    int j;

    i = ft_strlen(iden) - 1;
    j = 0;

    while (j <= i)
    {
        if(str[j] != iden[j])
            return (-1);
        j++;
    }
    return (1);
}