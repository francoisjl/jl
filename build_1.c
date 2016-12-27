/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jfrancoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 14:09:19 by jfrancoi          #+#    #+#             */
/*   Updated: 2016/12/23 14:09:33 by jfrancoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

char    *ft_read_file(char *file_name)
{
    int		fd;
    int		ret;
    char	*buff;

    ret = 0;
    fd = open(file_name, O_RDONLY);
    buff = (char*)malloc(BUFFSIZE * sizeof(char));
    if (fd >= 0)
    	ret = read(fd, buff, BUFFSIZE);
    {
        buff[ret] = '\0';
        write(1, buff, ret + 1);
    }
    close(fd);
    return (buff);
}

int	ft_check_format(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && j < 4)
	{
		if (str[i] != '.' || str[i] != '#' || str[i] != '\n')
				return (0);
		if (i % 5 == 0 && str[i] == '\n')
			j++;
		i++;
	}
	return (i);
}

int ft_check_and_count_figure(char *str)
{
	int i;
	int j;
	int nbr;

	i = 0;
	j = 1;
	nbr = 0;
	while (i < 20)
	{
		if (str[i] == '#')
		{
			nbr += (str[i + 1] < 20 && str[i + 1] == '#' ? 1 : 0);
			nbr += (str[i - 1] >= 0 && str[i - 1] == '#' ? 1 : 0);
			nbr += (str[i + 5] < 20 && str[i + 5] == '#' ? 1 : 0);
			nbr += (str[i - 5] >= 0 && str[i - 5] == '#' ? 1 : 0);
		}
		i++;
	}
	return (nbr);
	if(nbr >= 6)
	{
		j++;
	}
	return (j); 
} 

void		ft_set_tetra(t_point *points, int nbcar, int i, int y)
{
	if (nbcar == 1)
	{
		points->x1 = i % 5;
		points->y1 = y;
	}
	if (nbcar == 2)
	{
		points->x2 = (i % 5) - points->x1;
		points->y2 = y - points->y1;
	}
	if (nbcar == 3)
	{
		points->x3 = (i % 5) - points->x1;
		points->y3 = y - points->y1;
	}
	if (nbcar == 4)
	{
		points->x4 = (i % 5) - points->x1;
		points->y4 = y - points->y1;
		points->x1 = 0;
		points->y1 = 0;
	}
}

t_point		*ft_memo_tetra(char *str, char letter)
{
	int		i;
	int		nbcar;
	int		y;
	t_point	*points;

	i = 0;
	y = 0;
	nbcar = 1;
	points = malloc(sizeof(t_point));
	while (i < 21)
	{
		if (str[i] == '#')
			ft_set_tetra(points, nbcar, i, y);
		nbcar = nbcar + ((str[i] == '#') ? 1 : 0);
		if (str[i] == '\n')
			y++;
		i++;
	}
	points->prev = NULL;
	points->next = NULL;
	points->letter = letter;
	return (points);
}
