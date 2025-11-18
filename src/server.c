/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkieboom <rkieboom@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 23:33:52 by rkieboom          #+#    #+#             */
/*   Updated: 2025/11/18 22:42:49 by rkieboom         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static t_signal_data	*g_clients = NULL;

static void	handle_signal(int signum, siginfo_t *info, ucontext_t *uap);

int	main(void)
{
	struct sigaction		sa_usr;
	sigset_t				sig_set;
	void					(*handler)(int, siginfo_t *, void *);

	sigemptyset(&sig_set);
	sigaddset(&sig_set, SIGUSR1);
	sigaddset(&sig_set, SIGUSR2);
	sa_usr.sa_mask = sig_set;
	sa_usr.sa_flags = SA_SIGINFO;
	handler = (void (*)(int, siginfo_t *, void *)) handle_signal;
	sa_usr.sa_sigaction = handler;
	if (sigaction(SIGUSR1, &sa_usr, NULL) == -1 || sigaction(SIGUSR2, &sa_usr, NULL) == -1)
		return (ft_putstr_fd("Error: sigaction failed\n", 2), 1);
	ft_printf("%d\n", getpid());
	while (1)
	{
		pause();
	}
	return (0);
}

static void	handle_signal(int signum, siginfo_t *info, ucontext_t *uap)
{
	t_signal_data	*client;

	client = NULL;
	if (info->si_pid == 0)
		return ;
	if (signum == SIGUSR1)
		client = add_signal_bit_to_client(&g_clients, info->si_pid, 1);
	else if (signum == SIGUSR2)
		client = add_signal_bit_to_client(&g_clients, info->si_pid, 0);
	if (!client)
	{
		ft_putstr_fd("Error: Adding data to client failed\n", 2);
		return ;
	}
	if (!check_bits_full(&g_clients, info->si_pid))
		return ;
	(void)uap;
}
