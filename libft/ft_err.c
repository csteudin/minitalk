#include "libft.h"

int ft_err(char *str, int ret)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (ret);
}