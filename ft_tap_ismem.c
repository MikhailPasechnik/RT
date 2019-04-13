#include "libft.h"

void	ft_tap_ismem(t_tap_fl fl, const char *a, const char *b, size_t n)
{
	size_t	i;

	i = 0;
	while (i++ < n)
	{
		if (*a != *b)
		{
			ft_putstr("KO\n#   Failed test at ");
			ft_putstr(fl.file);
			ft_putstr(" line ");
			ft_putnbr(fl.line);
			ft_putstr("\n#      diff at: a[");
			ft_putnbr(i-1);
			ft_putstr("]\n");
			return ;
		}
		a++;
		b++;
	}
	ft_putstr("OK\n");
}
