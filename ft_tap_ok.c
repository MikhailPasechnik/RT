#include "libft.h"

void	ft_tap_ok(const char *file, int line,
				  int a, const char *name, ...)
{
	if (!a)
	{
		ft_putstr("KO\n");
		ft_putstr("#   Failed ");
		name ? ft_putstr(name) : ft_putstr("test");
		!name ? ft_putstr(" ") : ft_putstr("\n#   ");
		ft_putstr("at ");
		ft_putstr(file);
		ft_putstr(" line ");
		ft_putnbr(line);
		ft_putstr("\n");
	}
	else
		ft_putstr("OK\n");
}
