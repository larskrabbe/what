/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 19:27:23 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/07/13 19:05:56 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"get_next_line.h"
#include	<stdio.h> //del later

int	lookfor(int fd, char *buffer, char *tmp_buf)
{
	int	len;
	int	i;
	int pos;

	pos = 0;
	if (!(len = read(fd,buffer,BUFFERSIZE)))
		return (len);
	i = 0;
	while (i < len && buffer[i] != '\n')// &&  len < BUFFERSIZE)
		i++;
	if ( buffer[i] == '\n')/// ||  buffer[i] == '\0')
		i++;
	while (i + pos < len)
	{
		tmp_buf[pos] = buffer[i + pos];
		pos++;
	}
	if (pos != 0)
		tmp_buf[pos] = '\0';
	return (i);
}

char *rec_str_join(int fd,char *ptr,size_t size,char *tmp_buf)
{
	char	buffer[BUFFERSIZE];
	int		i;

	i = lookfor(fd, buffer,tmp_buf);
	if (i == BUFFERSIZE && buffer[i - 1] != '\n')
	{	
		ptr = rec_str_join(fd, ptr, size + i, &(*tmp_buf));
		if (ptr == NULL)
			return(NULL);
	}
	else if ((i == 0 && size == 0 ) || i < 0)
		return (NULL);
	else
	{
		ptr = malloc (sizeof(char) * (size + 1 + i));
		if (ptr == NULL)
			return(NULL);
		ptr[size  + i] = '\0';
	}
	while (i-- > 0)
		ptr[size + i] = buffer[i];
	return (ptr);
}

char	*get_next_line(int fd)
{
	char		*ptr = NULL;
	static char sta_buf[BUFFERSIZE];
	int			i;
	char		tmp_buf[BUFFERSIZE] = "";
	int 		k;
	
	k = 0;
	i = 0;
	if (fd > 4096 || fd < 0)
		return (NULL);
	while(sta_buf[i] != '\0' && sta_buf[i] != '\n')
		i++;
	if (sta_buf[i] == '\n')
	{
		i++;
		ptr = malloc(sizeof(char) * (i + 1));
		if (ptr == NULL)
			return (NULL);
		while (i > k)
		{
			ptr[k] = sta_buf[k];
			k++;
		}
		ptr[k] = '\0';
		k = 0;
		while (k + i < BUFFERSIZE)
		{
			sta_buf[k] = sta_buf[k+i];
			k++;
		}

		while (i >= 0)
		{
			sta_buf[k+i] = '\0';
			i--;
		}	
		return (ptr);
	}
	ptr = rec_str_join(fd, ptr, i, &(*tmp_buf));
	while ( i--  > 0)
		{
			ptr[i] = sta_buf[i];
			sta_buf[i] = '\0';
		}
	while (tmp_buf[k] != '\0')
	{
		sta_buf[k] = tmp_buf[k];
		k++;
	}
	while ( k <= BUFFERSIZE)
	{
		sta_buf[k] = '\0';
		k++;
	}
	return(ptr);
}
