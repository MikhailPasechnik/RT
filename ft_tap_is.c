#include "libft.h"

void	ft_tap_is(const char *file, int line,
				  const char *a, const char *b, const char *name, ...)
{
	if (ft_strcmp(a, b))
	{
		ft_putstr("KO\n");
		ft_putstr("#   Failed ");
		name ? ft_putstr(name) : ft_putstr("test");
		!name ? ft_putstr(" ") : ft_putstr("\n#   ");
		ft_putstr("at ");
		ft_putstr(file);
		ft_putstr(" line ");
		ft_putnbr(line);
		ft_putstr("\n#          got: '");
		ft_putstr(a);
		ft_putstr("'\n#     expected: '");
		ft_putstr(b);
		ft_putstr("'\n");
	}
	else
		ft_putstr("OK\n");
}
