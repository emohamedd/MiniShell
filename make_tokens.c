/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haarab <haarab@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:32:31 by emohamed          #+#    #+#             */
/*   Updated: 2023/09/25 20:41:08 by haarab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
				&& str[i] <= 'Z'))
			return (1);
		i++;
	}
	return (0);
}

int	is_char_in2d(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if ((str[i][j] >= 'a' && str[i][j] <= 'z') || (str[i][j] >= 'A'
					&& str[i][j] <= 'Z'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	lenght_of_the_2d(char **p)
{
	int	i;

	if (!p[0])
		return (0);
	i = 0;
	while (p[i])
	{
		i++;
	}
	return (i);
}

char	**split(char *s, char *delimiters)
{
	int		max_tokens;
	char	**tokens;
	int		token_count;
	char	*start;
	char	*end;
	int		in_quotes;
	char	quote_char;
	int		escaped;
	int		i;
	char	**new_tokens;

	max_tokens = ft_strlen(s) + 1;
	tokens = (char **)malloc(max_tokens * sizeof(char *));
	if (!tokens)
	{
		printf("allocation err\n");
		exit(1);
	}
	token_count = 0;
	start = s;
	end = s;
	in_quotes = 0;
	quote_char = '\0';
	escaped = 0;
	i = 0;
	while (end[i])
	{
		if (end[i] == '\'' || end[i] == '\"')
		{
			if (in_quotes && end[i] == quote_char)
			{
				in_quotes = 0;
				quote_char = '\0';
			}
			else if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = end[i];
			}
			escaped = 0;
		}
		else if (end[i] == '\\')
		{
			if (in_quotes)
			{
				escaped = !escaped;
			}
		}
		else if ((!in_quotes && ft_strchr(delimiters, end[i]) != NULL)
			|| (!in_quotes && (end[i] == ' ' || end[i] == '\t')))
		{
			if (start != end)
			{
				if (token_count >= max_tokens)
				{
					max_tokens *= 2;
					new_tokens = (char **)malloc(max_tokens * sizeof(char *));
					if (!new_tokens)
					{
						printf("allocation err\n");
						exit(1);
					}
					i = 0;
					while (i < token_count)
					{
						new_tokens[i] = tokens[i];
						i++;
					}
					free(tokens);
					tokens = new_tokens;
				}
				tokens[token_count] = (char *)malloc((end - start + 1)
						* sizeof(char));
				if (!tokens[token_count])
				{
					printf("allocation err\n");
					exit(1);
				}
				strncpy(tokens[token_count], start, end - start);
				tokens[token_count][end - start] = '\0';
				token_count++;
			}
			if (ft_strchr(delimiters, end[i]) != NULL)
			{
				if (token_count >= max_tokens)
				{
					max_tokens *= 2;
					new_tokens = (char **)malloc(max_tokens * sizeof(char *));
					if (!new_tokens)
					{
						printf("allocation err\n");
						exit(1);
					}
					i = 0;
					while (i < token_count)
					{
						new_tokens[i] = tokens[i];
						i++;
					}
					free(tokens);
					tokens = new_tokens;
				}
				tokens[token_count] = (char *)malloc(2 * sizeof(char));
				if (!tokens[token_count])
				{
					printf("allocation err\n");
					exit(1);
				}
				tokens[token_count][0] = end[i];
				tokens[token_count][1] = '\0';
				token_count++;
			}
			start = end + 1;
		}
		else if (escaped)
		{
			escaped = 0;
		}
		end++;
	}
	if (start != end)
	{
		if (token_count >= max_tokens)
		{
			max_tokens *= 2;
			new_tokens = (char **)malloc(max_tokens * sizeof(char *));
			if (!new_tokens)
			{
				printf("allocation err\n");
				exit(1);
			}
			i = 0;
			while (i < token_count)
			{
				new_tokens[i] = tokens[i];
				i++;
			}
			free(tokens);
			tokens = new_tokens;
		}
		tokens[token_count] = (char *)malloc((end - start + 1) * sizeof(char));
		if (!tokens[token_count])
		{
			printf("allocation err\n");
			exit(1);
		}
		strncpy(tokens[token_count], start, end - start);
		tokens[token_count][end - start] = '\0';
		token_count++;
	}
	tokens[token_count] = NULL;
	return (tokens);
}

char	**expand_quotes(char **tokens)
{
	int		i;
	int		num_quotes;
	char	**expanded_tokens;
	int		j;
	char	*current_token;
	int		token_length;
	char	*modified_token;
	int		k;
	int		l;

	i = 0;
	num_quotes = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '\"'))
		{
			num_quotes++;
		}
		i++;
	}
	expanded_tokens = malloc((i + num_quotes + 1) * sizeof(char *));
	if (expanded_tokens == NULL)
	{
		return (NULL);
	}
	j = 0;
	i = 0;
	while (tokens[i])
	{
		current_token = tokens[i];
		if (ft_strchr(current_token, '\"'))
		{
			token_length = ft_strlen(current_token);
			modified_token = malloc(token_length * sizeof(char));
			if (modified_token == NULL)
			{
				return (NULL);
			}
			k = 0;
			l = 0;
			while (l < token_length)
			{
				if (current_token[l] != '\"')
				{
					modified_token[k] = current_token[l];
					k++;
				}
				l++;
			}
			modified_token[k] = '\0';
			expanded_tokens[j] = modified_token;
			j++;
		}
		else
		{
			expanded_tokens[j] = ft_strdup(current_token);
			if (expanded_tokens[j] == NULL)
			{
				return (NULL);
			}
			j++;
		}
		i++;
	}
	expanded_tokens[j] = NULL;
	return (expanded_tokens);
}

char	**make_token(char *s)
{
	char	*special_chars;
	char	**tokens;
	char	**quote;

	special_chars = "<>|";
	tokens = split(s, special_chars);
	quote = expand_quotes(tokens);
	return (red_to_herdoc(quote));
	exit(1);
}

char	*alloc_s(char const *s, unsigned int start, int len)
{
	char	*stock;

	if (!s || !s[0])
		return (NULL);
	if (start >= ft_strlen(s))
		return ("");
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	stock = ft_strdup(s + start);
	if (!stock)
		return (NULL);
	stock[len] = '\0';
	return (stock);
}

t_info	**allocat_token(char **s, t_vars *vars)
{
	int		i;
	t_info	**inf;
	char	*trimmed_content;
	char	*var;

	i = 0;
	inf = malloc(sizeof(t_info *) * (lenght_of_the_2d(s) + 1));
	if (!inf)
	{
		printf("Err\n");
		exit(1);
	}
	while (s[i])
	{
		inf[i] = malloc(sizeof(t_info));
		inf[i]->content = s[i];
		inf[i]->size = lenght_of_the_2d(s);
		if (inf[i]->content[0] == '\''
			&& inf[i]->content[ft_strlen(inf[i]->content) - 1] == '\'')
		{
			if (inf[i]->content[1] == '\''
				&& inf[i]->content[ft_strlen(inf[i]->content) - 1] == '\'')
			{
				trimmed_content = ft_strtrim(inf[i]->content, "\'");
				if (ft_strlen(trimmed_content) > 0)
				{
					if (trimmed_content[0] == '$'
						&& ft_isalpha(trimmed_content[1]))
					{
						var = ft_getenv(trimmed_content + 1, vars);
						if (!var)
						{
							return (0);
						}
						inf[i]->content = ft_strdup(var);
						inf[i]->type = "ENV_EXPANDED";
						inf[i]->lenght = ft_strlen(inf[i]->content);
					}
				}
			}
		}
		else if ((inf[i]->content[0] == '$' && ft_isalpha(inf[i]->content[1])))
		{
			var = ft_getenv(inf[i]->content + 1, vars);
			if (!var)
			{
				return (0);
			}
			inf[i]->content = ft_strdup(var);
			inf[i]->type = "ENV_EXPANDED";
			inf[i]->lenght = ft_strlen(inf[i]->content);
		}
		else if (inf[i]->content[0] == '<')
			inf[i]->type = "RDIN";
		else if (inf[i]->content[0] == '>')
			inf[i]->type = "RDOUT";
		else if (inf[i]->content[0] == '|')
			inf[i]->type = "PIPE";
		else if (inf[i]->content[0] == '\"')
			inf[i]->type = "DBCOTE";
		if (inf[i]->content[0] == '\'')
			inf[i]->type = "SGCOTE";
		else if (is_char(s[i]))
			inf[i]->type = "STR";
		inf[i]->lenght = ft_strlen(inf[i]->content);
		i++;
	}
	return (inf);
}
