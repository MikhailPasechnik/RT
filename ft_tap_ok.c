#include "libft.h"

void	ft_tap_ok(t_tap_fl fl, int a)
{
	if (!a)
	{
		ft_putstr("KO\n#   Failed test at ");
		ft_putstr(fl.file);
		ft_putstr(" line ");
		ft_putnbr(fl.line);
		ft_putstr("\n");
	}
	else
		ft_putstr("OK\n");
}
