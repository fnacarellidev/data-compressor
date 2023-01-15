/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gathering_and_init_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:45:18 by fnacarel          #+#    #+#             */
/*   Updated: 2023/01/15 11:11:51 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./encoder.h"

static bool	is_in_array(char c, char *chars_found)
{
	while (*chars_found != '\0')
	{
		if (c == *chars_found)
			return (true);
		chars_found++;
	}
	return (false);
}

/*
Count number of occurrences of certain character in the string
*/
int	number_of_occurrences(char c, char *std_data)
{
	int	i;

	i = 0;
	if (std_data != NULL)
	{
		while (*std_data)
		{
			if (*std_data == c)
				i++;
			std_data++;
		}
	}
	return (i);
}

/*
This function goest through str, which is the data that I need to encode in the
program, and it looks for every unique character.
e.g: "foo baar arrrr beeearr beer" > "fobare"
it collects the unique characters in the string
*/
char	*chars_found_in_str(char *str)
{
	int		i;
	char	*chars_in_str;

	i = 0;
	chars_in_str = calloc(1, 256);
	while (*str)
	{
		if (!(is_in_array(*str, chars_in_str)))
			chars_in_str[i++] = *str;
		str++;
	}
	return (chars_in_str);
}

int	*set_frequencies(char *uniq_chars, char *std_data, size_t size)
{
	int	*arr;
	int	i;

	i = 0;
	arr = calloc(sizeof(int), size);
	while (uniq_chars[i] != '\0')
	{
		arr[i] = number_of_occurrences(uniq_chars[i], std_data);
		i++;
	}
	return (arr);
}
