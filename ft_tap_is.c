#include "libft.h"

void	ft_tap_is(t_tap_fl fl, const char *a, const char *b)
{
	if (ft_strcmp(a, b))
	{
		ft_putstr("KO\n#   Failed test ");
		ft_putstr(fl.file);
		ft_putstr(" line ");
		ft_putnbr(fl.line);
		ft_putstr("\n#          got: '");
		ft_putstr(a);
		ft_putstr("'\n#     expected: '");
		ft_putstr(b);
		ft_putstr("'\n");
	}
	else
		ft_putstr("OK\n");
}
