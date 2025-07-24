/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 08:49:31 by alejogogi         #+#    #+#             */
/*   Updated: 2024/10/21 04:52:53 by alejogogi        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_is_negative(int *num, int fd)
{
	if (*num < 0)
	{
		*num = -(*num);
		write(fd, "-", 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int			num;
	unsigned char			c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	ft_is_negative(&n, fd);
	num = (unsigned int)n;
	if (num >= 10)
		ft_putnbr_fd(num / 10, fd);
	c = (num % 10) + '0';
	write(fd, &c, 1);
}

/*
int	main(void)
{
	int number = -12345;

	ft_putnbr_fd(number, 1);
	write(1, "\n", 1);
	number = 67890;
	ft_putnbr_fd(number, 1);
	write(1, "\n", 1);
	number = 0;
	ft_putnbr_fd(number, 1);
	write(1, "\n", 1);
	number = -2147483648;
	ft_putnbr_fd(number, 1);
	write(1, "\n", 1);

	return (0);
}
*/