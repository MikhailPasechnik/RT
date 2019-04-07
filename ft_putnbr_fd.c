
#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
    if (nb >= 10 || nb <= -10)
    {
        ft_putnbr_fd(nb / 10, fd);
        ft_putchar_fd((nb > 0 ? (nb % 10) : -(nb % 10)) + '0', fd);
    }
    else
    {
        if (nb < 0)
            ft_putchar_fd('-', fd);
        ft_putchar_fd((nb > 0 ? (nb % 10) : -(nb % 10)) + '0', fd);
    }
}
