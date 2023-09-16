

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>

int	count_s_lenght(const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (j);
}

char	*allocat_s(const char *s, char c)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	p = malloc(sizeof(char) * len + 1);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	p = malloc(sizeof(char *) * count_s_lenght(s, c) + 1);
	if (!p)
		return (NULL);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			p[j] = allocat_s(&s[i], c);
			j++;
		}
		while (s[i] && s[i] != c)
			i++;
	}
	p[j] = NULL;
	return (p);
}

int lenght_of_the_2d(char **p)
{
    int i = 0;
    while(p[i])

    {
        i++;
    }
    return i;
}


char **make_token(char *s) 
{
    char **tokens = ft_split(s, ' ');
    int len = lenght_of_the_2d(tokens) + 1;
    char **new_tokens = (char **)malloc(sizeof(char *) * len);

    int i = 0;
    int j = 0;

    while (tokens[i]) 
    {
        if (strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], "<") == 0) {
    
            new_tokens[j] = (char *)malloc(sizeof(char) * (strlen(tokens[i]) + 1));
            strcpy(new_tokens[j], tokens[i]);

            // Check for consecutive redirection symbols
            while (tokens[i + 1] && (strcmp(tokens[i], tokens[i + 1]) == 0)) 
            {
                strcat(new_tokens[j], tokens[i + 1]);
                i++;
            }
            j++;
        } else {
            // Treat other tokens as separate tokens
            new_tokens[j] = (char *)malloc(strlen(tokens[i]) + 1);
            strcpy(new_tokens[j], tokens[i]);
            j++;
        }
        i++;
    }

    new_tokens[j] = NULL; // Null-terminate the new_tokens array


    return new_tokens;
}
int main()
{
    char *str = "hello amine > >  < < what are u doing | ls";

    char **s = make_token(str);
    int i = 0;
    while(s[i])
    {
        printf("%s\n", s[i]);
        i++;
    }
}