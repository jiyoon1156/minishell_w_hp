#include "minishell.h"

//quote 없애고 넣어주는 함수
char	*ft_substr_without_quote(char *str, unsigned int start, int len)
{
	//환경변수($처리도 여기서?)
	char	*ptr;
	int		i;
	int		quote;
	int		changed;

	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	i = 0;
	quote = 0;
	while (start < len)
	{
		if (str[start] == '\\' && quote != '\'')
			start++;
		changed = quote_check(&quote, str[start]);
		if (changed == 0)
			ptr[i++] = str[start];
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*info_redirection(char *line)
{
	char	*info;
	int		i;

	i = 0;
	if (!(info = malloc(sizeof(char) * 2)))
		return (0);
	//QUOTE 밖에 있는 redirection 은 작동해야하기에 판별하는걸 -1 곱해주는것으로 한다.
	info[i] = *(line++) * (-1);
	info[i + 1] = '\0';
	return (info);
}

void	get_info2(char *line, char **info, char *tmp, int quote)
{
	while (*line)
	{
		quote_check(&quote, *line);
		if (quote == 0 && ft_strchr(" ><", *line))
		{
			if (line - tmp > 0)//둘이 겹치면 info에 넣어주면 안되니까
				*info++ = ft_substr_without_quote(tmp, 0, (line - tmp));
			while (*line && *line == ' ')
				line++;
			//>> 일때랑 여러개일 때 파스에러처리
			if (*line == '>' || *line == '<') //quote 0 조건이 필요한가??
				*info++ = info_redirection(line++);
			// else if (*line == '|' && quote == 0)
			// 	*info++ = info_pipe_or_redirection(line++);
			while (*line && *line == ' ')
				line++;
			tmp = line;
		}
		else
			line++;
	}
	if (line - tmp > 0)
		*info++ = ft_substr_without_quote(tmp, 0, (line - tmp));
	*info = 0;
}
/* cmd 에서 info 가져오기
		따옴표 고려해서 */

char	**get_info(char *line)
{
	char	**info;
	char	*tmp;
	int		quote;

	info = malloc(sizeof(char *) * (count_char(line, ' ')
	+ count_char(line, '>') + 2));
	quote = 0;
	while (*line && *line == ' ')
		line++;
	tmp = line;
	get_info2(line, info, tmp, quote);

///////info 확인코드///////
	// int i = 0;
	// while (info[i])
	// {
	// 	ft_puts(info[i++]);
	// 	ft_puts("!\n");
	// }
//////////////////////////
	
	return (info);
}