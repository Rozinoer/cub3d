#include "cub3d.h"

static int create_rgb(int r, int g, int b)
{
    if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255 )
        return(r << 16 | g << 8 | b);
    else
        return(-1);
}

static char *skip(char *str, char c, t_game *game, int flag)
{
    if (flag == 0)
    {
        while ((*str == ' ' || *str == ',') && *str != '\0')
            str++;
    }
    else
    {
        while (*str == ' ' && *str != '\0')
            str++;
    }
    if (*str < '0' || *str > '9')
        error(-1, c, game);
    return (str);
}

int check_color(char *str, t_game *game, char c)
{
    int r;
    int g;
    int b;
    int color;

    color = -1;
    r = ft_atoi(str = skip(str, c, game, 1));
    str += ft_nbrlen(r);
    g = ft_atoi(str = skip(str, c, game, 0));
    str += ft_nbrlen(g);
    b = ft_atoi(str = skip(str, c, game, 0));
    skip(str, c, game, 1);
    color = create_rgb(r, g, b);
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

    i = ft_strlen(iden);
    j = 0;
    
    while (j <= i && iden[j] != '\0')
    {
        if(str[j] != iden[j])
            return (-1);
        j++;
    }
    return (1);
}