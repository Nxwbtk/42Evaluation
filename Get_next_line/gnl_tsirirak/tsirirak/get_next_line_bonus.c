/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsirirak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:08:47 by tsirirak          #+#    #+#             */
/*   Updated: 2022/10/03 04:32:02 by tsirirak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_join(char *s1, char *s2, int len_s2)
{
	char	*str;
	int		len;

	len = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1 == NULL)
		len = len_s2;
	else
		len = ft_strlen(s1) + len_s2;
	str = ft_strjoin_2(s1, s2, len_s2, len);
	if (s1)
		free(s1);
	return (str);
}

char	*ft_strjoin_2(char *s1, char *s2, int len_s2, int len)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = NULL;
	str = malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_memset(str, 0, len + 1);
	while (s1 != NULL && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 != NULL && j < len_s2)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	char			*buf;
	char			*s;
	static t_box	b[OPEN_MAX];

	buf = NULL;
	s = NULL;
	if (fd < 0 || fd > OPEN_MAX || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	s = get_next_line_2(fd, buf, &b[fd]);
	if (s == NULL)
	{
		s = ft_join(s, b[fd].str, len_nl(b[fd].str, ft_strlen(b[fd].str), 1));
		b[fd].str = ft_strchr_l(b[fd].str, 0);
		if (buf)
		{
			free(buf);
			buf = NULL;
		}
		return (s);
	}
	b[fd].str = ft_strchr_l(buf, 0);
	return (s);
}

char	*get_next_line_2(int fd, char *buf, t_box *b)
{
	char	*str;
	int		len_buf;
	int		b_len;
	int		nl;

	str = NULL;
	b_len = ft_strlen(b->str);
	nl = len_nl(b->str, b_len, 1);
	ft_memset(buf, 0, BUFFER_SIZE + 1);
	if (b->str != NULL && nl == b_len)
		str = b->str;
	while (b->str == NULL || (b->str && nl == b_len))
	{
		len_buf = read(fd, buf, BUFFER_SIZE);
		if (len_buf == 0)
			break ;
		buf[len_buf] = 0;
		str = ft_join(str, buf, len_nl(buf, len_buf, 1));
		if (len_nl(buf, len_buf, 2) != 0)
			break ;
	}
	return (str);
}
