#include "../../include/minishell.h"

static int check_llong(const char *str)
{
	const char *max = "9223372036854775807";
	const char *min = "9223372036854775808";
	int is_neg = 0;
	int len;

	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_neg = 1;
		str++;
	}
	while (*str == '0')
		str++;
	len = ft_strlen(str);
	if (len < 19)
		return (0);
	if (len > 19)
		return (1);
	if (is_neg == 1)
	{
		if (ft_strncmp(str, min, 19) > 0)
			return(1);
	}
	if (ft_strncmp(str, max, 19) > 0)
		return(1);
	return (0);
}

static int	check_number(const char	*str)
{
	int i;

	if (!str ||!*str)
		return (0);
	i = 0;
	if (str[i] == '+' ||str[i] == '-')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return(1);
}

int	ft_exit(char	**cmds)
{
	int	exit_status;

	ft_printf("exit\n");
	if (!cmds[1])
		exit(0);
	if (!check_number(cmds[1]) || check_llong(cmds[1]))
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", cmds[1]);
		exit(2);
	}
	if (cmds[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exit_status = ft_atoi(cmds[1]);
	exit(exit_status);
}
