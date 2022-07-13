/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe < lkrabbe@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 06:21:28 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/07/05 15:59:05 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// # include   <stdio.h>
# include   <unistd.h>
# include   <stdlib.h>

#ifndef BUFFERSIZE
# define BUFFERSIZE 42
#endif

char    *get_next_line(int fd);

#endif