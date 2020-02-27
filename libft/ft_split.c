/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_a.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bmans <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 09:05:27 by bmans         #+#    #+#                 */
/*   Updated: 2019/11/05 09:05:28 by bmans         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static unsigned int	ft_wordcount(char const *s, char c)
{
	unsigned int i;
	unsigned int wc;

	i = 0;
	wc = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			wc++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (wc);
}

static char			*ft_wordsplit(char **str, char c)
{
	unsigned int len;

	while (**str == c)
		(*str)++;
	len = 0;
	while (*(*str + len) && *(*str + len) != c)
		len++;
	*str = *str + len;
	return (ft_substr(*str - len, 0, len));
}

static char			**ft_removesplit(char **split, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		if (split[i])
			free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

char				**ft_split(char const *s, char c)
{
	char			**split;
	char			*str;
	char			*word;
	unsigned int	i;
	unsigned int	wc;

	if (!s)
		return (0);
	wc = ft_wordcount(s, c);
	split = malloc(sizeof(char*) * (wc + 1));
	if (split)
	{
		i = 0;
		str = (char*)s;
		while (i < wc)
		{
			word = ft_wordsplit(&str, c);
			if (!word)
				return (ft_removesplit(split, i));
			split[i] = word;
			i++;
		}
		split[wc] = 0;
	}
	return (split);
}
