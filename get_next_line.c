/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: SirR1ght <SirR1ght@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 19:35:46 by SirR1ght          #+#    #+#             */
/*   Updated: 2022/12/08 21:38:50 by SirR1ght         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		ft_wipe_ptr(char *s)
{
	if (s)
	{
		free(s);
		s = NULL;
	}
}

void		ft_wipe_pptr(char **s)
{
	if (*s)
	{
		free(*s);
		*s = NULL;
	}
}

static int	ft_getrest(char **rest, char **line)
{
	char	*tmp;

	if (!(*rest))
	{
		if (!(*line = ft_strdup("")))
			return (-1);
		return (0);
	}
	if ((tmp = ft_strfnl(*rest)))
	{
		*tmp++ = '\0';
		if (!(*line = ft_strdup(*rest)))
			return (-1);
		!tmp ? ft_wipe_pptr(&(*rest)) : ft_strcpy(*rest, tmp);
		return (1);
	}
	else
	{
		if (!(*line = ft_strdup(*rest)))
			return (-1);
		ft_wipe_pptr(&(*rest));
		return (0);
	}
	return (0);
}

static int	ft_readline(int fd, char *buf, char **rest, char **line)
{
	ssize_t		line_read;
	char		*tmp_line;
	char		*tmp;

	tmp = NULL;
	while (!tmp && (line_read = read(fd, buf, BUFFER_SIZE)))
	{
		buf[line_read] = '\0';
		if ((tmp = ft_strfnl(buf)))
		{
			*tmp++ = '\0';
			if (tmp)
				*rest = ft_strdup(tmp);
		}
		tmp_line = *line;
		if (!(*line = ft_strjoin(*line, buf)) || line_read < 0)
			return (-1);
		ft_wipe_ptr(tmp_line);
	}
	ft_wipe_ptr(buf);
	if (line_read == 0)
		ft_wipe_pptr(&(*rest));
	return ((line_read == 0) ? 0 : 1);
}

int			get_next_line(int fd, char **line)
{
	int			res;
	char		*buf;
	static char	*rest;

	if (!line || fd < 0 || fd > 10241 || BUFFER_SIZE <= 0 || \
	!(buf = (char *)malloc(BUFFER_SIZE + 1)) || (read(fd, rest, 0) < 0))
		return (-1);
	*line = NULL;
	if ((res = ft_getrest(&rest, line)) != 0)
	{
		ft_wipe_ptr(buf);
		return (res);
	}
	res = ft_readline(fd, buf, &rest, line);
	return (res);
}
