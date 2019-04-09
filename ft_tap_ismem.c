#include "libft.h"

void	ft_tap_ismem(const char *file, int line,
					 const char *a, const char *b, size_t n, const char *name, ...)
{
	size_t	i;

	i = 0;
	while (i++ < n)
	{
		if (*a != *b)
		{
			ft_putstr("KO\n");
			ft_putstr("#   Failed ");
			name ? ft_putstr(name) : ft_putstr("test");
			!name ? ft_putstr(" ") : ft_putstr("\n#   ");
			ft_putstr("at ");
			ft_putstr(file);
			ft_putstr(" line ");
			ft_putnbr(line);
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
