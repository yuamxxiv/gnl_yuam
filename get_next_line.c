/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amancheg <amancheg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 21:18:28 by amancheg          #+#    #+#             */
/*   Updated: 2026/02/12 15:45:32 by amancheg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*prendi_linea(char *statica)
{
	int		i;
	char	*str;

	i = 0;
	if (!statica)
		return (NULL);
	while (statica[i] && statica[i] != '\n' )
		i++;
	str = (char *) malloc (sizeof (char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (statica[i] && statica[i] != '\n')
	{
		str[i] = statica[i];
		i++;
	}
	if (statica[i] == '\n')
	{
		str[i] = statica[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*pulisci_statica(char *statica)
{
	int		i;
	int		j;
	char	*nuova_str;

	i = 0;
	while (statica[i] && statica[i] != '\n')
		i++;
	if (!statica[i])
	{
		free(statica);
		return (NULL);
	}
	nuova_str = (char *) malloc (sizeof(char) * (ft_strlen(statica) - i + 1));
	if (!nuova_str)
	{
		free(statica);
		return (NULL);
	}
	i++;
	j = 0;
	while (statica[i])
		nuova_str[j++] = statica[i++];
	nuova_str[j] = '\0';
	free (statica);
	return (nuova_str);
}

char	*lettura_nl(char *statica, int fd)
{
	char	*buffer;
	int		bytes_letti;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_letti = 1;
	while (!(ft_strchr(statica, '\n')) && bytes_letti != 0)
	{
		bytes_letti = read(fd, buffer, BUFFER_SIZE);
		if (bytes_letti == -1)
		{
			free (buffer);
			free (statica);
			return (NULL);
		}
		buffer[bytes_letti] = '\0';
		statica = ft_strjoin (statica, buffer);
	}
	free (buffer);
	return (statica);
}

char	*get_next_line(int fd)
{
	static char	*statica;
	char		*linea;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	statica = lettura_nl (statica, fd);
	if (!statica || statica[0] == '\0')
	{
		free (statica);
		statica = NULL;
		return (NULL);
	}
	linea = prendi_linea(statica);
	statica = pulisci_statica(statica);
	return (linea);
}
