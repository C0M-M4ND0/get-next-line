/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oabdelha <oabdelha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 09:42:29 by oabdelha          #+#    #+#             */
/*   Updated: 2022/03/24 09:23:10 by oabdelha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_string(char *backup)
{
	char	*string;
	int		i;

	i = 0;
	if (!backup[i])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	if (backup[i] == '\n')
		i++;
	string = malloc((i + 1) * sizeof(char));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i - 1] != '\n')
	{
		string[i] = backup[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

char	*get_new_backup(char *backup)
{
	char	*newbackup;
	int		i;
	int		l;

	i = 0;
	while (backup[i] != '\n' && backup[i])
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	newbackup = malloc((ft_strlen(backup) - i + 1) * sizeof(char));
	if (newbackup == NULL)
		return (NULL);
	i++;
	l = 0;
	while (backup[i])
		newbackup[l++] = backup[i++];
	newbackup[l] = '\0';
	free(backup);
	backup = NULL;
	return (newbackup);
}

char	*ft_helper(int fd, char *backup, char *buff, int i)
{
	char	*temp;

	while (!ft_strchr(backup) && i != 0)
	{
		i = read (fd, buff, BUFFER_SIZE);
		if (i == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		temp = backup;
		if (!temp)
		{
			temp = malloc(1 * sizeof(char));
			if (temp == NULL)
				return (NULL);
			temp[0] = '\0';
		}
		backup = ft_strjoin(temp, buff);
		free(temp);
	}
	free(buff);
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*string;
	char		*buff;
	int			i;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	i = 1;
	backup = ft_helper(fd, backup, buff, i);
	if (backup == NULL)
		return (NULL);
	string = get_string(backup);
	backup = get_new_backup(backup);
	return (string);
}
